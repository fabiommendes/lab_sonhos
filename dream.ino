/********************************************************************************************************
 *                                           Config dream
 ********************************************************************************************************/
#define DEFAULT_DREAM_DURATION 8
int dream_duration_cfg = DEFAULT_DREAM_DURATION;

void inline setup_cfg_dream() {
    // Nada a fazer!
}

/* 
Configuraçao do inicio do sonho lucido obedece ao seguinte protocolo:
    direita: aumenta a duraçao
    esquerda: diminui a duracao
    config: seleciona a duracao desejada
    
Os estados sao "sonh", "alar", "hora"
 */
void update_cfg_dream() {
  char msg[5];
  
  // Verifica açoes de botoes e muda texto em menu
  if (button_click(BTN_RIGHT, 200, 500)) {
    dream_duration_cfg += 1;
    
  } else if (button_click(BTN_LEFT, 200, 500)) {
    dream_duration_cfg -= 1;
    dream_duration_cfg = max(dream_duration_cfg, -1);
    
  } else if (button_click(BTN_CONFIG, 200, 500)) {
    menu_transition();
    if (dream_duration_cfg >= 0) { 
      change_state(STATE_DREAM);
    } else {
      change_state(STATE_HOUR);
    }
    dream_duration_cfg = DEFAULT_DREAM_DURATION;
    return;
  }
  
  // Escreve um valor na tela correspondente ao valor de dream_duration_cfg
  if (dream_duration_cfg < 0) {
    display_write("off");
  } else {
    set_duration_message(msg, dream_duration_cfg);
    display_write(msg);
  }
  
  // Sai caso o tempo tenha expirado
  if (button_idle() > 5000) {
    if (dream_duration_cfg < 0) {
        change_state(STATE_HOUR);
    } else {
      change_state(STATE_DREAM);
    }
  }
}


/*
  Converte um numero na faixa de "dream_duration_cfg" em uma mensagem de texto
  explicitando as horas
 */
void set_duration_message(char *buffer, int value) {
  buffer[0] = '-';
  buffer[1] = (value / 2) + '0';
  buffer[2] = ':';
  buffer[3] = 3 * (value % 2) + '0';
  buffer[4] = '0';
}


/********************************************************************************************************
 *                                           Run dream
 ********************************************************************************************************/
void update_dream() {
  // Reduz a luz gradualmente (fica insensivel a comando)
  for (int i=0; i < 128; i++) {
     decrease_brightness(2);
     delay(10);
  }
  light_off();
  
  // Entra no estado WAITING
  change_state(STATE_DREAM_WAITING);
}


void update_dream_waiting() {
  display_write("drea");
}


void update_dream_flashing() {
  display_write("drea");
}
