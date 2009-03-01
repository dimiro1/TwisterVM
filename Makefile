CC=g++
CFLAGS=-Wall
ZENOBJS=vm.o zen.o bytecode.o
ZENCOBJS=bytecode.o zenc.o

all: zen zenc

.DEFAULT: all

zen: $(ZENOBJS)
	$(CC) $(CFLAGS) $(ZENOBJS) -o zen

zenc: $(ZENCOBJS)
	$(CC) $(CFLAGS) $(ZENCOBJS) -o zenc

clean:
	rm -f *.o

