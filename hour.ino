/********************************************************************************************************
 *                                           Config hour
 ********************************************************************************************************/
boolean cfg_edit_minutes = true;

void inline setup_cfg_hour() {
  // Nada a fazer
}

void update_cfg_hour() {
  char buffer[6];
  
  // Faz o display tremer nas horas ou nos minutos
  get_hour_string(buffer);
  display_write(buffer);
  delay(5);
  if (cfg_edit_minutes) {
    buffer[3] = ' ';
    buffer[4] = ' ';
  } else {
    buffer[0] = ' ';
    buffer[1] = ' ';
  }
  display_write(buffer);
  delay(15);
  
  // Le entradas: botao cfg para alternar modo minuto/hora
  if (button_click(BTN_CONFIG, 50, 500)) {
    cfg_edit_minutes = !cfg_edit_minutes;
    
  // Botoes direcionais para alterar valor numerico
  } else if (button_click(BTN_RIGHT, 300, 100)) {
    if (cfg_edit_minutes) {
      set_minute((get_minute() + 1) % 60);
    } else {
      set_hour((get_hour() + 1) % 24);
    }
  } else if (button_click(BTN_LEFT, 300, 100)) {
    if (cfg_edit_minutes) {
      set_minute((get_minute() + 59) % 60);
    } else {
      set_hour((get_hour() + 23) % 24);
    }
  }
  
  // Sai caso o tempo tenha expirado
  if (button_idle() > 5000) {
    change_state(STATE_HOUR);
  }
}


/********************************************************************************************************
 *                                           Config hour
 ********************************************************************************************************/
// Escreve a hora atual no display.
void display_write_hour() {
  char buffer[6];
  get_hour_string(buffer);
  display_write(buffer);
}

void update_hour() {
  void (*event)();
  buzzer_off();
  
  if (button_click(BTN_CONFIG, 200, 500)) {
    change_state(STATE_MENU);
  }
  else if (button_click(BTN_RIGHT, 10)) {
    increase_brightness(10);
  }
  else if (button_click(BTN_LEFT, 10)) {
    decrease_brightness(10);
  }
  
  event = expired_scheduled_event();
  /*if (run_event != NULL) {
    event();
  }*/
  display_write_hour();
}
