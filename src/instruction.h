/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-29 19:37:57 BRT>
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

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "global.h"
#include "opcode.h"

class Instruction {
public:
  Instruction ();
  Instruction (const unsigned int _opcode);

  Instruction (const unsigned int _opcode,
					const unsigned int _A);

  Instruction (const unsigned int _opcode,
					const unsigned int _A,
					const unsigned int _C);

  Instruction (const unsigned int _opcode,
					const unsigned int _A,
					const unsigned int _B,
					const unsigned int _C);

  unsigned int opcode : 8;
  unsigned int A : 12;
  unsigned int B : 12;
  unsigned int C : 12;
};

class TwcFile {
public:
  TwcFile (const int _code_len);
  TwcFile ();
  virtual ~TwcFile ();

  void add_instruction (const Instruction _code_len);
  void alloc_code_section (const int _code_len);
  int magic;
  int code_len;
  int pc;							  /* instrução atual em code section */
  Instruction *code_section;
};


#endif /* _INSTRUCTION_H_ */

