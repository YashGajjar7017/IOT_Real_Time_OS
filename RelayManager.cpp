#include "RelayManager.h"

RelayManager::RelayManager() : _lastProcessTick(0), _lastRuntimeSaveTick(0), _lastOneSecondTick(0) {
    _relayMutex = xSemaphoreCreateMutex();

    // Default Channel 1
    _channels[0].id = 1;
    _channels[0].pin = RELAY_1_PIN;
    strncpy(_channels[0].name, "Relay 1 (D1)", sizeof(_channels[0].name) - 1);
    _channels[0].state = false;
    _channels[0].activeLow = true;   // Standard relay module active low
    _channels[0].ratedWatts = 100.0f; // 100W default load
    _channels[0].totalOnSeconds = 0;
    _channels[0].sessionOnSeconds = 0;
    _channels[0].timer = { false, 0, 0, 0, 0, false, false };
    _channels[0].schedule = { false, 8, 0, 0, 18, 0, 0, 0xFF };

    // Default Channel 2
    _channels[1].id = 2;
    _channels[1].pin = RELAY_2_PIN;
    strncpy(_channels[1].name, "Relay 2 (D2)", sizeof(_channels[1].name) - 1);
    _channels[1].state = false;
    _channels[1].activeLow = true;
    _channels[1].ratedWatts = 100.0f;
    _channels[1].totalOnSeconds = 0;
    _channels[1].sessionOnSeconds = 0;
    _channels[1].timer = { false, 0, 0, 0, 0, false, false };
    _channels[1].schedule = { false, 18, 0, 0, 22, 0, 0, 0xFF };
}

RelayManager::~RelayManager() {
    if (_relayMutex != NULL) {
        vSemaphoreDelete(_relayMutex);
    }
}

RelayManager& RelayManager::getInstance() {
    static RelayManager instance;
    return instance;
}

void RelayManager::begin() {
    // Configure GPIOs
    pinMode(_channels[0].pin, OUTPUT);
    pinMode(_channels[1].pin, OUTPUT);
    pinMode(STATUS_LED_PIN, OUTPUT);

    loadFromPreferences();

    // Set initial physical state
    applyPhysicalPin(1);
    applyPhysicalPin(2);

    _lastProcessTick = millis();
    _lastRuntimeSaveTick = millis();
    _lastOneSecondTick = millis();

    Serial.println("[RelayManager] Initialized with 2 channels on GPIO " + String(_channels[0].pin) + " and " + String(_channels[1].pin));
}

void RelayManager::applyPhysicalPin(uint8_t channelId) {
    if (channelId < 1 || channelId > 2) return;
    uint8_t idx = channelId - 1;
    
    // Active LOW vs Active HIGH calculation
    uint8_t level = _channels[idx].activeLow ? (_channels[idx].state ? LOW : HIGH) : (_channels[idx].state ? HIGH : LOW);
    digitalWrite(_channels[idx].pin, level);

    // Update Status LED (lights up if any relay is ON)
    bool anyOn = _channels[0].state || _channels[1].state;
    digitalWrite(STATUS_LED_PIN, anyOn ? HIGH : LOW);
}

void RelayManager::setRelayState(uint8_t channelId, bool state) {
    if (channelId < 1 || channelId > 2) return;
    
    if (xSemaphoreTake(_relayMutex, portMAX_DELAY) == pdTRUE) {
        uint8_t idx = channelId - 1;
        if (_channels[idx].state != state) {
            _channels[idx].state = state;
            applyPhysicalPin(channelId);
            Serial.printf("[RelayManager] Relay %d state -> %s\n", channelId, state ? "ON" : "OFF");
        }
        xSemaphoreGive(_relayMutex);
    }
}

void RelayManager::toggleRelay(uint8_t channelId) {
    if (channelId < 1 || channelId > 2) return;
    
    if (xSemaphoreTake(_relayMutex, portMAX_DELAY) == pdTRUE) {
        uint8_t idx = channelId - 1;
        _channels[idx].state = !_channels[idx].state;
        applyPhysicalPin(channelId);
        Serial.printf("[RelayManager] Relay %d toggled -> %s\n", channelId, _channels[idx].state ? "ON" : "OFF");
        xSemaphoreGive(_relayMutex);
    }
}

