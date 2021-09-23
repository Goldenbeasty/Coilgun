#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int safety = 4;
const int ohterarduino = 5;
const int volt = A7;

// Defined RGB control pins (all pins are PWM)
const int RGB_red = 10;
const int RGB_green = 11;
const int RGB_blue = 9;
float R_value = 0;
float G_value = 0;
float B_value = 0;
bool dohuechange = true;
int hue = 0;
float time_of_last_hue_reset = 0;
int huecycle_time = 30000;

// Needed to calculate the battery voltage
float vout = 0.0;
float vin = 0.0;
float R1 = 98100.0; // resistance of R1 (R15)(100K)
float R2 = 10607.0; // resistance of R2 (R16)(10K)
int value = 0; // for calculating Vbat
const float critvoltage = 22.2;

// Needed to display safety change
bool statusmessage = false;
float timeofstatechange = 0;
bool safetystate = true;
bool triggerdown = true;

const int samplecount = 50;
float voltagearray [samplecount];
int currentarray = 0;

void setup(){
    pinMode(2,INPUT); // Set trigger pin
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS); //initialize display
    pinMode(safety, INPUT); // Safety switch Normally LOW
    pinMode(volt, INPUT); // Battery voltage level according to the voltage divider
    pinMode(RGB_red, OUTPUT); // Red led logic output for led strip
    pinMode(RGB_green, OUTPUT); // Green led logic output for led strip
    pinMode(RGB_blue, OUTPUT); // Blue led logic output for led strip

    while (digitalRead(safety) == HIGH){
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(2,2);
        display.println("Switch");
        display.setCursor(2,16);
        display.println("Warning!");
        display.display();
        display.clearDisplay();
        digitalWrite(RGB_red, HIGH);
        digitalWrite(RGB_green, LOW);
        digitalWrite(RGB_blue, LOW);
    }
    while (digitalRead(2) == true){
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(2,2);
        display.println("Trigger");
        display.setCursor(2,16);
        display.println("Warning!");
        display.display();
        display.clearDisplay();
        digitalWrite(RGB_red, LOW);
        digitalWrite(RGB_green, LOW);
        digitalWrite(RGB_blue, HIGH);
    }
}

void loop(){
    if (digitalRead(2) == HIGH){ // Read trigger state
        triggerdown = true;
    }
    else{
        triggerdown = false;
    }

    if (digitalRead(safety) == HIGH){ // Read safety state
        R_value = 255;
        G_value = 0;
        B_value = 0;
        dohuechange = false;

        if (safetystate){
            timeofstatechange = millis();  // Resets statechange timer
        }
        if (millis() - timeofstatechange < 2000){
            statusmessage = true;
        }
        else{
            statusmessage = false;
        }

        safetystate = false;
    }
    else if (digitalRead(safety) == LOW){

        if (millis() - timeofstatechange < 10000){
            R_value = 0;
            G_value = 255;
            B_value = 0;
        }
        else {
            dohuechange = true;
        }

        if (safetystate == false){
            timeofstatechange = millis(); // Resets statechange timer
        }
        if (millis() - timeofstatechange < 2000){
            statusmessage = true;
        }
        else{
            statusmessage = false;
        }

        safetystate = true;
    }

    if (dohuechange){ // Somehow the most difficult part of writing this code
        hue = (millis() - time_of_last_hue_reset) * 360 / huecycle_time; // Calculates current hue based on time passed since last hue reset

        if (0 < hue and hue <= 60){
            G_value = hue * 4.25;
        }
        if (60 < hue and hue <= 120){
            R_value = 255 - ((hue - 60) * 4.25);
        }
        if (120 < hue and hue <= 180){
            B_value = (hue - 120) * 4.25;
        }
        if (180 < hue and hue <= 240){
            G_value = 255 - ((hue - 180) * 4.25);
        }
        if (240 < hue and hue <= 300){
            R_value = (hue - 240) * 4.25;
        }
        if (300 < hue and hue <= 360){
            B_value = 255 - ((hue - 300) * 4.25);
        }
        if (hue > 360){
            time_of_last_hue_reset = millis(); // timer reset

            R_value = 255; // For some reason needed to make it loop nicely
            G_value = 0;
            B_value = 0;
        }
    }

    value = analogRead(volt); // read the value at analog input
    vout = (value * 5.0) / 1024.0;
    vin = vout / (R2/(R1+R2));
    if (vin<0.9) {
    vin=0.0; //statement to quash undesired reading!
    }
    voltagearray [currentarray] = vin;
    for (int i = 0; i < samplecount; i++){
        vin = vin + voltagearray[i];
    }
    vin = vin / samplecount;
    if (currentarray < samplecount){
        currentarray++;
    }
    if(currentarray >= samplecount){
        currentarray = 0;
    }

    if (statusmessage == false){ // Checks for display priority  // Do I need to implement a framerate cap?
        if (safetystate == false){
            display.drawRoundRect(0,0,128,32,3,WHITE);
        }
        display.setTextSize(4); // Draw 3X-scale text
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(2,2);
        display.println(vin);

        if (vin < critvoltage and vin != 0.0){
            display.setCursor(100,4);
            display.setTextSize(1);
            display.println("LOW");
        }

        if (triggerdown){ // BUG #7 when voltage is >= 10 V (2 primary digits) the LOW and PUK indicators are written over
            display.setCursor(100,16);
            display.setTextSize(1);
            display.println("PUK"); // Stands for pumped up kicks
        }
    }
    
    else if (statusmessage){ // Check if screen needs to display safety change
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,13);

        if (digitalRead(safety) == HIGH){
            display.println("SAFETY OFF");
        }
        else if (digitalRead(safety) == LOW){
            display.println("SAFETY ON");
        }
    }

    analogWrite(RGB_red, R_value);
    analogWrite(RGB_green, G_value);
    analogWrite(RGB_blue, B_value);
    Serial.println();
    display.display();
    display.clearDisplay();
}