/*
 * vm.h
 * A simple VM implementation
 * Copyright (c) 2009 Claudemiro Alves Feitosa Neto
 */
#ifndef VM_H
#define VM_H

#include "global.h"
#include "exec_context.h"
#include "opcode.h"
#include "instruction.h"
#include "error.h"

#include <cstdio>
#include <iostream>

#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::cerr;

#include <string>
#include <stdexcept>
/* exception */
using std::out_of_range;

#include <map>
#include <stack>

/* Memory type */
/* typedef std::set<Object *> Memory; */

class VM {
public:
  ~VM ();
  void load (string progname);

  void execute ();

#ifdef HAVE_COMPUTED_GOTO
  void dispatch_goto ();
#else
  void dispatch_switch ();
#endif

  void list ();
  void list_sp ();

private:
  /* Registers */
  std::map<int, string, std::less<int> > s_registers; /* string_registers */
  std::map<int, double, std::less<int> > n_registers; /* number_registers */
  Error error_emitter;

  /* TODO: fazer com que a pilha guarde todos os tipos primitivos */
  std::stack<float> sp;
  ExecContext *current_context;  /* programa sendo executado */

  void reset ();
  void reset_sp ();
  void push (float value);
  float pop ();
  float top (); // get the element in sp top, but dont pop it

  /* registers gets */
  inline string RS (int i)
  { 
	 return s_registers[i]; 
  }
  inline double RN (int i)
  { 
	 return n_registers[i];
  }

  /* registers sets */
  inline void RS (int i, string s)
  { 
	 s_registers[i] = s; 
  }
  inline void RN (int i, double n) 
  { 
	 n_registers[i] = n;
  }
};

#endif

