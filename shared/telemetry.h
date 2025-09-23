#ifndef TELEMETRY_H
#define TELEMETRY_H

// Your telemetry code here
typedef struct {
    float latitude;     // GPS latitude
    float longitude;    // GPS longitude
    float altitude;     // GPS altitude
    float speed;       // GPS speed
    int batteryLevel;   // Battery level percentage
    int signalStrength; // Signal strength in dBm
    unsigned long timestamp; // Timestamp in milliseconds
    char message[50]; // Message buffer
} telemetry_struct;

#endif // TELEMETRY_H