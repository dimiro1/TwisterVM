/*
 * vm.h
 * A simple VM implementation
 * Copyright (c) 2009 Claudemiro Alves Feitosa Neto
 */
#ifndef VM_H
#define VM_H

#include "opcode.h"
#include "instruction.h"

#include <cstdio>

#include <iostream>

using std::cout;
using std::endl;
using std::ios;
using std::cerr;

#include <fstream>
using std::ifstream;

#include <stack>

class VM {
 public:

   VM ();
   ~VM ();
   int load (char *progname);
   int execute (Instruction &);
   int run ();
   void reset ();
   void disassemble ();

   void push (float value);
   float pop ();
   float getop (); // get the element in sp top, but dont pop it
   void disassemble_sp ();

 private:

   std::stack<float> sp;
   int pc; // program counter
   Instruction *program;
   int current_program_size; // number of bytecodes
};

#endif						\

