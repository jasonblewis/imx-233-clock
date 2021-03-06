// http://olimex.wordpress.com/2012/09/11/imx233-olinuxino-gpios-faster-and-faster/
// http://www.jann.cc/2013/05/04/imx233_olinuxino_current_state.html


#include "gpio-mmap.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sched.h>
#include <string.h>

#define BBGPIO_01 0,1 // where BB stands for Bank Bit
#define BBGPIO_02 0,2
#define BBGPIO_04 0,4
#define BBGPIO_05 0,5
#define BBGPIO_06 0,6
#define BBGPIO_07 0,7
#define BBGPIO_16 0,16
#define BBGPIO_51 1,19

   ///bit number 76543210    least significant 7 bits contain the decoder

//                         hgfedcba
#define SSDISP_0 0x3F // 0b00111111
#define SSDISP_1 0x06 // 0b00000110
#define SSDISP_2 0x5B // 0b01011011
#define SSDISP_3 0x4F // 0b01001111
#define SSDISP_4 0x66 // 0b01100110
#define SSDISP_5 0x6D // 0b01101101
#define SSDISP_6 0x7D // 0b01111101
#define SSDISP_7 0x07 // 0b00000111
#define SSDISP_8 0x7F // 0b01111111
#define SSDISP_9 0x6F // 0b01101111


#define SSDISP_a 0b00000001
#define SSDISP_b 0b00000010
#define SSDISP_c 0b00000100
#define SSDISP_d 0b00001000
#define SSDISP_e 0b00010000
#define SSDISP_f 0b00100000
#define SSDISP_g 0b01000000
#define SSDISP_h 0b10000000

const char ssdisp[10] = {
  SSDISP_0,
  SSDISP_1,
  SSDISP_2,
  SSDISP_3,
  SSDISP_4,
  SSDISP_5,
  SSDISP_6,
  SSDISP_7,
  SSDISP_8,
  SSDISP_9
    }; 

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

const unsigned int PWMTable[] = {
  0,    1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 13,
  16,   19, 23, 26, 29, 32,  35,  39,  43,  47,  51,  55, 60, 66,
  71,   77, 84, 91, 98, 106, 114, 123, 133, 143, 154, 166,
  179,  192, 207, 222, 239, 257, 276, 296, 317, 341, 366,
  392,  421, 451, 483, 518, 555, 595, 638, 684, 732, 784,
  840,  900, 964, 1032, 1105, 1184, 1267, 1357, 1453, 1555,
  1665, 1782, 1907, 2042, 2185, 2339, 2503, 2679, 2867, 3069,
  3284, 3514, 3761, 4024, 4096};

const unsigned char max_brightness = 55;

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


int display_number(const digit ldigig, const unsigned char num) {
/* takes a digit of type digit, and a number 0-9 and displays that number on the digit */
  if ((num < 0) || (num > 9) ) {
    //printf("display_number can only accept num from 0-9\n");
    return 1;
      } else {
    for ( int x = 0; x < eSEGH; x++) {
      GPIO_WRITE_PIN(digit1[x],(ssdisp[num] >> x) & 1);
      //printf("displayed %d\n",num);
    }
  }
  return 0;
}

#define sleepon 5
#define sleepoff 1995

int main() {
  
  /* struct sched_param sp; */
  /* memset( &sp, 0, sizeof(sp) ); */
  /* sp.sched_priority = 99; */
  /* sched_setscheduler( 0, SCHED_FIFO, &sp ); */
 

  time_t rawtime;
  struct tm * timeinfo;
  initialise_io();
  
  initialise_digit(digit1);
  /* initialise_digit(digit2); */
  /* initialise_digit(digit3); */
  /* initialise_digit(digit4); */

  #ifdef gperf
  uint32_t loop_counter = 0;
  #endif
  char cursecond = 0;
  bool displayed = false;

  uint64_t sleep_for = 1000*1000*.2;    // 12ms
  uint64_t sleep_for_on = 1000*10*.21;    // 12ms
  uint64_t sleep_for_off = 1000*1000*12;    // 12ms
  
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  
  while (1) {
    if (displayed) {
      sleep_for = sleep_for_off;
    } else {
      sleep_for = sleep_for_on;
    };
    
    uint64_t next_ns = (uint64_t)tp.tv_nsec + sleep_for;
    tp.tv_sec += next_ns  / 1000000000;
    tp.tv_nsec = next_ns % 1000000000;


    // get current time
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    cursecond = (timeinfo->tm_sec) % 10;
    // display last digit of seconds of current time
    if (!displayed) {
        display_number (digit1,(cursecond));
        displayed = true;
    }
    else {
      initialise_digit (digit1);
      displayed = false;
    };
    
 
    
   
    #ifdef gperf
    if (loop_counter++ > 6000000) { 
      exit(0); };
    #endif
    while (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &tp, NULL));
    
  }
}

/*
# Local Variables:
# compile-command: "make clock_nanosleep"
# End:
*/
