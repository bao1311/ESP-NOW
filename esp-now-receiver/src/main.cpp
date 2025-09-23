#include <Arduino.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>
#include <string>
#include <telemetry.h>
#include <shared_functions.h>
using namespace std;
// Global value definition
// put function declarations here:
int myFunction(int, int);
void OnDataRecv(const uint8_t *, const uint8_t *, int);

// Message data type
telemetry_struct receivedData;

void setup() {
  // put your setup code here, to run once:

  // In setup()
  // Set baud rate for Serial Monitor to 115200
  Serial.begin(115200);
  // Set device as a Wi-Fi Station (required for ESP-NOW)
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // Set the channel to match the sender's channel
  Serial.println("Wifi channel set to 1");
  // Register the receive callback function
  if (esp_now_register_recv_cb(OnDataRecv) != ESP_OK) {
    Serial.println("Error registering ESP-NOW receive callback");
  }
}

void loop() {
  // put your main code here, to run repeatedly
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  delay(1000);
  Serial.println("Looping...");
}

// put function definitions here:

// Call back function (according to ESP-IDF framework)
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  Serial.print("MAC Address of the sender: ");
  printMACAddress(mac);
  Serial.print("Data received: ");
  Serial.print("Message: ");
  Serial.println(receivedData.message);
  Serial.print("GPS Latitude: ");
  Serial.println(receivedData.latitude, 6);
  Serial.print("GPS Longitude: ");
  Serial.println(receivedData.longitude, 6);
  Serial.print("GPS Altitude: ");
  Serial.println(receivedData.altitude);
  Serial.print("GPS Speed: ");
  Serial.println(receivedData.speed);
  Serial.print("Battery Level: ");
  Serial.println(receivedData.batteryLevel);
  Serial.print("Signal Strength: ");
  Serial.println(receivedData.signalStrength);
  Serial.print("Timestamp: ");
  Serial.println(receivedData.timestamp);
  Serial.println(); 
}

