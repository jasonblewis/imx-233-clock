// http://olimex.wordpress.com/2012/09/11/imx233-olinuxino-gpios-faster-and-faster/
// http://www.jann.cc/2013/05/04/imx233_olinuxino_current_state.html
// gcc -o mm7segment mm7segment.c
#include "gpio-mmap.h"

#define SEGA 16
#define SEGB 7
#define SEGC 6
#define SEGD 5
#define SEGE 4
#define SEGF 51
#define SEGG 2
#define SEGDP 1


int main() {
  gpio_map();
  //  gpio_output(2,1); //bank 2 bit 1 = GPIO65 the LED on board
  gpio_output(0,1);
  gpio_output(0,2);
  gpio_output(0,4);
  gpio_output(0,5);
  gpio_output(0,6);
  gpio_output(0,7);
  gpio_output(0,16);
  gpio_output(1,19);
  
  while (1) {
    GPIO_WRITE_PIN(SEGA,1);
    GPIO_WRITE_PIN(SEGB,1);
    GPIO_WRITE_PIN(SEGC,1);
    GPIO_WRITE_PIN(SEGD,1);
    GPIO_WRITE_PIN(SEGE,1);
    GPIO_WRITE_PIN(SEGF,1);
    GPIO_WRITE_PIN(SEGG,1);
    GPIO_WRITE_PIN(SEGDP,1);
    sleep(1);
    GPIO_WRITE_PIN(SEGA,0);
    GPIO_WRITE_PIN(SEGB,0);
    GPIO_WRITE_PIN(SEGC,0);
    GPIO_WRITE_PIN(SEGD,0);
    GPIO_WRITE_PIN(SEGE,0);
    GPIO_WRITE_PIN(SEGF,0);
    GPIO_WRITE_PIN(SEGG,0);
    GPIO_WRITE_PIN(SEGDP,0);
    sleep(1);
  }
}

/*
# Local Variables:
# compile-command: "gcc -o mm7segment mm7segment.c"
# End:
*/
