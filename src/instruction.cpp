/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-29 19:37:47 BRT>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licences>
 */

#include "instruction.h"

Instruction::Instruction ()
{
   opcode = OP_NOP;
   A = NULL;
	B = NULL;
	C = NULL;
}

Instruction::Instruction (const unsigned int _opcode)
{
   opcode = _opcode;
   A = NULL;
	B = NULL;
	C = NULL;
}

Instruction::Instruction (const unsigned int _opcode,
								  const unsigned int _A)
{
   opcode = _opcode;
   A = _A;
	B = NULL;
	C = NULL;
}

Instruction::Instruction (const unsigned int _opcode,
								  const unsigned int _A,
								  const unsigned int _C)
{
   opcode = _opcode;
   A = _A;
	B = NULL;
	C = _C;
}

Instruction::Instruction (const unsigned int _opcode,
								  const unsigned int _A,
								  const unsigned int _B,
								  const unsigned int _C)
{
   opcode = _opcode;
   A = _A;
	B = _B;
	C = _C;
}

TwcFile::TwcFile (const int _code_len)
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

void TwcFile::add_instruction (const Instruction _b)
{
  code_section[pc++] = _b;
}

void TwcFile::alloc_code_section (const int _code_len)
{
  code_section = new Instruction[_code_len];
  code_len = _code_len;
}

TwcFile::~TwcFile ()
{
  delete [] code_section;
}

