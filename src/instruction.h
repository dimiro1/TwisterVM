#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <iostream>

#include "opcode.h"
#include <cstring>
#define MAGIC_VERSION_NUM 0x01 // version 0.1

class Instruction {
public:
  Instruction();
  Instruction(Opcode _opcode);
  Instruction(Opcode _opcode, float _operand);

  Opcode opcode;
  float operand;
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

