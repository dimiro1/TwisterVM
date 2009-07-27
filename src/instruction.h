/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-27 07:59:13 BRT>
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
  Instruction (unsigned int _opcode);
  Instruction (unsigned int _opcode, unsigned int _A);
  Instruction (unsigned int _opcode, unsigned int _A,
					unsigned int _C);

  Instruction (unsigned int _opcode, unsigned int _A,
					unsigned int _B, unsigned int _C);

  unsigned int opcode : 8;
  unsigned int A : 12;
  unsigned int B : 12;
  unsigned int C : 12;
  /* isso não é muito legal, usado apenas no assembler */
  bool label_defined;			  /* informa se o label foi definido. */
};

class TwcFile {
public:
  TwcFile (int _code_len);
  TwcFile ();
  virtual ~TwcFile ();

  void add_instruction (Instruction _code_len);
  void alloc_code_section (int _code_len);
  int magic;
  int code_len;
  int pc;							  /* instrução atual em code section */
  Instruction *code_section;
};


#endif /* _INSTRUCTION_H_ */

