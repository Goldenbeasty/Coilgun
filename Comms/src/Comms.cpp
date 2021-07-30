#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void trigger();
void releasetrigger();

const int safety = 4;
const int ohterarduino = 5;
const int volt = A7;

const int RGB_red = 9;
const int RGB_green = 10;
const int RGB_blue = 11;

float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // resistance of R1 (100K) -see text!
float R2 = 10000.0; // resistance of R2 (10K) - see text!
int value = 0; // for calculating Vbat

bool statusmessage = false;
float timeofstatechange = 0;
bool safetystate = true;

void setup(){
    attachInterrupt(digitalPinToInterrupt(2),trigger,RISING);
    attachInterrupt(digitalPinToInterrupt(2),releasetrigger,FALLING);
    pinMode(safety, INPUT);
    pinMode(volt, INPUT);
    pinMode(RGB_red, OUTPUT);
    pinMode(RGB_green, OUTPUT);
    pinMode(RGB_blue, OUTPUT);
}

void trigger(){ // TODO Implement a way to show that trigger is pushed down on OLED
    if (digitalRead(safety) == HIGH){
        digitalWrite(ohterarduino,HIGH);
    }
}
void releasetrigger(){
    digitalWrite(ohterarduino, LOW);
}

void loop(){

    if (digitalRead(safety) == HIGH){
        digitalWrite(RGB_green, LOW);
        digitalWrite(RGB_red, HIGH);
        if (safetystate == true){
            timeofstatechange = millis();
        }
        if (millis() - timeofstatechange < 1000){
            statusmessage = true;
        }
        else{
            statusmessage = false;
        }

        safetystate = false;
    }
    else if (digitalRead(safety) == LOW){
        digitalWrite(RGB_red, LOW);
        digitalWrite(RGB_green, HIGH);
        if (safetystate == false){
            timeofstatechange = millis();
        }
        if (millis() - timeofstatechange < 1000){
            statusmessage = true;
        }
        else{
            statusmessage = false;
        }

        safetystate = true;
    }

    // God's Blessing on this Wonderful World!

    value = analogRead(volt); // read the value at analog input
    vout = (value * 5.0) / 1024.0; // see text
    vin = vout / (R2/(R1+R2)); 
    if (vin<0.09) {
    vin=0.0;//statement to quash undesired reading !
    }
    if (statusmessage == false){
        // TODO OLED refine control, Voltage monitoring
        display.setTextSize(2);             // Draw 2X-scale text
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(8,8);
        display.println(vin);
        display.display();
    }
    else if (statusmessage == true){
        if (digitalRead(safety) == HIGH){
            display.println("SAFETY OFF");
            display.display();
        }
        else if (digitalRead(safety) == LOW){
            display.println("SAFETY ON");
            display.display();
        }
    }
    
}