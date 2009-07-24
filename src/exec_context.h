/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-24 16:02:01 BRT>
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
		code_len (0) {}

  unsigned char magic;
  /* vm version */
  unsigned short major_version;
  unsigned short minor_version;

  unsigned short string_table_len;
  unsigned short num_table_len;
  unsigned short code_len;
};

/* mantem informações que estão sendo executadas */
/* TODO: mudar o nome para TwcFile */
/* TODO: Criar uma classe para manter as informações que estão em execução.
         Uma especie de Processo.
*/
class ExecContext {
public:
  ExecContext ()
	 : current_string_pos (0),
		current_num_pos (0),
		pc (0) {}
  ~ExecContext ();

  Header header;
  /* tables */
  char *string_table;
  NUMBER *num_table;
  /* code */
  Instruction *code_section;

  int pc;							  /* program counter */
  unsigned short current_string_pos;
  unsigned short current_num_pos;

  /* necessario apenas no assembler */
  int add_string (const char *string)
  {
	 int offset = current_string_pos;
	 int len = strlen (string) - 2; /* remove aspas */
	 strncpy ((string_table + current_string_pos), &string[1], len);
	 string_table[current_string_pos + len] = EOS;
	 current_string_pos += (len + 1);
	 return offset;
  }

  int add_num (NUMBER n)
  {
	 int offset = current_num_pos;
	 num_table[current_num_pos++] = n;
	 return offset;
  }


  inline char * get_string (short n)
  {
	 return string_table + n;
  }

  inline NUMBER get_num (short n)
  {
	 return num_table[n];
  }

  /* FIXME: Responsabilidade da VM */
  void load_file (string file_name)
	 throw (BadFileException, NotRecognizedFileException, bad_alloc);
};

#endif /* _EXEC_CONTEXT_H_ */
