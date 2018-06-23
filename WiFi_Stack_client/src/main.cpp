#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;
// Use WiFiClient class to create TCP connections
WiFiClient client;

// Functions declaration
void wifi_connection_esp();

// This port and IP are the ones that we will use to connect to ESP32
const uint16_t port = 80;
const char * host = "10.31.1.35"; // ip or dns

void setup() {
  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network
  WiFiMulti.addAP("Human-A1-721-2G_EXT", "bsys12bsys34");
  Serial.print("Wait for WiFi... ");
  //Start the connection of the client and wait until connect to the lan
  while(WiFiMulti.run() != WL_CONNECTED) {
          Serial.print(".");
          delay(100);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  //print the IP assigned to the device
  Serial.println(WiFi.localIP());
  delay(500);
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, port)) {
          Serial.println("connection failed");
          Serial.println("wait 5 sec...");
          delay(50);
          return;
  }
}

void loop() {
  wifi_connection_esp();
}

void wifi_connection_esp() {
  // This string will be send to the server
  client.print("Stack is online");
  Serial.println("Stack is online");
  delay(500);
}
