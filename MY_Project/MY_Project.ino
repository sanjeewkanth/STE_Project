#include <ArduinoMqttClient.h>
#include <WiFiClient.h>
#include <WiFi.h>
//#include "arduino_secrets.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
const char* ssid = "Dialog 4G 404";        // your network SSID (name)
const char* pass = "b1f50Ce1";    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);



const char* broker = "test.mosquitto.org";
int port = 1883;
const char* topic  = "EE_Project/esp32";


//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // attempt to connect to Wifi network:
  setup_wifi();

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis();
  String payload = "Hi";

  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;

    //record random value from A0, A1 and A2
//    int Rvalue = analogRead(A0);
//    int Rvalue2 = analogRead(A1);
//    int Rvalue3 = analogRead(A2);

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
//    Serial.println(Rvalue);

//    Serial.print("Sending message to topic: ");
//    Serial.println(topic2);
//    Serial.println(Rvalue2);
//
//    Serial.print("Sending message to topic: ");
//    Serial.println(topic2);
//    Serial.println(Rvalue3);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print(payload);
    mqttClient.endMessage();

//    mqttClient.beginMessage(topic2);
//    mqttClient.print(Rvalue2);
//    mqttClient.endMessage();
//
//    mqttClient.beginMessage(topic3);
//    mqttClient.print(Rvalue3);
//    mqttClient.endMessage();

    Serial.println();
  }
}
