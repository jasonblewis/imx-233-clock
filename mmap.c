// http://olimex.wordpress.com/2012/09/11/imx233-olinuxino-gpios-faster-and-faster/
// http://www.jann.cc/2013/05/04/imx233_olinuxino_current_state.html
#include "gpio-mmap.h"

#define BBGPIO_04 0,4 // where BB stands for Bank Bit


int main() {
  gpio_map();
  gpio_output(2,1); //bank 2 bit 1 = GPIO65 the LED on board
  gpio_output(0,1); //bank 2 bit 1 = GPIO65 the LED on board
  gpio_output(0,2); //bank 2 bit 1 = GPIO65 the LED on board
  gpio_output(BBGPIO_04); //bank 2 bit 1 = GPIO65 the LED on board

  while (1) {
    GPIO_WRITE_PIN(65,1);
    GPIO_WRITE_PIN(1,1);
    GPIO_WRITE_PIN(2,1);
    GPIO_WRITE_PIN(4,1);
    sleep(1);
    GPIO_WRITE_PIN(65,0);
    GPIO_WRITE_PIN(1,0);
    GPIO_WRITE_PIN(2,0);
    GPIO_WRITE_PIN(4,0);
    sleep(1);
  }
}
