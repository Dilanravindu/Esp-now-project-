09.07 11:07 AM
# ESP-NOW LCD Display Project

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![ESP32](https://img.shields.io/badge/Platform-ESP32%20%7C%20ESP8266-blue)
![Arduino](https://img.shields.io/badge/Environment-Arduino-orange)

Welcome to the **ESP-NOW LCD Display Project**! This project showcases wireless communication using ESP-NOW between an ESP32 (transmitter) and an ESP8266 (receiver) with a 16x2 I2C LCD display. The ESP32 sends data (`ID`, `value`, `text: Hello from ESP32`) to the ESP8266, which displays it on the LCD along with RSSI and signal bars, cycling every 2 seconds. Optimized for long-range (~92 meters tested with RSSI ~-75 dBm), this project is ideal for IoT enthusiasts exploring ESP-NOW and LCD integration.

**Developer**: Dilan Smith  
**Email**: [mbdilanravindu@gmail.com](mailto:mbdilanravindu@gmail.com)

## Features
- **ESP32 Transmitter**: Sends `ID`, `value`, and `text` every 2 seconds via ESP-NOW.
- **ESP8266 Receiver**: Displays data on a 16x2 I2C LCD, cycling:
  - `ID` and `value` (e.g., `ID: 1`, `Value: 42.5`)
  - RSSI and signal bars (0-5, based on -90 to -50 dBm, e.g., `RSSI: -75 dBm`, `Bars: ███`)
  - Text (e.g., `Text: Hello from ESP32`)
- **Range Optimization**: Max TX power (20.5 dBm), 1 Mbps PHY rate, channel 1.
- **Debugging**: Serial Monitor output for both boards.
- **Tested**: Achieves ~92 meters with line-of-sight.

## Project Structure
