/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-21 15:56:54 BRT>
 */

#ifndef _EXEC_CONTEXT_H_
#define _EXEC_CONTEXT_H_

#include "global.h"
#include "instruction.h"

class Header {
public:
  Header ()
	 : string_table_len (0),
		num_table_len (0),
		label_table_len (0),
		code_len (0) {}

  unsigned char magic;
  /* vm version */
  unsigned short major_version;
  unsigned short minor_version;

  unsigned short string_table_len;
  unsigned short num_table_len;
  unsigned short label_table_len;
  unsigned short code_len;
};

/* mantem informações que estão sendo executadas */
class ExecContext {
public:
  ExecContext () : current_string_pos (0), pc (0) {}
  ~ExecContext ();

  Header header;
  /* tables */
  char *string_table;
  NUMBER *num_table;
  LABEL *label_table;
  /* code */
  Instruction *code_section;

  int pc;							  /* program counter */
  unsigned short current_string_pos;

  /* necessario apenas no assembler */
  void add_string (const char *string)
  {
	 int len = strlen(string);
	 strcpy ((string_table + current_string_pos), string);
	 string_table[current_string_pos + len] = EOS;
	 current_string_pos += (len + 1);
  }

  inline char * get_string (short n)
  {
	 return string_table + n;
  }

  inline NUMBER get_num (short n)
  {
	 return num_table[n];
  }

  inline LABEL get_label (short n)
  {
	 return label_table[n];
  }

  void load_file (string file_name) 
	 throw (BadFileException, NotRecognizedFileException, bad_alloc);
};

#endif /* _EXEC_CONTEXT_H_ */
