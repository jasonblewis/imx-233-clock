#define GPIO_WRITE_PIN(gpio,value) GPIO_WRITE((gpio)>>5, (gpio)&31, value)
#define GPIO_BASE 0x80018000
#define GPIO_WRITE_PIN(gpio,value) GPIO_WRITE((gpio)>>5, (gpio)&31, value)
#define GPIO_WRITE(bank,pin,value) (gpio_mmap[0x140+((bank)<<2)+((value)?1:2)] = 1<<(pin))
#define GPIO_READ_PIN(gpio) GPIO_READ((gpio)>>5, (gpio)&31)
#define GPIO_READ(bank,pin) ((gpio_mmap[0x180+((bank)<<2)] >> (pin)) & 1)


extern int *gpio_mmap;

void *gpio_map();
int gpio_rd(long offset);
void gpio_wr(long offset, long value);
void gpio_output(int bank, int pin);
void gpio_input(int bank, int pin);

/*
# Local Variables:
# compile-command: "ccache gcc -c gpio-mmap.c -o gpio-mmap.o"
# End:
*/
