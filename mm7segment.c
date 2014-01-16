// http://olimex.wordpress.com/2012/09/11/imx233-olinuxino-gpios-faster-and-faster/
// http://www.jann.cc/2013/05/04/imx233_olinuxino_current_state.html
// gcc -o mm7segment mm7segment.c
#include "gpio-mmap.h"
#include <stdio.h>
#include <time.h>

#define SEGA 16
#define SEGB 7
#define SEGC 6
#define SEGD 5
#define SEGE 4
#define SEGF 51
#define SEGG 2
#define SEGDP 1

#define BBGPIO_01 0,1 // where BB stands for Bank Bit
#define BBGPIO_02 0,2
#define BBGPIO_04 0,4
#define BBGPIO_05 0,5
#define BBGPIO_06 0,6
#define BBGPIO_07 0,7
#define BBGPIO_16 0,16
#define BBGPIO_51 0,51

   ///bit number 76543210    least significant 7 bits contain the decoder
   ///           -abcdefg
#define SSDISP_0 0b01111110
#define SSDISP_1 0b01100000
#define SSDISP_2 0b01101101
#define SSDISP_3 0b01111001
#define SSDISP_4 0b00110011
#define SSDISP_5 0b01011011
#define SSDISP_6 0b01011111
#define SSDISP_7 0b01110000
#define SSDISP_8 0b01110011
#define SSDISP_9 0b01111110


enum ssdigit {  
eSEGA,
  eSEGB,
  eSEGC,
  eSEGD,
  eSEGE,
  eSEGF,
  eSEGG,
  eSEGH,
  item_count
  };

int digit1[item_count]; //= {16,7,6,5,4,51,2,1};

int display_digit(unsigned char num) {
}

int main() {

digit1[eSEGA] = 16;
digit1[eSEGB] = 7;
digit1[eSEGC] = 6;
digit1[eSEGD] = 5;
digit1[eSEGE] = 4;
digit1[eSEGF] = 51;
digit1[eSEGG] = 2;
digit1[eSEGH] = 1;


  gpio_map();
  //  gpio_output(2,1); //bank 2 bit 1 = GPIO65 the LED on board
  gpio_output(BBGPIO_01); 
  gpio_output(BBGPIO_02);
  gpio_output(BBGPIO_04);
  gpio_output(BBGPIO_05);
  gpio_output(BBGPIO_06);
  gpio_output(BBGPIO_07);
  gpio_output(BBGPIO_16);
  gpio_output(BBGPIO_51);
  
  while (1) {
    GPIO_WRITE_PIN(SEGA,1);
    GPIO_WRITE_PIN(SEGB,1);
    GPIO_WRITE_PIN(SEGC,1);
    GPIO_WRITE_PIN(SEGD,1);
    GPIO_WRITE_PIN(SEGE,1);
    GPIO_WRITE_PIN(SEGF,1);
    GPIO_WRITE_PIN(SEGG,1);
//    GPIO_WRITE_PIN(SEGDP,1);
    sleep(1);
    GPIO_WRITE_PIN(SEGA,0);
    GPIO_WRITE_PIN(SEGB,0);
    GPIO_WRITE_PIN(SEGC,0);
    GPIO_WRITE_PIN(SEGD,0);
    GPIO_WRITE_PIN(SEGE,0);
    GPIO_WRITE_PIN(SEGF,0);
    GPIO_WRITE_PIN(SEGG,0);
//    GPIO_WRITE_PIN(SEGDP,0);
    sleep(1);
  }
}

/*
# Local Variables:
# compile-command: "gcc -o mm7segment mm7segment.c"
# End:
*/
