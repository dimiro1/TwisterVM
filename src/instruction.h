#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "global.h"
#include <iostream>

#include "opcode.h"
#include <cstring>

class Instruction {
public:
  Instruction ();
  Instruction (unsigned int _opcode);
  Instruction (unsigned int _opcode, unsigned int _A);
  Instruction (unsigned int _opcode, unsigned int _A, 
					unsigned int _B);

  Instruction (unsigned int _opcode, unsigned int _A, 
					unsigned int _B, unsigned int _C);

  unsigned int opcode;
  unsigned int A : 12;
  unsigned int B : 12;
  unsigned int C : 12;
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

