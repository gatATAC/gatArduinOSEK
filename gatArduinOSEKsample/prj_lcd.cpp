#include <Arduino.h>
#include <LiquidCrystal.h>

#include "prj_dre.h"
#include "prj_cfg.h"

//extern LiquidCrystal lcd;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

#ifdef CFG_USE_I2C
const char *rpiStatusStrings[] = {".UNKNOWN","....INIT","...READY","SHUTDOWN",".....OFF"};
#endif

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

void prj_lcd_display_message(uint8_t pos, uint8_t line, char *msg){
  lcd.setCursor(pos,line);
  lcd.print(msg);
}

int read_LCD_buttons(){               // read the buttons
    adc_key_in = analogRead(0);       // read the value from the sensor 

    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result

    if (adc_key_in > 1000) return btnNONE; 

/*
    // For V1.1 comment the other threshold and use the one above:
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 450)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  */

   // For V1.0 us this threshold 
   
     if (adc_key_in < 50)   return btnRIGHT;  
     if (adc_key_in < 195)  return btnUP; 
     if (adc_key_in < 380)  return btnDOWN; 
     if (adc_key_in < 555)  return btnLEFT; 
     if (adc_key_in < 790)  return btnSELECT;   

    return btnNONE;                // when all others fail, return this.
}

#ifdef CFG_USE_I2C
uint8_t last_rpiStatus=RPI_STATUS_UNKNOWN;
#endif

void prj_lcd_setup(void){
   lcd.begin(16, 2);               // start the library
   lcd.setCursor(0,0);             // set the LCD cursor   position 
#ifdef CFG_USE_I2C
   lcd.print("RPiStat.");  // print a simple message on the LCD
   lcd.print(rpiStatusStrings[dre.rpiStatus]);
#else
  lcd.print("Welcome...");
#endif
}

void prj_lcd_process(void){
   //lcd.setCursor(9,1);             // move cursor to second line "1" and 9 spaces over
   //lcd.print(millis()/1000);       // display seconds elapsed since power-up
   //prj_lcd_display_message(6,1,"hola caracola");
   uint8_t i;
   
   for (i=0;i<NUM_BUTTONS;i++){
     lcd.setCursor(7+i,1);
     lcd.print(dre.buttonState[i]);
   }

#ifdef CFG_USE_I2C
  lcd.setCursor(8,0);
  if (last_rpiStatus!=dre.rpiStatus){
    lcd.print(rpiStatusStrings[dre.rpiStatus]);
    last_rpiStatus=dre.rpiStatus;
  }
#endif

  lcd.setCursor(0,1);             // move to the begining of the second line
  lcd_key = read_LCD_buttons();   // read the buttons

  switch (lcd_key){               // depending on which button was pushed, we perform an action

       case btnRIGHT:{             //  push button "RIGHT" and show the word on the screen
            lcd.print("RIGHT ");
            break;
       }
       case btnLEFT:{
             lcd.print("LEFT   "); //  push button "LEFT" and show the word on the screen
             break;
       }    
       case btnUP:{
             lcd.print("UP    ");  //  push button "UP" and show the word on the screen
             break;
       }
       case btnDOWN:{
             lcd.print("DOWN  ");  //  push button "DOWN" and show the word on the screen
             break;
       }
       case btnSELECT:{
             lcd.print("SELECT");  //  push button "SELECT" and show the word on the screen
             break;
       }
       case btnNONE:{
             lcd.print("NONE  ");  //  No action  will show "None" on the screen
             break;
       }
   }
}

