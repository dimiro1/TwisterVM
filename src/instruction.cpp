#include "opcode.h"
#include "instruction.h"


Instruction::Instruction ()
{
   opcode = OP_NOP;
   op1 = NULL;
	op2 = NULL;
	op3 = NULL;
}

Instruction::Instruction (Opcode _opcode)
{
   opcode = _opcode;
   op1 = NULL;
	op2 = NULL;
	op3 = NULL;
}

Instruction::Instruction (Opcode _opcode, int _op1)
{
   opcode = _opcode;
   op1 = _op1;
	op2 = NULL;
	op3 = NULL;
}

Instruction::Instruction (Opcode _opcode, int _op1, int _op2)
{
   opcode = _opcode;
   op1 = _op1;
	op2 = _op2;
	op3 = NULL;
}

Instruction::Instruction (Opcode _opcode, int _op1, int _op2, int _op3)
{
   opcode = _opcode;
   op1 = _op1;
	op2 = _op2;
	op3 = _op3;
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

