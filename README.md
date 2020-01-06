# ThrottleQuadrant
A simple 6 axis throttle quadrant for Arduino Micro or Leonardo
Version 1.0

Jarno Rankinen

Requirements:
  Arduino Micro (or Leonardo, as long as its with the ATMega32U4 chip)
  
  6 linear slide potentiometers (10 kOhm is OK)
  
  Wires
  
  USB-microUSB cable
  
  Breadboard (optional)

  Arduino IDE

  Arduino Joystick library: https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-1.0
    This sketch uses the Joystick.h -library
    Download ZIP and place Joystick folder to your Documents/Arduino/libraries directory

Wiring:
  For each slider, connect the 
  - slider's GND to Arduino GND
  - slider's VCC to corresponding analog input
  
  The SIGNAL pin of the slider is left unconnected.
  
  The pins in the slider are as follows:
  
        _____
       | |   |  Vcc
       |   | |  SIG
       |     |
       |     |
       |     |
       |     |
       |     |
       |  |  |  GND
       |_____|
       
Follow the instructions in the beginning of ThrottleQuadrant.ino to calibrate the sliders.

Enjoy flying!
