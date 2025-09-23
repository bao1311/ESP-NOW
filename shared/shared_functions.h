#ifndef SHARED_FUNCTIONS_H
#define SHARED_FUNCTIONS_H
#include <Arduino.h>
// Your shared functions code here
/*
Help function to print MAC address in standard format
*/
inline void printMACAddress(const uint8_t* mac) {
  for (int i = 0; i < 6; i++) {
    Serial.print(mac[i], HEX);
    if (i < 5) {
      Serial.print(":");
    }
  }
  Serial.println();
}
#endif // SHARED_FUNCTIONS_H