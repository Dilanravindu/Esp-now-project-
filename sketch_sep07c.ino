/*
 * ESP8266 Receiver with I2C 16x2 LCD for ESP-NOW
 * Developer: Dilan Smith
 * Email: mbdilanravindu@gmail.com
 * Description: Receives ID, value, and text via ESP-NOW and displays on LCD with RSSI and signal bars.
 */

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <LiquidCrystal_I2C.h>

// For RSSI and channel
extern "C" {
  #include <user_interface.h>
}

// Initialize LCD (address 0x27, update to 0x3F if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Structure to match transmitter
typedef struct struct_message {
  int id;
  float value;
  char text[32];
} struct_message;

struct_message myData;

// Map RSSI to signal bars (0 to 5)
int getSignalBars(int32_t rssi) {
  if (rssi >= -50) return 5;
  else if (rssi >= -60) return 4;
  else if (rssi >= -70) return 3;
  else if (rssi >= -80) return 2;
  else if (rssi >= -90) return 1;
  else return 0;
}

// Print signal bars to Serial
void printSignalBars(int bars) {
  Serial.print("Signal Strength: ");
  for (int i = 0; i < bars; i++) {
    Serial.print("|");
  }
  for (int i = bars; i < 5; i++) {
    Serial.print(" ");
  }
  Serial.print(" (");
  Serial.print(bars);
  Serial.println("/5 bars)");
}

// Display ID and value on LCD
void displayIdAndValue(int id, float value) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ID: ");
  lcd.print(id);
  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.print(value, 1);
}

// Display RSSI and bars on LCD
void displayRssiAndBars(int32_t rssi, int bars) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RSSI: ");
  lcd.print(rssi);
  lcd.print(" dBm");
  lcd.setCursor(0, 1);
  lcd.print("Bars: ");
  for (int i = 0; i < bars; i++) {
    lcd.write(0xFF);
  }
}

// Display text on LCD
void displayText(const char* text) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Text: ");
  lcd.print(text);
}

// Callback for received data
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  int32_t rssi = wifi_station_get_rssi();
  int bars = getSignalBars(rssi);
  memcpy(&myData, incomingData, sizeof(myData));

  // Serial output
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("ID: ");
  Serial.println(myData.id);
  Serial.print("Value: ");
  Serial.println(myData.value);
  Serial.print("Text: ");
  Serial.println(myData.text);
  Serial.print("RSSI: ");
  Serial.print(rssi);
  Serial.println(" dBm");
  printSignalBars(bars);
  Serial.println();

  // LCD output: Cycle displays
  displayIdAndValue(myData.id, myData.value);
  delay(2000);
  displayRssiAndBars(rssi, bars);
  delay(2000);
  displayText(myData.text);
  delay(2000);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ESP-NOW Receiver");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  Serial.println("LCD Initialized");
  delay(2000);
  lcd.clear();

  // Set Wi-Fi channel
  wifi_set_channel(1);
  Serial.print("ESP8266 Wi-Fi Channel: ");
  Serial.println(wifi_get_channel());

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    lcd.clear();
    lcd.print("ESP-NOW Error");
    return;
  }

  // Set role to receiver
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing needed
}