void RelayManager::setAllOff() {
    if (xSemaphoreTake(_relayMutex, portMAX_DELAY) == pdTRUE) {
        for (int i = 0; i < 2; i++) {
            _channels[i].state = false;
            _channels[i].timer.enabled = false;
            _channels[i].timer.isCountingDown = false;
            applyPhysicalPin(i + 1);
        }
        Serial.println("[RelayManager] Emergency ALL OFF triggered!");
        xSemaphoreGive(_relayMutex);
    }
}

RelayChannel RelayManager::getChannel(uint8_t channelId) {
    RelayChannel copy;
    if (channelId < 1 || channelId > 2) return copy;
    
    if (xSemaphoreTake(_relayMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
        copy = _channels[channelId - 1];
        xSemaphoreGive(_relayMutex);
    }
    return copy;
}

bool RelayManager::getRelayState(uint8_t channelId) {
    if (channelId < 1 || channelId > 2) return false;
    bool state = false;
    if (xSemaphoreTake(_relayMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
        state = _channels[channelId - 1].state;
        xSemaphoreGive(_relayMutex);
    }
    return state;
}

void RelayManager::setCountdownTimer(uint8_t channelId, uint32_t startDelaySec, uint32_t durationSec, bool enable) {
    if (channelId < 1 || channelId > 2) return;
    
    if (xSemaphoreTake(_relayMutex, portMAX_DELAY) == pdTRUE) {
        uint8_t idx = channelId - 1;
        _channels[idx].timer.enabled = enable;
        _channels[idx].timer.startDelaySec = startDelaySec;
        _channels[idx].timer.durationSec = durationSec;
        _channels[idx].timer.timerStartEpoch = TimeManager::getInstance().getEpochTime();
        
        if (enable) {
            _channels[idx].timer.isCountingDown = true;
            if (startDelaySec > 0) {
                _channels[idx].timer.inDelayPhase = true;
                _channels[idx].timer.remainingSec = startDelaySec;
                _channels[idx].state = false; // Stay OFF while waiting
            } else {
                _channels[idx].timer.inDelayPhase = false;
                _channels[idx].timer.remainingSec = durationSec;
                _channels[idx].state = true;  // Turn ON immediately
            }
            applyPhysicalPin(channelId);
            Serial.printf("[RelayManager] Relay %d Timer Started: Delay=%u s, Duration=%u s\n", channelId, startDelaySec, durationSec);
        } else {
            _channels[idx].timer.isCountingDown = false;
            Serial.printf("[RelayManager] Relay %d Timer Cancelled\n", channelId);
        }
        xSemaphoreGive(_relayMutex);
    }
}

void RelayManager::cancelCountdownTimer(uint8_t channelId) {
    setCountdownTimer(channelId, 0, 0, false);
}

void RelayManager::setSchedule(uint8_t channelId, uint8_t startH, uint8_t startM, uint8_t endH, uint8_t endM, uint8_t daysActive, bool enable) {
    if (channelId < 1 || channelId > 2) return;
    
    if (xSemaphoreTake(_relayMutex, portMAX_DELAY) == pdTRUE) {
        uint8_t idx = channelId - 1;
        _channels[idx].schedule.enabled = enable;
        _channels[idx].schedule.startHour = startH;
        _channels[idx].schedule.startMinute = startM;
        _channels[idx].schedule.startSecond = 0;
        _channels[idx].schedule.endHour = endH;
        _channels[idx].schedule.endMinute = endM;
        _channels[idx].schedule.endSecond = 0;
        _channels[idx].schedule.daysActive = daysActive;

        saveToPreferences();
        Serial.printf("[RelayManager] Relay %d Schedule: %02d:%02d to %02d:%02d (Enabled: %d)\n", channelId, startH, startM, endH, endM, enable);
        xSemaphoreGive(_relayMutex);
    }
}

void RelayManager::cancelSchedule(uint8_t channelId) {
    if (channelId < 1 || channelId > 2) return;
    if (xSemaphoreTake(_relayMutex, portMAX_DELAY) == pdTRUE) {
        _channels[channelId - 1].schedule.enabled = false;
        saveToPreferences();
        xSemaphoreGive(_relayMutex);
    }
}

void RelayManager::updateChannelConfig(uint8_t channelId, const char* name, bool activeLow, float ratedWatts) {
    if (channelId < 1 || channelId > 2) return;
    
    if (xSemaphoreTake(_relayMutex, portMAX_DELAY) == pdTRUE) {
        uint8_t idx = channelId - 1;
        if (name && strlen(name) > 0) {
            strncpy(_channels[idx].name, name, sizeof(_channels[idx].name) - 1);
            _channels[idx].name[sizeof(_channels[idx].name) - 1] = '\0';
        }
        _channels[idx].activeLow = activeLow;
        _channels[idx].ratedWatts = (ratedWatts > 0.0f) ? ratedWatts : 100.0f;
        
        applyPhysicalPin(channelId);
        saveToPreferences();
        xSemaphoreGive(_relayMutex);
    }
}

void RelayManager::processEngine() {
    uint32_t now = millis();

    // 1-second interval execution
    if (now - _lastOneSecondTick >= 1000) {
        _lastOneSecondTick = now;

        if (xSemaphoreTake(_relayMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
            checkTimers();
            checkSchedules();
            updateRuntimeMetrics();
            xSemaphoreGive(_relayMutex);
        }
    }

    // Auto-save runtime every 5 minutes
    if (now - _lastRuntimeSaveTick >= 300000) {
        _lastRuntimeSaveTick = now;
        saveRuntime();
    }
}

void RelayManager::checkTimers() {
    for (int i = 0; i < 2; i++) {
        if (_channels[i].timer.enabled && _channels[i].timer.isCountingDown) {
            if (_channels[i].timer.remainingSec > 0) {
                _channels[i].timer.remainingSec--;
            }

            if (_channels[i].timer.remainingSec == 0) {
                if (_channels[i].timer.inDelayPhase) {
                    // Delay phase ended -> Start ON phase
                    _channels[i].timer.inDelayPhase = false;
                    _channels[i].timer.remainingSec = _channels[i].timer.durationSec;
                    _channels[i].state = true;
                    applyPhysicalPin(i + 1);
                    Serial.printf("[RelayManager] Timer delay elapsed. Relay %d turned ON for %u s\n", i + 1, _channels[i].timer.durationSec);
                    
                    if (_channels[i].timer.durationSec == 0) {
                        // If duration is 0, stay ON permanently
                        _channels[i].timer.isCountingDown = false;
                        _channels[i].timer.enabled = false;
                    }
                } else {
                    // ON phase duration ended -> Turn OFF
                    _channels[i].state = false;
                    _channels[i].timer.isCountingDown = false;
                    _channels[i].timer.enabled = false;
                    applyPhysicalPin(i + 1);
                    Serial.printf("[RelayManager] Timer duration finished. Relay %d turned OFF\n", i + 1);
                }
            }
        }
    }
}

void RelayManager::checkSchedules() {
    if (!TimeManager::getInstance().isTimeSynchronized()) {
        return; // Need synchronized clock to evaluate daily schedules
    }

    int year, month, day, hour, minute, second, dayOfWeek;
    TimeManager::getInstance().getTimeBreakdown(year, month, day, hour, minute, second, dayOfWeek);

    uint32_t currentSec = hour * 3600 + minute * 60 + second;
    uint8_t dayBit = (1 << dayOfWeek); // Sunday is bit 0, Monday bit 1...

    for (int i = 0; i < 2; i++) {
        // Countdown timer has priority over schedule while active
        if (_channels[i].timer.enabled && _channels[i].timer.isCountingDown) {
            continue;
        }

        if (_channels[i].schedule.enabled) {
            // Check day of week mask
            if ((_channels[i].schedule.daysActive & dayBit) || (_channels[i].schedule.daysActive == 0xFF)) {
                uint32_t startSec = _channels[i].schedule.startHour * 3600 + _channels[i].schedule.startMinute * 60 + _channels[i].schedule.startSecond;
                uint32_t endSec   = _channels[i].schedule.endHour * 3600 + _channels[i].schedule.endMinute * 60 + _channels[i].schedule.endSecond;

                bool shouldBeOn = false;
                if (startSec < endSec) {
                    // Standard same-day window (e.g. 08:00 to 18:00)
                    shouldBeOn = (currentSec >= startSec && currentSec < endSec);
                } else if (startSec > endSec) {
                    // Overnight window spanning midnight (e.g. 20:00 to 06:00)
                    shouldBeOn = (currentSec >= startSec || currentSec < endSec);
                }

                if (_channels[i].state != shouldBeOn) {
                    _channels[i].state = shouldBeOn;
                    applyPhysicalPin(i + 1);
                    Serial.printf("[RelayManager] Schedule triggered: Relay %d -> %s\n", i + 1, shouldBeOn ? "ON" : "OFF");
                }
            }
        }
    }
}

void RelayManager::updateRuntimeMetrics() {
    for (int i = 0; i < 2; i++) {
        if (_channels[i].state) {
            _channels[i].totalOnSeconds++;
            _channels[i].sessionOnSeconds++;
        }
    }
}

void RelayManager::loadFromPreferences() {
    if (_prefs.begin("relay_cfg", true)) { // Read-only mode
        for (int i = 0; i < 2; i++) {
            String prefix = "r" + String(i + 1) + "_";
            String name = _prefs.getString((prefix + "name").c_str(), _channels[i].name);
            strncpy(_channels[i].name, name.c_str(), sizeof(_channels[i].name) - 1);
            
            _channels[i].activeLow = _prefs.getBool((prefix + "actlow").c_str(), _channels[i].activeLow);
            _channels[i].ratedWatts = _prefs.getFloat((prefix + "watts").c_str(), _channels[i].ratedWatts);
            _channels[i].totalOnSeconds = _prefs.getUInt((prefix + "totsec").c_str(), 0);

            _channels[i].schedule.enabled = _prefs.getBool((prefix + "sch_en").c_str(), false);
            _channels[i].schedule.startHour = _prefs.getUChar((prefix + "sch_sh").c_str(), 8);
            _channels[i].schedule.startMinute = _prefs.getUChar((prefix + "sch_sm").c_str(), 0);
            _channels[i].schedule.endHour = _prefs.getUChar((prefix + "sch_eh").c_str(), 18);
            _channels[i].schedule.endMinute = _prefs.getUChar((prefix + "sch_em").c_str(), 0);
            _channels[i].schedule.daysActive = _prefs.getUChar((prefix + "sch_days").c_str(), 0xFF);
        }
        _prefs.end();
        Serial.println("[RelayManager] Preferences loaded successfully.");
    }
}

void RelayManager::saveToPreferences() {
    if (_prefs.begin("relay_cfg", false)) { // Read-Write mode
        for (int i = 0; i < 2; i++) {
            String prefix = "r" + String(i + 1) + "_";
            _prefs.putString((prefix + "name").c_str(), _channels[i].name);
            _prefs.putBool((prefix + "actlow").c_str(), _channels[i].activeLow);
            _prefs.putFloat((prefix + "watts").c_str(), _channels[i].ratedWatts);
            
            _prefs.putBool((prefix + "sch_en").c_str(), _channels[i].schedule.enabled);
            _prefs.putUChar((prefix + "sch_sh").c_str(), _channels[i].schedule.startHour);
            _prefs.putUChar((prefix + "sch_sm").c_str(), _channels[i].schedule.startMinute);
            _prefs.putUChar((prefix + "sch_eh").c_str(), _channels[i].schedule.endHour);
            _prefs.putUChar((prefix + "sch_em").c_str(), _channels[i].schedule.endMinute);
            _prefs.putUChar((prefix + "sch_days").c_str(), _channels[i].schedule.daysActive);
        }
        _prefs.end();
    }
}

void RelayManager::saveRuntime() {
    if (_prefs.begin("relay_cfg", false)) {
        _prefs.putUInt("r1_totsec", _channels[0].totalOnSeconds);
        _prefs.putUInt("r2_totsec", _channels[1].totalOnSeconds);
        _prefs.end();
    }
}
