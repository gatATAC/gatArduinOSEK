/* --- Button status broadcast of status buttons and timer measurements --- */

#include "Arduino.h"
#include "gttc_types.h"
#include "prj_tty_brcast.h"
#include "gttc_timer.h"
#include "prj_dre.h"

uint8_t contButton=BUTTON_BROADCAST_PERIOD_CYCLES;

void buttonBroadcast(void) {
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
    Serial.print(" -> Boton1: ");
    Serial.print(dre.buttonState[0]);
    Serial.print(" | Boton2: ");
    Serial.print(dre.buttonState[1]);
    Serial.print(" | Boton3: ");
    Serial.print(dre.buttonState[2]);
    Serial.print(" | Boton4: ");
    Serial.println(dre.buttonState[3]);
  }
}
