/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-29 19:46:13 BRT>
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
  void load (const string progname);
  void execute ();
  void list () const;

private:
  /* Registers */
  std::map<int, STRING, std::less<int> > s_registers; /* string_registers */
  std::map<int, NUMBER, std::less<int> > n_registers; /* number_registers */
  Error error_emitter;

  ExecContext *current_context;  /* programa sendo executado */
  void dispatch ();

  /* registers get */
  inline STRING RS (const unsigned int i);
  inline NUMBER RN (const unsigned int i);

  /* registers set */
  inline void RS (const unsigned int i,
						const STRING s);
  inline void RN (const unsigned int i,
						const NUMBER n);
};

#endif

