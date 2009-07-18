/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-18 20:38:27 BRT>
 */

#include "exec_context.h"

/* ARQUIVO */
/* 
	----------------------------------------------------
	| name             |       bits           |  bytes |
	----------------------------------------------------
	| magic            |         8            |   1    | 
	| has_string_table |         8            |   1    |
	| has_num_table    |         8            |   1    |
	| string_table_len |         16           |   2    |
	| string_table     | string_table_len * 8 |        |
	| num_table_len    |         16           |   2    |
	| num_table        | num_table_len * 64   |        |
	| code_len         |         16           |   2    |
	| code             |    code_len * 96     |        |
	----------------------------------------------------
 */
void ExecContext::load_file (string file_name)
  throw (BadFileException, NotRecognizedFileException, bad_alloc)
{

  ifstream infile (file_name.c_str (), ios::binary);
  
  if (!infile) 
	 throw BadFileException (file_name);

  /* tenta pegar o numero mágico */
  infile.read (reinterpret_cast<char *>(&magic), 
					sizeof (unsigned char));

  if (magic != MAGIC_VERSION_NUM)
	 throw NotRecognizedFileException (file_name);

  /* ler informação sobre tebelas */
  infile.read (reinterpret_cast<char *>(&has_string_table), 
					sizeof (unsigned char));
  infile.read (reinterpret_cast<char *>(&has_num_table), 
					sizeof (unsigned char));

  /* ler tabelas estaticas */
  /* strings */

  if (has_string_table)
	 {
		infile.read ( reinterpret_cast<char *>(&string_table_len), 
						  sizeof (unsigned short));
		try
		  {
			 string_table = new char[string_table_len];
		  }
		catch (bad_alloc e)
		  {
			 cerr << "Unable to allocate memory to string_table!" << endl;
			 abort ();
		  }
		
		infile.read ( reinterpret_cast<char *>(string_table), 
						  string_table_len * sizeof (char));
	 }

  /* numeros */
  if (has_num_table)
	 {
		infile.read ( reinterpret_cast<char *>(&num_table_len), 
						  sizeof (unsigned short));
		try
		  {
			 num_table = new double[num_table_len];
		  }
		catch (bad_alloc e)
		  {
			 cerr << "Unable to allocate memory to num_table!" << endl;
			 abort ();
		  }

		infile.read ( reinterpret_cast<char *>(num_table), 
						  num_table_len * sizeof (double));
	 }

  /* ler codigo */
  infile.read (reinterpret_cast<char *>(&code_len), 
					sizeof (unsigned short));

  try
	 { 
		code_section = new Instruction[code_len];
	 }
  catch (bad_alloc e) 
	 {
		cerr << "Unable to allocate memory to code_section!" << endl;
		abort ();
	 }

  infile.read (reinterpret_cast<char *>(code_section), 
					code_len * sizeof (Instruction));

  infile.close ();
}

