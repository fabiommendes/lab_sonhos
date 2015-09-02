/********************************************************************************************************
 *                                           Config hour
 ********************************************************************************************************/
boolean cfg_edit_minutes_hour = true;

void update_cfg_hour() {
  uint8_t hour = get_hour(), min = get_minute();
  edit_hour(&hour, &min, &cfg_edit_minutes_hour);
  set_hour(hour);
  set_minute(min);
  
  // Sai caso o tempo tenha expirado
  if (button_idle() > 5000) {
    change_state(STATE_HOUR);
  }
}


/********************************************************************************************************
 *                                           Config hour
 ********************************************************************************************************/
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
