#include "PowerManager.h"

PowerManager::PowerManager() : _lastActivityTick(0), _stateChangeTick(0), _processTicks(0) {
    _powerMutex = xSemaphoreCreateMutex();

    _config.enabled = false;
    _config.permanentStayOn = true;       // Default: Permanent Always-On Mode
    _config.isApSleeping = false;
    _config.sleepIntervalMin = 15;        // 15 minutes off
    _config.wakeWindowMin = 3;            // 3 minutes on
    _config.inactivityTimeoutMin = 3;     // 3 minutes no-activity timeout
    _config.nextStateChangeEpoch = 0;

    strncpy(_apSsid, DEFAULT_AP_SSID, sizeof(_apSsid) - 1);
    strncpy(_apPass, DEFAULT_AP_PASS, sizeof(_apPass) - 1);
}

PowerManager::~PowerManager() {
    if (_powerMutex != NULL) {
        vSemaphoreDelete(_powerMutex);
    }
}

PowerManager& PowerManager::getInstance() {
    static PowerManager instance;
    return instance;
}

void PowerManager::begin(const char* apSsid, const char* apPass) {
    if (apSsid && strlen(apSsid) > 0) {
        strncpy(_apSsid, apSsid, sizeof(_apSsid) - 1);
    }
    if (apPass) {
        strncpy(_apPass, apPass, sizeof(_apPass) - 1);
    }

    loadFromPreferences();

    _lastActivityTick = millis();
    _stateChangeTick = millis();
    _processTicks = 0;
}

void PowerManager::setLowPowerMode(bool enable, uint32_t sleepMin, uint32_t wakeMin) {
    if (xSemaphoreTake(_powerMutex, portMAX_DELAY) == pdTRUE) {
        _config.enabled = enable;
        if (enable) {
            _config.permanentStayOn = false; // Enabling low power turns off permanent stay on
        }
        if (sleepMin >= 1) _config.sleepIntervalMin = sleepMin;
        if (wakeMin >= 1) _config.wakeWindowMin = wakeMin;

        if (!enable && _config.isApSleeping) {
            wakeUpAP();
        }

        _lastActivityTick = millis();
        _stateChangeTick = millis();
        saveToPreferences();
        
        Serial.printf("[PowerManager] Low Power Mode: %s (Sleep: %u min, Wake: %u min)\n", 
                      enable ? "ENABLED" : "DISABLED", _config.sleepIntervalMin, _config.wakeWindowMin);
        xSemaphoreGive(_powerMutex);
    }
}

void PowerManager::setPermanentStayOn(bool permanentStayOn) {
    if (xSemaphoreTake(_powerMutex, portMAX_DELAY) == pdTRUE) {
        _config.permanentStayOn = permanentStayOn;
        if (permanentStayOn) {
            _config.enabled = false; // Disable sleep duty cycling
            if (_config.isApSleeping) {
                wakeUpAP();
            }
        }
        _lastActivityTick = millis();
        _stateChangeTick = millis();
        saveToPreferences();

        Serial.printf("[PowerManager] Permanent Stay-On Mode: %s\n", permanentStayOn ? "ENABLED (Sleep Disabled)" : "DISABLED");
        xSemaphoreGive(_powerMutex);
    }
}

void PowerManager::registerUserActivity() {
    if (xSemaphoreTake(_powerMutex, pdMS_TO_TICKS(20)) == pdTRUE) {
        _lastActivityTick = millis();
        xSemaphoreGive(_powerMutex);
    }
}

bool PowerManager::isLowPowerEnabled() {
    bool en = false;
    if (xSemaphoreTake(_powerMutex, pdMS_TO_TICKS(20)) == pdTRUE) {
        en = _config.enabled && !_config.permanentStayOn;
        xSemaphoreGive(_powerMutex);
    }
    return en;
}

bool PowerManager::isPermanentStayOn() {
    bool p = true;
    if (xSemaphoreTake(_powerMutex, pdMS_TO_TICKS(20)) == pdTRUE) {
        p = _config.permanentStayOn;
        xSemaphoreGive(_powerMutex);
    }
    return p;
}

bool PowerManager::isApSleeping() {
    bool sleeping = false;
    if (xSemaphoreTake(_powerMutex, pdMS_TO_TICKS(20)) == pdTRUE) {
        sleeping = _config.isApSleeping;
        xSemaphoreGive(_powerMutex);
    }
    return sleeping;
}

LowPowerConfig PowerManager::getConfig() {
    LowPowerConfig copy;
    if (xSemaphoreTake(_powerMutex, pdMS_TO_TICKS(20)) == pdTRUE) {
        copy = _config;
        xSemaphoreGive(_powerMutex);
    }
    return copy;
}

