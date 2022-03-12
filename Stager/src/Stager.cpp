#include <Arduino.h>

void resetcoil(); // needs to be declared when using .cpp files in VS code, if you build this in Arduino IDE everithing above line 4 does not need to be included

//I'm just a friendly slime

// Pins to sense the high signal of optical sensors
#define sensorpin1 7
#define sensorpin2 8
#define sensorpin3 9
#define sensorpin4 10
#define sensorpin5 11
#define sensorpin6 12

// Pins to drive the MOSFETs with
#define mosfetpin1 14
#define mosfetpin2 15
#define mosfetpin3 16
#define mosfetpin4 17
#define mosfetpin5 18
#define mosfetpin6 19

// Software enable/disable for individual coils, could be done on compiler level
#define allowcoil1 true
#define allowcoil2 true
#define allowcoil3 true
// #define allowcoil4 false
// #define allowcoil5 false
// #define allowcoil6 false

volatile unsigned long watchdogbreak = 0;
#define watchdogtime 2000 // in ms
// To make sure that a used coil will not turn back on
volatile bool coilhasbeenused1 = true;
volatile bool coilhasbeenused2 = true;
volatile bool coilhasbeenused3 = true;
// volatile bool coilhasbeenused4 = true;
// volatile bool coilhasbeenused5 = true;
// volatile bool coilhasbeenused6 = true; 

void setup() {
  pinMode(sensorpin1, INPUT);
  pinMode(sensorpin2, INPUT);
  pinMode(sensorpin3, INPUT);
  // pinMode(sensorpin4, INPUT);
  // pinMode(sensorpin5, INPUT);
  // pinMode(sensorpin6, INPUT);

  pinMode(mosfetpin1, OUTPUT);
  pinMode(mosfetpin2, OUTPUT);
  pinMode(mosfetpin3, OUTPUT);
  // pinMode(mosfetpin4, OUTPUT);
  // pinMode(mosfetpin5, OUTPUT);
  // pinMode(mosfetpin6, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2),resetcoil,RISING); // Interrupt from the other microcontroller
}

void resetcoil(){
  watchdogbreak = millis() + watchdogtime;
  coilhasbeenused1 = false;
  coilhasbeenused2 = false;
  coilhasbeenused3 = false;
  // coilhasbeenused4 = false;
  // coilhasbeenused5 = false;
  // coilhasbeenused6 = false;
}

void loop(){
  if (millis() >= watchdogbreak){
    coilhasbeenused1 = true;
    coilhasbeenused2 = true;
    coilhasbeenused3 = true;
  }

  if (coilhasbeenused1 == false and allowcoil1 and digitalRead(sensorpin1) == LOW){ // Checks if the coil is allowed to work, if the sensor is clear, if the bullet has already passed
    digitalWrite(mosfetpin1, HIGH);
  }
  else{
    digitalWrite(mosfetpin1, LOW);
    coilhasbeenused1 = true;
  }
  
  if (coilhasbeenused2 == false and allowcoil2 and coilhasbeenused1 and digitalRead(sensorpin2) == LOW){
    digitalWrite(mosfetpin2, HIGH);
  }
  else{
    digitalWrite(mosfetpin2, LOW);
    if (coilhasbeenused1){
        coilhasbeenused2 = true;
    }
  }

  if (coilhasbeenused3 == false and allowcoil3 and coilhasbeenused1 and coilhasbeenused2 and digitalRead(sensorpin3) == LOW){
    digitalWrite(mosfetpin3,HIGH);
  }
  else{
    digitalWrite(mosfetpin3, LOW);
    if (coilhasbeenused2){
      coilhasbeenused3 = true;
    }
  }
}
