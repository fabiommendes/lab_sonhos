/********************************************************************************************************
 *                                           Config alarm
 ********************************************************************************************************/
uint8_t alarm_hour = 0, alarm_min = 0;
unsigned long alarm_time;
boolean cfg_edit_minutes_alarm = true;

void edit_hour(uint8_t *hour, uint8_t *min, boolean *edit_minutes) {
  char buffer[6];

  // Faz o display tremer nas horas ou nos minutos
  get_hour_string(buffer, hour[0], min[0]);
  display_write(buffer);
  delay(5);
  if (edit_minutes[0]) {
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
    edit_minutes[0] = !edit_minutes[0];
    
  // Botoes direcionais para alterar valor numerico
  } else if (button_click(BTN_RIGHT, 300, 100)) {
    if (edit_minutes[0]) {
      min[0] = (min[0] + 1) % 60;
    } else {
      hour[0] = (hour[0] + 1) % 24;
    }
  } else if (button_click(BTN_LEFT, 300, 100)) {
    if (edit_minutes) {
      min[0] = (min[0] + 59) % 60; // igual a (min - 1) mod 60, mas respeita sinal
    } else {
      hour[0] = (hour[0] + 23) % 24;
    }
  }
}

void update_cfg_alarm() {
  edit_hour(&alarm_hour, &alarm_min, &cfg_edit_minutes_alarm);
  
  // Sai caso o tempo tenha expirado
  if (button_idle() > 5000) {
    change_state(STATE_HOUR);
  }
}

/********************************************************************************************************
 *                                            Run alarm
 ********************************************************************************************************/
void update_alarm() {
  // Toca alarme e luzes para tentar acordar o usuario
  for (int i=0; i < 4; i++) {
    display_write_hour();
    buzzer_on(755);

    // pisca a luz
    light_on(); delay(50);
    buzzer_on(760);
    light_off(); delay(30);
    light_on(); delay(i == 3? 130: 20);
    
    // para o buzzer
    display_write("  :  ");
    buzzer_off(); delay(20);
  }
  display_write_hour();
  light_off();
  delay(700);
 
  // Verifica se o usuario cancelou
  if (button_click(BTN_CONFIG, 1000, 500)) {
    change_state(STATE_HOUR);
  }
}
