#include <Arduino.h>

const int sensorpin1 = 7;
const int sensorpin2 = 8;
const int sensorpin3 = 9;
const int sensorpin4 = 10;
const int sensorpin5 = 11;
const int sensorpin6 = 12;

const int mosfetpin1 = 14;
const int mosfetpin2 = 15;
const int mosfetpin3 = 16;
const int mosfetpin4 = 17;
const int mosfetpin5 = 18;
const int mosfetpin6 = 19;

bool allowcoil1 = true;
bool allowcoil2 = true;
bool allowcoil3 = true;
bool allowcoil4 = true;
bool allowcoil5 = true;
bool allowcoil6 = true;


void setup() {
  // put your setup code here, to run once:
  // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorpin1, INPUT);
  pinMode(sensorpin2, INPUT);
  pinMode(sensorpin3, INPUT);
  pinMode(sensorpin4, INPUT);
  pinMode(sensorpin5, INPUT);
  pinMode(sensorpin6, INPUT);

  pinMode(mosfetpin1, OUTPUT);
  pinMode(mosfetpin2, OUTPUT);
  pinMode(mosfetpin3, OUTPUT);
  pinMode(mosfetpin4, OUTPUT);
  pinMode(mosfetpin5, OUTPUT);
  pinMode(mosfetpin6, OUTPUT);

}

void loop() { //Kinda dumb thing I am doing here, I still need to update the logic diagram and it is already so late -_-
  // put your main code here, to run repeatedly:
 if (digitalRead(sensorpin1) == HIGH and allowcoil1 == true){
   digitalWrite(mosfetpin1, HIGH);
 }
 else{
   digitalWrite(mosfetpin1, LOW);
 }

 if (digitalRead(sensorpin2) == HIGH and allowcoil2 == true){
   digitalWrite(mosfetpin2, HIGH);
 }
 else{
   digitalWrite(mosfetpin2, LOW);
 }

 if (digitalRead(sensorpin3) == HIGH and allowcoil3 == true){
   digitalWrite(mosfetpin3, HIGH);
 }
 else{
   digitalWrite(mosfetpin3, LOW);
 }

 if (digitalRead(sensorpin4) == HIGH and allowcoil4 == true){
   digitalWrite(mosfetpin4, HIGH);
 }
 else{
   digitalWrite(mosfetpin4, LOW);
 }

  if (digitalRead(sensorpin5) == HIGH and allowcoil5 == true){
    digitalWrite(mosfetpin5, HIGH);
  }
  else{
    digitalWrite(mosfetpin5, LOW);
  }

  if (digitalRead(sensorpin6) == HIGH and allowcoil6 == true){
    digitalWrite(mosfetpin6, HIGH);
  }
  else{
    digitalWrite(mosfetpin6, LOW);
  }
}