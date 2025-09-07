09.07 11:10 AM
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

esp-now-lcd-project/ ├── esp32_tx.ino           # ESP32 transmitter code ├── esp8266_rx_lcd.ino     # ESP8266 receiver code with LCD └── README.md          
    # Project documentation

## Hardware Requirements
- **ESP32**: Any ESP32 board (e.g., ESP32 DevKit).
- **ESP8266**: NodeMCU 1.0 (ESP-12E Module).
- **LCD**: 16x2 LCD with I2C backpack (PCF8574, address 0x27 or 0x3F).
- **Power**: Stable 5V supply (USB or external, 500 mA+ recommended).
- **Wiring for ESP8266**:
  - LCD SCL → D1 (GPIO 5)
  - LCD SDA → D2 (GPIO 4)
  - LCD VCC → Vin (5V)
  - LCD GND → GND

## Software Requirements
- **Arduino IDE**: Version 1.8.19 or later ([download](https://www.arduino.cc/en/software)).
- **Board Packages**:
  - ESP32: `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
  - ESP8266: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
- **Library**: `LiquidCrystal_I2C` by Frank de Brabander (install via Library Manager).

## Installation Instructions
1. **Install Arduino IDE**:
   - Download and install from [arduino.cc](https://www.arduino.cc/en/software).

2. **Add Board Packages**:
   - In Arduino IDE, go to **File > Preferences**.
   - Add ESP32 and ESP8266 URLs to "Additional Boards Manager URLs" (comma-separated).
   - Go to **Tools > Board > Boards Manager**, search for "esp32" and "esp8266", install latest versions (ESP32: 3.3.0+, ESP8266: 3.1.2+).

3. **Install Library**:
   - Go to **Sketch > Include Library > Manage Libraries**.
   - Search for "LiquidCrystal I2C" by Frank de Brabander and install (~1.1.2).

4. **Verify LCD I2C Address**:
   - Run an I2C scanner sketch (e.g., [I2C Scanner](https://playground.arduino.cc/Main/I2cScanner/)) to find the LCD address (0x27 or 0x3F).
   - Update `LiquidCrystal_I2C lcd(0x27, 16, 2)` in `esp8266_rx_lcd.ino` if needed (e.g., `0x3F`).

5. **Upload Code**:
   - **ESP32 Transmitter**:
     - Open `esp32_tx.ino`.
     - Select **Tools > Board > ESP32 Dev Module**.
     - Set: 240 MHz, QIO, 80 MHz, 4MB, 921600 baud.
     - Connect ESP32, upload (Ctrl+U).
   - **ESP8266 Receiver**:
     - Open `esp8266_rx_lcd.ino`.
     - Select **Tools > Board > NodeMCU 1.0 (ESP-12E Module)**.
     - Set: 80 MHz, 4MB (FS:2MB OTA:~1019KB), 115200 baud.
     - Connect NodeMCU, upload (Ctrl+U).

6. **Test**:
   - Power both boards (use USB or external 5V supply).
   - Open Serial Monitor (115200 baud) for both:
     - **ESP32**: Should show "Peer added successfully", "Sent with success".
     - **ESP8266**: Should show "LCD Initialized", channel 1, and data (e.g., `ID: 1`, `Value: 42.5`, `Text: Hello from ESP32`, `RSSI: -75 dBm`, `Bars: ||   (2/5 bars)`).
   - LCD should cycle every 2 seconds:
     ```
     ID: 1
     Value: 42.5
     ```
     ```
     RSSI: -75 dBm
     Bars: ███
     ```
     ```
     Text: Hello from ESP32
     ```
   - Adjust LCD contrast potentiometer if display is blank or faint.

## Troubleshooting
- **Blank LCD**:
  - Verify I2C address with scanner.
  - Check wiring: SCL → D1, SDA → D2, VCC → 5V, GND → GND.
  - Adjust contrast potentiometer on I2C backpack.
  - Try `LiquidCrystal_I2C_ESP` library (John Rickman) if issues persist (update `#include` in `esp8266_rx_lcd.ino`).
  - Use external 5V supply (500 mA+).
- **No Data Received**:
  - Confirm ESP32 MAC (`0x84, 0xCC, 0xA8, 0xB0, 0x68, 0x0A`) and channel (1) in `esp32_tx.ino`.
  - Check ESP32 Serial Monitor for "Sent with success".
  - Ensure boards are within range (~92 meters tested).
- **Compilation Errors**:
  - Update board packages and library.
  - Enable verbose output (**File > Preferences**) for details.
  - Check for library conflicts (e.g., multiple `WiFi.h` versions).

## Contributing
Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/your-feature`).
3. Commit changes (`git commit -m "Add your feature"`).
4. Push to the branch (`git push origin feature/your-feature`).
5. Open a Pull Request.

Please follow the [Code of Conduct](CODE_OF_CONDUCT.md) (to be added) and ensure your code is well-documented.

## Contact
For questions or support, contact Dilan Smith at [mbdilanravindu@gmail.com](mailto:mbdilanravindu@gmail.com).

## License
This project is licensed under the [MIT License](LICENSE) - feel free to use and modify!

## Acknowledgments
- Built with [Arduino IDE](https://www.arduino.cc) and [ESP-NOW](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html).
- Thanks to the open-source community for libraries and tools!

---

Happy coding, and let's make wireless IoT projects shine! 

