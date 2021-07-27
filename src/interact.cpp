#include <Arduino.h>

const int safety = 4;
const int ohterarduino = 5;
const int volt = A7;

float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // resistance of R1 (100K) -see text!
float R2 = 10000.0; // resistance of R2 (10K) - see text!
int value = 0;

void setup(){
attachInterrupt(digitalPinToInterrupt(2),trigger,RISING);
attachInterrupt(digitalPinToInterrupt(2),releasetrigger,FALLING);
pinMode(safety, INPUT);
pinMode(volt, INPUT);
}

void trigger(){
    if (digitalRead(safety) == HIGH){
        digitalWrite(ohterarduino,HIGH);
    }
}
void releasetrigger(){
    digitalWrite(ohterarduino, LOW);
}

void loop(){
    // God's Blessing on this Wonderful World!
   // read the value at analog input
   value = analogRead(volt);
   vout = (value * 5.0) / 1024.0; // see text
   vin = vout / (R2/(R1+R2)); 
   if (vin<0.09) {
   vin=0.0;//statement to quash undesired reading !
   }
    // TODO OLED control, Voltage monitoring
}