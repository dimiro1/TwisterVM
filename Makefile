CC=g++
CFLAGS=-Wall
ZENOBJS=vm.o zen.o bytecode.o
ZENCOBJS=bytecode.o zenc.o

all: zen.out zenc.out

.DEFAULT: all

zen.out: $(ZENOBJS)
	$(CC) $(CFLAGS) $(ZENOBJS) -o zen.out

zenc.out: $(ZENCOBJS)
	$(CC) $(CFLAGS) $(ZENCOBJS) -o zenc.out

clean:
	rm -f *.o *.out


