#ifndef _ASM_GEN_H_
#define _ASM_GEN_H_

#include "../bytecode.h"

#include <iostream>
using std::ios;
using std::endl;
using std::cout;
using std::cerr;

#include <fstream>
using std::ofstream;
using std::ifstream;

#include <string>
using std::string;

class AsmGen {
public:
  AsmGen (string _output_file_name);
  ~AsmGen ();

  void alloc_instruction_array (int _code_len);
  void write_to_file ();

  void emit_add ();
  void emit_div ();
  void emit_getop ();
  void emit_halt ();
  void emit_mult ();
  void emit_nop ();
  void emit_pop ();
  void emit_print ();
  void emit_push (float operand);
  void emit_puts ();
  void emit_reset ();
  void emit_sub ();

private:
  CompiledBytecode *assembled_file;
  string output_file_name;
  ofstream *output_file;
};


#endif /* _ASM_GEN_H_ */