uint32_t PowerManager::getSecondsUntilNextState() {
    uint32_t remaining = 0;
    if (xSemaphoreTake(_powerMutex, pdMS_TO_TICKS(20)) == pdTRUE) {
        if (_config.permanentStayOn) {
            remaining = 0;
        } else {
            uint32_t elapsed = millis() - _stateChangeTick;
            if (_config.isApSleeping) {
                uint32_t targetMs = _config.sleepIntervalMin * 60 * 1000;
                remaining = (elapsed < targetMs) ? ((targetMs - elapsed) / 1000) : 0;
            } else if (_config.enabled) {
                uint32_t actElapsed = millis() - _lastActivityTick;
                uint32_t targetMs = _config.wakeWindowMin * 60 * 1000;
                remaining = (actElapsed < targetMs) ? ((targetMs - actElapsed) / 1000) : 0;
            }
        }
        xSemaphoreGive(_powerMutex);
    }
    return remaining;
}

uint32_t PowerManager::getTickCount() {
    return _processTicks;
}

void PowerManager::wakeUpAP() {
    Serial.println("[PowerManager] Waking up Wi-Fi AP...");
    WiFi.mode(WIFI_AP);
    
    IPAddress local_IP(AP_IP_OCTET_1, AP_IP_OCTET_2, AP_IP_OCTET_3, AP_IP_OCTET_4);
    IPAddress gateway(AP_IP_OCTET_1, AP_IP_OCTET_2, AP_IP_OCTET_3, AP_IP_OCTET_4);
    IPAddress subnet(255, 255, 255, 0);
    
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(_apSsid, strlen(_apPass) > 0 ? _apPass : NULL, DEFAULT_AP_CHANNEL, 0, DEFAULT_AP_MAX_CONN);

    _config.isApSleeping = false;
    _lastActivityTick = millis();
    _stateChangeTick = millis();
    Serial.printf("[PowerManager] AP Awake: %s (IP: 192.168.4.1)\n", _apSsid);
}

void PowerManager::putAPToSleep() {
    if (_config.permanentStayOn) {
        return; // Inhibit sleep if permanent stay on is checked
    }
    Serial.println("[PowerManager] Putting Wi-Fi AP to sleep (Power Saving)...");
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_OFF);

    _config.isApSleeping = true;
    _stateChangeTick = millis();
    Serial.printf("[PowerManager] Wi-Fi AP disabled. Next wake in %u minutes.\n", _config.sleepIntervalMin);
}

void PowerManager::processEngine() {
    _processTicks++;
    if (xSemaphoreTake(_powerMutex, pdMS_TO_TICKS(50)) == pdTRUE) {
        // If permanent stay on is enabled, ensure AP remains awake
        if (_config.permanentStayOn) {
            if (_config.isApSleeping) {
                wakeUpAP();
            }
        } else if (_config.enabled) {
            uint32_t now = millis();

            if (!_config.isApSleeping) {
                // If stations are connected, treat as active
                if (WiFi.softAPgetStationNum() > 0) {
                    _lastActivityTick = now;
                }

                // Check inactivity timeout
                uint32_t activeTimeoutMs = _config.wakeWindowMin * 60 * 1000;
                if (now - _lastActivityTick >= activeTimeoutMs) {
                    // No activity during wake window -> Enter sleep
                    putAPToSleep();
                }
            } else {
                // AP is sleeping, check if sleep interval has elapsed
                uint32_t sleepIntervalMs = _config.sleepIntervalMin * 60 * 1000;
                if (now - _stateChangeTick >= sleepIntervalMs) {
                    // Sleep period finished -> Wake up AP for discovery window
                    wakeUpAP();
                }
            }
        }
        xSemaphoreGive(_powerMutex);
    }
}

void PowerManager::loadFromPreferences() {
    if (_prefs.begin("pwr_cfg", true)) {
        _config.permanentStayOn = _prefs.getBool("lp_stay_on", true); // Default: Stay on permanently
        _config.enabled = _prefs.getBool("lp_en", false);
        _config.sleepIntervalMin = _prefs.getUInt("lp_sleep", 15);
        _config.wakeWindowMin = _prefs.getUInt("lp_wake", 3);
        _prefs.end();
        Serial.printf("[PowerManager] Preferences loaded: PermanentStayOn=%d, LowPowerEn=%d\n", _config.permanentStayOn, _config.enabled);
    }
}

void PowerManager::saveToPreferences() {
    if (_prefs.begin("pwr_cfg", false)) {
        _prefs.putBool("lp_stay_on", _config.permanentStayOn);
        _prefs.putBool("lp_en", _config.enabled);
        _prefs.putUInt("lp_sleep", _config.sleepIntervalMin);
        _prefs.putUInt("lp_wake", _config.wakeWindowMin);
        _prefs.end();
        Serial.println("[PowerManager] Preferences saved permanently.");
    }
}
