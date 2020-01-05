/************************************************************************************
 * Throttle Quadrant using Arduino Micro & slide potentiometers
 * version 1.1
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
 * v1.1 Switched to Joystick.h (single joystick library) for hassle-free Linux support. Changed behavior to update joystick axis output value
 *      only if raw value changes more than +/-3, to filter input and allow simultaneous keyboard control.
 * 
 **********************************************************************************/





#include "Joystick.h"
#define Joystick_includeRxAxis false
#define Joystick_includeRyAxis false
#define Joystick_includeRzAxis false

uint16_t throttle_l = 0;       // raw data from the slider
uint16_t throttle_lmin = 14, throttle_lmax = 236; //min & max values for calibration
int throttle_l_axis = 0;     // the value to give to the Joystick axis
int tl_old = 0;

uint16_t throttle_r = 0;
uint16_t throttle_rmin = 14, throttle_rmax = 234;
int throttle_r_axis = 0;
int tr_old = 0;

uint16_t prop_l = 0;
uint16_t prop_lmin = 14, prop_lmax = 226;
int prop_l_axis = 0;
int pl_old = 0;

uint16_t prop_r = 0;
uint16_t prop_rmin = 14, prop_rmax = 232;
int prop_r_axis = 0;
int pr_old = 0;

uint16_t mix_l = 0;
uint16_t mix_lmin = 15, mix_lmax = 231;
int mix_l_axis = 0;
int ml_old = 0;

uint16_t mix_r = 0;
uint16_t mix_rmin = 15, mix_rmax = 235;
int mix_r_axis = 0;
int mr_old = 0;

double rotation_multip = 1.591;

/************* SET THIS AS true TO TURN CALIBRATION ON********************/
bool calib = false; //Serial monitor on/off

unsigned int delta(uint16_t a, uint16_t b) {
  int x = a - b;
  return abs(x);
}

void setup() {

  //Check that these are correct for your build
  pinMode(A0, INPUT_PULLUP);  //xa
  pinMode(A1, INPUT_PULLUP);  //ya
  pinMode(A2, INPUT_PULLUP);  //xb
  pinMode(A3, INPUT_PULLUP);  //yb
  pinMode(A4, INPUT_PULLUP);  //xc
  pinMode(A5, INPUT_PULLUP);  //yc

  Serial.begin(9600);
  Joystick.begin(false);

  tl_old = throttle_l = analogRead(A0);
  tr_old = throttle_r = analogRead(A1);
  pl_old = prop_l = analogRead(A2);
  pr_old = prop_r = analogRead(A3);
  ml_old = mix_l = analogRead(A4);
  mr_old = mix_r = analogRead(A5);
  
}

void loop() {
  throttle_l = analogRead(A0);
  throttle_l_axis = 256*throttle_l/(throttle_lmax-throttle_lmin+5) - 128 - throttle_lmin;  //convert raw values -> -128 - 128 (roughly, joystick calibration is still recommended via e.g. Windows joystick interface)
  
  throttle_r = analogRead(A1);
  throttle_r_axis = 256*throttle_r/(throttle_rmax-throttle_rmin+5) - 128 - throttle_rmin;
  
  prop_l = analogRead(A2);
  prop_l_axis = 256*prop_l/(prop_lmax-prop_lmin+5) - 128 - prop_lmin;

  prop_r = analogRead(A3);
  prop_r_axis = prop_r * rotation_multip - (prop_rmin + 5);
  //prop_r_axis = 256*prop_r/(prop_rmax-prop_rmin+5) - prop_rmin;

  mix_l = analogRead(A4);
  mix_l_axis = mix_l * rotation_multip - (mix_lmin + 5);

  mix_r = analogRead(A5);
  mix_r_axis = 254*(mix_r - mix_rmin)/(mix_rmax - mix_rmin);
  
  if(calib==true) {               //Serial monitor for calibration
    Serial.println();
    Serial.print("throttle_l=");Serial.print(throttle_l);
    Serial.print(" -> ");
    Serial.print("throttle_l_axis=");Serial.println(throttle_l_axis);
    Serial.print("throttle_r=");Serial.print(throttle_r);
    Serial.print(" -> ");
    Serial.print("throttle_r_axis=");Serial.println(throttle_r_axis);
    Serial.print("prop_l=");Serial.print(prop_l);
    Serial.print(" -> ");
    Serial.print("prop_l_axis=");Serial.println(prop_l_axis);
    Serial.print("prop_r=");Serial.print(prop_r);
    Serial.print(" -> ");
    Serial.print("prop_r_axis=");Serial.println(prop_r_axis);
    Serial.print("mix_l=");Serial.print(mix_l);
    Serial.print(" -> ");
    Serial.print("mix_l_axis=");Serial.println(mix_l_axis);
    Serial.print("mix_r=");Serial.print(mix_r);
    Serial.print(" -> ");
    Serial.print("mix_r_axis=");Serial.println(mix_r_axis);
  }

  //Set the axis values using Joystick library
        Joystick.setXAxis(throttle_l_axis);
        Joystick.setYAxis(throttle_r_axis);
        Joystick.setZAxis(prop_l_axis);
        Joystick.setXAxisRotation(prop_r_axis);
        Joystick.setYAxisRotation(mix_l_axis);
        Joystick.setRudder(mix_r_axis);
  
 
  if (delta(throttle_l_axis, tl_old)>3 || delta(throttle_r_axis, tr_old)>3 || delta(prop_l_axis, pl_old)>3 || delta(prop_r_axis, pr_old)>3 || delta(mix_l_axis, ml_old)>3 || delta(mix_r_axis, mr_old)>3){
        tl_old = throttle_l_axis;
        tr_old = throttle_r_axis;
        pl_old = prop_l_axis;
        pr_old = prop_r_axis;
        ml_old = mix_l_axis;
        mr_old = mix_r_axis;
        Joystick.sendState();
    
  }

  delay(20);  //this reduces load on the controller
}
