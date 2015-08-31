/********************************************************************************************************
 *                                           Menu
 ********************************************************************************************************/
// Macros e variveis globais
uint8_t menu_global_state = 3;

/* 
Menu obedece ao seguinte protocolo:
    direita: alterna valor do menu para frente
    esquerda: alterna valor do menu para tras
    config: seleciona menu e muda de estado
    
Os estados sao "sonh", "alar", "hora"
 */
void update_menu() {
  boolean do_change = false;
  
  // Verifica açoes de botoes e muda texto em menu
  if (button_click(BTN_RIGHT, 100, 300)) {
    menu_global_state += 1;
    menu_transition();
    
  } else if (button_click(BTN_LEFT, 100, 300)) {
    menu_global_state -= 1;
    menu_transition();
    
  } else if (button_click(BTN_CONFIG, 100, 300)) {
    do_change = true;
    menu_transition();
  }
  menu_global_state = menu_global_state % 3 + 3;
  
  // Escreve no display e possivelmente muda de estado
  switch (menu_global_state) {
    case 0:
    case 3:
      display_write("sonh");
      if (do_change) change_state(STATE_CFG_DREAM);
      break;
    case 1:
    case 4:
      display_write("alar");
      if (do_change) change_state(STATE_CFG_ALARM);
      break;
    case 2:
    case 5:
      display_write("hora");
      if (do_change) change_state(STATE_CFG_HOUR);
      break;
  }
}

