#include <Arduino.h>

const int safety = 4;
const int ohterarduino = 5;

void setup(){
attachInterrupt(digitalPinToInterrupt(2),trigger,RISING);
attachInterrupt(digitalPinToInterrupt(2),releasetrigger,FALLING);
pinMode(safety, INPUT);
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

    // TODO OLED control, Voltage monitoring
}