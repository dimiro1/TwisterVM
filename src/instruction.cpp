#include "opcode.h"
#include "instruction.h"


Instruction::Instruction ()
{
   opcode = OP_NOP;
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
  code_section = new Instruction[_code_len];
}

TwcFile::TwcFile()
{
  magic = MAGIC_VERSION_NUM;
  pc = 0;
}

void TwcFile::add_instruction (Instruction _b)
{
  code_section[pc++] = _b;
}

void TwcFile::alloc_code_section (int _code_len)
{
  code_section = new Instruction[_code_len];
  code_len = _code_len;
}

TwcFile::~TwcFile ()
{
  delete [] code_section;
}

