// Monash University Winter Research Project 2022
// ESP8266 to Oculus via WiFi
// ESP8266 acts as I2C master to Arduino Mega which handles actuators
// Written by Ryan Wee

// Libraries
#include <ESP8266WiFi.h>
#include <Wire.h>

// Port numbers
#define Air1IN1 9
#define Air1IN2 10
#define Air1IN1 7
#define Air2IN2 6
#define Air1PWMA 11
#define PWMB 5
#define STBY 8
#define POT 0

// Parameters
const int baudRate = 9600;
const int slaveNumber = 1;
const int pollRate = 500;
bool debug = true;

// WiFi setup
const char* ssid = "XGL_Floatation_Tank";
const char* pass = "xglfloatationtank";   // Min 8 characters

// Declare server object
WiFiServer server(80);    // Port 80 used for Internet


void setup() {
  // Start I2C bus as master
  Wire.begin();

  // Start serial monitor if debug enabled
  if (debug) {
    Serial.begin(baudRate);
    Serial.println();
    Serial.println("Hello!");
  }
  
  // Start WiFi AP
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass, 1, 0);    // softAP(ssid, pw, ch, hide)
  server.begin();
  if (debug) {
    Serial.println("Setting AP");
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("Password: ");
    Serial.println(pass);
  }
}


void loop() {
  // Listen for incoming clients
  WiFiClient client = server.available();

  // String to hold incoming data
  String currentLine = "";

  if (client) {
    if (debug) {
      Serial.println("Client detected");
    }

    // While client is connected
    while (client.connected()) {
      // Read from client if content available
      if (client.available()) {
        char c = client.read();
        char response;
        if (debug) {
          // Output received character in serial monitor
          Serial.write(c);
        }

        // 1: Char is newline
        if (c == '\n') {
          // 1a: Current line is blank, hence consecutive \n
          // Denotes end of client HTTP request
          // Client expects response (sensor measurement data)
          if (currentLine.length() == 0) {
            response = sensorResponse();
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print(response);
            client.print("<br>");
            client.println();
            break;
          }

          // 1b: Current line is not blank
          // Clear currentLine
          else {
            currentLine = "";
          }
        }

        // 2: Char is data tx'ed by client
        // Char is not newline '\n' or carriage return '\r'
        // Append char to currentLine
        else if (c != '\r') {
          currentLine += c;
        }
      }

      // Transmit to I2C slave
      char sendBuffer[32];
      currentLine.toCharArray(sendBuffer, 32);
      Wire.beginTransmission(slaveNumber);
      Wire.write(sendBuffer);
      Wire.endTransmission();

      // Transmission delay
      delay(pollRate);
    }

    // Client has disconnected
    // Close the connection
    client.stop();
  }

  // Temporary
  delay(100);
}


char sensorResponse() {
  // Return measurement values of all connected sensors

  // Concat measurement values
  char output = 'a';
  return output;
}
