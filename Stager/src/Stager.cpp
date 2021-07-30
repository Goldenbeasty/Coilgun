#include <Arduino.h>

void resetcoil(); // needs to be declared when using .cpp files in VS code, if you build this in Arduino IDE everithing above line 4 does not need to be included

// By default hasfired bool will be set to true and only will be enabled right before activating coils 1 & 2

//I'm just a friendly slime

float starttime = 0;

// Pins to sense the high signal of optical sensors
const int sensorpin1 = 7; 
const int sensorpin2 = 8;
const int sensorpin3 = 9;
const int sensorpin4 = 10;
const int sensorpin5 = 11;
const int sensorpin6 = 12;

// Pins to drive the MOSFETs with
const int mosfetpin1 = 14;
const int mosfetpin2 = 15;
const int mosfetpin3 = 16;
const int mosfetpin4 = 17;
const int mosfetpin5 = 18;
const int mosfetpin6 = 19;

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

// const int firesignalpin = 2; // Pin to recive the shoot command // TODO currently unused




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

  Serial.begin(9600);

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
  starttime = micros();

  if (allowcoil1 == true){ // Checks if the coil is alloed to work, if the sensor is clear, if the bullet has already been passed
    if (digitalRead(sensorpin1) == HIGH){
      if (coilhasbeenused1 == false){
        digitalWrite(mosfetpin1, HIGH);
      }
    }
    
    // digitalWrite(mosfetpin1, HIGH);
  }
  else{
    digitalWrite(mosfetpin1, LOW);
    coilhasbeenused1 = true;
  }
  
  if (allowcoil2 == true){ // Sane as coil 1
    if (digitalRead(sensorpin2) == HIGH){
      if (coilhasbeenused2 == false){
        digitalWrite(mosfetpin2, HIGH);
      }
    }
    // digitalWrite(mosfetpin2, HIGH);
  }
  else{
    digitalWrite(mosfetpin2, LOW);
    coilhasbeenused2 = true;
  }

  if (allowcoil3 == true){ // Checks if the coil is allowed to work, if the sensor is clear, if the bullet has passed it's coil and if the bullet has passed two coils prior
    if (digitalRead(sensorpin3) == HIGH){
      if (coilhasbeenused3 == false){
        if (coilhasbeenused1 == true){
          digitalWrite(mosfetpin3,HIGH);
        }
      }
    }
    // digitalWrite(mosfetpin3, HIGH);
  } 
  else{
    digitalWrite(mosfetpin3, LOW);
    if (coilhasbeenused1 == true){
    coilhasbeenused3 = true;
    }
  }
  
  if (allowcoil4 == true){ // Same as coil 3
    if (digitalRead(sensorpin4) == HIGH){
      if (coilhasbeenused4 == false){
        if (coilhasbeenused2 == true){
          digitalWrite(mosfetpin4, HIGH);
        }
      }
    }
    // digitalWrite(mosfetpin4, HIGH);
  }
  else{
    digitalWrite(mosfetpin4, LOW);
    if (coilhasbeenused2 == true){
      coilhasbeenused4 = true;
    }
  }

  if (allowcoil5 == true){ // Same as coil 3
    if (digitalRead(sensorpin5) == HIGH){
      if (coilhasbeenused5 == false){
        if (coilhasbeenused3 == true){
          digitalWrite(mosfetpin5, HIGH);
        }
      }
    }
    // digitalWrite(mosfetpin5,HIGH);
  }
  else{
    digitalWrite(mosfetpin5,LOW);
    if (coilhasbeenused3 == false){
      coilhasbeenused5 = true;
    }
  }

  if (allowcoil6 == true){ // Same as coil 3
    if (digitalRead(sensorpin6) == HIGH){
      if (coilhasbeenused6 == false){
        if (coilhasbeenused4 == true){
          digitalWrite(mosfetpin6,HIGH);
        }
      }
    }
    // digitalWrite(mosfetpin6, HIGH);
  }
  else{
    digitalWrite(mosfetpin6, LOW);
    if (coilhasbeenused4 == true){
      coilhasbeenused6 = true;
    }
  }

Serial.println(micros() - starttime);
}

// table main 60-64 microseconds
// removing allowcoil under 1 microsecond less time spent per loop
// 36 microsecons unoptimized lazy code -_- rlly?