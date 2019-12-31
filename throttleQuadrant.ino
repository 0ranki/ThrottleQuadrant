/************************************************************************************
 * Throttle Quadrant using Arduino Micro & slide potentiometers
 * version 1.0
 * 
 * https://github.com/jarnorankinen/ThrottleQuadrant
 * 
 * Jarno Rankinen
 * jarno.rankinen+github@gmail.com
 * 
 * It is recommended to connect one slider at a time and calibrate, then wire the next one and so on.
 * 
 * Check the input pins in setup()!!
 * 
 * Shows up as three joysticks, all named "Arduino Micro", use simulators own interface to bind the controls to correct axis.
 * It may be necessary to invert some axis.
 * 
 * Calibration: (for xa-axis in this example)
 * - Set calib = true
 * - Upload to Arduino
 * - Open the serial monitor
 * - Move the slilder corresponding to xa-axis to its min & max positions
 * - Note the min & max values of xa
 * - Input the values to xamin & xamax
 * - Upload to Arduino
 * - Repeat for each axis
 * 
 * Future features: input averaging to filter the slight movements of levers in simulator
 * 
 **********************************************************************************/





#include "Joystick3.h"

uint16_t xa = 0;       // raw data from the slider
uint16_t xamin = 14, xamax = 236; //min & max values for calibration
int xa_axis = 0;     // the value to give to the Joystick axis

uint16_t ya = 0;
uint16_t yamin = 14, yamax = 234;
int ya_axis = 0;

uint16_t xb = 0;
uint16_t xbmin = 14, xbmax = 226;
int xb_axis = 0;

uint16_t yb = 0;
uint16_t ybmin = 14, ybmax = 232;
int yb_axis = 0;

uint16_t xc = 0;
uint16_t xcmin = 15, xcmax = 231;
int xc_axis = 0;

uint16_t yc = 0;
uint16_t ycmin = 15, ycmax = 235;
int yc_axis = 0;

/************* SET THIS AS true TO TURN CALIBRATION ON********************/
bool calib = false; //Serial monitor on/off

void setup() {

  //Check that these are correct for your build
  pinMode(A0, INPUT_PULLUP);  //xa
  pinMode(A1, INPUT_PULLUP);  //ya
  pinMode(A2, INPUT_PULLUP);  //xb
  pinMode(A3, INPUT_PULLUP);  //yb
  pinMode(A4, INPUT_PULLUP);  //xc
  pinMode(A5, INPUT_PULLUP);  //yc

  Serial.begin(9600);
  Joystick[0].begin();
  Joystick[1].begin();
  Joystick[2].begin();

}

void loop() {
  xa = analogRead(A0);
  xa_axis = 256*xa/(xamax-xamin+5) - 128 - xamin;  //convert raw values -> -128 - 128 (roughly, joystick calibration is still recommended via e.g. Windows joystick interface)
  
  ya = analogRead(A1);
  ya_axis = 256*ya/(yamax-yamin+5) - 128 - yamin;
  
  xb = analogRead(A2);
  xb_axis = 256*xb/(xbmax-xbmin+5) - 128 - xbmin;

  yb = analogRead(A3);
  yb_axis = 256*yb/(ybmax-ybmin+5) - 128 - ybmin;

  xc = analogRead(A4);
  xc_axis = 256*xc/(xcmax-xcmin+5) - 128 - xcmin;

  yc = analogRead(A5);
  yc_axis = 256*yc/(ycmax-ycmin+5) - 128 - ycmin;
  
  if(calib==true) {               //Serial monitor for calibration
    Serial.println();
    Serial.print("xa=");Serial.print(xa);
    Serial.print(" -> ");
    Serial.print("xa_axis=");Serial.println(xa_axis);
    Serial.print("ya=");Serial.print(ya);
    Serial.print(" -> ");
    Serial.print("ya_axis=");Serial.println(ya_axis);
    Serial.print("xb=");Serial.print(xb);
    Serial.print(" -> ");
    Serial.print("xb_axis=");Serial.println(xb_axis);
    Serial.print("yb=");Serial.print(yb);
    Serial.print(" -> ");
    Serial.print("yb_axis=");Serial.println(yb_axis);
    Serial.print("xc=");Serial.print(xc);
    Serial.print(" -> ");
    Serial.print("xc_axis=");Serial.println(xc_axis);
    Serial.print("yc=");Serial.print(yc);
    Serial.print(" -> ");
    Serial.print("yc_axis=");Serial.println(yc_axis);
  }


  //Set the axis values using Joystick library
  Joystick[0].setXAxis(xa_axis);
  Joystick[0].setYAxis(ya_axis);
  Joystick[1].setXAxis(xb_axis);
  Joystick[1].setYAxis(yb_axis);
  Joystick[2].setXAxis(xc_axis);
  Joystick[2].setYAxis(yc_axis);

}
