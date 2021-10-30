#include <Arduino.h>

void resetcoil(); // needs to be declared when using .cpp files in VS code, if you build this in Arduino IDE everithing above line 4 does not need to be included

// By default hasfired bool will be set to true and only will be enabled right before activating coils 1 & 2

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

// Software enable/disable for individual coils
bool allowcoil1 = true;
bool allowcoil2 = true;
bool allowcoil3 = true;
bool allowcoil4 = true;
bool allowcoil5 = true;
bool allowcoil6 = true;

// To make sure that a used coil will not turn back on
volatile bool coilhasbeenused1 = true;
volatile bool coilhasbeenused2 = true;
volatile bool coilhasbeenused3 = true;
volatile bool coilhasbeenused4 = true;
volatile bool coilhasbeenused5 = true;
volatile bool coilhasbeenused6 = true; 

void setup() {// just the setup to assign pinmodes // probably can be done more easly, but I don't care, just keep it simple
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

  attachInterrupt(digitalPinToInterrupt(2),resetcoil,RISING); // Interrupt from the other microcontroller
}

void resetcoil(){ // Enables coils for fireing
  coilhasbeenused1 = false;
  coilhasbeenused2 = false;
  coilhasbeenused3 = false;
  coilhasbeenused4 = false;
  coilhasbeenused5 = false;
  coilhasbeenused6 = false;
}

void loop(){ // Currently takes around 60 microseconds to loop, probably can be optimized, if you want you can write it in assembely language if you wish so :)
  if (coilhasbeenused1 == false){ // Checks if the coil is allowed to work, if the sensor is clear, if the bullet has already passed
    if (allowcoil1){
      if (digitalRead(sensorpin1) == LOW){
        digitalWrite(mosfetpin1, HIGH);
      }
    }
  }
  else{
    digitalWrite(mosfetpin1, LOW);
    coilhasbeenused1 = true;
  }
  
  if (coilhasbeenused2 == false){ // Same as coil 1
    if (allowcoil2){
      if (digitalRead(sensorpin2) == LOW){
        digitalWrite(mosfetpin2, HIGH);
      }
    }
  }
  else{
    digitalWrite(mosfetpin2, LOW);
    coilhasbeenused2 = true;
  }

  if (coilhasbeenused3 == false){ // Checks if the coil is allowed to work, if the sensor is clear, if the bullet has passed it's coil and if the bullet has passed two coils prior
    if (coilhasbeenused1){
      if (allowcoil3){
        if (digitalRead(sensorpin3) == LOW){
          digitalWrite(mosfetpin3,HIGH);
        }
      }
    }
  } 
  else{
    digitalWrite(mosfetpin3, LOW);
    if (coilhasbeenused1){
      coilhasbeenused3 = true;
    }
  }
  
  if (coilhasbeenused4 == false){ // Same as coil 3
    if (coilhasbeenused2){
      if (allowcoil4){
        if (digitalRead(sensorpin4) == LOW){
          digitalWrite(mosfetpin4, HIGH);
        }
      }
    }
  }
  else{
    digitalWrite(mosfetpin4, LOW);
    if (coilhasbeenused2){
      coilhasbeenused4 = true;
    }
  }

  if (coilhasbeenused5 == false){ // Same as coil 3
    if (coilhasbeenused3){
      if (allowcoil5){
        if (digitalRead(sensorpin5) == LOW){
          digitalWrite(mosfetpin5, HIGH);
        }
      }
    }
  }
  else{
    digitalWrite(mosfetpin5,LOW);
    if (coilhasbeenused3 == false){
      coilhasbeenused5 = true;
    }
  }

  if (coilhasbeenused6 == false){ // Same as coil 3
    if (coilhasbeenused4){
      if (allowcoil6){
        if (digitalRead(sensorpin6) == LOW){
          digitalWrite(mosfetpin6,HIGH);
        }
      }
    }
  }
  else{
    digitalWrite(mosfetpin6, LOW);
    if (coilhasbeenused4){
      coilhasbeenused6 = true;
    }
  }
}