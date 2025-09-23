#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <string.h>
#include <telemetry.h>
using namespace std;
// put function declarations here:
int myFunction(int, int);
uint8_t rightAddress[] = {0x44, 0x1D, 0x64, 0xF1, 0x02, 0x28};
uint8_t leftAddress[] = {0x44, 0x1D, 0x64, 0xF1, 0x73, 0x38};

/*
* Mock data for telemetry
*/
float latitude[] = {21.005, 21.006, 21.007, 21.008};
float longitude[] = {105.843, 105.844, 105.845, 105.846};
float attitude[] = {10.0, 20.0, 30.0, 40.0};
float speed[] = {0.1, 0.2, 0.3, 0.4};
int batteryLevel[] = {100, 90, 80, 70};
int signalStrength[] = {4, 3, 2, 1};
unsigned long timestamp[] = {1625152800, 1625152860, 1625152920, 1625152980};

char myString[][50] = {"I am Bao", "I am currently learning ESP-NOW communication", "I love programming", "I learn how to use struct in C++"};
// Data packet for receiver (example using telemetry data structure)
telemetry_struct myData;


void setup() {
  // put your setup code here, to run once:
  // Adjust the baud rate
  Serial.begin(115200);

  // Initialize WiFi in STA mode (required for ESP-NOW)
  WiFi.mode(WIFI_STA);


    // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  /*
  * Set WiFi channel and peer information
  * Wifi channel must be the same as the receiver
  * We can use channel 1,6,11 to avoid overlapping
  */
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // Set WiFi channel to 1
  // Peer info configuration
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, leftAddress, 6);
  peerInfo.channel = 1;  
  peerInfo.ifidx = WIFI_IF_STA; // Ensure the interface is set to STA
  peerInfo.encrypt = false;

  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  Led blinking code (Does not work because esp32-devkit-v4 only have the power led)
  */
 /*
  digitalWrite(5, HIGH);  // Turn LED on
  Serial.println(digitalRead(5)); // Print out the value of pin 2
  delay(1000);            // Wait 1 second
  digitalWrite(5, LOW);   // Turn LED off
  Serial.println(digitalRead(5)); // Print out the value of pin 2
  delay(1000);            // Wait 1 second
 */
  Serial.println("Sending message to left node");
  strcpy(myData.message, myString[random(0,4)]); // Copy FROM myString TO myData.message
  myData.value = random(1,100);
  Serial.println("Mac address of the receiver: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(leftAddress[i], HEX);
    if (i < 5) {
      Serial.print(":");
    }
  }
  Serial.println();

  esp_err_t result = esp_now_send(leftAddress, (uint8_t *) &myData, sizeof(myData));
  delay(2000);
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}