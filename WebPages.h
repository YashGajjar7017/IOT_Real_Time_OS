#ifndef WEBPAGES_H
#define WEBPAGES_H

#include <Arduino.h>

const char INDEX_HTML[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>ESP32 Real-Time Dual Relay Controller</title>
  <style>
    :root {
      --bg: #0b0f19;
      --card-bg: rgba(23, 32, 54, 0.7);
      --card-border: rgba(255, 255, 255, 0.08);
      --primary: #00e5ff;
      --primary-glow: rgba(0, 229, 255, 0.35);
      --success: #00e676;
      --success-glow: rgba(0, 230, 118, 0.35);
      --danger: #ff1744;
      --danger-glow: rgba(255, 23, 68, 0.35);
      --warning: #ffab00;
      --text: #ffffff;
      --text-muted: #8e9bb0;
      --card-radius: 18px;
    }
    * { box-sizing: border-box; margin: 0; padding: 0; font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif; }
    body { background-color: var(--bg); color: var(--text); min-height: 100vh; padding: 16px; display: flex; flex-direction: column; align-items: center; background-image: radial-gradient(circle at 10% 20%, rgba(0, 229, 255, 0.05) 0%, transparent 40%), radial-gradient(circle at 90% 80%, rgba(0, 230, 118, 0.04) 0%, transparent 40%); }
    .container { width: 100%; max-width: 600px; display: flex; flex-direction: column; gap: 16px; }
    
    /* Header */
    header { background: var(--card-bg); backdrop-filter: blur(12px); -webkit-backdrop-filter: blur(12px); border: 1px solid var(--card-border); border-radius: var(--card-radius); padding: 16px 20px; display: flex; justify-content: space-between; align-items: center; box-shadow: 0 8px 32px rgba(0,0,0,0.3); }
    .logo-area { display: flex; align-items: center; gap: 12px; }
    .logo-icon { width: 36px; height: 36px; border-radius: 10px; background: linear-gradient(135deg, var(--primary), #7c4dff); display: flex; align-items: center; justify-content: center; font-weight: 800; font-size: 18px; color: #fff; box-shadow: 0 0 15px var(--primary-glow); }
    .title-box h1 { font-size: 18px; font-weight: 700; letter-spacing: -0.3px; }
    .title-box p { font-size: 12px; color: var(--text-muted); }
    .header-actions { display: flex; gap: 8px; align-items: center; }
    .btn-icon { background: rgba(255,255,255,0.06); border: 1px solid var(--card-border); color: var(--text); width: 38px; height: 38px; border-radius: 10px; cursor: pointer; display: flex; align-items: center; justify-content: center; transition: all 0.2s; }
    .btn-icon:active { transform: scale(0.92); }

    /* Time & Status Bar */
    .status-bar { background: var(--card-bg); backdrop-filter: blur(12px); border: 1px solid var(--card-border); border-radius: 12px; padding: 10px 16px; display: flex; justify-content: space-between; align-items: center; font-size: 13px; }
    .time-display { display: flex; align-items: center; gap: 8px; font-weight: 600; color: var(--primary); }
    .sync-btn { background: rgba(0, 229, 255, 0.15); border: 1px solid var(--primary); color: var(--primary); padding: 4px 10px; border-radius: 6px; font-size: 11px; font-weight: 600; cursor: pointer; transition: all 0.2s; }
    .sync-btn:active { background: var(--primary); color: #000; }

    /* Relay Card */
    .relay-card { background: var(--card-bg); backdrop-filter: blur(12px); border: 1px solid var(--card-border); border-radius: var(--card-radius); padding: 18px; display: flex; flex-direction: column; gap: 14px; position: relative; overflow: hidden; box-shadow: 0 8px 24px rgba(0,0,0,0.25); transition: border-color 0.3s; }
    .relay-card.active { border-color: rgba(0, 230, 118, 0.4); box-shadow: 0 0 25px rgba(0, 230, 118, 0.15); }
    .relay-card.active::before { content:''; position: absolute; top: 0; left: 0; width: 4px; height: 100%; background: var(--success); }

    .relay-header { display: flex; justify-content: space-between; align-items: center; }
    .relay-title { font-size: 17px; font-weight: 700; display: flex; align-items: center; gap: 8px; }
    .relay-badge { font-size: 10px; padding: 3px 8px; border-radius: 20px; font-weight: 700; letter-spacing: 0.5px; text-transform: uppercase; }
    .badge-off { background: rgba(255,255,255,0.08); color: var(--text-muted); }
    .badge-on { background: var(--success); color: #000; box-shadow: 0 0 10px var(--success-glow); }

    /* Main Toggle Switch */
    .switch-row { display: flex; justify-content: space-between; align-items: center; background: rgba(0,0,0,0.25); padding: 12px 16px; border-radius: 12px; }
    .switch-label { font-size: 14px; font-weight: 500; }
    .toggle-switch { position: relative; width: 56px; height: 30px; display: inline-block; }
    .toggle-switch input { opacity: 0; width: 0; height: 0; }
    .slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: #334155; transition: .3s; border-radius: 30px; }
    .slider:before { position: absolute; content: ""; height: 22px; width: 22px; left: 4px; bottom: 4px; background-color: white; transition: .3s; border-radius: 50%; }
    input:checked + .slider { background-color: var(--success); box-shadow: 0 0 12px var(--success-glow); }
    input:checked + .slider:before { transform: translateX(26px); }

    /* Tabs inside Relay */
    .tab-nav { display: flex; gap: 6px; background: rgba(0,0,0,0.3); padding: 4px; border-radius: 10px; }
    .tab-btn { flex: 1; padding: 7px 0; background: transparent; border: none; color: var(--text-muted); font-size: 12px; font-weight: 600; border-radius: 7px; cursor: pointer; transition: all 0.2s; }
    .tab-btn.active { background: rgba(255,255,255,0.1); color: var(--text); }
    .tab-pane { display: none; flex-direction: column; gap: 12px; padding-top: 4px; }
    .tab-pane.active { display: flex; }

    /* Inputs & Forms */
    .form-group { display: flex; flex-direction: column; gap: 6px; }
    .form-label { font-size: 12px; color: var(--text-muted); font-weight: 500; }
    .input-row { display: flex; gap: 8px; }
    .input-box { flex: 1; background: rgba(0,0,0,0.35); border: 1px solid var(--card-border); color: #fff; padding: 8px 12px; border-radius: 8px; font-size: 13px; outline: none; }
    .input-box:focus { border-color: var(--primary); }

    /* Action Buttons */
    .btn { padding: 9px 16px; border-radius: 8px; font-size: 13px; font-weight: 600; border: none; cursor: pointer; transition: all 0.2s; display: flex; align-items: center; justify-content: center; gap: 6px; }
    .btn:active { transform: scale(0.96); }
    .btn-primary { background: linear-gradient(135deg, var(--primary), #00b0ff); color: #000; font-weight: 700; box-shadow: 0 4px 15px var(--primary-glow); }
    .btn-danger { background: rgba(255, 23, 68, 0.15); border: 1px solid var(--danger); color: var(--danger); }
    .btn-danger:active { background: var(--danger); color: #fff; }
    .btn-success { background: var(--success); color: #000; font-weight: 700; }

    /* Live Countdown Progress Bar */
    .timer-live-box { background: rgba(0, 229, 255, 0.08); border: 1px solid rgba(0, 229, 255, 0.2); border-radius: 10px; padding: 10px 14px; display: flex; flex-direction: column; gap: 6px; }
    .timer-live-header { display: flex; justify-content: space-between; font-size: 12px; }
    .timer-countdown { font-family: monospace; font-size: 16px; font-weight: 700; color: var(--primary); }
    .progress-track { width: 100%; height: 6px; background: rgba(255,255,255,0.1); border-radius: 10px; overflow: hidden; }
    .progress-fill { height: 100%; background: linear-gradient(90deg, var(--primary), var(--success)); width: 0%; transition: width 0.5s ease; }

    /* Stats Grid */
    .stats-row { display: grid; grid-template-columns: 1fr 1fr; gap: 8px; font-size: 12px; }
    .stat-item { background: rgba(0,0,0,0.25); padding: 8px 10px; border-radius: 8px; display: flex; flex-direction: column; gap: 2px; }
    .stat-val { font-weight: 700; font-size: 13px; color: var(--primary); }

    /* Telemetry & Master Controls */
    .telemetry-card { background: var(--card-bg); backdrop-filter: blur(12px); border: 1px solid var(--card-border); border-radius: var(--card-radius); padding: 16px; display: flex; flex-direction: column; gap: 12px; }
    .telemetry-grid { display: grid; grid-template-columns: repeat(2, 1fr); gap: 10px; }
    .telem-box { background: rgba(0,0,0,0.25); border: 1px solid var(--card-border); border-radius: 10px; padding: 10px; display: flex; flex-direction: column; gap: 4px; }
    .telem-title { font-size: 11px; color: var(--text-muted); }
    .telem-val { font-size: 15px; font-weight: 700; }

    .master-btn { width: 100%; background: linear-gradient(135deg, #d50000, #ff1744); color: #fff; font-size: 14px; font-weight: 700; padding: 12px; border-radius: 12px; border: none; cursor: pointer; box-shadow: 0 4px 20px var(--danger-glow); transition: transform 0.2s; }
    .master-btn:active { transform: scale(0.97); }

    /* Modal */
    .modal-overlay { position: fixed; top: 0; left: 0; width: 100%; height: 100%; background: rgba(0,0,0,0.7); backdrop-filter: blur(8px); display: none; align-items: center; justify-content: center; z-index: 100; padding: 16px; }
    .modal-overlay.open { display: flex; }
    .modal { background: #131a2a; border: 1px solid var(--card-border); border-radius: var(--card-radius); width: 100%; max-width: 480px; max-height: 90vh; overflow-y: auto; padding: 20px; display: flex; flex-direction: column; gap: 16px; }
    .modal-header { display: flex; justify-content: space-between; align-items: center; border-bottom: 1px solid var(--card-border); padding-bottom: 12px; }
    .modal-title { font-size: 16px; font-weight: 700; }
    .close-btn { background: transparent; border: none; color: var(--text-muted); font-size: 20px; cursor: pointer; }

    /* Toast Notification */
    #toast { position: fixed; bottom: 24px; left: 50%; transform: translateX(-50%) translateY(100px); background: #1e293b; border: 1px solid var(--primary); color: #fff; padding: 10px 20px; border-radius: 30px; font-size: 13px; font-weight: 600; box-shadow: 0 10px 30px rgba(0,0,0,0.5); opacity: 0; transition: all 0.3s ease; z-index: 200; pointer-events: none; }
    #toast.show { transform: translateX(-50%) translateY(0); opacity: 1; }
  </style>
</head>
<body>

  <div class="container">
    <!-- Header -->
    <header>
      <div class="logo-area">
        <div class="logo-icon">⚡</div>
        <div class="title-box">
          <h1>ESP32 IoT AP Relay</h1>
          <p>Real-Time Dual Channel & Power Saver</p>
        </div>
      </div>
      <div class="header-actions">
        <button class="btn-icon" id="openSettingsBtn" title="Settings">⚙️</button>
      </div>
    </header>

    <!-- Time & Status Bar -->
    <div class="status-bar">
      <div class="time-display">
        <span>🕒</span>
        <span id="liveClock">--:--:--</span>
        <span id="liveDate" style="color:var(--text-muted); font-size:11px;">(Not Synced)</span>
      </div>
      <button class="sync-btn" id="phoneSyncBtn" title="Sync time with your phone">📱 Sync Phone</button>
    </div>

    <!-- Relay 1 Card -->
    <div class="relay-card" id="relayCard1">
      <div class="relay-header">
        <div class="relay-title">
          <span id="r1Name">Relay 1 (D1)</span>
        </div>
        <span class="relay-badge badge-off" id="r1Badge">OFF</span>
      </div>

      <!-- Main Toggle Switch -->
      <div class="switch-row">
        <span class="switch-label">Manual Output State</span>
        <label class="toggle-switch">
          <input type="checkbox" id="r1Switch" onchange="toggleRelay(1, this.checked)">
          <span class="slider"></span>
        </label>
      </div>

      <!-- Live Timer Info (Shown if active) -->
      <div class="timer-live-box" id="r1TimerLiveBox" style="display:none;">
        <div class="timer-live-header">
          <span id="r1TimerPhase">Timer: Active</span>
          <span class="timer-countdown" id="r1TimerCountdown">00:00</span>
        </div>
        <div class="progress-track">
          <div class="progress-fill" id="r1TimerProgress"></div>
        </div>
        <button class="btn btn-danger" style="padding:4px 8px; font-size:11px; margin-top:4px;" onclick="cancelTimer(1)">Cancel Timer</button>
      </div>

      <!-- Tabs for Timers & Schedules -->
      <div class="tab-nav">
        <button class="tab-btn active" onclick="switchTab(1, 'timer')">⏱️ Timer</button>
        <button class="tab-btn" onclick="switchTab(1, 'sched')">📅 Schedule</button>
        <button class="tab-btn" onclick="switchTab(1, 'stats')">📊 Energy</button>
      </div>

      <!-- Tab: Countdown Timer -->
      <div class="tab-pane active" id="r1TabTimer">
        <div class="form-group">
          <label class="form-label">Start Delay (Turn ON after):</label>
          <div class="input-row">
            <input type="number" class="input-box" id="r1DelayMin" placeholder="Mins" min="0" value="0">
            <input type="number" class="input-box" id="r1DelaySec" placeholder="Secs" min="0" max="59" value="0">
          </div>
        </div>
        <div class="form-group">
          <label class="form-label">ON Duration (Stay ON for):</label>
          <div class="input-row">
            <input type="number" class="input-box" id="r1DurMin" placeholder="Mins" min="0" value="10">
            <input type="number" class="input-box" id="r1DurSec" placeholder="Secs" min="0" max="59" value="0">
          </div>
        </div>
        <button class="btn btn-primary" onclick="setTimer(1)">Start Countdown Timer</button>
      </div>

      <!-- Tab: Daily Schedule -->
      <div class="tab-pane" id="r1TabSched">
        <div class="form-group">
          <label class="form-label">Daily Turn ON Time (HH:MM):</label>
          <input type="time" class="input-box" id="r1SchedStart" value="08:00">
        </div>
        <div class="form-group">
          <label class="form-label">Daily Turn OFF Time (HH:MM):</label>
          <input type="time" class="input-box" id="r1SchedEnd" value="18:00">
        </div>
        <div class="input-row" style="align-items:center; justify-content:space-between; margin-top:4px;">
          <span style="font-size:12px; color:var(--text-muted);">Enable Daily Schedule</span>
          <label class="toggle-switch">
            <input type="checkbox" id="r1SchedEn" onchange="setSchedule(1)">
            <span class="slider"></span>
          </label>
        </div>
      </div>

      <!-- Tab: Stats -->
      <div class="tab-pane" id="r1TabStats">
        <div class="stats-row">
          <div class="stat-item">
            <span class="telem-title">Total ON Time</span>
            <span class="stat-val" id="r1TotTime">0h 0m</span>
          </div>
          <div class="stat-item">
            <span class="telem-title">Est. Energy Consumed</span>
            <span class="stat-val" id="r1Energy">0.000 kWh</span>
          </div>
        </div>
      </div>
    </div>

    <!-- Relay 2 Card -->
    <div class="relay-card" id="relayCard2">
      <div class="relay-header">
        <div class="relay-title">
          <span id="r2Name">Relay 2 (D2)</span>
        </div>
        <span class="relay-badge badge-off" id="r2Badge">OFF</span>
      </div>

      <!-- Main Toggle Switch -->
      <div class="switch-row">
        <span class="switch-label">Manual Output State</span>
        <label class="toggle-switch">
          <input type="checkbox" id="r2Switch" onchange="toggleRelay(2, this.checked)">
          <span class="slider"></span>
        </label>
      </div>

      <!-- Live Timer Info (Shown if active) -->
      <div class="timer-live-box" id="r2TimerLiveBox" style="display:none;">
        <div class="timer-live-header">
          <span id="r2TimerPhase">Timer: Active</span>
          <span class="timer-countdown" id="r2TimerCountdown">00:00</span>
        </div>
        <div class="progress-track">
          <div class="progress-fill" id="r2TimerProgress"></div>
        </div>
        <button class="btn btn-danger" style="padding:4px 8px; font-size:11px; margin-top:4px;" onclick="cancelTimer(2)">Cancel Timer</button>
      </div>

      <!-- Tabs for Timers & Schedules -->
      <div class="tab-nav">
        <button class="tab-btn active" onclick="switchTab(2, 'timer')">⏱️ Timer</button>
        <button class="tab-btn" onclick="switchTab(2, 'sched')">📅 Schedule</button>
        <button class="tab-btn" onclick="switchTab(2, 'stats')">📊 Energy</button>
      </div>

      <!-- Tab: Countdown Timer -->
      <div class="tab-pane active" id="r2TabTimer">
        <div class="form-group">
          <label class="form-label">Start Delay (Turn ON after):</label>
          <div class="input-row">
            <input type="number" class="input-box" id="r2DelayMin" placeholder="Mins" min="0" value="0">
            <input type="number" class="input-box" id="r2DelaySec" placeholder="Secs" min="0" max="59" value="0">
          </div>
        </div>
        <div class="form-group">
          <label class="form-label">ON Duration (Stay ON for):</label>
          <div class="input-row">
            <input type="number" class="input-box" id="r2DurMin" placeholder="Mins" min="0" value="15">
            <input type="number" class="input-box" id="r2DurSec" placeholder="Secs" min="0" max="59" value="0">
          </div>
        </div>
        <button class="btn btn-primary" onclick="setTimer(2)">Start Countdown Timer</button>
      </div>

      <!-- Tab: Daily Schedule -->
      <div class="tab-pane" id="r2TabSched">
        <div class="form-group">
          <label class="form-label">Daily Turn ON Time (HH:MM):</label>
          <input type="time" class="input-box" id="r2SchedStart" value="18:00">
        </div>
        <div class="form-group">
          <label class="form-label">Daily Turn OFF Time (HH:MM):</label>
          <input type="time" class="input-box" id="r2SchedEnd" value="22:00">
        </div>
        <div class="input-row" style="align-items:center; justify-content:space-between; margin-top:4px;">
          <span style="font-size:12px; color:var(--text-muted);">Enable Daily Schedule</span>
          <label class="toggle-switch">
            <input type="checkbox" id="r2SchedEn" onchange="setSchedule(2)">
            <span class="slider"></span>
          </label>
        </div>
      </div>

      <!-- Tab: Stats -->
      <div class="tab-pane" id="r2TabStats">
        <div class="stats-row">
          <div class="stat-item">
            <span class="telem-title">Total ON Time</span>
            <span class="stat-val" id="r2TotTime">0h 0m</span>
          </div>
          <div class="stat-item">
            <span class="telem-title">Est. Energy Consumed</span>
            <span class="stat-val" id="r2Energy">0.000 kWh</span>
          </div>
        </div>
      </div>
    </div>

    <!-- Power Saver & Diagnostics -->
    <div class="telemetry-card">
      <div style="display:flex; justify-content:space-between; align-items:center;">
        <span style="font-weight:700; font-size:14px;">🔋 Low Power AP Duty-Cycle</span>
        <label class="toggle-switch">
          <input type="checkbox" id="lowPowerEnSwitch" onchange="toggleLowPower(this.checked)">
          <span class="slider"></span>
        </label>
      </div>
      <div style="font-size:12px; color:var(--text-muted);" id="lowPowerDesc">
        When enabled, turns off Wi-Fi AP after inactivity. AP re-awakens every 15 mins for discovery.
      </div>
      
      <div class="telemetry-grid" style="margin-top:8px;">
        <div class="telem-box">
          <span class="telem-title">ESP32 Temp</span>
          <span class="telem-val" id="telemTemp">-- °C</span>
        </div>
        <div class="telem-box">
          <span class="telem-title">Free Memory</span>
          <span class="telem-val" id="telemHeap">-- KB</span>
        </div>
        <div class="telem-box">
          <span class="telem-title">System Uptime</span>
          <span class="telem-val" id="telemUptime">--</span>
        </div>
        <div class="telem-box">
          <span class="telem-title">Connected Phones</span>
          <span class="telem-val" id="telemClients">1</span>
        </div>
      </div>

      <!-- Master Emergency Kill Switch -->
      <button class="master-btn" onclick="killAllRelays()">🚨 EMERGENCY ALL OFF</button>
    </div>
  </div>

  <!-- Settings & Manual Time Modal -->
  <div class="modal-overlay" id="settingsModal">
    <div class="modal">
      <div class="modal-header">
        <div class="modal-title">⚙️ System & Power Settings</div>
        <button class="close-btn" id="closeSettingsBtn">&times;</button>
      </div>

      <!-- Manual Time Setting -->
      <div class="form-group">
        <label class="form-label" style="font-weight:700; color:var(--primary);">🕒 Manual Date & Time Adjustment</label>
        <input type="datetime-local" class="input-box" id="manualDateTimeInput">
        <button class="btn btn-primary" style="margin-top:6px;" onclick="saveManualTime()">Set ESP32 Time</button>
      </div>

      <!-- Low Power Settings -->
      <div class="form-group" style="border-top:1px solid var(--card-border); padding-top:12px;">
        <label class="form-label" style="font-weight:700; color:var(--warning);">🔋 Power Saver Timing</label>
        <div class="input-row">
          <div style="flex:1;">
            <span class="form-label">AP Sleep (Minutes):</span>
            <input type="number" class="input-box" id="lpSleepMin" value="15" min="1" max="120">
          </div>
          <div style="flex:1;">
            <span class="form-label">Wake Window (Mins):</span>
            <input type="number" class="input-box" id="lpWakeMin" value="3" min="1" max="30">
          </div>
        </div>
        <button class="btn btn-primary" style="margin-top:6px;" onclick="savePowerConfig()">Save Power Cycles</button>
      </div>

      <!-- Channel Names & Load Wattage -->
      <div class="form-group" style="border-top:1px solid var(--card-border); padding-top:12px;">
        <label class="form-label" style="font-weight:700; color:var(--text);">🏷️ Channel 1 Customization</label>
        <input type="text" class="input-box" id="cfgR1Name" placeholder="Relay 1 Name" value="Relay 1">
        <div class="input-row" style="margin-top:4px;">
          <input type="number" class="input-box" id="cfgR1Watts" placeholder="Load Watts (e.g. 100)" value="100">
          <label style="display:flex; align-items:center; gap:6px; font-size:12px;">
            <input type="checkbox" id="cfgR1ActiveLow" checked> Active LOW
          </label>
        </div>
      </div>

      <div class="form-group">
        <label class="form-label" style="font-weight:700; color:var(--text);">🏷️ Channel 2 Customization</label>
        <input type="text" class="input-box" id="cfgR2Name" placeholder="Relay 2 Name" value="Relay 2">
        <div class="input-row" style="margin-top:4px;">
          <input type="number" class="input-box" id="cfgR2Watts" placeholder="Load Watts (e.g. 100)" value="100">
          <label style="display:flex; align-items:center; gap:6px; font-size:12px;">
            <input type="checkbox" id="cfgR2ActiveLow" checked> Active LOW
          </label>
        </div>
      </div>

      <button class="btn btn-success" style="margin-top:8px;" onclick="saveChannelConfigs()">Save Channel Settings</button>
    </div>
  </div>

  <div id="toast">Notification</div>

  <script>
    let isModalOpen = false;

    // Toast helper
    function showToast(msg) {
      const toast = document.getElementById('toast');
      toast.innerText = msg;
      toast.classList.add('show');
      setTimeout(() => toast.classList.remove('show'), 2500);
    }

    // Modal Handlers
    document.getElementById('openSettingsBtn').onclick = () => {
      document.getElementById('settingsModal').classList.add('open');
      isModalOpen = true;
    };
    document.getElementById('closeSettingsBtn').onclick = () => {
      document.getElementById('settingsModal').classList.remove('open');
      isModalOpen = false;
    };

    // Tab Switching
    function switchTab(relayId, tabName) {
      const card = document.getElementById(`relayCard${relayId}`);
      card.querySelectorAll('.tab-btn').forEach(btn => btn.classList.remove('active'));
      card.querySelectorAll('.tab-pane').forEach(pane => pane.classList.remove('active'));

      event.target.classList.add('active');
      if (tabName === 'timer') card.querySelector(`#r${relayId}TabTimer`).classList.add('active');
      if (tabName === 'sched') card.querySelector(`#r${relayId}TabSched`).classList.add('active');
      if (tabName === 'stats') card.querySelector(`#r${relayId}TabStats`).classList.add('active');
    }

    // Relay Manual Toggle
    async function toggleRelay(id, state) {
      try {
        const res = await fetch('/api/relay', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `id=${id}&state=${state ? 1 : 0}`
        });
        if (res.ok) {
          showToast(`Relay ${id} switched ${state ? 'ON' : 'OFF'}`);
          fetchStatus();
        }
      } catch (err) {
        showToast('Error sending command');
      }
    }

    // Countdown Timer Start
    async function setTimer(id) {
      const delayMin = parseInt(document.getElementById(`r${id}DelayMin`).value) || 0;
      const delaySec = parseInt(document.getElementById(`r${id}DelaySec`).value) || 0;
      const durMin = parseInt(document.getElementById(`r${id}DurMin`).value) || 0;
      const durSec = parseInt(document.getElementById(`r${id}DurSec`).value) || 0;

      const totalDelay = delayMin * 60 + delaySec;
      const totalDur = durMin * 60 + durSec;

      if (totalDelay === 0 && totalDur === 0) {
        showToast('Please specify a valid delay or duration');
        return;
      }

      try {
        const res = await fetch('/api/timer', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `id=${id}&start_delay=${totalDelay}&duration=${totalDur}&enable=1`
        });
        if (res.ok) {
          showToast(`Relay ${id} Timer Activated!`);
          fetchStatus();
        }
      } catch(err) {
        showToast('Error starting timer');
      }
    }

    // Cancel Countdown Timer
    async function cancelTimer(id) {
      try {
        const res = await fetch('/api/timer', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `id=${id}&enable=0`
        });
        if (res.ok) {
          showToast(`Relay ${id} Timer Cancelled`);
          fetchStatus();
        }
      } catch(err) {
        showToast('Error cancelling timer');
      }
    }

    // Schedule Set
    async function setSchedule(id) {
      const isEn = document.getElementById(`r${id}SchedEn`).checked;
      const startVal = document.getElementById(`r${id}SchedStart`).value.split(':');
      const endVal = document.getElementById(`r${id}SchedEnd`).value.split(':');

      const startH = parseInt(startVal[0]) || 0;
      const startM = parseInt(startVal[1]) || 0;
      const endH = parseInt(endVal[0]) || 0;
      const endM = parseInt(endVal[1]) || 0;

      try {
        const res = await fetch('/api/schedule', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `id=${id}&start_h=${startH}&start_m=${startM}&end_h=${endH}&end_m=${endM}&days=255&enable=${isEn ? 1 : 0}`
        });
        if (res.ok) {
          showToast(`Relay ${id} Schedule ${isEn ? 'Enabled' : 'Disabled'}`);
          fetchStatus();
        }
      } catch(err) {
        showToast('Error saving schedule');
      }
    }

    // Phone Time Sync
    async function syncPhoneTime() {
      const now = new Date();
      const epochSec = Math.floor(now.getTime() / 1000);
      const tzOffset = -now.getTimezoneOffset(); // in minutes

      try {
        const res = await fetch('/api/time/sync', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `epoch=${epochSec}&tz_offset=${tzOffset}`
        });
        if (res.ok) {
          showToast('Time Synced with Phone!');
          fetchStatus();
        }
      } catch(err) {
        showToast('Time sync failed');
      }
    }
    document.getElementById('phoneSyncBtn').onclick = syncPhoneTime;

    // Manual Time Save
    async function saveManualTime() {
      const val = document.getElementById('manualDateTimeInput').value;
      if (!val) { showToast('Select valid date & time'); return; }
      const d = new Date(val);
      const epochSec = Math.floor(d.getTime() / 1000);

      try {
        const res = await fetch('/api/time/manual', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `year=${d.getFullYear()}&month=${d.getMonth()+1}&day=${d.getDate()}&hour=${d.getHours()}&min=${d.getMinutes()}&sec=${d.getSeconds()}`
        });
        if (res.ok) {
          showToast('Manual Time Saved!');
          document.getElementById('settingsModal').classList.remove('open');
          fetchStatus();
        }
      } catch(err) {
        showToast('Failed to set manual time');
      }
    }

    // Toggle Low Power Mode
    async function toggleLowPower(en) {
      const sleepMin = parseInt(document.getElementById('lpSleepMin').value) || 15;
      const wakeMin = parseInt(document.getElementById('lpWakeMin').value) || 3;

      try {
        const res = await fetch('/api/power', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `enable=${en ? 1 : 0}&sleep_min=${sleepMin}&wake_min=${wakeMin}`
        });
        if (res.ok) {
          showToast(`Low Power Mode ${en ? 'Enabled' : 'Disabled'}`);
          fetchStatus();
        }
      } catch(err) {
        showToast('Error setting low power mode');
      }
    }

    async function savePowerConfig() {
      const en = document.getElementById('lowPowerEnSwitch').checked;
      toggleLowPower(en);
    }

    // Save Channel Configs
    async function saveChannelConfigs() {
      const r1Name = document.getElementById('cfgR1Name').value;
      const r1Watts = parseFloat(document.getElementById('cfgR1Watts').value) || 100;
      const r1ActLow = document.getElementById('cfgR1ActiveLow').checked;

      const r2Name = document.getElementById('cfgR2Name').value;
      const r2Watts = parseFloat(document.getElementById('cfgR2Watts').value) || 100;
      const r2ActLow = document.getElementById('cfgR2ActiveLow').checked;

      try {
        await fetch('/api/settings', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `r1_name=${encodeURIComponent(r1Name)}&r1_watts=${r1Watts}&r1_actlow=${r1ActLow?1:0}&r2_name=${encodeURIComponent(r2Name)}&r2_watts=${r2Watts}&r2_actlow=${r2ActLow?1:0}`
        });
        showToast('Channel settings saved!');
        document.getElementById('settingsModal').classList.remove('open');
        fetchStatus();
      } catch(err) {
        showToast('Failed saving channel settings');
      }
    }

    // Emergency Kill All
    async function killAllRelays() {
      if (confirm('Are you sure you want to turn OFF all relays immediately?')) {
        try {
          const res = await fetch('/api/all_off', { method: 'POST' });
          if (res.ok) {
            showToast('All Relays Forced OFF!');
            fetchStatus();
          }
        } catch(err) {
          showToast('Error triggering Emergency Off');
        }
      }
    }

    function formatSecs(secs) {
      const m = Math.floor(secs / 60);
      const s = secs % 60;
      return `${String(m).padStart(2,'0')}:${String(s).padStart(2,'0')}`;
    }

    function formatHoursMin(totalSecs) {
      const h = Math.floor(totalSecs / 3600);
      const m = Math.floor((totalSecs % 3600) / 60);
      return `${h}h ${m}m`;
    }

    // Status Polling Loop
    async function fetchStatus() {
      try {
        const res = await fetch('/api/status');
        if (!res.ok) return;
        const data = await res.json();

        // Clock & Date
        document.getElementById('liveClock').innerText = data.time.clock;
        document.getElementById('liveDate').innerText = data.time.date + (data.time.synced ? ' (Synced)' : ' (Not Synced)');

        // Relay 1
        const r1 = data.r1;
        document.getElementById('r1Name').innerText = r1.name;
        document.getElementById('r1Switch').checked = r1.state;
        const card1 = document.getElementById('relayCard1');
        const badge1 = document.getElementById('r1Badge');
        if (r1.state) {
          card1.classList.add('active');
          badge1.className = 'relay-badge badge-on';
          badge1.innerText = 'ON';
        } else {
          card1.classList.remove('active');
          badge1.className = 'relay-badge badge-off';
          badge1.innerText = 'OFF';
        }
        
        // R1 Timer
        const tBox1 = document.getElementById('r1TimerLiveBox');
        if (r1.timer.active) {
          tBox1.style.display = 'flex';
          document.getElementById('r1TimerPhase').innerText = r1.timer.in_delay ? 'Delay Phase (Turn ON in):' : 'Active Phase (Turn OFF in):';
          document.getElementById('r1TimerCountdown').innerText = formatSecs(r1.timer.remaining);
          const totalSpan = r1.timer.in_delay ? r1.timer.delay_sec : r1.timer.dur_sec;
          const pct = totalSpan > 0 ? ((totalSpan - r1.timer.remaining) / totalSpan) * 100 : 100;
          document.getElementById('r1TimerProgress').style.width = pct + '%';
        } else {
          tBox1.style.display = 'none';
        }

        // R1 Schedule & Stats
        if (!isModalOpen) {
          document.getElementById('r1SchedEn').checked = r1.schedule.enabled;
          document.getElementById('r1SchedStart').value = `${String(r1.schedule.start_h).padStart(2,'0')}:${String(r1.schedule.start_m).padStart(2,'0')}`;
          document.getElementById('r1SchedEnd').value = `${String(r1.schedule.end_h).padStart(2,'0')}:${String(r1.schedule.end_m).padStart(2,'0')}`;
        }
        document.getElementById('r1TotTime').innerText = formatHoursMin(r1.total_sec);
        const kwh1 = ((r1.total_sec / 3600) * (r1.watts / 1000)).toFixed(3);
        document.getElementById('r1Energy').innerText = `${kwh1} kWh`;

        // Relay 2
        const r2 = data.r2;
        document.getElementById('r2Name').innerText = r2.name;
        document.getElementById('r2Switch').checked = r2.state;
        const card2 = document.getElementById('relayCard2');
        const badge2 = document.getElementById('r2Badge');
        if (r2.state) {
          card2.classList.add('active');
          badge2.className = 'relay-badge badge-on';
          badge2.innerText = 'ON';
        } else {
          card2.classList.remove('active');
          badge2.className = 'relay-badge badge-off';
          badge2.innerText = 'OFF';
        }

        // R2 Timer
        const tBox2 = document.getElementById('r2TimerLiveBox');
        if (r2.timer.active) {
          tBox2.style.display = 'flex';
          document.getElementById('r2TimerPhase').innerText = r2.timer.in_delay ? 'Delay Phase (Turn ON in):' : 'Active Phase (Turn OFF in):';
          document.getElementById('r2TimerCountdown').innerText = formatSecs(r2.timer.remaining);
          const totalSpan = r2.timer.in_delay ? r2.timer.delay_sec : r2.timer.dur_sec;
          const pct = totalSpan > 0 ? ((totalSpan - r2.timer.remaining) / totalSpan) * 100 : 100;
          document.getElementById('r2TimerProgress').style.width = pct + '%';
        } else {
          tBox2.style.display = 'none';
        }

        // R2 Schedule & Stats
        if (!isModalOpen) {
          document.getElementById('r2SchedEn').checked = r2.schedule.enabled;
          document.getElementById('r2SchedStart').value = `${String(r2.schedule.start_h).padStart(2,'0')}:${String(r2.schedule.start_m).padStart(2,'0')}`;
          document.getElementById('r2SchedEnd').value = `${String(r2.schedule.end_h).padStart(2,'0')}:${String(r2.schedule.end_m).padStart(2,'0')}`;
        }
        document.getElementById('r2TotTime').innerText = formatHoursMin(r2.total_sec);
        const kwh2 = ((r2.total_sec / 3600) * (r2.watts / 1000)).toFixed(3);
        document.getElementById('r2Energy').innerText = `${kwh2} kWh`;

        // Low Power Mode
        document.getElementById('lowPowerEnSwitch').checked = data.power.enabled;
        if (data.power.enabled) {
          document.getElementById('lowPowerDesc').innerText = `Low Power Active: Sleeping in ${data.power.next_state_sec}s (Wake every ${data.power.sleep_min}m)`;
        } else {
          document.getElementById('lowPowerDesc').innerText = 'When enabled, turns off Wi-Fi AP after inactivity. AP re-awakens every 15 mins for discovery.';
        }

        // Telemetry
        document.getElementById('telemTemp').innerText = `${data.telem.temp_c.toFixed(1)} °C`;
        document.getElementById('telemHeap').innerText = `${Math.round(data.telem.free_heap / 1024)} KB`;
        const ut_h = Math.floor(data.telem.uptime_sec / 3600);
        const ut_m = Math.floor((data.telem.uptime_sec % 3600) / 60);
        document.getElementById('telemUptime').innerText = `${ut_h}h ${ut_m}m`;
        document.getElementById('telemClients').innerText = data.telem.clients;

        // Auto sync time on first load if not synced yet
        if (!data.time.synced && !window.hasAutoSynced) {
          window.hasAutoSynced = true;
          syncPhoneTime();
        }
      } catch (err) {
        console.error('Polling error:', err);
      }
    }

    // Auto-poll status every 1 second
    setInterval(fetchStatus, 1000);
    fetchStatus();
  </script>
</body>
</html>
)rawliteral";

#endif // WEBPAGES_H
