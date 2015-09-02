/********************************************************************************************************
 *                                          Real Time Clock
 ********************************************************************************************************
 */

// Pins do Real time clock p/ chip DS1307
#include <DS1307.h>
#define RTC_SDA A4
#define RTC_SCL A5
DS1307 rtc_ctl(RTC_SDA, RTC_SCL);


void setup_rtc() {
  // Relogio em tempo real DS1307
  rtc_ctl.halt(false);
    
  //Definicoes do pino SQW/Out
  rtc_ctl.setSQWRate(SQW_RATE_1);
  rtc_ctl.enableSQW(true);
}


// Grava uma string do tipo HH:MM no buffer de entrada.
// Assume que o buffer possui pelo menos 6 entradas para 
// conseguir gravar o valor nulo no final da string.
void get_hour_string(char* buffer, uint8_t hour, uint8_t min) {
  buffer[0] = (hour / 10) + 48; // 48 == '0' em ascii
  buffer[1] = (hour % 10) + 48;
  buffer[2] = ':';
  buffer[3] = (min / 10) + 48;
  buffer[4] = (min % 10) + 48;
  buffer[5] = 0; // terminaçao nula da string
}

void get_hour_string(char* buffer) {
  Time time = rtc_ctl.getTime();
  get_hour_string(buffer, time.hour, time.min);
}


// Escreve a hora atual no display.
void display_write_hour() {
  char buffer[6];
  get_hour_string(buffer);
  display_write(buffer);
}


// Retorna um inteiro com o valor da hora
uint8_t get_hour() {
  return rtc_ctl.getTime().hour;
}

void set_hour(uint8_t value) {
  Time current_time = rtc_ctl.getTime();
  rtc_ctl.setTime(value, current_time.min, current_time.sec);
}


// Retorna um inteiro com o valor da hora
uint8_t get_minute() {
  return rtc_ctl.getTime().min;
}

void set_minute(uint8_t value) {
  Time current_time = rtc_ctl.getTime();
  rtc_ctl.setTime(current_time.hour, value, current_time.sec);
}

/********************************************************************************************************
 *                                             Buzzer
 ********************************************************************************************************
 */

#define BUZZER_PIN 9
  
/*
  Desliga o buzzer independentemente do estado atual.
 */
void buzzer_off() {
  noTone(BUZZER_PIN);
  // tone(BUZZER_PIN, freq)
}


/*
  Desliga o buzzer independentemente do estado atual.
 */
void buzzer_on(int freq) {
  tone(BUZZER_PIN, freq);
}


/********************************************************************************************************
 *                                             Main LED
 ********************************************************************************************************
 */
#define MAIN_LIGHT_PIN 4
#define BRIGHTNESS_STEP 8
uint8_t main_light_brightness = 64;

void inline setup_lights() {
  light_on(main_light_brightness);
}


/*
  Desliga a luz principal.
 */
void inline light_off() {
  light_on(0);
}

/*
  Liga a luz principal.
  
  Sem argumentos, configura a luminosidade no valor maximo.
  
  Pode ser chamada com um argumento ajustavel entre 0-255 para valores intermediarios.
 */
void inline light_on(uint8_t value) {
  main_light_brightness = value;
  analogWrite(MAIN_LIGHT_PIN, main_light_brightness);
}

void inline light_on() {
  light_on(255);
}


/*
  As proximas funcoes aumentam/diminuem a luminosidade da luz principal 
  pelo passo dado.
  
  A luminosidade absoluta varia entre 0 e 255.
 */
void increase_brightness(uint8_t step) {
  if (step >= 255 - main_light_brightness) {
    main_light_brightness = 255;
  }
  else {
    main_light_brightness += step;
  }
  analogWrite(MAIN_LIGHT_PIN, main_light_brightness);
}

void increase_brightness() {
  increase_brightness(BRIGHTNESS_STEP);
}

void decrease_brightness(uint8_t step) {
  if (step >= main_light_brightness) {
    main_light_brightness = 0;
  }
  else {
    main_light_brightness -= step;
  }
  analogWrite(MAIN_LIGHT_PIN, main_light_brightness);
}

void decrease_brightness() {
  decrease_brightness(BRIGHTNESS_STEP);
}


