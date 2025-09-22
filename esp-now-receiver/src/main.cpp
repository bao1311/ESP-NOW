#include <Arduino.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

// Global value definition
// put function declarations here:
int myFunction(int, int);
void OnDataRecv(const uint8_t *, const uint8_t *, int);

// Message data type
typedef struct test_struct {
  char message[50];
  int value;
} test_struct;

test_struct myData;

void setup() {
  // put your setup code here, to run once:

  // In setup()
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // Set the channel to match the sender's channel
  Serial.println("Wifi channel set to 1");
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
int myFunction(int x, int y) {
  return x + y;
}
// Call back function
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Message: ");
  Serial.println(myData.message);
  Serial.print("Value: ");
  Serial.println(myData.value);
}

