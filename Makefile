CC=g++
COCOR = cococpp
CFLAGS=-Wall
ZENOBJS=vm.o zen.o bytecode.o
ZENCOBJS=bytecode.o zenc.o
FRAMESDIR = "/usr/share/coco-cpp"

all: zen.out zenc.out assembler

.DEFAULT: all

zen.out: $(ZENOBJS)
	$(CC) $(CFLAGS) $(ZENOBJS) -o zen.out

zenc.out: $(ZENCOBJS)
	$(CC) $(CFLAGS) $(ZENCOBJS) -o zenc.out

assembler: assembler/Assembler.o

assembler/Assembler.o: assembler/Parser.o assembler/Scanner.o assembler/Main.o
	$(CC) assembler/Parser.o assembler/Scanner.o assembler/Main.o bytecode.cpp -o assembler/assembler

assembler/Parser.cpp assembler/Scanner.cpp: assembler/Assembler.atg
	$(COCOR) -frames $(FRAMESDIR) assembler/Assembler.atg

assembler/Parser.o assembler/Scanner.o: assembler/Parser.cpp assembler/Scanner.cpp

assembler/Main.o: assembler/Main.cpp

clean:
	rm -f *.o *.out


