CC=ccache gcc
CFLAGS=-Wall -std=gnu99 -pedantic  -O0 -fbuiltin -g
# for debugging #defines
#gcc -gdwarf-2 -g3  -std=gnu99 -pedantic -o mm7segment mm7segment.c
DEPS = mm7segment.h
OBJ = gpio-mmap.o mm7segment.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
mm7segment: mm7segment.o gpio-mmap.o
	$(CC) -o $@ $^ $(CFLAGS) 

clean:
	rm -f *.o
