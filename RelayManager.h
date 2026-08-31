#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include <Arduino.h>
#include <Preferences.h>
#include "Config.h"
#include "TimeManager.h"

class RelayManager {
public:
    static RelayManager& getInstance();

    void begin();
    
    // Core Relay Actions (Thread-safe)
    void setRelayState(uint8_t channelId, bool state);
    void toggleRelay(uint8_t channelId);
    void setAllOff();
    
    // Getters
    RelayChannel getChannel(uint8_t channelId);
    bool getRelayState(uint8_t channelId);
    
    // Countdown Timer Management
    void setCountdownTimer(uint8_t channelId, uint32_t startDelaySec, uint32_t durationSec, bool enable);
    void cancelCountdownTimer(uint8_t channelId);
    
    // Daily Schedule Management
    void setSchedule(uint8_t channelId, uint8_t startH, uint8_t startM, uint8_t endH, uint8_t endM, uint8_t daysActive, bool enable);
    void cancelSchedule(uint8_t channelId);
    
    // Configuration & Metadata
    void updateChannelConfig(uint8_t channelId, const char* name, bool activeLow, float ratedWatts);
    
    // FreeRTOS Execution Engine (called every ~100ms from Core 1 Task)
    void processEngine();

    // NVS Persistence
    void loadFromPreferences();
    void saveToPreferences();
    void saveRuntime();

private:
    RelayManager();
    ~RelayManager();
    
    RelayManager(const RelayManager&) = delete;
    RelayManager& operator=(const RelayManager&) = delete;

    void applyPhysicalPin(uint8_t channelId);
    void checkTimers();
    void checkSchedules();
    void updateRuntimeMetrics();

    RelayChannel _channels[2];
    SemaphoreHandle_t _relayMutex;
    Preferences _prefs;

    uint32_t _lastProcessTick;
    uint32_t _lastRuntimeSaveTick;
    uint32_t _lastOneSecondTick;
};

#endif // RELAY_MANAGER_H
