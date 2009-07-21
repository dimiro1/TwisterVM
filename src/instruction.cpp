/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-21 13:44:21 BRT>
 */

#include "instruction.h"

Instruction::Instruction ()
{
   opcode = OP_NOP;
   A = NULL;
	B = NULL;
	C = NULL;
}

Instruction::Instruction (unsigned int _opcode)
{
   opcode = _opcode;
   A = NULL;
	B = NULL;
	C = NULL;
}

Instruction::Instruction (unsigned int _opcode, unsigned int _A)
{
   opcode = _opcode;
   A = _A;
	B = NULL;
	C = NULL;
}

Instruction::Instruction (unsigned int _opcode, unsigned int _A, unsigned int _B)
{
   opcode = _opcode;
   A = _A;
	B = _B;
	C = NULL;
}

Instruction::Instruction (unsigned int _opcode, unsigned int _A, 
								  unsigned int _B, unsigned int _C)
{
   opcode = _opcode;
   A = _A;
	B = _B;
	C = _C;
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

