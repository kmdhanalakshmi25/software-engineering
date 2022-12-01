#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial nodemcu(5, 6);

int data=A0;


void setup() 
{
  Serial.begin (9600);
  nodemcu.begin(9600);
  pinMode(data,INPUT);
  Serial.println("Program started");
}


void loop(){

  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();



    data["Air_Q"] = analogRead(A0);
    data.printTo(nodemcu);
    jsonBuffer.clear();

  delay(1000);
  Serial.print("Air Q Data :");
  Serial.println(analogRead(A0));

  if
  
}
