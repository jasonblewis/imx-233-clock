CC=ccache gcc
CFLAGS=-Wall -std=gnu99 -pedantic  -O2
#-g  -fbuiltin -gdwarf-2 -g3 -pg
# for debugging #defines
#gcc -gdwarf-2 -g3  -std=gnu99 -pedantic -o mm7segment mm7segment.c
DEPS = mm7segment.h
OBJ = gpio-mmap.o mm7segment.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c  -o $@ $< 

mm7segment: mm7segment.o gpio-mmap.o
	$(CC) $(CFLAGS) -o $@ $^ 

clock_nanosleep: clock_nanosleep.o gpio-mmap.o
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -f *.o

#distclean: clean
#	rm clock_nanosleep mm7segment


