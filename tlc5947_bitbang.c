#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>
#include "gpio-mmap.h"


//MOSI -> bank[0], pin[20]
//MISO -> bank[0], pin[0]
//SCK -> bank[0], pin[24]
//cs - bank[0], pin[3]
//res - bank[1], pin[23]
//dc  - bank[1], ping[24]g

//////////////////  gpio header pin number
/* #define mosi 0,1 // pin 17  // 16 */
/* #define sck  0,2  // pin 15 // 6 */
/* #define cs   0,4  // pin 11 // 2 */


#define mosi 16 // pin 17  // 16
#define sck  6  // pin 15 // 6
#define cs   2  // pin 11 // 2


#define SEND_BYTE_SPI(data)                                              \
  {                                                                      \
    uint16_t ldata = data;                                                        \
    ldata <<=4;                                                          \
    for(int i = 0; i < 12; i++) {                                        \
      if(ldata & 0x0800) {                                               \
        GPIO_WRITE_PIN(mosi, 1);                                              \
      } else {                                                          \
        GPIO_WRITE_PIN(mosi, 0);                                              \
      }                                                                 \
      nanosleep(1000);                                                  \
      GPIO_WRITE_PIN(sck, 0);                                               \
      nanosleep(1000);                                                  \
      GPIO_WRITE_PIN(sck, 1);                                               \
                                                                        \
      ldata <<= 1;                                                       \
    }                                                                   \
  }



#define segments 24

uint16_t segment[segments];


static void Initialize_SPI(void)
{
  gpio_map();
  // Initialie SPI Interface pins as GPIOs
  gpio_output(0,1);
  gpio_output(0,2);
  gpio_output(0,4);
  
  GPIO_WRITE(0,2,1); //sck
  GPIO_WRITE(0,1,1); //mosi
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
