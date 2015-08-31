/********************************************************************************************************
 *                                           Config alarm
 ********************************************************************************************************/
void update_cfg_alarm() {
    display_write("cfga");
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
