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

TwcFile::TwcFile (int _code_len)
{
  magic = MAGIC_VERSION_NUM;
  code_len = _code_len;
  pc = 0;
  instructions = new Instruction[_code_len];
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

void TwcFile::alloc_instruction_section (int _code_len)
{
  instructions = new Instruction[_code_len];
  code_len = _code_len;
}

TwcFile::~TwcFile ()
{
  delete [] instructions;
}

