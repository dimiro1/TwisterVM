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
  TwcFile (int _size);
  TwcFile ();
  virtual ~TwcFile ();

  void add_instruction (Instruction _size);
  void alloc_instruction_section (int _size);
  int magic;
  int size;
  int pc;
  Instruction *instructions;
};


#endif /* _INSTRUCTION_H_ */

