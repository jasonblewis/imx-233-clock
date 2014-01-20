CC=ccache gcc
CFLAGS=-Wall -std=gnu99 -pedantic 
DEPS = mm7segment.h
OBJ = gpio-mmap.o mm7segment.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
mm7segment: mm7segment.o gpio-mmap.o
	$(CC) -o $@ $^ $(CFLAGS) 

clean:
	rm -f *.o
