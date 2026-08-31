# ESP32 Real-Time Dual-Relay Controller with AP Web Server & Power Saver

A real-time, FreeRTOS-driven IoT dual-relay controller powered by the ESP32. It creates its own standalone Wi-Fi Access Point (AP), serves a mobile-responsive Glassmorphic Web UI on **Port 80**, provides independent countdown timers & daily clock schedules for **Relay 1 (D1)** and **Relay 2 (D2)**, syncs time directly with your smartphone browser, and includes an intelligent **Low-Power AP Duty-Cycle Mode**.

---

## Key Features

1. **Standalone Wi-Fi AP (No Router / No Internet Needed)**:
   - Broadcasts its own secure network: `ESP32-Power-Relay` (Password: `12345678`).
   - Serves the dashboard directly on `http://192.168.4.1:80` with automatic captive portal redirect.
2. **Zero-Delay Real-Time Architecture (FreeRTOS Multi-Core)**:
   - **Core 1**: Dedicated high-priority Relay Execution & Timer Scheduler task with 100ms precision.
   - **Core 0**: Wi-Fi, DNS, and Web Server processing.
   - Instantaneous response when toggling relays from your phone without blocking delays.
3. **Independent Dual-Relay Control**:
   - **Relay 1 (Pin D1 / GPIO 22)** and **Relay 2 (Pin D2 / GPIO 21)**.
   - **Countdown Timer Mode**: Specify a Start Delay (turn ON in X mins) and ON Duration (stay ON for Y mins) with real-time countdown progress bar.
   - **Daily Schedule Mode**: Set 24h Turn-ON time (`HH:MM`) and Turn-OFF time (`HH:MM`) with day-of-week filters.
4. **Smart Time Synchronization**:
   - **1-Click Phone Sync**: Automatically grabs exact timestamp and timezone from the mobile browser on connection.
   - **Manual Time Insertion**: Set custom date and time via the built-in datetime picker in settings.
5. **Intelligent AP Low-Power Duty Cycling**:
   - Turns off the power-hungry Wi-Fi radio when no user is connected/active (dropping power from ~150mA to ~20mA).
   - Automatically wakes the AP up every 15–20 minutes for a short 3-minute discovery window.
   - If user connects and uses the web UI, the AP stays awake. If no user interacts, it goes back to sleep.
   - FreeRTOS relay schedules and timers continue running uninterrupted even when AP is asleep.
6. **Flash Memory Persistence (NVS / Preferences)**:
   - Saves all schedules, relay custom names, active-low polarity, load wattage, and power settings permanently across power cuts.
7. **Premium UI & Energy Telemetry**:
   - Modern Glassmorphism dark theme with glowing neon indicators.
   - Real-time ESP32 chip temperature (`°C` and `°F`), Free RAM heap, Uptime, and Connected clients.
   - Lifetime runtime tracking and estimated energy consumption (**kWh**) based on configured load wattage.
   - Emergency Master Kill Switch ("🚨 EMERGENCY ALL OFF").

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
 |  [ D2 / GPIO 2  ] ----> Built-in Status LED (Active)  |
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
| **LED** | `GPIO 2` | Onboard Blue Status Indicator | Active HIGH (Turns ON if any relay is active) |

> [!NOTE]
> If your ESP32 board uses different GPIOs for D1 and D2 (e.g., GPIO 5 and GPIO 4), simply edit `RELAY_1_PIN` and `RELAY_2_PIN` in [`Config.h`](file:///c:/Data/Coding/IOT_Code/AP_Relay_Control/Config.h).

---

## Installation & Flashing Instructions

### Requirements
- **Arduino IDE** (v1.8.19+ or v2.x) OR **PlatformIO**.
- **ESP32 Arduino Board Package** (v2.0.x or v3.x).
- Standard USB-to-MicroUSB / Type-C cable.

### Step-by-Step Guide
1. Open the Arduino IDE.
2. Go to **File -> Preferences**, and add the ESP32 Board Manager URL if not already present:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to **Tools -> Board -> Boards Manager**, search for `esp32` by Espressif Systems, and install it.
4. Open [`AP_Relay_Control.ino`](file:///c:/Data/Coding/IOT_Code/AP_Relay_Control/AP_Relay_Control.ino).
5. In **Tools**, select:
   - **Board**: `ESP32 Dev Module` (or your specific ESP32 variant)
   - **Flash Frequency**: `80MHz`
   - **Upload Speed**: `921600` (or `115200`)
   - **Port**: Select your ESP32 COM port
6. Click **Upload** (Arrow icon). *(Hold the `BOOT` button on your ESP32 board if upload doesn't start automatically).*

> [!TIP]
> **No external libraries required!** The sketch uses standard ESP32 core libraries (`WiFi.h`, `WebServer.h`, `DNSServer.h`, `Preferences.h`, `time.h`).

---

## How to Use

1. **Power Up**: Connect the ESP32 to a 5V power source (USB or 5V DC adapter).
2. **Connect Phone to Wi-Fi**:
   - Open your phone's Wi-Fi settings.
   - Connect to **`ESP32-Power-Relay`**.
   - Enter password: **`12345678`**.
3. **Open Dashboard**:
   - If captive portal opens automatically, tap to open.
   - Otherwise, open any browser (Safari / Chrome) and go to: **`http://192.168.4.1`**.
4. **Time Sync**:
   - The web app automatically synchronizes the ESP32 internal clock with your phone on load.
   - You can also tap **"📱 Sync Phone"** or set custom time manually in Settings (`⚙️`).
5. **Operate Relays**:
   - **Manual Toggle**: Tap the ON/OFF switches for instant switching.
   - **Start Countdown Timer**: Enter delay and duration under the **⏱️ Timer** tab and tap *Start Countdown Timer*.
   - **Set Daily Schedule**: Enter Start/End times under the **📅 Schedule** tab and toggle the schedule switch.
   - **Power Saver**: Enable the **🔋 Low Power AP Duty-Cycle** switch to let Wi-Fi sleep during inactivity.

---

## REST API Reference

For automation, smart home integration, or custom HTTP clients:

| Method | Endpoint | Parameters | Description |
| :--- | :--- | :--- | :--- |
| `GET` | `/api/status` | None | Returns full JSON system state, relays, timers, time, and telemetry |
| `POST` | `/api/relay` | `id=1&state=1` (or toggle without state) | Turn ON/OFF/Toggle Relay 1 or 2 |
| `POST` | `/api/timer` | `id=1&start_delay=0&duration=600&enable=1` | Start or cancel countdown timer (seconds) |
| `POST` | `/api/schedule` | `id=1&start_h=8&start_m=0&end_h=18&end_m=0&enable=1` | Set daily start/end schedule |
| `POST` | `/api/time/sync` | `epoch=1725100000&tz_offset=330` | Sync software RTC with UNIX timestamp & timezone |
| `POST` | `/api/time/manual` | `year=2026&month=8&day=31&hour=16&min=30&sec=0` | Set RTC date and time manually |
| `POST` | `/api/power` | `enable=1&sleep_min=15&wake_min=3` | Configure low power AP duty cycle |
| `POST` | `/api/settings` | `r1_name=Pump&r1_watts=250&r1_actlow=1...` | Configure relay names, wattage, and active-low polarity |
| `POST` | `/api/all_off` | None | Emergency kill switch - immediately forces all relays OFF |

---

## License & Credits
Developed for ESP32 Dual-Core Embedded Real-Time IoT Systems. Free and open source under MIT License.
