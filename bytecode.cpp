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
  magic = MAGIC_VERSION_NUM;
  size = _size;
  pc = 0;
  instructions = new ByteCode[_size];
}

CompiledBytecode::CompiledBytecode()
{
  magic = MAGIC_VERSION_NUM;
  pc = 0;
}

void CompiledBytecode::add_instruction (ByteCode _b)
{
  instructions[pc++] = _b;
}

void CompiledBytecode::alloc_instructions (int _size)
{
  instructions = new ByteCode[_size];
  size = _size;
}

CompiledBytecode::~CompiledBytecode ()
{
  delete [] instructions;
}

