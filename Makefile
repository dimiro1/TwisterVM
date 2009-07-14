CC=g++
COCOR = cococpp
CFLAGS=-Wall
VMOBJS=vm.o Twister.o instruction.o
ASMOBJS = assembler/Parser.o assembler/Scanner.o assembler/Twisterc.o instruction.o assembler/AsmGen.o
FRAMESDIR = "/usr/share/coco-cpp"

all: twister assembler/twisterc

opcode.cpp: opcode.h
vm.cpp: vm.h NotRecognizedFileException.h BadFileException.h
instruction.cpp: instruction.h

twister: $(VMOBJS)
	$(CC) $(CFLAGS) $(VMOBJS) -o twister

# Assembler
assembler/twisterc: $(ASMOBJS) 
	$(CC) $(CFLAGS) $(ASMOBJS) -o assembler/twisterc

assembler/Parser.cpp assembler/Scanner.cpp: assembler/Assembler.atg
	$(COCOR) -frames $(FRAMESDIR) assembler/Assembler.atg

assembler/Parser.o assembler/Scanner.o: assembler/Parser.cpp assembler/Scanner.cpp

assembler/Twisterc.o: assembler/Twisterc.cpp

assembler/AsmGen.o: instruction.o assembler/AsmGen.h

clean:
	rm -f *.o *.out *.old


