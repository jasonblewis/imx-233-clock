// http://olimex.wordpress.com/2012/09/11/imx233-olinuxino-gpios-faster-and-faster/
// http://www.jann.cc/2013/05/04/imx233_olinuxino_current_state.html
// gcc -o mm7segment mm7segment.c


#include "gpio-mmap.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define BBGPIO_01 0,1 // where BB stands for Bank Bit
#define BBGPIO_02 0,2
#define BBGPIO_04 0,4
#define BBGPIO_05 0,5
#define BBGPIO_06 0,6
#define BBGPIO_07 0,7
#define BBGPIO_16 0,16
#define BBGPIO_51 1,19

   ///bit number 76543210    least significant 7 bits contain the decoder
   ///           -abcdefg
//                        hgfedcba
#define SSDISP_0 0x3F //0b00111111
#define SSDISP_1 0x06 //0b00000110
#define SSDISP_2 0b01011011
#define SSDISP_3 0b01001111
#define SSDISP_4 0b01100110
#define SSDISP_5 0b01101101
#define SSDISP_6 0b01111101
#define SSDISP_7 0b00000111
#define SSDISP_8 0b01111111
#define SSDISP_9 0b01101111

#define SSDISP_a 0b00000001
#define SSDISP_b 0b00000010
#define SSDISP_c 0b00000100
#define SSDISP_d 0b00001000
#define SSDISP_e 0b00010000
#define SSDISP_f 0b00100000
#define SSDISP_g 0b01000000
#define SSDISP_h 0b10000000

enum ssdigit {  
  eSEGA,
  eSEGB,
  eSEGC,
  eSEGD,
  eSEGE,
  eSEGF,
  eSEGG,
  eSEGH,
  eSEGDP,
  item_count
};


typedef int digit [item_count]; 
//digit digit1; //= {16,7,6,5,4,51,2,1};
const digit digit1 = {16,7,6,5,4,51,2,1};

void initialise_io() {
  gpio_map();
 
  gpio_output(BBGPIO_01);
  gpio_output(BBGPIO_02);
  gpio_output(BBGPIO_04);
  gpio_output(BBGPIO_05);
  gpio_output(BBGPIO_06);
  gpio_output(BBGPIO_07);
  gpio_output(BBGPIO_16);
  gpio_output(BBGPIO_51);
}
// turn off all segments and dp of a digit
void initialise_digit(const digit ldigit) {
    for ( int x = 0; x < item_count; x++) {
      GPIO_WRITE_PIN(ldigit[x],0);
    }
}


void display_number(const digit ldigig, const unsigned char num) {
  for ( int x = 0; x < eSEGH; x++) {
    GPIO_WRITE_PIN(digit1[x],(SSDISP_9 >> x) & 1);
  }
}

#define sleepon 150000
#define sleepoff 150000
int main() {
  
  initialise_io();
  
  initialise_digit(digit1);
  /* initialise_digit(digit2); */
  /* initialise_digit(digit3); */
  /* initialise_digit(digit4); */

  while (1) {

    // write a one to each pin in the digit, excluding decimal point
    /* for ( int x = 0; x < eSEGH; x++) { */
    /*   GPIO_WRITE_PIN(digit1[x],1); */
    /* } */
    display_number(digit1,7);
    usleep(sleepon);

    /* for ( int x = 0; x < eSEGH; x++) { */
    /*   GPIO_WRITE_PIN(digit1[x],0); */
    /* } */
    initialise_digit(digit1);
    usleep(sleepoff);
  }
}

/*
# Local Variables:
# compile-command: "make mm7segment"
# End:
*/
