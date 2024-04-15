#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <Wire.h> //dl library of this
#include <ESP8266WiFi.h>// dl library
#include <BlynkSimpleEsp8266.h>// dl library
#include <ArduinoModbus.h>// dl library

#define BLYNK_PRINT Serial
#define RE D0
#define DE D1

const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

char auth[] = ""; //auth token
char ssid[] = ""; //wifi name
char pass[] = ""; //wifi password

byte values[5];

void setup() {
  Serial.begin(9600);
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
}
 
void loop() {
  Blynk.virtualWrite(V1, readSensor(nitro)); 
  delay(250);
  Blynk.virtualWrite(V2, readSensor(phos)); 
  delay(250);
  Blynk.virtualWrite(V3, readSensor(pota)); 
  delay(250);
}

byte readSensor(const byte* command){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(command,8)==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
      values[i] = mod.read();
      Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
