/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-22 10:19:12 BRT>
 */

#ifndef VM_H
#define VM_H

#include "global.h"
/* informações sobre dispatch de instruções */
#include "dispatch.h"
#include "exec_context.h"
#include "instruction.h"

class VM {
public:
  ~VM ();
  void load (string progname);
  void execute ();
  void list ();
    
private:
  /* Registers */
  std::map<int, STRING, std::less<int> > s_registers; /* string_registers */
  std::map<int, NUMBER, std::less<int> > n_registers; /* number_registers */
  Error error_emitter;

  ExecContext *current_context;  /* programa sendo executado */
  void dispatch ();

  /* registers gets */
  inline STRING RS (int i);
  inline NUMBER RN (int i);

  /* registers sets */
  inline void RS (int i, STRING s);
  inline void RN (int i, NUMBER n);
};

#endif

