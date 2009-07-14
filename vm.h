/*
 * vm.h
 * A simple VM implementation
 * Copyright (c) 2009 Claudemiro Alves Feitosa Neto
 */
#ifndef VM_H
#define VM_H

#include "opcode.h"
#include "instruction.h"

/* Exceptions */
#include "NotRecognizedFileException.h"
#include "BadFileException.h"

#include <cstdio>
#include <iostream>

using std::cout;
using std::endl;
using std::ios;
using std::cerr;

#include <iomanip>
using std::hex;

#include <fstream>
using std::ifstream;

#include <set>
#include <stack>

/* Memory type */
/* typedef std::set<Object *> Memory; */

class VM {
public:

  VM ();
  ~VM ();

  int load (char *progname) 
	 throw (BadFileException, NotRecognizedFileException);

  int execute ();
  void disassemble ();
  void disassemble_sp ();

private:
  /* Memory mem; */
  std::stack<float> sp;
  int pc; // program counter
  Instruction *code_section;
  int code_len; // number of bytecodes

  const char *running_file_name; /* arquivo sendo executado. */

  void reset ();
  void reset_sp ();
  void push (float value);
  float pop ();
  float top (); // get the element in sp top, but dont pop it
};

#endif

