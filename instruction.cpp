#include "opcode.h"
#include "instruction.h"


Instruction::Instruction ()
{
   opcode = NOP;
   operand = NULL;
}

Instruction::Instruction (Opcode _opcode)
{
   opcode = _opcode;
   operand = NULL;
}

Instruction::Instruction (Opcode _opcode, float _operand)
{
   opcode = _opcode;
   operand = _operand;
}

TwcFile::TwcFile (int _size)
{
  magic = MAGIC_VERSION_NUM;
  size = _size;
  pc = 0;
  instructions = new Instruction[_size];
}

TwcFile::TwcFile()
{
  magic = MAGIC_VERSION_NUM;
  pc = 0;
}

void TwcFile::add_instruction (Instruction _b)
{
  instructions[pc++] = _b;
}

void TwcFile::alloc_instruction_section (int _size)
{
  instructions = new Instruction[_size];
  size = _size;
}

TwcFile::~TwcFile ()
{
  delete [] instructions;
}

