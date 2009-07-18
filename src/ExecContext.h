/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-18 16:38:30 BRT>
 */

#ifndef _EXEC_CONTEXT_H_
#define _EXEC_CONTEXT_H_

#include "global.h"
#include "instruction.h"
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

  unsigned char magic;
  unsigned char has_string_table;
  unsigned char has_num_table;
  /* tables */
  unsigned short string_table_len;
  char *string_table;
  unsigned short num_table_len;
  double *num_table;

  /* code */
  unsigned short code_len;
  Instruction *code_section;

  int pc;							  /* program counter */
  unsigned short current_string_pos;

  /* necessario apenas no assembler */
  void add_string (const char *string)
  {
	 int len = strlen(string);
	 strcpy ((string_table + current_string_pos), string);
	 string_table[current_string_pos + len] = EOS;
	 current_string_pos = len + 1;
  }

  inline char * get_string (short n)
  {
	 return string_table + n;
  }

  inline double get_num (short n)
  {
	 return num_table[n];
  }

  void load_file (string file_name) 
	 throw (BadFileException, NotRecognizedFileException, bad_alloc);
};

#endif /* _EXEC_CONTEXT_H_ */
