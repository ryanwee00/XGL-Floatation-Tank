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
    delay(10);
  }
  
  // Start WiFi AP
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass, 1, 1);    // softAP(ssid, pw, ch, hide)
  server.begin();
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
        if (debug) {
          // Output received character in serial monitor
          Serial.write(c));
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
      Wire.beginTransmission(slaveNumber);
      Wire.write(currentLine);
      Wire.endTransmission();

      // Transmission delay
      delay(pollRate);
    }

    // Client has disconnected
    // Close the connection
    client.stop();
  }
}


char sensorResponse() {
  // Return measurement values of all connected sensors

  // Concat measurement values


  return output
}


void loop() {
  // Check for incoming clients
  WiFiClient client = server.available();
  if (!client) {
    return
  }

  // Read client request line
  String request = client.readStringUntil('\r');
  if (debug) {
    Serial.println(request);
  }
  client.flush();

  // Perform request
  // Add IFTTT functionality here
  if (request.indexOf("/airPump1/on") != -1) {
    digitalWrite
  }


}






#include <SPI.h> //What is used to communicate witht he WiFi chip
#include <WiFi101.h> //Wifi library fro Arduino MKR1000 and WiFi shield

int lControl =  6; //Digital pin that LED is connected to on the MKR1000
char ssid[] = "YourNetwork";      // your network SSID (name)
char pass[] = "YourPassword";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS; //status of wifi

WiFiServer server(80); //declare server object and spedify port, 80 is port used for internet

void setup() {
  //Uncomment serial for debugging and to see details of WiFi connection
 // Serial.begin(9600);
 // while (!Serial) {
     // wait for serial port to connect. Needed for native USB port only
//  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
  //  Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
 //   Serial.print("Attempting to connect to SSID: ");
 //   Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();
  // you're connected now, so print out the status:
 // printWifiStatus();
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,

 

   // Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
       // Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Value at A0 is ");
            client.print(analogRead(A0));
            client.print("<br>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(lControl, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(lControl, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
   // Serial.println("client disconnected");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
