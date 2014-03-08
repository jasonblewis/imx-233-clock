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


#define lat 53 // header pin 20, bank 1, bit 21
#define output_enable_bar 25 // header pin 24, bank 0, bit 25
#define clk 23 // header pin 26, bank 0, bit 23
#define din 91 // header pin 28, bank 2, bit 27



struct gpio_s {
  int bank;
  int pin;
};

struct gpio_s gpio[] = {
  { 0 ,   0 }, // pin 0 
  { 0 ,   1 }, // pin 1 
  { 0 ,   2 }, // pin 2 
  { 0 ,   3 }, // pin 3 
  { 0 ,   4 }, // pin 4 
  { 0 ,   5 }, // pin 5 
  { 0 ,   6 }, // pin 6 
  { 0 ,   7 }, // pin 7 
  { 0 ,   8 }, // pin 8 
  { 0 ,   9 }, // pin 9 
  { 0 ,  10 }, // pin 10 
  { 0 ,  11 }, // pin 11 
  { 0 ,  12 }, // pin 12 
  { 0 ,  13 }, // pin 13 
  { 0 ,  14 }, // pin 14 
  { 0 ,  15 }, // pin 15 
  { 0 ,  16 }, // pin 16 
  { 0 ,  17 }, // pin 17 
  { 0 ,  18 }, // pin 18 
  { 0 ,  19 }, // pin 19 
  { 0 ,  20 }, // pin 20 
  { 0 ,  21 }, // pin 21 
  { 0 ,  22 }, // pin 22 
  { 0 ,  23 }, // pin 23 
  { 0 ,  24 }, // pin 24 
  { 0 ,  25 }, // pin 25 
  { 0 ,  26 }, // pin 26 
  { 0 ,  27 }, // pin 27 
  { 0 ,  28 }, // pin 28 
  { 0 ,  29 }, // pin 29 
  { 0 ,  30 }, // pin 30 
  { 0 ,  31 }, // pin 31 
  { 1 ,   0 }, // pin 32 
  { 1 ,   1 }, // pin 33 
  { 1 ,   2 }, // pin 34 
  { 1 ,   3 }, // pin 35 
  { 1 ,   4 }, // pin 36 
  { 1 ,   5 }, // pin 37 
  { 1 ,   6 }, // pin 38 
  { 1 ,   7 }, // pin 39 
  { 1 ,   8 }, // pin 40 
  { 1 ,   9 }, // pin 41 
  { 1 ,  10 }, // pin 42 
  { 1 ,  11 }, // pin 43 
  { 1 ,  12 }, // pin 44 
  { 1 ,  13 }, // pin 45 
  { 1 ,  14 }, // pin 46 
  { 1 ,  15 }, // pin 47 
  { 1 ,  16 }, // pin 48 
  { 1 ,  17 }, // pin 49 
  { 1 ,  18 }, // pin 50 
  { 1 ,  19 }, // pin 51 
  { 1 ,  20 }, // pin 52 
  { 1 ,  21 }, // pin 53 
  { 1 ,  22 }, // pin 54 
  { 1 ,  23 }, // pin 55 
  { 1 ,  24 }, // pin 56 
  { 1 ,  25 }, // pin 57 
  { 1 ,  26 }, // pin 58 
  { 1 ,  27 }, // pin 59 
  { 1 ,  28 }, // pin 60 
  { 1 ,  29 }, // pin 61 
  { 1 ,  30 }, // pin 62 
  { 1 ,  31 }, // pin 63 
  { 2 ,   0 }, // pin 64 
  { 2 ,   1 }, // pin 65 
  { 2 ,   2 }, // pin 66 
  { 2 ,   3 }, // pin 67 
  { 2 ,   4 }, // pin 68 
  { 2 ,   5 }, // pin 69 
  { 2 ,   6 }, // pin 70 
  { 2 ,   7 }, // pin 71 
  { 2 ,   8 }, // pin 72 
  { 2 ,   9 }, // pin 73 
  { 2 ,  10 }, // pin 74 
  { 2 ,  11 }, // pin 75 
  { 2 ,  12 }, // pin 76 
  { 2 ,  13 }, // pin 77 
  { 2 ,  14 }, // pin 78 
  { 2 ,  15 }, // pin 79 
  { 2 ,  16 }, // pin 80 
  { 2 ,  17 }, // pin 81 
  { 2 ,  18 }, // pin 82 
  { 2 ,  19 }, // pin 83 
  { 2 ,  20 }, // pin 84 
  { 2 ,  21 }, // pin 85
  { 2 ,  22 }, // pin 86
  { 2 ,  23 }, // pin 87
  { 2 ,  24 }, // pin 88
  { 2 ,  25 }, // pin 89
  { 2 ,  26 }, // pin 90
  { 2 ,  27 }, // pin 91
  { 2 ,  28 }  // pin 92
};



#define Twh1ns 30 // minimum pulse duration  

#define SEND_BYTE_SPI(data)                                              \
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
    }                                                                   \
  }



#define segments 24

uint16_t segment[segments];


void Initialize_SPI(void)
{
  gpio_map();
  // Initialise SPI Interface pins as GPIOs
  gpio_output(gpio[lat].bank,gpio[lat].pin); // lat
  gpio_output(gpio[output_enable_bar].bank,gpio[output_enable_bar].pin); // output_enable_bar
  gpio_output(gpio[clk].bank,gpio[clk].pin); // clk
  gpio_output(gpio[din].bank,gpio[din].pin); // din

  GPIO_WRITE(0,2,1); //clk
  GPIO_WRITE(0,1,1); //din
}

/* END OF SECTION */




void LEDInit(void)
{  	
	// Initialie SPI Interface
    Initialize_SPI();
    for (int i=0; i < segments - 1; i++ ) {
      segment[i] = 0;
      SEND_BYTE_SPI(segment[i]);
    }
      
}

 
int main(int argc, char **argv)
{
	Initialize_SPI();

	return 0;

}



/*
# Local Variables:
# compile-command: "make tlc5947_bitbang"
# End:
*/
