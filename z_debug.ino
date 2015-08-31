int debug_dec_integer = 0;

void inline setup_debug() {
  // Nada a fazer!
}

void update_debug() {
  // debug_button_statet(BTN_CONFIG);
  debug_print_dec();
}

void debug_print_dec() {
  if (button_click(BTN_RIGHT, 30, 30)) debug_dec_integer++;
  if (button_click(BTN_LEFT, 30, 30)) debug_dec_integer--;
  display_write(debug_dec_integer);
}

void debug_button_state(uint8_t button) {
  unsigned long delta_t = (button_down_duration(button) / 100);
  char buffer[6];
  
  buffer[0] = btn_is_pressed[button]? '1': '0';
  buffer[1] = button_click(button, 500, 500)? '1': '0';
  buffer[2] = (delta_t / 10) % 10 + '0';
  buffer[3] = (delta_t % 10) + '0';

  display_write(buffer);
  delay(200);
}
