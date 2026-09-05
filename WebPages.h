#ifndef WEBPAGES_H
#define WEBPAGES_H

#include <Arduino.h>

// =====================================================================
// DEDICATED PORT 500 OTA FIRMWARE UPDATE PORTAL HTML
// =====================================================================
const char OTA_HTML[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>ESP32 OTA Firmware Flashing Station (Port 500)</title>
  <style>
    :root {
      --bg: #0f172a;
      --bg-gradient: radial-gradient(circle at 20% 20%, rgba(0, 229, 255, 0.12) 0%, transparent 50%), radial-gradient(circle at 80% 80%, rgba(59, 130, 246, 0.10) 0%, transparent 50%);
      --card-bg: rgba(30, 41, 59, 0.90);
      --card-inner-bg: #131b2a;
      --card-border: rgba(255, 255, 255, 0.15);
      --primary: #00e5ff;
      --primary-glow: rgba(0, 229, 255, 0.4);
      --success: #00e676;
      --success-glow: rgba(0, 230, 118, 0.4);
      --danger: #ff3366;
      --warning: #ffb703;
      --text: #ffffff;
      --text-sub: #cbd5e1;
      --text-muted: #94a3b8;
      --input-bg: #1e293b;
      --card-radius: 16px;
    }
    * { box-sizing: border-box; margin: 0; padding: 0; font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif; }
    body { background-color: var(--bg); background-image: var(--bg-gradient); color: var(--text); min-height: 100vh; padding: 20px 16px; display: flex; flex-direction: column; align-items: center; justify-content: center; }
    .container { width: 100%; max-width: 520px; display: flex; flex-direction: column; gap: 18px; }
    .card { background: var(--card-bg); backdrop-filter: blur(12px); -webkit-backdrop-filter: blur(12px); border: 1px solid var(--card-border); border-radius: var(--card-radius); padding: 22px; display: flex; flex-direction: column; gap: 16px; box-shadow: 0 10px 35px rgba(0,0,0,0.4); }
    .header-box { display: flex; align-items: center; gap: 12px; }
    .logo-icon { width: 42px; height: 42px; border-radius: 12px; background: linear-gradient(135deg, var(--primary), #3b82f6); display: flex; align-items: center; justify-content: center; font-size: 22px; box-shadow: 0 0 16px var(--primary-glow); }
    .title-box h1 { font-size: 18px; font-weight: 700; color: #fff; }
    .title-box p { font-size: 12px; color: var(--text-sub); }
    .badge { display: inline-flex; align-items: center; gap: 6px; font-family: monospace; font-size: 11px; font-weight: 700; background: rgba(0, 229, 255, 0.15); border: 1px solid var(--primary); color: var(--primary); padding: 4px 10px; border-radius: 8px; width: fit-content; }
    .dropzone { border: 2px dashed rgba(0, 229, 255, 0.4); background: var(--card-inner-bg); border-radius: 14px; padding: 26px 16px; text-align: center; cursor: pointer; transition: all 0.2s; display: flex; flex-direction: column; align-items: center; gap: 8px; }
    .dropzone:hover, .dropzone.dragover { border-color: var(--primary); background: rgba(0, 229, 255, 0.06); transform: scale(1.01); }
    .drop-icon { font-size: 32px; }
    .file-info { display: none; background: var(--card-inner-bg); border: 1px solid var(--card-border); border-radius: 10px; padding: 12px 14px; font-size: 12px; color: #fff; justify-content: space-between; align-items: center; }
    .btn { padding: 12px 20px; border-radius: 10px; font-size: 14px; font-weight: 800; border: none; cursor: pointer; transition: all 0.2s; display: flex; align-items: center; justify-content: center; gap: 8px; }
    .btn:active { transform: scale(0.97); }
    .btn-primary { background: linear-gradient(135deg, var(--primary), #00b0ff); color: #000; box-shadow: 0 4px 16px var(--primary-glow); }
    .btn-primary:disabled { background: #334155; color: #64748b; cursor: not-allowed; box-shadow: none; }
    .btn-secondary { background: rgba(255,255,255,0.08); border: 1px solid var(--card-border); color: #fff; font-size: 12px; text-decoration: none; padding: 10px 16px; border-radius: 10px; display: flex; align-items: center; justify-content: center; gap: 6px; }
    .progress-box { display: none; flex-direction: column; gap: 6px; background: var(--card-inner-bg); border: 1px solid var(--card-border); border-radius: 10px; padding: 12px 14px; }
    .progress-track { width: 100%; height: 10px; background: rgba(255,255,255,0.1); border-radius: 10px; overflow: hidden; }
    .progress-fill { height: 100%; background: linear-gradient(90deg, var(--primary), var(--success)); width: 0%; transition: width 0.2s; }
    .status-msg { display: none; padding: 12px 14px; border-radius: 10px; font-size: 12px; font-weight: 600; line-height: 1.4; }
    .status-success { background: rgba(0, 230, 118, 0.15); border: 1px solid var(--success); color: var(--success); }
    .status-error { background: rgba(255, 51, 102, 0.15); border: 1px solid var(--danger); color: #ff6b8b; }
    .info-card { background: rgba(255, 255, 255, 0.04); border: 1px solid rgba(255, 255, 255, 0.08); border-radius: 10px; padding: 12px 14px; font-size: 11px; color: var(--text-sub); display: flex; flex-direction: column; gap: 4px; line-height: 1.4; }
    .info-card b { color: #fff; }
    .footer { text-align: center; font-size: 11px; color: var(--text-muted); display: flex; flex-direction: column; gap: 4px; }
  </style>
</head>
<body>
  <div class="container">
    <div class="card">
      <div class="header-box">
        <div class="logo-icon">🚀</div>
        <div class="title-box">
          <h1>OTA Firmware Flashing Station</h1>
          <p>ESP32 Dedicated Port 500 Secure Service</p>
        </div>
      </div>

      <div class="badge">🔒 Port 500 Active &bull; Current FW: v2.0.0-OTA</div>

      <input type="file" id="firmwareFile" accept=".bin" style="display:none;" onchange="handleFileSelected(event)">

      <div class="dropzone" id="dropzone" onclick="document.getElementById('firmwareFile').click()">
        <span class="drop-icon">📦</span>
        <div style="font-weight:700; font-size:14px; color:#fff;">Click or Drag & Drop Compiled .bin File</div>
        <div style="font-size:12px; color:var(--text-sub);">Select standard ESP32 binary firmware image (.bin)</div>
      </div>

      <div class="file-info" id="fileInfoBox">
        <span id="fileNameText" style="font-weight:700; overflow:hidden; text-overflow:ellipsis; white-space:nowrap; max-width:70%;">firmware.bin</span>
        <span id="fileSizeText" style="color:var(--primary); font-family:monospace;">0 KB</span>
      </div>

      <div class="progress-box" id="progressContainer">
        <div style="display:flex; justify-content:space-between; font-size:12px;">
          <span id="progressStatusText" style="color:var(--primary); font-weight:700;">Uploading firmware...</span>
          <span id="progressPctText" style="font-weight:800; font-family:monospace; color:var(--primary);">0%</span>
        </div>
        <div class="progress-track">
          <div class="progress-fill" id="progressBar"></div>
        </div>
      </div>

      <div class="status-msg" id="statusBox"></div>

      <button class="btn btn-primary" id="uploadBtn" onclick="uploadFirmware()" disabled>⚡ Flash Firmware to ESP32</button>

      <div class="info-card">
        <div>💡 <b>LED Status Indicator Rules:</b></div>
        <div>• <b>Blue LED Blinks 5 Times:</b> Update Success! System will auto-restart.</div>
        <div>• <b>Blue LED Blinks 3 Times:</b> Update Failed. Check compiled binary.</div>
      </div>

      <a href="http://192.168.4.1/" class="btn btn-secondary">⬅️ Return to Main Web Control (Port 80)</a>
    </div>

    <div class="footer">
      <span>ESP32 Real-Time Dual Relay Controller</span>
      <span>OTA Server running on Port 500</span>
    </div>
  </div>

  <script>
    let selectedFile = null;
    const dropzone = document.getElementById('dropzone');
    const fileInput = document.getElementById('firmwareFile');
    const uploadBtn = document.getElementById('uploadBtn');

    dropzone.addEventListener('dragover', (e) => { e.preventDefault(); dropzone.classList.add('dragover'); });
    dropzone.addEventListener('dragleave', () => dropzone.classList.remove('dragover'));
    dropzone.addEventListener('drop', (e) => {
      e.preventDefault();
      dropzone.classList.remove('dragover');
      if (e.dataTransfer.files.length > 0) {
        selectFile(e.dataTransfer.files[0]);
      }
    });

    function handleFileSelected(e) {
      if (e.target.files.length > 0) {
        selectFile(e.target.files[0]);
      }
    }

    function selectFile(file) {
      if (!file.name.endsWith('.bin')) {
        alert('Please select a compiled ESP32 .bin file.');
        return;
      }
      selectedFile = file;
      document.getElementById('fileNameText').innerText = file.name;
      document.getElementById('fileSizeText').innerText = (file.size / 1024).toFixed(1) + ' KB';
      document.getElementById('fileInfoBox').style.display = 'flex';
      uploadBtn.disabled = false;
    }

    function uploadFirmware() {
      if (!selectedFile) return;
      uploadBtn.disabled = true;
      dropzone.style.pointerEvents = 'none';

      const progressBox = document.getElementById('progressContainer');
      const progressBar = document.getElementById('progressBar');
      const progressStatus = document.getElementById('progressStatusText');
      const progressPct = document.getElementById('progressPctText');
      const statusBox = document.getElementById('statusBox');

      progressBox.style.display = 'flex';
      statusBox.style.display = 'none';
      progressBar.style.width = '0%';
      progressPct.innerText = '0%';
      progressStatus.innerText = 'Uploading firmware to OTA partition...';

      const xhr = new XMLHttpRequest();
      const formData = new FormData();
      formData.append('update', selectedFile, selectedFile.name);

      xhr.upload.addEventListener('progress', (e) => {
        if (e.lengthComputable) {
          const pct = Math.round((e.loaded / e.total) * 100);
          progressBar.style.width = pct + '%';
          progressPct.innerText = pct + '%';
          if (pct === 100) {
            progressStatus.innerText = 'Flashing Flash Partition & Validating CRC...';
          }
        }
      });

      xhr.onreadystatechange = function() {
        if (xhr.readyState === 4) {
          if (xhr.status === 200) {
            statusBox.className = 'status-msg status-success';
            statusBox.innerHTML = '🎉 <b>OTA Update Success!</b><br>Blue LED is blinking <b>5 times</b>.<br>Device is restarting with new firmware in 3 seconds...';
            statusBox.style.display = 'block';
            progressStatus.innerText = 'Flashing Complete!';
            setTimeout(() => { window.location.href = 'http://192.168.4.1/'; }, 4500);
          } else {
            statusBox.className = 'status-msg status-error';
            statusBox.innerHTML = '❌ <b>OTA Update Failed!</b><br>Blue LED is blinking <b>3 times</b>.<br>Error: ' + (xhr.responseText || 'Verification failed. Please retry.');
            statusBox.style.display = 'block';
            uploadBtn.disabled = false;
            dropzone.style.pointerEvents = 'auto';
            progressStatus.innerText = 'Flash Error!';
          }
        }
      };

      xhr.onerror = function() {
        statusBox.className = 'status-msg status-error';
        statusBox.innerHTML = '❌ <b>Network/Upload Error!</b><br>Blue LED blinking 3 times on failure. Check connection.';
        statusBox.style.display = 'block';
        uploadBtn.disabled = false;
        dropzone.style.pointerEvents = 'auto';
      };

      xhr.open('POST', '/update', true);
      xhr.send(formData);
    }
  </script>
</body>
</html>
)rawliteral";

// =====================================================================
// MAIN WEB DASHBOARD UI (PORT 80)
// =====================================================================
const char INDEX_HTML[] PROGMEM = R"rawliteral(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>ESP32 Real-Time OS Dual Relay Controller</title>
  <style>
    :root {
      --bg: #141824;
      --bg-gradient: radial-gradient(circle at 15% 20%, rgba(0, 229, 255, 0.08) 0%, transparent 45%), radial-gradient(circle at 85% 80%, rgba(0, 230, 118, 0.07) 0%, transparent 45%);
      --card-bg: rgba(30, 41, 59, 0.88);
      --card-inner-bg: #192233;
      --card-border: rgba(255, 255, 255, 0.16);
      --primary: #00e5ff;
      --primary-glow: rgba(0, 229, 255, 0.4);
      --success: #00e676;
      --success-glow: rgba(0, 230, 118, 0.4);
      --danger: #ff3366;
      --danger-glow: rgba(255, 51, 102, 0.4);
      --warning: #ffb703;
      --text: #ffffff;
      --text-sub: #cbd5e1;
      --text-muted: #94a3b8;
      --input-bg: #131b29;
      --card-radius: 16px;
    }
    * { box-sizing: border-box; margin: 0; padding: 0; font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif; }
    body { background-color: var(--bg); background-image: var(--bg-gradient); color: var(--text); min-height: 100vh; padding: 16px; display: flex; flex-direction: column; align-items: center; }
    .container { width: 100%; max-width: 620px; display: flex; flex-direction: column; gap: 16px; }
    
    /* Header */
    header { background: var(--card-bg); backdrop-filter: blur(12px); -webkit-backdrop-filter: blur(12px); border: 1px solid var(--card-border); border-radius: var(--card-radius); padding: 16px 20px; display: flex; justify-content: space-between; align-items: center; box-shadow: 0 8px 30px rgba(0,0,0,0.35); }
    .logo-area { display: flex; align-items: center; gap: 12px; }
    .logo-icon { width: 38px; height: 38px; border-radius: 10px; background: linear-gradient(135deg, var(--primary), #3b82f6); display: flex; align-items: center; justify-content: center; font-weight: 800; font-size: 20px; color: #000; box-shadow: 0 0 16px var(--primary-glow); }
    .title-box h1 { font-size: 18px; font-weight: 700; color: #fff; letter-spacing: -0.2px; }
    .title-box p { font-size: 12px; color: var(--text-sub); }
    .header-actions { display: flex; gap: 8px; align-items: center; }
    .btn-icon { background: rgba(255,255,255,0.1); border: 1px solid var(--card-border); color: #fff; width: 40px; height: 40px; border-radius: 10px; cursor: pointer; display: flex; align-items: center; justify-content: center; font-size: 18px; transition: all 0.2s; }
    .btn-icon:active { transform: scale(0.92); }

    /* Time & Status Bar */
    .status-bar { background: var(--card-bg); backdrop-filter: blur(12px); border: 1px solid var(--card-border); border-radius: 12px; padding: 12px 16px; display: flex; justify-content: space-between; align-items: center; font-size: 13px; box-shadow: 0 4px 16px rgba(0,0,0,0.25); }
    .time-display { display: flex; align-items: center; gap: 8px; font-weight: 700; color: var(--primary); font-size: 14px; }
    .sync-btn { background: rgba(0, 229, 255, 0.2); border: 1px solid var(--primary); color: var(--primary); padding: 6px 14px; border-radius: 8px; font-size: 12px; font-weight: 700; cursor: pointer; transition: all 0.2s; }
    .sync-btn:active { background: var(--primary); color: #000; }

    /* Permanent Stay-On Banner Box */
    .stayon-box { background: linear-gradient(135deg, rgba(0, 229, 255, 0.12), rgba(59, 130, 246, 0.12)); border: 1px solid rgba(0, 229, 255, 0.35); border-radius: 14px; padding: 14px 16px; display: flex; justify-content: space-between; align-items: center; box-shadow: 0 4px 16px rgba(0,0,0,0.2); }
    .stayon-info { display: flex; flex-direction: column; gap: 3px; max-width: 80%; }
    .stayon-title { font-size: 14px; font-weight: 700; color: #fff; display: flex; align-items: center; gap: 6px; }
    .stayon-sub { font-size: 11px; color: var(--text-sub); line-height: 1.3; }

    /* Total Energy Consumption Summary Card */
    .energy-total-card { background: linear-gradient(135deg, rgba(0, 230, 118, 0.10), rgba(0, 229, 255, 0.08)); border: 1px solid rgba(0, 230, 118, 0.38); border-radius: 14px; padding: 14px 16px; display: flex; flex-direction: column; gap: 10px; box-shadow: 0 4px 20px rgba(0,0,0,0.25); }
    .energy-total-header { display: flex; justify-content: space-between; align-items: center; }
    .energy-title { font-size: 14px; font-weight: 700; color: #fff; display: flex; align-items: center; gap: 6px; }
    .energy-val-badge { font-family: monospace; font-size: 16px; font-weight: 800; color: var(--success); background: rgba(0, 230, 118, 0.18); border: 1px solid var(--success); padding: 3px 10px; border-radius: 8px; box-shadow: 0 0 12px var(--success-glow); }
    .energy-subgrid { display: grid; grid-template-columns: 1fr 1fr; gap: 8px; }
    .energy-subitem { background: var(--card-inner-bg); border: 1px solid var(--card-border); border-radius: 8px; padding: 8px 10px; display: flex; flex-direction: column; gap: 2px; }
    .energy-subtitle { font-size: 10px; color: var(--text-sub); font-weight: 600; }
    .energy-subval { font-size: 13px; font-weight: 700; color: #fff; }

    /* Relay Card */
    .relay-card { background: var(--card-bg); backdrop-filter: blur(12px); border: 1px solid var(--card-border); border-radius: var(--card-radius); padding: 18px; display: flex; flex-direction: column; gap: 14px; position: relative; overflow: hidden; box-shadow: 0 8px 24px rgba(0,0,0,0.3); transition: border-color 0.3s; }
    .relay-card.active { border-color: rgba(0, 230, 118, 0.6); box-shadow: 0 0 25px rgba(0, 230, 118, 0.25); }
    .relay-card.active::before { content:''; position: absolute; top: 0; left: 0; width: 5px; height: 100%; background: var(--success); }

    .relay-header { display: flex; justify-content: space-between; align-items: center; }
    .relay-title { font-size: 17px; font-weight: 700; display: flex; align-items: center; gap: 8px; color: #fff; }
    .relay-badge { font-size: 11px; padding: 4px 10px; border-radius: 20px; font-weight: 800; letter-spacing: 0.5px; text-transform: uppercase; }
    .badge-off { background: rgba(255,255,255,0.12); color: var(--text-sub); border: 1px solid rgba(255,255,255,0.15); }
    .badge-on { background: var(--success); color: #000; box-shadow: 0 0 12px var(--success-glow); }

    /* Main Toggle Switch */
    .switch-row { display: flex; justify-content: space-between; align-items: center; background: var(--card-inner-bg); border: 1px solid var(--card-border); padding: 12px 16px; border-radius: 12px; }
    .switch-label { font-size: 14px; font-weight: 600; color: #fff; }
    .toggle-switch { position: relative; width: 56px; height: 30px; display: inline-block; }
    .toggle-switch input { opacity: 0; width: 0; height: 0; }
    .slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: #475569; transition: .3s; border-radius: 30px; }
    .slider:before { position: absolute; content: ""; height: 22px; width: 22px; left: 4px; bottom: 4px; background-color: white; transition: .3s; border-radius: 50%; }
    input:checked + .slider { background-color: var(--success); box-shadow: 0 0 14px var(--success-glow); }
    input:checked + .slider:before { transform: translateX(26px); }

    /* Inching / Quick Pulse Action (Commented out) */
    /*
    .pulse-row { display: flex; align-items: center; justify-content: space-between; gap: 8px; background: rgba(255,255,255,0.04); border: 1px dashed var(--card-border); padding: 8px 12px; border-radius: 10px; }
    .pulse-btn { background: rgba(0, 229, 255, 0.15); border: 1px solid var(--primary); color: #fff; font-size: 11px; font-weight: 700; padding: 6px 12px; border-radius: 6px; cursor: pointer; transition: all 0.2s; }
    .pulse-btn:active { background: var(--primary); color: #000; }
    */

    /* Tabs inside Relay */
    .tab-nav { display: flex; gap: 6px; background: var(--card-inner-bg); border: 1px solid var(--card-border); padding: 4px; border-radius: 10px; }
    .tab-btn { flex: 1; padding: 8px 0; background: transparent; border: none; color: var(--text-sub); font-size: 12px; font-weight: 600; border-radius: 7px; cursor: pointer; transition: all 0.2s; }
    .tab-btn.active { background: rgba(255,255,255,0.18); color: #ffffff; font-weight: 700; }
    .tab-pane { display: none; flex-direction: column; gap: 12px; padding-top: 4px; }
    .tab-pane.active { display: flex; }

    /* Inputs & Forms */
    .form-group { display: flex; flex-direction: column; gap: 6px; }
    .form-label { font-size: 12px; color: var(--text-sub); font-weight: 600; }
    .input-row { display: flex; gap: 8px; }
    .input-box { flex: 1; background: var(--input-bg); border: 1px solid #3b4861; color: #fff; padding: 10px 12px; border-radius: 8px; font-size: 13px; outline: none; }
    .input-box:focus { border-color: var(--primary); box-shadow: 0 0 8px var(--primary-glow); }

    /* Weekday Selection Bar */
    .weekday-bar { display: flex; gap: 4px; justify-content: space-between; margin-top: 4px; }
    .day-btn { flex: 1; padding: 7px 0; font-size: 11px; font-weight: 700; background: var(--input-bg); border: 1px solid #3b4861; color: var(--text-sub); border-radius: 6px; cursor: pointer; text-align: center; transition: all 0.2s; user-select: none; }
    .day-btn.selected { background: linear-gradient(135deg, var(--primary), #00b0ff); color: #000; border-color: var(--primary); box-shadow: 0 0 10px var(--primary-glow); }
    .day-presets { display: flex; gap: 6px; }
    .preset-btn { font-size: 10px; font-weight: 700; background: rgba(255,255,255,0.06); border: 1px solid var(--card-border); color: var(--text-sub); padding: 3px 8px; border-radius: 4px; cursor: pointer; }
    .preset-btn:active { background: rgba(255,255,255,0.18); color: #fff; }

    /* Action Buttons */
    .btn { padding: 10px 16px; border-radius: 8px; font-size: 13px; font-weight: 700; border: none; cursor: pointer; transition: all 0.2s; display: flex; align-items: center; justify-content: center; gap: 6px; }
    .btn:active { transform: scale(0.96); }
    .btn-primary { background: linear-gradient(135deg, var(--primary), #00b0ff); color: #000; font-weight: 800; box-shadow: 0 4px 15px var(--primary-glow); }
    .btn-danger { background: rgba(255, 51, 102, 0.2); border: 1px solid var(--danger); color: #fff; font-weight: 700; }
    .btn-danger:active { background: var(--danger); color: #fff; }
    .btn-success { background: var(--success); color: #000; font-weight: 800; }

    /* Live Progress Box */
    .live-prog-box { background: rgba(0, 229, 255, 0.1); border: 1px solid rgba(0, 229, 255, 0.3); border-radius: 10px; padding: 12px 14px; display: flex; flex-direction: column; gap: 8px; }
    .live-prog-header { display: flex; justify-content: space-between; font-size: 13px; font-weight: 600; }
    .live-prog-val { font-family: monospace; font-size: 16px; font-weight: 800; color: var(--primary); }
    .progress-track { width: 100%; height: 8px; background: rgba(255,255,255,0.15); border-radius: 10px; overflow: hidden; }
    .progress-fill { height: 100%; background: linear-gradient(90deg, var(--primary), var(--success)); width: 0%; transition: width 0.5s ease; }

    /* Stats Grid */
    .stats-row { display: grid; grid-template-columns: 1fr 1fr; gap: 8px; font-size: 12px; }
    .stat-item { background: var(--card-inner-bg); border: 1px solid var(--card-border); padding: 10px 12px; border-radius: 8px; display: flex; flex-direction: column; gap: 4px; }
    .stat-val { font-weight: 800; font-size: 14px; color: var(--primary); }

    /* Telemetry & RTOS Core Diagnostics */
    .telemetry-card { background: var(--card-bg); backdrop-filter: blur(12px); border: 1px solid var(--card-border); border-radius: var(--card-radius); padding: 16px; display: flex; flex-direction: column; gap: 12px; box-shadow: 0 8px 24px rgba(0,0,0,0.3); }
    .telemetry-grid { display: grid; grid-template-columns: repeat(2, 1fr); gap: 10px; }
    .telem-box { background: var(--card-inner-bg); border: 1px solid var(--card-border); border-radius: 10px; padding: 10px 12px; display: flex; flex-direction: column; gap: 4px; }
    .telem-title { font-size: 11px; color: var(--text-sub); font-weight: 600; }
    .telem-val { font-size: 15px; font-weight: 800; color: #fff; }

    /* Real-Time Live Activity Event Log Console */
    .event-log-box { background: #0e131d; border: 1px solid var(--card-border); border-radius: 10px; padding: 10px 12px; font-family: monospace; font-size: 11px; max-height: 140px; overflow-y: auto; display: flex; flex-direction: column; gap: 4px; }
    .event-entry { display: flex; gap: 8px; color: #cbd5e1; border-bottom: 1px solid rgba(255,255,255,0.05); padding: 2px 0; }
    .event-time { color: var(--primary); font-weight: 700; min-width: 75px; }

    .master-btn { width: 100%; background: linear-gradient(135deg, #e11d48, #ff1744); color: #fff; font-size: 14px; font-weight: 800; padding: 13px; border-radius: 12px; border: none; cursor: pointer; box-shadow: 0 4px 20px var(--danger-glow); transition: transform 0.2s; }
    .master-btn:active { transform: scale(0.97); }

    /* Modal */
    .modal-overlay { position: fixed; top: 0; left: 0; width: 100%; height: 100%; background: rgba(0,0,0,0.75); backdrop-filter: blur(8px); display: none; align-items: center; justify-content: center; z-index: 100; padding: 16px; }
    .modal-overlay.open { display: flex; }
    .modal { background: #1a2233; border: 1px solid var(--card-border); border-radius: var(--card-radius); width: 100%; max-width: 500px; max-height: 90vh; overflow-y: auto; padding: 20px; display: flex; flex-direction: column; gap: 16px; box-shadow: 0 16px 40px rgba(0,0,0,0.6); }
    .modal-header { display: flex; justify-content: space-between; align-items: center; border-bottom: 1px solid var(--card-border); padding-bottom: 12px; }
    .modal-title { font-size: 16px; font-weight: 700; color: #fff; }
    .close-btn { background: transparent; border: none; color: var(--text-sub); font-size: 24px; cursor: pointer; }

    /* Footer */
    .footer-card { background: var(--card-bg); backdrop-filter: blur(12px); -webkit-backdrop-filter: blur(12px); border: 1px solid var(--card-border); border-radius: var(--card-radius); padding: 14px 18px; display: flex; flex-direction: column; gap: 8px; box-shadow: 0 4px 20px rgba(0,0,0,0.25); margin-top: 4px; }
    .footer-top { display: flex; justify-content: space-between; align-items: center; flex-wrap: wrap; gap: 8px; }
    .footer-brand { display: flex; align-items: center; gap: 10px; }
    .footer-icon { font-size: 20px; color: var(--primary); }
    .footer-title { font-size: 13px; font-weight: 700; color: #fff; }
    .footer-pins { font-size: 11px; color: var(--text-sub); }
    .footer-pins b { color: var(--primary); }
    .footer-badges { display: flex; gap: 6px; align-items: center; }
    .version-badge { font-family: monospace; font-size: 11px; font-weight: 700; background: rgba(0, 229, 255, 0.15); border: 1px solid var(--primary); color: var(--primary); padding: 3px 8px; border-radius: 6px; }
    .port500-badge { font-family: monospace; font-size: 11px; font-weight: 700; padding: 3px 8px; border-radius: 6px; }
    .port500-badge.enabled { background: rgba(0, 230, 118, 0.2); border: 1px solid var(--success); color: var(--success); }
    .port500-badge.disabled { background: rgba(255, 255, 255, 0.08); border: 1px solid rgba(255, 255, 255, 0.2); color: var(--text-muted); }
    .footer-bottom { display: flex; justify-content: space-between; align-items: center; border-top: 1px solid rgba(255,255,255,0.06); padding-top: 8px; font-size: 11px; color: var(--text-muted); }

    /* Toast Notification */
    #toast { position: fixed; bottom: 24px; left: 50%; transform: translateX(-50%) translateY(100px); background: #1e293b; border: 1px solid var(--primary); color: #fff; padding: 12px 24px; border-radius: 30px; font-size: 13px; font-weight: 700; box-shadow: 0 10px 30px rgba(0,0,0,0.5); opacity: 0; transition: all 0.3s ease; z-index: 200; pointer-events: none; }
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
          <h1>ESP32 Real-Time Dual Relay</h1>
          <p>Real-Time OS Multi-Tasking & Power Control</p>
        </div>
      </div>
      <div class="header-actions">
        <button class="btn-icon" id="openSettingsBtn" title="System Settings">⚙️</button>
      </div>
    </header>

    <!-- Time & Status Bar -->
    <div class="status-bar">
      <div class="time-display">
        <span>🕒</span>
        <span id="liveClock">--:--:-- --</span>
        <span id="liveDate" style="color:var(--text-sub); font-size:12px; font-weight:normal;">(Not Synced)</span>
      </div>
      <button class="sync-btn" id="phoneSyncBtn" title="Sync time with phone">📱 Sync Phone</button>
    </div>

    <!-- Permanent Stay-On System Banner Box -->
    <div class="stayon-box">
      <div class="stayon-info">
        <span class="stayon-title">⚡ Permanent Always-On Mode</span>
        <span class="stayon-sub" id="stayOnStatusText">Disable AP auto-sleep. Runs 24/7 permanently stored in Flash.</span>
      </div>
      <label class="toggle-switch">
        <input type="checkbox" id="permanentStayOnSwitch" onchange="togglePermanentStayOn(this.checked)">
        <span class="slider"></span>
      </label>
    </div>

    <!-- Total Energy Consumption Card -->
    <div class="energy-total-card">
      <div class="energy-total-header">
        <div class="energy-title">
          <span>⚡ Total Energy Consumed</span>
        </div>
        <span class="energy-val-badge" id="totalKwhBadge">0.000 kWh</span>
      </div>
      <div class="energy-subgrid">
        <div class="energy-subitem">
          <span class="energy-subtitle">Total Runtime (All Relays)</span>
          <span class="energy-subval" id="totalRuntimeVal">0h 0m</span>
        </div>
        <div class="energy-subitem">
          <span class="energy-subtitle">Live Connected Power</span>
          <span class="energy-subval" id="totalLiveWattsVal" style="color:var(--success);">0.0 W</span>
        </div>
      </div>
    </div>

    <!-- Relay 1 Card -->
    <div class="relay-card" id="relayCard1">
      <div class="relay-header">
        <div class="relay-title">
          <span id="r1Name">Relay 1 (D2)</span>
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
      <div class="live-prog-box" id="r1TimerLiveBox" style="display:none;">
        <div class="live-prog-header">
          <span id="r1TimerPhase">Timer: Active</span>
          <span class="live-prog-val" id="r1TimerCountdown">00:00</span>
        </div>
        <div class="progress-track">
          <div class="progress-fill" id="r1TimerProgress"></div>
        </div>
        <button class="btn btn-danger" style="padding:5px 10px; font-size:11px; margin-top:2px;" onclick="cancelTimer(1)">Cancel Countdown</button>
      </div>

      <!-- Live Cycle Info (Shown if active) -->
      <div class="live-prog-box" id="r1CycleLiveBox" style="display:none; background:rgba(0, 230, 118, 0.1); border-color:rgba(0,230,118,0.3);">
        <div class="live-prog-header">
          <span id="r1CyclePhase">🔁 Cycle Running</span>
          <span class="live-prog-val" id="r1CycleCountdown" style="color:var(--success);">00:00</span>
        </div>
        <div class="progress-track">
          <div class="progress-fill" id="r1CycleProgress"></div>
        </div>
        <button class="btn btn-danger" style="padding:5px 10px; font-size:11px; margin-top:2px;" onclick="cancelCycle(1)">Stop Cycle Loop</button>
      </div>

      <!-- Tabs for Timers, Cycles & Schedules -->
      <div class="tab-nav">
        <button class="tab-btn active" onclick="switchTab(1, 'timer')">⏱️ Timer</button>
        <button class="tab-btn" onclick="switchTab(1, 'cycle')">🔁 Cycle</button>
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

      <!-- Tab: Cyclic Automation -->
      <div class="tab-pane" id="r1TabCycle">
        <div class="form-group">
          <label class="form-label">ON Time per Cycle (Secs/Mins):</label>
          <div class="input-row">
            <input type="number" class="input-box" id="r1CycOnMin" placeholder="Mins" min="0" value="0">
            <input type="number" class="input-box" id="r1CycOnSec" placeholder="Secs" min="1" value="30">
          </div>
        </div>
        <div class="form-group">
          <label class="form-label">OFF Time per Cycle (Secs/Mins):</label>
          <div class="input-row">
            <input type="number" class="input-box" id="r1CycOffMin" placeholder="Mins" min="0" value="0">
            <input type="number" class="input-box" id="r1CycOffSec" placeholder="Secs" min="1" value="30">
          </div>
        </div>
        <div class="form-group">
          <label class="form-label">Total Cycles (0 = Infinite Loop):</label>
          <input type="number" class="input-box" id="r1CycTotal" placeholder="0 = Continuous Infinite Loop" min="0" value="0">
        </div>
        <button class="btn btn-primary" onclick="setCycle(1)">Start Cycle Automation</button>
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
        <div class="form-group">
          <div style="display:flex; justify-content:space-between; align-items:center;">
            <label class="form-label">Active Weekdays:</label>
            <div class="day-presets">
              <button type="button" class="preset-btn" onclick="selectDayPreset(1, 'all')">All</button>
              <button type="button" class="preset-btn" onclick="selectDayPreset(1, 'weekdays')">Mon-Fri</button>
              <button type="button" class="preset-btn" onclick="selectDayPreset(1, 'weekends')">Sat-Sun</button>
            </div>
          </div>
          <div class="weekday-bar" id="r1WeekdayBar">
            <div class="day-btn selected" data-day="0" onclick="toggleDay(1, 0)">Sun</div>
            <div class="day-btn selected" data-day="1" onclick="toggleDay(1, 1)">Mon</div>
            <div class="day-btn selected" data-day="2" onclick="toggleDay(1, 2)">Tue</div>
            <div class="day-btn selected" data-day="3" onclick="toggleDay(1, 3)">Wed</div>
            <div class="day-btn selected" data-day="4" onclick="toggleDay(1, 4)">Thu</div>
            <div class="day-btn selected" data-day="5" onclick="toggleDay(1, 5)">Fri</div>
            <div class="day-btn selected" data-day="6" onclick="toggleDay(1, 6)">Sat</div>
          </div>
        </div>
        <div class="input-row" style="align-items:center; justify-content:space-between; margin-top:4px;">
          <span style="font-size:12px; color:var(--text-sub); font-weight:600;">Enable Daily Schedule</span>
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
            <span class="telem-title">Total ON Runtime</span>
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
          <span id="r2Name">Relay 2 (D4)</span>
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
      <div class="live-prog-box" id="r2TimerLiveBox" style="display:none;">
        <div class="live-prog-header">
          <span id="r2TimerPhase">Timer: Active</span>
          <span class="live-prog-val" id="r2TimerCountdown">00:00</span>
        </div>
        <div class="progress-track">
          <div class="progress-fill" id="r2TimerProgress"></div>
        </div>
        <button class="btn btn-danger" style="padding:5px 10px; font-size:11px; margin-top:2px;" onclick="cancelTimer(2)">Cancel Countdown</button>
      </div>

      <!-- Live Cycle Info (Shown if active) -->
      <div class="live-prog-box" id="r2CycleLiveBox" style="display:none; background:rgba(0, 230, 118, 0.1); border-color:rgba(0,230,118,0.3);">
        <div class="live-prog-header">
          <span id="r2CyclePhase">🔁 Cycle Running</span>
          <span class="live-prog-val" id="r2CycleCountdown" style="color:var(--success);">00:00</span>
        </div>
        <div class="progress-track">
          <div class="progress-fill" id="r2CycleProgress"></div>
        </div>
        <button class="btn btn-danger" style="padding:5px 10px; font-size:11px; margin-top:2px;" onclick="cancelCycle(2)">Stop Cycle Loop</button>
      </div>

      <!-- Tabs for Timers, Cycles & Schedules -->
      <div class="tab-nav">
        <button class="tab-btn active" onclick="switchTab(2, 'timer')">⏱️ Timer</button>
        <button class="tab-btn" onclick="switchTab(2, 'cycle')">🔁 Cycle</button>
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

      <!-- Tab: Cyclic Automation -->
      <div class="tab-pane" id="r2TabCycle">
        <div class="form-group">
          <label class="form-label">ON Time per Cycle (Secs/Mins):</label>
          <div class="input-row">
            <input type="number" class="input-box" id="r2CycOnMin" placeholder="Mins" min="0" value="0">
            <input type="number" class="input-box" id="r2CycOnSec" placeholder="Secs" min="1" value="30">
          </div>
        </div>
        <div class="form-group">
          <label class="form-label">OFF Time per Cycle (Secs/Mins):</label>
          <div class="input-row">
            <input type="number" class="input-box" id="r2CycOffMin" placeholder="Mins" min="0" value="0">
            <input type="number" class="input-box" id="r2CycOffSec" placeholder="Secs" min="1" value="30">
          </div>
        </div>
        <div class="form-group">
          <label class="form-label">Total Cycles (0 = Infinite Loop):</label>
          <input type="number" class="input-box" id="r2CycTotal" placeholder="0 = Continuous Infinite Loop" min="0" value="0">
        </div>
        <button class="btn btn-primary" onclick="setCycle(2)">Start Cycle Automation</button>
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
        <div class="form-group">
          <div style="display:flex; justify-content:space-between; align-items:center;">
            <label class="form-label">Active Weekdays:</label>
            <div class="day-presets">
              <button type="button" class="preset-btn" onclick="selectDayPreset(2, 'all')">All</button>
              <button type="button" class="preset-btn" onclick="selectDayPreset(2, 'weekdays')">Mon-Fri</button>
              <button type="button" class="preset-btn" onclick="selectDayPreset(2, 'weekends')">Sat-Sun</button>
            </div>
          </div>
          <div class="weekday-bar" id="r2WeekdayBar">
            <div class="day-btn selected" data-day="0" onclick="toggleDay(2, 0)">Sun</div>
            <div class="day-btn selected" data-day="1" onclick="toggleDay(2, 1)">Mon</div>
            <div class="day-btn selected" data-day="2" onclick="toggleDay(2, 2)">Tue</div>
            <div class="day-btn selected" data-day="3" onclick="toggleDay(2, 3)">Wed</div>
            <div class="day-btn selected" data-day="4" onclick="toggleDay(2, 4)">Thu</div>
            <div class="day-btn selected" data-day="5" onclick="toggleDay(2, 5)">Fri</div>
            <div class="day-btn selected" data-day="6" onclick="toggleDay(2, 6)">Sat</div>
          </div>
        </div>
        <div class="input-row" style="align-items:center; justify-content:space-between; margin-top:4px;">
          <span style="font-size:12px; color:var(--text-sub); font-weight:600;">Enable Daily Schedule</span>
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
            <span class="telem-title">Total ON Runtime</span>
            <span class="stat-val" id="r2TotTime">0h 0m</span>
          </div>
          <div class="stat-item">
            <span class="telem-title">Est. Energy Consumed</span>
            <span class="stat-val" id="r2Energy">0.000 kWh</span>
          </div>
        </div>
      </div>
    </div>

    <!-- Power Saver & RTOS Telemetry -->
    <div class="telemetry-card">
      <div style="display:flex; justify-content:space-between; align-items:center;">
        <span style="font-weight:700; font-size:14px; color:#fff;">🔋 Auto-Sleep Power Saver</span>
        <label class="toggle-switch">
          <input type="checkbox" id="lowPowerEnSwitch" onchange="toggleLowPower(this.checked)">
          <span class="slider"></span>
        </label>
      </div>
      <div style="font-size:12px; color:var(--text-sub);" id="lowPowerDesc">
        When enabled, turns off Wi-Fi AP after inactivity. AP re-awakens every 5 mins for discovery.
      </div>
      
      <div class="telemetry-grid" style="margin-top:4px;">
        <div class="telem-box">
          <span class="telem-title">ESP32 Chip Temp</span>
          <span class="telem-val" id="telemTemp">-- °C</span>
        </div>
        <div class="telem-box">
          <span class="telem-title">Free Heap Memory</span>
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
        <div class="telem-box">
          <span class="telem-title">Core 1 RTOS Ticks</span>
          <span class="telem-val" id="telemRelayTicks" style="color:var(--primary);">--</span>
        </div>
        <div class="telem-box">
          <span class="telem-title">Core 0 RTOS Ticks</span>
          <span class="telem-val" id="telemPowerTicks" style="color:var(--success);">--</span>
        </div>
      </div>

      <!-- Real-Time Activity Log -->
      <div style="display:flex; flex-direction:column; gap:6px; margin-top:6px;">
        <span style="font-size:12px; font-weight:700; color:var(--text-sub);">📜 Real-Time System Event Stream:</span>
        <div class="event-log-box" id="eventLogContainer">
          <div class="event-entry"><span class="event-time">--:--:--</span><span>Connecting to Real-Time OS...</span></div>
        </div>
      </div>

      <!-- Master Emergency Kill Switch -->
      <button class="master-btn" onclick="killAllRelays()">🚨 EMERGENCY ALL OFF</button>
    </div>

    <!-- System Footer with Firmware Version & Pin Mapping -->
    <footer class="footer-card">
      <div class="footer-top">
        <div class="footer-brand">
          <span class="footer-icon">⚡</span>
          <div>
            <div class="footer-title">ESP32 RTOS Control System</div>
            <div class="footer-pins">Relay 1: <b>D2 (GPIO 2)</b> &bull; Relay 2: <b>D4 (GPIO 4)</b></div>
          </div>
        </div>
        <div class="footer-badges">
          <span class="version-badge" id="footerFwVer">FW: v2.0.0-OTA</span>
          <span class="port500-badge disabled" id="footerPort500Status">Port 500: OFF</span>
        </div>
      </div>
      <div class="footer-bottom">
        <span>Dual-Core FreeRTOS &bull; Standalone AP Server</span>
        <span id="footerOtaHint">OTA Firmware Flasher Ready</span>
      </div>
    </footer>
  </div>

  <!-- Settings Modal -->
  <div class="modal-overlay" id="settingsModal">
    <div class="modal">
      <div class="modal-header">
        <div class="modal-title">⚙️ System & Power Settings</div>
        <button class="close-btn" id="closeSettingsBtn">&times;</button>
      </div>

      <!-- Permanent Stay-On Preference -->
      <div class="form-group">
        <label class="form-label" style="font-weight:700; color:var(--primary);">⚡ Permanent Always-On Setting</label>
        <label style="display:flex; align-items:center; gap:10px; font-size:13px; color:#fff; cursor:pointer;">
          <input type="checkbox" id="modalPermanentStayOn" style="width:18px; height:18px;">
          <span>Keep AP & System running permanently (Disable sleep)</span>
        </label>
        <span style="font-size:11px; color:var(--text-sub);">When checked, AP auto-sleep is disabled permanently in device Flash memory across power restarts.</span>
      </div>

      <!-- Manual Time Setting -->
      <div class="form-group" style="border-top:1px solid var(--card-border); padding-top:12px;">
        <label class="form-label" style="font-weight:700; color:var(--primary);">🕒 Manual Date & Time Adjustment</label>
        <input type="datetime-local" class="input-box" id="manualDateTimeInput">
        <button class="btn btn-primary" style="margin-top:6px;" onclick="saveManualTime()">Set ESP32 Time</button>
      </div>

      <!-- Low Power Settings -->
      <div class="form-group" style="border-top:1px solid var(--card-border); padding-top:12px;">
        <label class="form-label" style="font-weight:700; color:var(--warning);">🔋 Power Saver Sleep Duty Cycles</label>
        <div class="input-row">
          <div style="flex:1;">
            <span class="form-label">AP Sleep (Minutes):</span>
            <input type="number" class="input-box" id="lpSleepMin" value="5" min="1" max="120">
          </div>
          <div style="flex:1;">
            <span class="form-label">Wake Window (Mins):</span>
            <input type="number" class="input-box" id="lpWakeMin" value="2" min="1" max="30">
          </div>
        </div>
      </div>

      <!-- Channel Customization & Power-On State -->
      <div class="form-group" style="border-top:1px solid var(--card-border); padding-top:12px;">
        <label class="form-label" style="font-weight:700; color:var(--text);">🏷️ Channel 1 Customization</label>
        <input type="text" class="input-box" id="cfgR1Name" placeholder="Relay 1 Name" value="Relay 1">
        <div class="input-row" style="margin-top:4px;">
          <input type="number" class="input-box" id="cfgR1Watts" placeholder="Load Watts (e.g. 100)" value="100">
          <label style="display:flex; align-items:center; gap:6px; font-size:12px; color:#fff;">
            <input type="checkbox" id="cfgR1ActiveLow" checked> Active LOW
          </label>
        </div>
        <div style="margin-top:6px;">
          <span class="form-label">Power-On Default State:</span>
          <select class="input-box" id="cfgR1PwrOn" style="width:100%; margin-top:2px;">
            <option value="0">Always Boot OFF (Safest)</option>
            <option value="1">Always Boot ON</option>
            <option value="2">Restore Previous State before Power Cut</option>
          </select>
        </div>
      </div>

      <div class="form-group" style="border-top:1px solid var(--card-border); padding-top:12px;">
        <label class="form-label" style="font-weight:700; color:var(--text);">🏷️ Channel 2 Customization</label>
        <input type="text" class="input-box" id="cfgR2Name" placeholder="Relay 2 Name" value="Relay 2">
        <div class="input-row" style="margin-top:4px;">
          <input type="number" class="input-box" id="cfgR2Watts" placeholder="Load Watts (e.g. 100)" value="100">
          <label style="display:flex; align-items:center; gap:6px; font-size:12px; color:#fff;">
            <input type="checkbox" id="cfgR2ActiveLow" checked> Active LOW
          </label>
        </div>
        <div style="margin-top:6px;">
          <span class="form-label">Power-On Default State:</span>
          <select class="input-box" id="cfgR2PwrOn" style="width:100%; margin-top:2px;">
            <option value="0">Always Boot OFF (Safest)</option>
            <option value="1">Always Boot ON</option>
            <option value="2">Restore Previous State before Power Cut</option>
          </select>
        </div>
      </div>

      <!-- OTA Firmware Update & Port 500 Security Section -->
      <div class="form-group" style="border-top:1px solid var(--card-border); padding-top:14px;">
        <div style="display:flex; justify-content:space-between; align-items:center;">
          <label class="form-label" style="font-weight:700; color:var(--primary); font-size:13px;">⚡ OTA Firmware Update</label>
          <span class="version-badge" id="modalFwVer">v2.0.0-OTA</span>
        </div>
        
        <!-- Port 500 Security Toggle -->
        <div style="background:var(--card-inner-bg); border:1px solid var(--card-border); border-radius:10px; padding:10px 12px; margin-top:6px; display:flex; flex-direction:column; gap:6px;">
          <div style="display:flex; justify-content:space-between; align-items:center;">
            <span style="font-size:13px; font-weight:700; color:#fff;">Port 500 OTA Server (Security)</span>
            <label class="toggle-switch">
              <input type="checkbox" id="port500EnSwitch" onchange="togglePort500(this.checked)">
              <span class="slider"></span>
            </label>
          </div>
          <span style="font-size:11px; color:var(--text-sub);">Disabled by default for security. When enabled, open dedicated flasher at <a id="port500Link" href="http://192.168.4.1:500" target="_blank" style="color:var(--primary); text-decoration:underline; display:none;">http://192.168.4.1:500</a></span>
        </div>

        <!-- Port 80 Direct Firmware Flashing -->
        <div style="background:var(--card-inner-bg); border:1px solid var(--card-border); border-radius:10px; padding:12px; margin-top:8px; display:flex; flex-direction:column; gap:8px;">
          <span style="font-size:12px; font-weight:700; color:#fff;">Upload .bin Firmware via Port 80:</span>
          <input type="file" id="port80FileInput" accept=".bin" class="input-box" style="padding:6px; font-size:11px;" onchange="onPort80FileSelected()">
          <div id="port80FileInfo" style="display:none; font-size:11px; color:var(--primary); font-family:monospace;"></div>
          
          <div id="port80ProgressBox" style="display:none; flex-direction:column; gap:4px;">
            <div style="display:flex; justify-content:space-between; font-size:11px;">
              <span id="port80ProgressStatus" style="color:var(--primary);">Uploading...</span>
              <span id="port80ProgressPct" style="font-weight:700; color:var(--primary);">0%</span>
            </div>
            <div class="progress-track" style="height:6px;">
              <div class="progress-fill" id="port80ProgressBar"></div>
            </div>
          </div>

          <button type="button" class="btn btn-primary" id="port80UploadBtn" style="padding:8px 12px; font-size:12px;" onclick="uploadFirmwarePort80()" disabled>🚀 Upload & Flash Firmware</button>
          <span style="font-size:10px; color:var(--text-muted); line-height:1.3;">💡 Blue LED will blink <b>5 times</b> on success (followed by auto-restart) or <b>3 times</b> if the update fails.</span>
        </div>
      </div>

      <button class="btn btn-success" style="margin-top:8px;" onclick="saveAllSettings()">Save All Settings to Memory</button>
    </div>
  </div>

  <div id="toast">Notification</div>

  <script>
    let isModalOpen = false;
    const rDays = { 1: 0xFF, 2: 0xFF };

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
      if (tabName === 'cycle') card.querySelector(`#r${relayId}TabCycle`).classList.add('active');
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

    /* Pulse Trigger - Commented out for now
    async function triggerPulse(id, ms) {
      try {
        const res = await fetch('/api/pulse', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `id=${id}&ms=${ms}`
        });
        if (res.ok) {
          showToast(`Relay ${id} triggered with ${ms}ms Pulse!`);
          fetchStatus();
        }
      } catch(err) {
        showToast('Error triggering pulse');
      }
    }
    */

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
          showToast(`Relay ${id} Countdown Timer Activated!`);
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
          showToast(`Relay ${id} Countdown Cancelled`);
          fetchStatus();
        }
      } catch(err) {
        showToast('Error cancelling timer');
      }
    }

    // Cyclic Automation Start
    async function setCycle(id) {
      const onMin = parseInt(document.getElementById(`r${id}CycOnMin`).value) || 0;
      const onSec = parseInt(document.getElementById(`r${id}CycOnSec`).value) || 0;
      const offMin = parseInt(document.getElementById(`r${id}CycOffMin`).value) || 0;
      const offSec = parseInt(document.getElementById(`r${id}CycOffSec`).value) || 0;
      const totalCycles = parseInt(document.getElementById(`r${id}CycTotal`).value) || 0;

      const totalOnSec = onMin * 60 + onSec;
      const totalOffSec = offMin * 60 + offSec;

      if (totalOnSec <= 0 || totalOffSec <= 0) {
        showToast('Specify valid ON & OFF times');
        return;
      }

      try {
        const res = await fetch('/api/cycle', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `id=${id}&on_sec=${totalOnSec}&off_sec=${totalOffSec}&cycles=${totalCycles}&enable=1`
        });
        if (res.ok) {
          showToast(`Relay ${id} Cycle Automation Started!`);
          fetchStatus();
        }
      } catch(err) {
        showToast('Error starting cycle');
      }
    }

    // Cancel Cycle Automation
    async function cancelCycle(id) {
      try {
        const res = await fetch('/api/cycle', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `id=${id}&enable=0`
        });
        if (res.ok) {
          showToast(`Relay ${id} Cycle Stopped`);
          fetchStatus();
        }
      } catch(err) {
        showToast('Error stopping cycle');
      }
    }

    // Weekday Toggle & Presets
    function toggleDay(relayId, dayIdx) {
      if (rDays[relayId] === 0xFF) {
        rDays[relayId] = 0x7F; // expand all 7 days before toggling single day
      }
      rDays[relayId] ^= (1 << dayIdx);
      updateDayUi(relayId);
      setSchedule(relayId);
    }

    function selectDayPreset(relayId, preset) {
      if (preset === 'all') rDays[relayId] = 0x7F;
      else if (preset === 'weekdays') rDays[relayId] = 0x3E; // Mon(1)+Tue(2)+Wed(4)+Thu(8)+Fri(16) = 62
      else if (preset === 'weekends') rDays[relayId] = 0x41; // Sun(0)+Sat(6) = 65
      updateDayUi(relayId);
      setSchedule(relayId);
    }

    function updateDayUi(relayId) {
      const bar = document.getElementById(`r${relayId}WeekdayBar`);
      if (!bar) return;
      const mask = rDays[relayId];
      bar.querySelectorAll('.day-btn').forEach(btn => {
        const d = parseInt(btn.getAttribute('data-day'));
        if ((mask & (1 << d)) || mask === 0xFF) {
          btn.classList.add('selected');
        } else {
          btn.classList.remove('selected');
        }
      });
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
      const mask = rDays[id] !== undefined ? rDays[id] : 0xFF;

      try {
        const res = await fetch('/api/schedule', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `id=${id}&start_h=${startH}&start_m=${startM}&end_h=${endH}&end_m=${endM}&days=${mask}&enable=${isEn ? 1 : 0}`
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
          // Immediately update liveClock in 12h format
          let h = now.getHours();
          const ampm = h >= 12 ? 'PM' : 'AM';
          h = h % 12;
          if (h === 0) h = 12;
          const m = String(now.getMinutes()).padStart(2, '0');
          const s = String(now.getSeconds()).padStart(2, '0');
          document.getElementById('liveClock').innerText = `${String(h).padStart(2, '0')}:${m}:${s} ${ampm}`;
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

    // Permanent Stay-On Mode Toggle
    async function togglePermanentStayOn(stayOn) {
      try {
        const res = await fetch('/api/power', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `stay_on=${stayOn ? 1 : 0}`
        });
        if (res.ok) {
          showToast(`Permanent Stay-On Mode ${stayOn ? 'Enabled' : 'Disabled'}`);
          fetchStatus();
        }
      } catch(err) {
        showToast('Error changing stay-on setting');
      }
    }

    // Toggle Low Power Mode
    async function toggleLowPower(en) {
      const sleepMin = parseInt(document.getElementById('lpSleepMin').value) || 5;
      const wakeMin = parseInt(document.getElementById('lpWakeMin').value) || 2;

      try {
        const res = await fetch('/api/power', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `enable=${en ? 1 : 0}&sleep_min=${sleepMin}&wake_min=${wakeMin}`
        });
        if (res.ok) {
          showToast(`Low Power Auto-Sleep ${en ? 'Enabled' : 'Disabled'}`);
          fetchStatus();
        }
      } catch(err) {
        showToast('Error setting low power mode');
      }
    }

    // Save All Settings
    async function saveAllSettings() {
      const stayOn = document.getElementById('modalPermanentStayOn').checked;
      const sleepMin = parseInt(document.getElementById('lpSleepMin').value) || 5;
      const wakeMin = parseInt(document.getElementById('lpWakeMin').value) || 2;

      const r1Name = document.getElementById('cfgR1Name').value;
      const r1Watts = parseFloat(document.getElementById('cfgR1Watts').value) || 100;
      const r1ActLow = document.getElementById('cfgR1ActiveLow').checked;
      const r1PwrOn = parseInt(document.getElementById('cfgR1PwrOn').value) || 0;

      const r2Name = document.getElementById('cfgR2Name').value;
      const r2Watts = parseFloat(document.getElementById('cfgR2Watts').value) || 100;
      const r2ActLow = document.getElementById('cfgR2ActiveLow').checked;
      const r2PwrOn = parseInt(document.getElementById('cfgR2PwrOn').value) || 0;

      try {
        await fetch('/api/power', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `stay_on=${stayOn ? 1 : 0}&sleep_min=${sleepMin}&wake_min=${wakeMin}`
        });

        await fetch('/api/settings', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `r1_name=${encodeURIComponent(r1Name)}&r1_watts=${r1Watts}&r1_actlow=${r1ActLow?1:0}&r1_pwron=${r1PwrOn}&r2_name=${encodeURIComponent(r2Name)}&r2_watts=${r2Watts}&r2_actlow=${r2ActLow?1:0}&r2_pwron=${r2PwrOn}`
        });

        showToast('All Settings Permanently Saved!');
        document.getElementById('settingsModal').classList.remove('open');
        isModalOpen = false;
        fetchStatus();
      } catch(err) {
        showToast('Failed saving settings');
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

        // Permanent Stay-On Status
        document.getElementById('permanentStayOnSwitch').checked = data.power.stay_on;
        if (!isModalOpen) {
          document.getElementById('modalPermanentStayOn').checked = data.power.stay_on;
        }
        if (data.power.stay_on) {
          document.getElementById('stayOnStatusText').innerText = 'Permanent Active Mode. Sleep is disabled; system & AP run 24/7.';
        } else {
          document.getElementById('stayOnStatusText').innerText = 'Power Saver mode enabled. AP will sleep after inactivity.';
        }

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
        
        // R1 Countdown Timer
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

        // R1 Cycle Automation
        const cBox1 = document.getElementById('r1CycleLiveBox');
        if (r1.cycle && r1.cycle.active) {
          cBox1.style.display = 'flex';
          const cycleLabel = r1.cycle.total_cycles > 0 ? `Cycle ${r1.cycle.current_cycle+1}/${r1.cycle.total_cycles}` : `Cycle #${r1.cycle.current_cycle+1} (Infinite)`;
          document.getElementById('r1CyclePhase').innerText = `🔁 ${cycleLabel} [${r1.cycle.in_on ? 'ON Phase' : 'OFF Phase'}]`;
          document.getElementById('r1CycleCountdown').innerText = formatSecs(r1.cycle.remaining);
          const phaseSpan = r1.cycle.in_on ? r1.cycle.on_sec : r1.cycle.off_sec;
          const pct = phaseSpan > 0 ? ((phaseSpan - r1.cycle.remaining) / phaseSpan) * 100 : 100;
          document.getElementById('r1CycleProgress').style.width = pct + '%';
        } else {
          cBox1.style.display = 'none';
        }

        // R1 Schedule & Stats
        if (!isModalOpen) {
          document.getElementById('r1SchedEn').checked = r1.schedule.enabled;
          document.getElementById('r1SchedStart').value = `${String(r1.schedule.start_h).padStart(2,'0')}:${String(r1.schedule.start_m).padStart(2,'0')}`;
          document.getElementById('r1SchedEnd').value = `${String(r1.schedule.end_h).padStart(2,'0')}:${String(r1.schedule.end_m).padStart(2,'0')}`;
          if (r1.schedule.days !== undefined) {
            rDays[1] = r1.schedule.days;
            updateDayUi(1);
          }
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

        // R2 Countdown Timer
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

        // R2 Cycle Automation
        const cBox2 = document.getElementById('r2CycleLiveBox');
        if (r2.cycle && r2.cycle.active) {
          cBox2.style.display = 'flex';
          const cycleLabel = r2.cycle.total_cycles > 0 ? `Cycle ${r2.cycle.current_cycle+1}/${r2.cycle.total_cycles}` : `Cycle #${r2.cycle.current_cycle+1} (Infinite)`;
          document.getElementById('r2CyclePhase').innerText = `🔁 ${cycleLabel} [${r2.cycle.in_on ? 'ON Phase' : 'OFF Phase'}]`;
          document.getElementById('r2CycleCountdown').innerText = formatSecs(r2.cycle.remaining);
          const phaseSpan = r2.cycle.in_on ? r2.cycle.on_sec : r2.cycle.off_sec;
          const pct = phaseSpan > 0 ? ((phaseSpan - r2.cycle.remaining) / phaseSpan) * 100 : 100;
          document.getElementById('r2CycleProgress').style.width = pct + '%';
        } else {
          cBox2.style.display = 'none';
        }

        // R2 Schedule & Stats
        if (!isModalOpen) {
          document.getElementById('r2SchedEn').checked = r2.schedule.enabled;
          document.getElementById('r2SchedStart').value = `${String(r2.schedule.start_h).padStart(2,'0')}:${String(r2.schedule.start_m).padStart(2,'0')}`;
          document.getElementById('r2SchedEnd').value = `${String(r2.schedule.end_h).padStart(2,'0')}:${String(r2.schedule.end_m).padStart(2,'0')}`;
          if (r2.schedule.days !== undefined) {
            rDays[2] = r2.schedule.days;
            updateDayUi(2);
          }
        }
        document.getElementById('r2TotTime').innerText = formatHoursMin(r2.total_sec);
        const kwh2 = ((r2.total_sec / 3600) * (r2.watts / 1000)).toFixed(3);
        document.getElementById('r2Energy').innerText = `${kwh2} kWh`;

        // Total Combined Energy Consumption Metrics
        const totalSecs = r1.total_sec + r2.total_sec;
        const totalKwh = (((r1.total_sec / 3600) * (r1.watts / 1000)) + ((r2.total_sec / 3600) * (r2.watts / 1000))).toFixed(3);
        const liveWatts = (r1.state ? r1.ratedWatts || r1.watts : 0) + (r2.state ? r2.ratedWatts || r2.watts : 0);
        document.getElementById('totalKwhBadge').innerText = `${totalKwh} kWh`;
        document.getElementById('totalRuntimeVal').innerText = formatHoursMin(totalSecs);
        document.getElementById('totalLiveWattsVal').innerText = `${liveWatts.toFixed(1)} W`;

        // Low Power Mode Switch
        document.getElementById('lowPowerEnSwitch').checked = data.power.enabled;
        if (data.power.stay_on) {
          document.getElementById('lowPowerDesc').innerText = 'Permanent Always-On is Active: Auto-sleep disabled. System runs 24/7.';
        } else if (data.power.enabled) {
          document.getElementById('lowPowerDesc').innerText = `Auto-Sleep Active: Sleeping in ${data.power.next_state_sec}s (Wake every ${data.power.sleep_min}m)`;
        } else {
          document.getElementById('lowPowerDesc').innerText = 'Auto-sleep disabled. System will remain awake.';
        }

        // Telemetry & FreeRTOS stats
        document.getElementById('telemTemp').innerText = `${data.telem.temp_c.toFixed(1)} °C`;
        document.getElementById('telemHeap').innerText = `${Math.round(data.telem.free_heap / 1024)} KB`;
        const ut_h = Math.floor(data.telem.uptime_sec / 3600);
        const ut_m = Math.floor((data.telem.uptime_sec % 3600) / 60);
        document.getElementById('telemUptime').innerText = `${ut_h}h ${ut_m}m`;
        document.getElementById('telemClients').innerText = data.telem.clients;
        if (data.telem.rtos_relay_ticks !== undefined) {
          document.getElementById('telemRelayTicks').innerText = data.telem.rtos_relay_ticks;
          document.getElementById('telemPowerTicks').innerText = data.telem.rtos_power_ticks;
        }

        // Firmware Version & Port 500 Status in Footer & Settings Modal
        if (data.fw_ver) {
          document.getElementById('footerFwVer').innerText = `FW: ${data.fw_ver}`;
          const mFw = document.getElementById('modalFwVer');
          if (mFw) mFw.innerText = data.fw_ver;
        }
        if (data.port500 !== undefined) {
          const p500Switch = document.getElementById('port500EnSwitch');
          if (!isModalOpen && p500Switch) p500Switch.checked = data.port500;
          const p500Badge = document.getElementById('footerPort500Status');
          const p500Link = document.getElementById('port500Link');
          if (p500Badge) {
            if (data.port500) {
              p500Badge.className = 'port500-badge enabled';
              p500Badge.innerText = 'Port 500: Active';
              if (p500Link) p500Link.style.display = 'inline';
            } else {
              p500Badge.className = 'port500-badge disabled';
              p500Badge.innerText = 'Port 500: OFF';
              if (p500Link) p500Link.style.display = 'none';
            }
          }
        }

        // Event Logs Stream
        if (data.logs && data.logs.length > 0) {
          const logBox = document.getElementById('eventLogContainer');
          let html = '';
          data.logs.forEach(l => {
            html += `<div class="event-entry"><span class="event-time">[${l.time}]</span><span>${l.msg}</span></div>`;
          });
          logBox.innerHTML = html;
        }

        // Auto sync time on first load if not synced yet
        if (!data.time.synced && !window.hasAutoSynced) {
          window.hasAutoSynced = true;
          syncPhoneTime();
        }
      } catch (err) {
        console.error('Polling error:', err);
      }
    }

    // Port 500 OTA Toggle
    async function togglePort500(en) {
      try {
        const res = await fetch('/api/ota/port500', {
          method: 'POST',
          headers: {'Content-Type': 'application/x-www-form-urlencoded'},
          body: `enable=${en ? 1 : 0}`
        });
        if (res.ok) {
          showToast(`Port 500 OTA Server ${en ? 'Enabled' : 'Disabled'}`);
          fetchStatus();
        }
      } catch(err) {
        showToast('Failed to toggle Port 500');
      }
    }

    // Port 80 OTA File Selection
    let port80File = null;
    function onPort80FileSelected() {
      const input = document.getElementById('port80FileInput');
      const info = document.getElementById('port80FileInfo');
      const btn = document.getElementById('port80UploadBtn');
      if (input.files.length > 0) {
        port80File = input.files[0];
        if (!port80File.name.endsWith('.bin')) {
          showToast('Please select a compiled .bin firmware file');
          input.value = '';
          port80File = null;
          info.style.display = 'none';
          btn.disabled = true;
          return;
        }
        info.innerText = `Selected: ${port80File.name} (${(port80File.size / 1024).toFixed(1)} KB)`;
        info.style.display = 'block';
        btn.disabled = false;
      } else {
        port80File = null;
        info.style.display = 'none';
        btn.disabled = true;
      }
    }

    // Port 80 OTA Firmware Upload & Flash
    function uploadFirmwarePort80() {
      if (!port80File) return;
      const btn = document.getElementById('port80UploadBtn');
      const pBox = document.getElementById('port80ProgressBox');
      const pBar = document.getElementById('port80ProgressBar');
      const pStatus = document.getElementById('port80ProgressStatus');
      const pPct = document.getElementById('port80ProgressPct');

      btn.disabled = true;
      pBox.style.display = 'flex';
      pBar.style.width = '0%';
      pPct.innerText = '0%';
      pStatus.innerText = 'Uploading firmware to OTA partition...';
      pStatus.style.color = 'var(--primary)';

      const xhr = new XMLHttpRequest();
      const formData = new FormData();
      formData.append('update', port80File, port80File.name);

      xhr.upload.addEventListener('progress', (e) => {
        if (e.lengthComputable) {
          const pct = Math.round((e.loaded / e.total) * 100);
          pBar.style.width = pct + '%';
          pPct.innerText = pct + '%';
          if (pct === 100) {
            pStatus.innerText = 'Writing Flash & Verifying CRC...';
          }
        }
      });

      xhr.onreadystatechange = function() {
        if (xhr.readyState === 4) {
          if (xhr.status === 200) {
            pStatus.innerText = '🎉 OTA Success! Blue LED blinking 5 times...';
            pStatus.style.color = 'var(--success)';
            showToast('Firmware Flashed Successfully! Rebooting...');
            setTimeout(() => { location.reload(); }, 4500);
          } else {
            pStatus.innerText = '❌ OTA Failed! Blue LED blinking 3 times.';
            pStatus.style.color = 'var(--danger)';
            showToast('OTA Firmware Flash Failed');
            btn.disabled = false;
          }
        }
      };

      xhr.onerror = function() {
        pStatus.innerText = '❌ Upload Network Error! Blue LED blinking 3 times.';
        pStatus.style.color = 'var(--danger)';
        showToast('Upload network error');
        btn.disabled = false;
      };

      xhr.open('POST', '/api/ota/upload', true);
      xhr.send(formData);
    }

    // Auto-poll status every 1 second
    setInterval(fetchStatus, 1000);
    fetchStatus();
  </script>
</body>
</html>
)rawliteral";

#endif // WEBPAGES_H
