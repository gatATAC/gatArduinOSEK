/* --- Button status broadcast of status buttons and timer measurements --- */

#include "Arduino.h"
#include "gttc_types.h"
#include "gttc_timer.h"
#include "prj_cfg.h"
#include "prj_dre.h"
#include "prj_tty_brcast.h"

uint8_t contButton=BUTTON_BROADCAST_PERIOD_CYCLES;

void buttonBroadcast(void) {
  
  uint8_t i;
  char bufaux[2];
  
  // Vemos si nos toca refrescarlos o no
  contButton--;
  if (contButton<=0){
    contButton=BUTTON_BROADCAST_PERIOD_CYCLES;
    // Los volcamos por el puerto serie

    Serial.print(syncInvocations);
    syncInvocations=0;
    Serial.print(" | ");
    Serial.print(busyMicros);
#ifdef TIMEBASE_USE_MS
    Serial.print(" | ");
    Serial.print(busyMillis);
    Serial.print(" | ");
    Serial.print(previousMillis);
#endif
    Serial.print(" | ");
    Serial.print(previousMicros);
    Serial.print(" -> ");
    for (i=0;i<NUM_BUTTONS;i++){
      Serial.print("Boton");
      Serial.print(itoa(i,bufaux,10));
      Serial.print(": ");
      Serial.print(dre.buttonState[i]);
      Serial.print(" | ");
    }
    Serial.println("");
  }
}

