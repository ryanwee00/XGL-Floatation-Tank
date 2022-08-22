// Monash University Winter Research Project 2022
// Arduino Mega controls actuators
// Arduino Mega acts as I2C slave to ESP8266 which handles WiFi
// Written by Ryan Wee

// Libraries
#include <Wire.h>
#include <stdio.h>
#include <string.h>

// Pin numbers
// Pump types - air/water
// Number - corresponding to pump
// A/B - controls direction (swap for forward/reverse)
#define air1A 22
#define air1B 23
#define air2A 24
#define air2B 25
#define air3A 26
#define air3B 27
#define air4A 28
#define air4B 29
#define airPWM1 2
#define airPWM2 3
#define airPWM3 4
#define airPWM4 5
#define water1A 30
#define water1B 31
#define water2A 32
#define water2B 33
#define waterPWM1 6
#define waterPWM2 7
#define bilge 34
#define stby 8

// Parameters
const int baudRate = 9600;
const int slaveNumber = 1;
const int actuators = 7;    // Number of actuators (pumps)
bool debug = true;

// Declare buffer for received data
volatile char receivedLine[];
volatile bool receivedFlag = false;
char delim1[] = ", ";
char delim2[] = "_";
int state[actuators] = {0};

void setup() {
  // Start I2C bus as slave
  Wire.begin(slaveNumber);

  // Declare interrupt handler
  Wire.onReceive(receiveEvent);

  // Start serial monitor if debug enabled
  if (debug) {
    Serial.begin(baudRate);
    delay(10);
  }
}

void loop() {
  // If I2C transmission received
  if (receivedFlag == true) {
    // For now, display received I2C string
    if (debug) {
      Serial.println(receivedLine);
      delay(10);
    }

    // Decode received I2C string
    // String format: Air1_VAL, Air2_VAL, Air3_VAL, ...
    char *tokenPtr = strtok(receivedLine, delim1);

    // Split individual values with delim2
    // Follow this array format:
    // Air1, Air2, Air3, Air4, Water1, Water2, Bilge
    while (tokenPtr != NULL) {
      
    }

    // Reset flag
    receivedFlag = false;
  }
  delay(10);
}


// Interrupt handler
  void receiveEvent(int length) {
    Wire.readBytes(receivedLine, length);
    receivedFlag = true;
  }
