/****************************
  MQTT Serial Gateway
  
  - Publish all messages received via serial to state MQTT topic
  - Forward all messages received on the command topic to serial
  
*/
// Libraries for WIFI
#include <ESP8266WiFi.h>

// Libraries for MQTT
#include "PubSubClient.h"

// Signatures for functions used in this file
#include "definitions.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "YourWIFI"
#define WLAN_PASS       "YourPW"

/************************* MQTT Setup *********************************/

#define MQTT_SERVER "mqtt-host.de"  //change to your server
#define MQTT_PORT  1883                   
#define MQTT_USERNAME "MQTT_Username"
#define MQTT_PASSWORD "MQTT_Password"
#define MQTT_CLIENT_ID "MQTT_ClientID"
#define MQTT_STATE_TOPIC "serial/state" // all received serial messages are send to this topic
#define MQTT_COMMAND_TOPIC "serial/command"
#define SERIAL_SPEED 115200

/************************* Global Variables *********************************/

// MQTT
WiFiClient WiFiclient;
PubSubClient MQTTclient(MQTT_SERVER, MQTT_PORT, callback, WiFiclient); 

// Serial Connection
String serialInput;

/************************* Setup and Loop *********************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_SPEED);
  delay(10);

  // Connect to WiFi access point.
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  // Connect to MQTT
  while (!MQTTclient.connected()) {
    reconnect();
  }

  subscribeTo(MQTT_COMMAND_TOPIC);
}


void loop() {
  if (!MQTTclient.connected()) {
    reconnect();
  }
  MQTTclient.loop();

  while (Serial.available()) {
    delay(3);  //delay to allow buffer to fill
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer
      serialInput += c; //makes the string readString
    }
  }
  if (serialInput.length() > 0)
  {
    SerialMessageReceived(serialInput); 
    serialInput = "";
  }

}
