# Coilgun
Software for my coilgun project

Required Arduino libraries:

  in comms.cpp:
  
    Wire, SPI, Adafruit_GFX, Adafruit_SSD1306
    
  no special libraries are required for stager.cpp
  
 The code is Written in VScode in C++ and using PlatformIO plugin for management.
 
 The code is supposed to run on two Arduino nanos (ATmega328 (New Bootloader)) named Stager and Comms 
 
 Cpp files for both nanos can be found at /Stager/src/Stager.cpp and /Comms/src/Comms.cpp respectively.
 
 Gerber files for the PCB can be found at /PCB.zip 
 
 note that this is not the final PCB design
 
 On the PCB U1 is Comms and U2 is Stager.
