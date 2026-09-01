# ESP32 Real-Time OS Dual-Relay Controller with AP Web Server & Power Saver

A real-time, FreeRTOS multi-core IoT dual-relay controller powered by the ESP32. It creates its own standalone Wi-Fi Access Point (AP), serves a responsive high-contrast Slate/Charcoal Web UI on **Port 80**, provides independent countdown timers, cyclic loop automation, momentary inching pulses, daily clock schedules for **Relay 1 (D1)** and **Relay 2 (D2)**, syncs time directly with your smartphone browser, and includes a **Permanent Stay-On System** as well as an intelligent **Low-Power AP Duty-Cycle Mode**.

---

## Key Features

1. **Standalone Wi-Fi AP (No Router / No Internet Needed)**:
   - Broadcasts its own secure network: `ESP32-Power-Relay` (Password: `12345678`).
   - Serves the dashboard directly on `http://192.168.4.1:80` with automatic captive portal redirect.
2. **Zero-Delay Real-Time Architecture (FreeRTOS Multi-Core)**:
   - **Core 1**: Dedicated high-priority Relay Execution, Cyclic Automation & Timer Scheduler task with 100ms precision.
   - **Core 0**: Wi-Fi, DNS, Web Server processing, and Power Management.
   - Instantaneous response when toggling relays from your phone without blocking delays.
3. **High-Contrast Slate / Light-Black Theme**:
   - Modern, high-visibility Slate & Charcoal UI with crisp luminous borders, bright typography, and vibrant status badges for outdoor and low-light visibility.
4. **Permanent Stay-On Mode (Saved in Flash / NVS)**:
   - Dedicated persistent checkbox to keep the system and AP running 24/7 permanently without sleeping.
   - Stored directly in ESP32 Non-Volatile Storage (`Preferences`) across power resets.
5. **Advanced Relay Automations ("More Real-Time Work")**:
   - **Manual Switching**: Instant physical toggle with active-low / active-high polarity configuration.
   - **Countdown Timer Mode**: Start Delay and ON Duration with live progress countdown.
   - **Cyclic Repeat Loop**: ON duration, OFF duration, and loop repeat count (or infinite loop) for water pumps, aerators, hydroponics, and cooling fans.
   - **Daily Schedule with Weekday Filters**: Set Turn-ON time (`HH:MM`) and Turn-OFF time (`HH:MM`) with interactive day-of-week checkboxes (Sun-Sat, Weekdays, Weekends).
   - **Power-On Default State**: Choose whether relays boot up as Always OFF, Always ON, or Restore Previous State after a power cut.
6. **Smart Time Synchronization & 12-Hour Display**:
   - **12-Hour Format**: Displays live clock in standard 12-hour format with AM/PM indicators.
   - **1-Click Phone Sync**: Automatically grabs exact timestamp and timezone from mobile browser on load.
   - **Manual Time Setting**: Set custom date and time via the built-in datetime picker in settings.
7. **Live Real-Time Activity Event Stream**:
   - In-memory event stream tracking the latest operations (timer finishes, schedule events, manual clicks, boots) directly on the web dashboard.
8. **Telemetry & Total Energy Consumption Metering**:
   - Real-time ESP32 chip temperature (`°C` and `°F`), Free RAM heap, System Uptime, Connected clients, and FreeRTOS Core 0 / Core 1 execution tick counters.
   - Total Combined Energy Consumption summary widget (**kWh**) across all channels, total runtime, and live connected wattage.
   - Emergency Master Kill Switch ("🚨 EMERGENCY ALL OFF").
9. **Optimized Low Power Battery Saving Duty Cycle**:
   - When low-power mode is enabled, the AP sleeps for **5 minutes**, then wakes up for a **2-minute discovery/connect window**.

---

## Hardware Wiring Diagram

