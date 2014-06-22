#include "prj_output.h"
#include "prj_pinout.h"
#include "prj_dre.h"
#include "Arduino.h"

void prjOutputInit(void){
  // set the digital pin as output:
  pinMode(ledPin1, OUTPUT);      
  pinMode(ledPin2, OUTPUT);      
  pinMode(ledPin3, OUTPUT);      
  pinMode(ledPin4, OUTPUT); 
}

void prjOutput(void){
  digitalWrite(ledPin1,dre.ledState[0]);
  digitalWrite(ledPin2,dre.ledState[1]);
  digitalWrite(ledPin3,dre.ledState[2]);
  digitalWrite(ledPin4,dre.ledState[3]);
}
