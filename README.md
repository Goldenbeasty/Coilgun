# Coilgun
Software for my coilgun project

Required Arduino libraries:

in comms.cpp:
  
    Adafruit_GFX, Adafruit_SSD1306, Adafruit BusIO
    
no special libraries are required for stager.cpp
  
The code is Written in VScode in C++ and using PlatformIO plugin for management.
 
The code is supposed to run on two Arduino nanos `ATmega328 (New Bootloader)` named Stager and Comms 
 
Cpp files for both nanos can be found at /Stager/src/Stager.cpp and /Comms/src/Comms.cpp respectively.
 
Gerber files for the PCB can be found at /PCB.zip 
 
On the PCB U1 is Comms and U2 is Stager.

 ## Installation

Clone the repo:
    
    git clone https://github.com/Goldenbeasty/Coilgun.git

Install the PlatformIO extention from the marketplace for VScode: Instructions [here](https://platformio.org/platformio-ide)

Open the directory `Comms` in VS code and press `Ctrl + Alt + B` to build the project and `Ctrl + Alt + U` to upload to the Arduino.

Do the same for `Stager`.

### Alternatively using ArduinoIDE

Open the files `Comms.cpp` and `Stager.cpp` in ArduinoIDE and install the libraries. Then upload the code to the Arduino.
