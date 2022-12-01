//Include Lib for Arduino to Nodemcu
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Replace with your network credentials
const char* ssid = "Root";
const char* password = "SudoUnlock";

unsigned long previousMillis = 0;
unsigned long interval = 30000;

//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);


WiFiClient client;

unsigned long myChannelNumber = 1964303;
const char * myWriteAPIKey = "YOREHVU7OJTHJEBL";

void setup() {

Serial.begin(115200);
  nodemcu.begin(9600);
  while (!Serial) continue;
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);

  
  initWiFi();
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  //The ESP8266 tries to reconnect automatically when the connection is lost
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}


void loop() {
  //print the Wi-Fi status every 30 seconds
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >=interval){
    switch (WiFi.status()){
      case WL_NO_SSID_AVAIL:
        Serial.println("Configured SSID cannot be reached");
        break;
      case WL_CONNECTED:
        Serial.println("Connection successfully established");
        break;
      case WL_CONNECT_FAILED:
        Serial.println("Connection failed");
        break;
    }
    Serial.printf("Connection status: %d\n", WiFi.status());
    Serial.print("RRSI: ");
    Serial.println(WiFi.RSSI());
    
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
 jsonBuffer.clear();
  return;
 }
   float Q = data["Air_Q"];
  Serial.print("Air Quality Data : ");
  Serial.println(Q);
  
    int x = ThingSpeak.writeField(myChannelNumber, 1,Q, myWriteAPIKey);
        if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }

    if(Q>250){
      Serial.println("Risk");
      int y = ThingSpeak.writeField(myChannelNumber, 2,1, myWriteAPIKey);
             if(y == 200){
      Serial.println("Channel updated field 2 successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
      
    }


//    
    previousMillis = currentMillis;
  }
}
