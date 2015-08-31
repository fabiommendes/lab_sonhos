/********************************************************************************************************
 *                                             Buttons
 ********************************************************************************************************/ 

// Botoes: definiçoes
#define BTN_CONFIG 0
#define BTN_LEFT 1
#define BTN_RIGHT 2
#define BTN_IS_JOYSTICK TRUE
#define BUTTON_COUNT 3

// Joystick
#ifdef BTN_IS_JOYSTICK
  #define joystick_vx_pin A0
  #define joystick_vy_pin A1
  #define JOYSTICK_TOL 50
#endif

// Variaveis globais
boolean btn_is_pressed[3] = {false, false, false};
boolean btn_is_clicked[3] = {false, false, false};
unsigned long btn_down_time[3] = {0, 0, 0};
unsigned long btn_touch_time[3] = {0, 0, 0};
unsigned long btn_poll_time = 0;


/*
  Atualiza o estado de todos os botoes. 
  
  Deve ser executado a cada frame, caso contrario a leitura dos botoes nao 
  funcionara.
 */
void button_poll() {
  btn_poll_time = millis();

  // Poll para botoes do joystick
  //#ifdef BTN_IS_JOYSTICK
    button_update_state(BTN_LEFT, analogRead(joystick_vx_pin) < JOYSTICK_TOL);
    button_update_state(BTN_RIGHT, analogRead(joystick_vx_pin) > 1023 - JOYSTICK_TOL);
    button_update_state(BTN_CONFIG, analogRead(joystick_vy_pin) < JOYSTICK_TOL); 
  //#endif /* BTN_IS_JOYSTICK */ 
}


/*
  Retorna verdadeiro caso o botao tenha sido pressionado.
  
  Se chamada com 3 argumentos, button_press(button, duration, cooldown), o evento 
  de clique sera disparado quando o usuario pressionar o botao por pelo menos duration
  milisegundos. Apos o clique, o botao sera ativo somente apos um periodo igual a 
  cooldown.
  
  Podemos chamar a funçao com 2 argumentos para fazer cooldown=0.
  
  Na forma com um unico argumento, o clique sera disparado somente quando o usuario
  soltar o botao.
 */
boolean button_click(uint8_t button, unsigned long duration, unsigned long cooldown) {
  if (button_down_duration(button) > duration) {
    btn_down_time[button] = btn_poll_time + cooldown;
    return true;
  }
  else {
    return false;
  }
}

boolean inline button_click(uint8_t button, unsigned long duration) {
  return button_click(button, duration, 0);
}

boolean inline button_click(uint8_t button) {
  return btn_is_clicked[button] && (btn_down_time[button] >= btn_poll_time);
}


/*
  Retorna o tempo em que o botao esta pressionado em milisegundos
  
  Caso o botao nao esteja pressionado, retorna zero.
 */
unsigned long button_down_duration(uint8_t button) {
  if (btn_is_pressed[button] && btn_down_time[button]) {
    if (btn_poll_time > btn_down_time[button]) {
      return btn_poll_time - btn_down_time[button];
    } else {
      return 0;
    }
  }
  return 0;
}


/* 
  Zera o contador do tempo em que o botao foi pressionado.
  
  Serve para identificar que um clique longo foi cancelado. Pode ser util
  durante a mudança de estado para que o clique longo nao se preserve
  de um estado para o outro.
 */
void button_reset() {
  for (int i=0; i < BUTTON_COUNT; i++) {
    btn_down_time[i] = 0;
    btn_touch_time[i] = 0;
  }
}


/* 
  Retorna o tempo transcorrido sem que nenhum botao tenha sido pressionado.
 */
unsigned long inline button_idle() {
  unsigned long touch_time = 0;
  for (int i=0; i < BUTTON_COUNT; i++) {
    touch_time = max(btn_touch_time[i], touch_time);
  }
  
  return btn_poll_time - touch_time;
}


/*
  Atualiza o estado de um unico botao.
  
  Funçao auxiliar interna usada para implementar poll_buttons()
 */
void button_update_state(uint8_t button, boolean is_down) {
  boolean was_down = btn_is_pressed[button];
  
  // Continua pressionando
  if (is_down && was_down) {
    btn_is_clicked[button] = false;
    btn_touch_time[button] = btn_poll_time;
  
  // Pressionou neste frame
  } else if (is_down && !was_down) {
    btn_down_time[button] = btn_poll_time;
    btn_is_clicked[button] = false;
    btn_touch_time[button] = btn_poll_time;

  // Soltou neste frame
  } else if ((!is_down) && was_down) {
    btn_down_time[button] = 0;
    btn_is_clicked[button] = true;
    
  // Continuou solto
  } else if ((!is_down) && (!was_down)) {
    btn_down_time[button] = 0;
    btn_is_clicked[button] = false;
  }
  
  btn_is_pressed[button] = is_down;
}
