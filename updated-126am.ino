#define BLYNK_TEMPLATE_ID "TMPL6Tfzll-VV"
#define BLYNK_TEMPLATE_NAME "Agribot"
#define BLYNK_AUTH_TOKEN "7zTW0G8q1YvNGMlwfhUBI6bYUQah4kwj"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Motor PINs
int ENA = D0; //change according to your wiring pls -terrence 
int IN1 = D1;
int IN2 = D2;
int IN3 = D3;
int IN4 = D4;
int ENB = D5;

bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;

const char auth[] =  BLYNK_AUTH_TOKEN; 
const char ssid[] =  "ILOVE-JACKTHEDOG"; 
const char pass[] = "rizzracknaruto03149723"; 
const char domain[] = "blynk.cloud";

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Blynk.begin(auth, ssid, pass, domain, 80);
}

BLYNK_WRITE(V0) {
  forward = param.asInt();
}

BLYNK_WRITE(V1) {
  backward = param.asInt();
}

BLYNK_WRITE(V2) {
  left = param.asInt();
}

BLYNK_WRITE(V3) {
  right = param.asInt();
}

BLYNK_WRITE(V4) {
  Speed = param.asInt();
}


void smartcar() {
  if (forward == 1) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft();
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright();
    Serial.println("carright");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop();
    Serial.println("carstop");
  }
}
void loop() {
  Blynk.run();
  smartcar();
}

void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carbackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}