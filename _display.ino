/********************************************************************************************************
 *                                             Display
 ********************************************************************************************************
 *
 * Funçoes de configuraçao do display. Utiliza a biblioteca TM1637Display, mas fornece uma interface 
 * que poderia ser adaptada para outros dispositivos. Subentende um display conectado aos pinos CLK e DIO
 * nas posiçoes dadas pelos defines DISPLAY_CLK e DISPLAY_DIO.
 * 
 * As principais funçoes de interaçao como  usuario sao "display_write" e "display_clear"
 */

#include <TM1637Display.h>
#define DISPLAY_CLK 2
#define DISPLAY_DIO 3
TM1637Display global_display_ctl(DISPLAY_CLK, DISPLAY_DIO);

/*
  Imprime uma mensagem no display.
  
  O argumento pode ser uma string de texto no formato "xxxx" ou "xx:xx", ou um numero
  inteiro. No ultimo caso, a funçao aceita um argumento adicional booleano que 
  especifica se o ":" deve ser escrito ou nao.
 */
void display_write(char *text_msg) {
  uint8_t segments[4] = {0, 0, 0, 0};
  uint8_t offset = 0;
   
  // Grava segmentos
  if (text_msg[2] == ':') {
     offset = 1;  
  }
  display_set_char(segments, 0, text_msg[0]);
  display_set_char(segments, 1, text_msg[1]);
  display_set_char(segments, 2, text_msg[2 + offset]);
  display_set_char(segments, 3, text_msg[3 + offset]);
  display_set_colon(segments, text_msg[2] == ':');
  
  // Transfere segmentos para o display
  global_display_ctl.setBrightness(0x0f);
  global_display_ctl.setSegments(segments, 4, 0);
}

void display_write(int number, boolean has_colon) {
  char *msg = "     ";
  boolean is_positive = number >= 0;
  uint8_t offset = (has_colon? 1: 0);
  
  if (!is_positive) {
    number = - number;
  }
  
  // Converte numero para string
  msg[3 + offset] = number % 10;
  msg[2 + offset] = (number / 10) % 10;
  msg[1] = (number / 100) % 10;
  msg[0] = is_positive? (number / 1000) % 10 : '-' - '0';

  // Converte numeros para ascii
  for (int i=0; i < 5; i++) {
    msg[i] += '0';
  }
  
  // Salva ":"
  if (has_colon) {
    msg[2] = ':';
  } 
  
  // Mostra mensagem
  display_write(msg);
}


void display_write(int number) {
  display_write(number, false);
}

/*
  Limpa o display.
 */
void inline display_clear() {
  display_write("    ");
}


/* 
  Imprime um caractere em uma posicao especifica do display
 */
void display_set_char(uint8_t *segments, int pos, char letter) {
  switch (letter) {
    case '\x00':
      segments[pos] = 0b10000000; break;
    case '\x01':
      segments[pos] = 0b01000000; break;
    case '\x02':
      segments[pos] = 0b00100000; break;
    case '\x03':
      segments[pos] = 0b00010000; break;
    case '\x04':
      segments[pos] = 0b00001000; break;
    case '\x05':
      segments[pos] = 0b00000100; break;
    case '\x06':
      segments[pos] = 0b00000010; break;
    case '\x07':
      segments[pos] = 0b00000001; break;  
    case ' ':
      segments[pos] = 0b00000000; break;
    case '-':
      segments[pos] = 0b01000000; break;
    case '0':
      segments[pos] = 0b00111111; break;
    case '1':
      segments[pos] = 0b00000110; break;
    case '2':
      segments[pos] = 0b01011011; break;
    case '3':
      segments[pos] = 0b01001111; break;
    case '4':
      segments[pos] = 0b01100110; break;
    case '5':
      segments[pos] = 0b01101101; break;
    case '6':
      segments[pos] = 0b01111101; break;
    case '7':
      segments[pos] = 0b00000111; break;
    case '8':
      segments[pos] = 0b01111111; break;
    case '9':
      segments[pos] = 0b01101111; break;
    case 'A':
    case 'a':
      segments[pos] = 0b01110111; break;
    case 'B':
    case 'b':
      segments[pos] = 0b01111100; break;
    case 'C':
    case 'c':
      segments[pos] = 0b00111001; break;
    case 'D':
    case 'd':
      segments[pos] = 0b01011110; break;
    case 'E':
    case 'e':
      segments[pos] = 0b01111001; break;
    case 'F':
    case 'f':
      segments[pos] = 0b01110001; break;
    case 'G':
    case 'g':
      segments[pos] = 0b01101111; break;
    case 'H':
    case 'h':
      segments[pos] = 0b01110110; break;
    
    case 'L':
    case 'l':
      segments[pos] = 0b00111000; break;
    case 'M':
    case 'm':
      segments[pos] = 0b01001111; break;
    case 'N':
    case 'n':
      segments[pos] = 0b01010100; break;

    case 'O':
    case 'o':
      segments[pos] = 0b00111111; break;
     
    case 'R':
      segments[pos] = 0b01110111; break;
    case 'r':
      segments[pos] = 0b01010000; break;
    case 'S':
    case 's':
      segments[pos] = 0b01101101; break;
      
    case 'U':
      segments[pos] = 0b00111110; break;
    case 'u':
      segments[pos] = 0b00011100; break;

    default:
      segments[pos] = 0b01010101;
  }
}


/* 
  Liga ou desliga o ":" na mensagem
 */
void display_set_colon(uint8_t *segments, boolean state) {
  if (state == false) {
    segments[1] &= 0b01111111;
  } else {
    segments[1] |= 0b10000000;
  }
}
