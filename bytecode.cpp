#include "opcode.h"
#include "bytecode.h"


ByteCode::ByteCode ()
{
   opcode = NOP;
   operand = NULL;
}

ByteCode::ByteCode (Opcode _opcode)
{
   opcode = _opcode;
   operand = NULL;
}

ByteCode::ByteCode (Opcode _opcode, float _operand)
{
   opcode = _opcode;
   operand = _operand;
}

CompiledBytecode::CompiledBytecode (int _size)
{
  magic = 0x01;					  /* 0.1 */
  size = _size;
  pc = 0;
  instructions = new ByteCode[_size];
}

CompiledBytecode::CompiledBytecode()
{
   //name = "";// dirty code
   /* size = 0; */
}

void CompiledBytecode::add_instruction (ByteCode b)
{
  instructions[pc++] = b;
}

CompiledBytecode::~CompiledBytecode ()
{
  delete [] instructions;
}

