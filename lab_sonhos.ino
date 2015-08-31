#include <stdint.h>
#include "globals.h"

// Define estado atual
void change_state(state_function_t state) {
  if (RUNNING_STATE != state) {
    button_reset();  
    RUNNING_STATE = state;
  }
}

// Inicializa subsistemas
void setup() {
  setup_lights();
  
  // Grava o estado inicial
  change_state(STATE_HOUR);
}   

// Delega o loop principal para o estado atual
void loop() {
    unsigned long t0 = millis();
    long sleep;
    
    button_poll();
    RUNNING_STATE();
    
    // Mantem uma taxa de atualizaçao de no maximo 20hz
    sleep = 50 - (millis() - t0);
    if (sleep > 0) {
      delay(sleep);
    }
    
}
