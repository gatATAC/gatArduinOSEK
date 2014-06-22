#include "prj_input.h"
#include "prj_pinout.h"
#include "prj_dre.h"
#include "Arduino.h"

void prjInputInit(void){
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);     
  pinMode(buttonPin2, INPUT);     
  pinMode(buttonPin3, INPUT);     
  pinMode(buttonPin4, INPUT);
}

void prjInput(void){
  // Buttons statuses read
  dre.buttonState[0] = digitalRead(buttonPin1);
  dre.buttonState[1] = digitalRead(buttonPin2);
  dre.buttonState[2] = digitalRead(buttonPin3);
  dre.buttonState[3] = digitalRead(buttonPin4);
}