```
 +-------------------------------------------------------+
 |                    ESP32 DEVKIT V1                   |
 |                                                       |
 |  [ VIN ] -------------> Relay Board VCC (+5V Power)   |
 |  [ GND ] -------------> Relay Board GND (Ground)      |
 |  [ D1 / GPIO 22 ] ----> Relay 1 IN1                   |
 |  [ D2 / GPIO 21 ] ----> Relay 2 IN2                   |
 |  [ D2 / GPIO 2  ] ----> Built-in Status LED (Disabled)|
 +-------------------------------------------------------+

 +-------------------------------------------------------+
 |                 2-CHANNEL RELAY MODULE                |
 |                                                       |
 |  VCC  --------------> ESP32 VIN (5V)                  |
 |  GND  --------------> ESP32 GND                       |
 |  IN1  --------------> ESP32 GPIO 22 (D1)              |
 |  IN2  --------------> ESP32 GPIO 21 (D2)              |
 |                                                       |
 |  Relay 1 COM/NO ----> Appliance 1 (e.g. Light / Fan)  |
 |  Relay 2 COM/NO ----> Appliance 2 (e.g. Pump / Heater)|
 +-------------------------------------------------------+
```

### Pin Mapping Table

| Logical Pin | ESP32 GPIO | Description | Default Active Polarity |
| :--- | :--- | :--- | :--- |
| **D1** | `GPIO 22` | Relay 1 Control Pin | Active LOW (Configurable) |
| **D2** | `GPIO 21` | Relay 2 Control Pin | Active LOW (Configurable) |
| **LED** | `GPIO 2` | Onboard Blue Status Indicator | Disabled / Kept OFF |

---

## Installation & Flashing Instructions

### Requirements
- **Arduino IDE** (v1.8.19+ or v2.x) OR **PlatformIO** / **Arduino CLI**.
- **ESP32 Arduino Board Package** (v2.0.x or v3.x).
- Standard USB-to-MicroUSB / Type-C cable.

### Step-by-Step Guide
1. Open the Arduino IDE.
2. Open [`IOT_Real_Time_OS.ino`](file:///c:/Data/Coding/IOT_Code/AP_Relay_Control/IOT_Real_Time_OS.ino).
3. In **Tools**, select:
   - **Board**: `ESP32 Dev Module` (or your specific ESP32 variant)
   - **Flash Frequency**: `80MHz`
   - **Upload Speed**: `921600` (or `115200`)
   - **Port**: Select your ESP32 COM port
4. Click **Upload** (Arrow icon).

---

## REST API Reference

| Method | Endpoint | Parameters | Description |
| :--- | :--- | :--- | :--- |
| `GET` | `/api/status` | None | Returns full JSON system state, relays, timers, cycles, events, and telemetry |
| `POST` | `/api/relay` | `id=1&state=1` | Turn ON/OFF/Toggle Relay 1 or 2 |
| `POST` | `/api/timer` | `id=1&start_delay=0&duration=600&enable=1` | Start or cancel countdown timer (seconds) |
| `POST` | `/api/cycle` | `id=1&on_sec=30&off_sec=30&cycles=0&enable=1` | Start or cancel cyclic automation loop |
| `POST` | `/api/schedule` | `id=1&start_h=8&start_m=0&end_h=18&end_m=0&days=127&enable=1` | Set daily start/end schedule with weekday bitmask |
| `POST` | `/api/time/sync` | `epoch=1725100000&tz_offset=330` | Sync software RTC with UNIX timestamp & timezone |
| `POST` | `/api/time/manual` | `year=2026&month=8&day=31&hour=16&min=30&sec=0` | Set RTC date and time manually |
| `POST` | `/api/power` | `stay_on=1` OR `enable=1&sleep_min=5&wake_min=2` | Configure Permanent Stay-On or Low-Power Sleep Duty Cycle |
| `POST` | `/api/settings` | `r1_name=Pump&r1_watts=250&r1_actlow=1&r1_pwron=0...` | Configure relay names, wattage, active-low polarity, and power-on state |
| `POST` | `/api/all_off` | None | Emergency kill switch - immediately forces all relays OFF |

---

## License & Credits
Developed for ESP32 Dual-Core Embedded Real-Time IoT Systems. Free and open source under MIT License.
