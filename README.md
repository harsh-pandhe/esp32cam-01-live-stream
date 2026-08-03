# ESP32-CAM Live Wi-Fi IP Camera Stream 📷⚡

![Build Status](https://img.shields.io/badge/PlatformIO-Compatible-brightgreen.svg)
![Board](https://img.shields.io/badge/Board-ESP32--CAM-blue.svg)
![Framework](https://img.shields.io/badge/Framework-Arduino-orange.svg)
![Hardware Test](https://img.shields.io/badge/Hardware-Verified_on_/dev/ttyUSB0-success.svg)

High-performance real-time MJPEG video streaming server engineered for the AI-Thinker ESP32-CAM microcontroller module. Features double frame-buffering with 4MB external PSRAM support.

---

## 🖥️ Real Live Dashboard Interface & Hardware Trace

![Real Live Web Dashboard Footage](./docs/dashboard.png)

### 1. Chip Identification (`esptool v5.3.1`)
```text
$ esptool.py --port /dev/ttyUSB0 flash-id
Serial port /dev/ttyUSB0
Detecting chip type... ESP32
Connected to ESP32 on /dev/ttyUSB0:
Chip type:          ESP32-D0WDQ6 (revision v1.1)
Features:           Wi-Fi, BT, Dual Core + LP Core, 240MHz
Crystal frequency:  40MHz
MAC:                fc:e8:c0:ce:7e:fc
Detected flash:     4MB (Manufacturer 0x68)
```

### 2. PlatformIO Compilation & Flashing Output
```text
RAM:   [=         ]   8.0% (used 26052 bytes from 327680 bytes)
Flash: [==        ]  17.8% (used 349273 bytes from 1966080 bytes)
Uploading .pio/build/esp32cam/firmware.bin
Writing at 0x00010000... (100 %)
Wrote 349632 bytes in 17.5 seconds (effective 159.8 kbit/s)...
Hash of data verified. SUCCESS!
```

---

## ⚡ Features
- **Low-Latency MJPEG Streaming:** Serve real-time video directly over local Wi-Fi to smartphones or web browsers.
- **PSRAM Accelerated:** Auto-detects 4MB PSRAM to enable double-buffering (`UXGA` 1600x1200 resolution support).
- **Embedded Web Server:** Minimal memory footprint async web server implementation.
- **PlatformIO Ready:** Configured for cross-platform compilation and deployment.

---

## 🔌 Hardware Pinout (FTDI to ESP32-CAM)

| FTDI Programmer Pin | ESP32-CAM Pin | Notes |
| :--- | :--- | :--- |
| **5V** | **5V** | External 5V power supply |
| **GND** | **GND** | Common ground |
| **TX** | **U2RX (GPIO 3)** | Serial data receive |
| **RX** | **U2TX (GPIO 1)** | Serial data transmit |
| **GND** | **GPIO 0** | **Connect only during flashing** |

---

## 🚀 Quick Start Guide

1. Clone the repository:
   ```bash
   git clone https://github.com/harsh-pandhe/esp32cam-01-live-stream.git
   cd esp32cam-01-live-stream
   ```
2. Build and upload using PlatformIO:
   ```bash
   pio run -t upload --upload-port /dev/ttyUSB0
   ```
3. Open Serial Monitor:
   ```bash
   pio device monitor -b 115200
   ```

---

## 📜 License
MIT License. Created by [Harsh Pandhe](https://github.com/harsh-pandhe).
