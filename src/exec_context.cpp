/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-19 08:49:19 BRT>
 */

#include "exec_context.h"

ExecContext::~ExecContext ()
{
  delete string_table;
  delete num_table;
  delete code_section;
}

/* ARQUIVO */
/*
	Header
	-----------------------------------
	| name              |    bits     |
	-----------------------------------
	| magic             |      8      |
	| string_table_len  |      12     |
	| num_table_len     |      12     |
	| code_len          |      12     |
	-----------------------------------

	Tables and code
	---------------------------------------------
	| name             |       bits             |
	---------------------------------------------
	| header           |           8            |
	| string_table     | string_table_len * 8   |
	| num_table        | num_table_len * 64     |
	| code             |    code_len * 44       |
	---------------------------------------------
 */
void ExecContext::load_file (string file_name)
  throw (BadFileException, NotRecognizedFileException, bad_alloc)
{

  ifstream infile (file_name.c_str (), ios::binary);

  if (!infile)
	 throw BadFileException (file_name);

  /* tenta pegar o cabeçalho */
  infile.read (reinterpret_cast<char *>(&header),
					sizeof (Header));

  if (header.magic != MAGIC_VERSION_NUM)
	 throw NotRecognizedFileException (file_name);

  if (header.string_table_len > 0)
	 {
		try
		  {
			 string_table = new char[header.string_table_len];
		  }
		catch (bad_alloc e)
		  {
			 cerr << "Unable to allocate memory to string_table!" << endl;
			 abort ();
		  }
		infile.read ( reinterpret_cast<char *>(string_table),
						  header.string_table_len * sizeof (char));
	 }

  /* numeros */
  if (header.num_table_len > 0)
	 {
		try
		  {
			 num_table = new double[header.num_table_len];
		  }
		catch (bad_alloc e)
		  {
			 cerr << "Unable to allocate memory to num_table!" << endl;
			 abort ();
		  }

		infile.read ( reinterpret_cast<char *>(num_table),
						  header.num_table_len * sizeof (double));
	 }

  /* ler codigo */
  try
	 {
		code_section = new Instruction[header.code_len];
	 }
  catch (bad_alloc e)
	 {
		cerr << "Unable to allocate memory to code_section!" << endl;
		abort ();
	 }

  infile.read (reinterpret_cast<char *>(code_section),
					header.code_len * sizeof (Instruction));

  infile.close ();
}
