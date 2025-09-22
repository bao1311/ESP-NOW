#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

// put function declarations here:
int myFunction(int, int);
uint8_t rightAddress[] = {0x44, 0x1D, 0x64, 0xF1, 0x02, 0x28};
uint8_t leftAddress[] = {0x44, 0x1D, 0x64, 0xF1, 0x73, 0x38};

// Data packet for receiver
typedef struct test_struct {
  char message[50];
  int value;
} test_struct;

test_struct myData;

void setup() {
  // put your setup code here, to run once:
  // Adjust the baud rate
  Serial.begin(9600);

    // Initialize WiFi in STA mode (required for ESP-NOW)
  WiFi.mode(WIFI_STA);


    // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // Set WiFi channel to 1
  // Peer info configuration
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, leftAddress, 6);
  peerInfo.channel = 1;  
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
  strcpy(myData.message, "Hello from ESP32");
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