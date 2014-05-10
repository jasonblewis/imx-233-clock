#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>
#include "gpio-mmap.h"
#include "tlc5947_bitbang.h"

#define lat 53 // header pin 20, bank 1, bit 21
#define output_enable_bar 25 // header pin 24, bank 0, bit 25
#define clk 23 // header pin 26, bank 0, bit 23
#define din 91 // header pin 28, bank 2, bit 27



#define Twh1ns 30 // minimum pulse duration  

#define SEND_WORD_SPI(data)                                              \
  {                                                                      \
    uint16_t ldata = data;                                                        \
    ldata <<=4;                                                          \
    for(int i = 0; i < 12; i++) {                                        \
      if(ldata & 0x0800) {                                               \
        GPIO_WRITE_PIN(din, 1);                                              \
      } else {                                                          \
        GPIO_WRITE_PIN(din, 0);                                              \
      }                                                                 \
      usleep(1);                                                  \
      GPIO_WRITE_PIN(clk, 0);                                               \
      usleep(1);                                                        \
      GPIO_WRITE_PIN(clk, 1);                                               \
                                                                        \
      ldata <<= 1;                                                       \
    } \
                                          \
  }

void send_word_spi(uint16_t data) {
  uint16_t ldata = data;                                                        
  ldata <<=4;                                                          
  for(int i = 0; i < 12; i++) {                                        
    if(ldata & 0x0800) {                                               
      GPIO_WRITE_PIN(din, 1);                                              
    } else {                                                          
      GPIO_WRITE_PIN(din, 0);                                              
    }                                                                 
    //usleep(1);                                                  
    GPIO_WRITE_PIN(clk, 0);                                               
    usleep(1);                                                        
    GPIO_WRITE_PIN(clk, 1);                                               
    
    ldata <<= 1;                                                       
  } 
}

#define segments 48

uint16_t segment[segments];


void Initialize_SPI(void)
{
  gpio_map();
  // Initialise SPI Interface pins as GPIOs
  gpio_output(gpio[lat].bank,gpio[lat].pin); // lat
  gpio_output(gpio[output_enable_bar].bank,gpio[output_enable_bar].pin); // output_enable_bar
  gpio_output(gpio[clk].bank,gpio[clk].pin); // clk
  gpio_output(gpio[din].bank,gpio[din].pin); // din

  GPIO_WRITE(gpio[clk].bank,gpio[clk].pin,1); //clk
  GPIO_WRITE(gpio[din].bank,gpio[din].pin,1); //din
  GPIO_WRITE(gpio[lat].bank,gpio[lat].pin,1); //lat
  GPIO_WRITE(gpio[output_enable_bar].bank,gpio[output_enable_bar].pin,0); //output_enable_bar
}

/* END OF SECTION */

void setLEDs(void)
{  	
  // send latch low
  GPIO_WRITE(gpio[lat].bank,gpio[lat].pin,0);
  usleep(1);
  
  for (int i=(segments -1); i >= 0; i-- ) {
      send_word_spi(segment[i]);
    }
  usleep(1);
  // send latch high
  GPIO_WRITE(gpio[lat].bank,gpio[lat].pin,1);  
  usleep(1);
      
}

int main(int argc, char **argv)
{
  Initialize_SPI();
  while(1) {
    for (int pos = 0; pos < 24; pos++) {
      segment[pos] = 0x000;
      segment[(pos + 1 ) % 24] = PWMTable[55];
      segment[(pos + 2 ) % 24] = PWMTable[55];
      setLEDs();
      usleep(1);
    }
  }
  return 0;
}


/*
# Local Variables:
# compile-command: "make tlc5947_bitbang"
# End:
*/
