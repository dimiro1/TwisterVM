CC=g++
COCOR = cococpp
CFLAGS=-Wall
ZENOBJS=vm.o zen.o bytecode.o
ASMOBJS = assembler/Parser.o assembler/Scanner.o assembler/Main.o bytecode.o assembler/AsmGen.o
FRAMESDIR = "/usr/share/coco-cpp"

all: vm assembler/assembler

vm: $(ZENOBJS)
	$(CC) $(CFLAGS) $(ZENOBJS) -o vm

assembler/assembler: $(ASMOBJS) 
	$(CC) $(CFLAGS) $(ASMOBJS) -o assembler/assembler

assembler/Parser.cpp assembler/Scanner.cpp: assembler/Assembler.atg
	$(COCOR) -frames $(FRAMESDIR) assembler/Assembler.atg

assembler/Parser.o assembler/Scanner.o: assembler/Parser.cpp assembler/Scanner.cpp

assembler/Main.o: assembler/Main.cpp

assembler/AsmGen.o: bytecode.o assembler/AsmGen.h

clean:
	rm -f *.o *.out *.old


