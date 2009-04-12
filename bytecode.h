#ifndef BYTECODE_H
#define BYTECODE_H

#include "opcode.h"
#include <cstring>

#define MAX_PROGRAM_SIZE 256 // this is horrible
#define MAX_STRING_NAME 50

class ByteCode {
    public:
        ByteCode();
        ByteCode(Opcode _opcode);
        ByteCode(Opcode _opcode, float _operand);

        Opcode opcode;
        float operand;
};


// the compiled program file
// we can't use pointers
// because when writing the Object in a file
// they will be NULL pointers.
// That's why to use an array for instructions with fixed size
// and a fixed size string name
//
// ? How use a list or a vector or some default data structure to save 
// ? the instructions.
class CompiledBytecode {
    public:
        CompiledBytecode(char *_name, int size);
        CompiledBytecode(int _size);
        CompiledBytecode();
        char name[MAX_STRING_NAME]; // can't be a pointer
        int size;
        ByteCode instructions[MAX_PROGRAM_SIZE]; // dirty code
};

#endif

