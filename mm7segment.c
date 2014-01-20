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


int display_number(digit ldigig, unsigned char num) {
  usleep(1);
  return 0;
}

int main() {
  
  //gpio_map();
  
  initialise_io();
  
  initialise_digit(digit1);

  while (1) {

    // write a one to each pin in the digit, excluding decimal point
    for ( int x = 0; x < eSEGH; x++) {
      GPIO_WRITE_PIN(digit1[x],1);
    }
    sleep(1);

    for ( int x = 0; x < eSEGH; x++) {
      GPIO_WRITE_PIN(digit1[x],0);
    }
    sleep(1);
  }
}

/*
# Local Variables:
# compile-command: "gcc -Wall -std=gnu99 -pedantic -o mm7segment mm7segment.c"
# End:
*/
