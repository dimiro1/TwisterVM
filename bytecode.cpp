#include "opcode.h"
#include "bytecode.h"


ByteCode::ByteCode()
{ 
    opcode = NOP; 
    operand = NULL; 
}

ByteCode::ByteCode(Opcode _opcode)
{
    opcode = _opcode;
    operand = NULL;
}

ByteCode::ByteCode(Opcode _opcode, int _operand)
{
    opcode = _opcode;
    operand = _operand;
}

CompiledBytecode::CompiledBytecode(char *_name, int _size)
{
    strcpy(name, _name);
    size = _size;
}

CompiledBytecode::CompiledBytecode(int _size)
{
    //name = ""; // dirty code
    size = _size;
}

CompiledBytecode::CompiledBytecode()
{
    //name = "";// dirty code
    size = 0;
}

