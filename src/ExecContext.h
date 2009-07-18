/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-18 09:10:34 BRT>
 */

#ifndef _EXEC_CONTEXT_H_
#define _EXEC_CONTEXT_H_

#include "instruction.h"
#include <cstring>
#include <cstdlib>

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::cerr;

#include <fstream>
using std::ifstream;

/* Exceptions */
#include <new>
using std::bad_alloc;

#include "NotRecognizedFileException.h"
#include "BadFileException.h"

/* mantem informações que estão sendo executadas */
class ExecContext {
public:
  ExecContext () : current_string_pos (0), pc (0) {}

  /* TODO: mudar para char */
  unsigned int magic;

  /* code */
  unsigned int code_len;
  Instruction *code_section;

  int pc;							  /* program counter */

  /* tables */
  unsigned int string_table_len;
  char *string_table;
  unsigned int num_table_len;
  double *num_table;

  unsigned int current_string_pos;

  /* necessario apenas no assembler */
  void add_string (const char *string)
  {
	 int len = strlen(string);
	 strcpy ((string_table + current_string_pos), string);
	 string_table[current_string_pos + len] = '\0';
	 current_string_pos = len + 1;
  }

  char * get_string (int n)
  {
	 return string_table + n;
  }

  void load_file (string file_name) 
	 throw (BadFileException, NotRecognizedFileException, bad_alloc);
};

#endif /* _EXEC_CONTEXT_H_ */
