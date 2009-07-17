#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <iostream>

#include "opcode.h"
#include <cstring>
#define MAGIC_VERSION_NUM 0x01 // version 0.1

class Instruction {
public:
  Instruction ();
  Instruction (Opcode _opcode);
  Instruction (Opcode _opcode, int _op1);
  Instruction (Opcode _opcode, int _op1, int _op2);
  Instruction (Opcode _opcode, int _op1, int _op2, int _op3);

  Opcode opcode;
  unsigned int op1;
  unsigned int op2;
  unsigned int op3;
};

/* TODO: esta classe deixará de esistir */
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

