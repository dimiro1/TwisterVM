/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-18 09:11:57 BRT>
 */

#include "ExecContext.h"

void ExecContext::load_file (string file_name)
  throw (BadFileException, NotRecognizedFileException, bad_alloc)
{

  ifstream infile (file_name.c_str (), ios::binary);
  
  if (!infile) 
	 throw BadFileException (file_name);

  /* tenta pegar o numero mágico */
  infile.read (reinterpret_cast<char *>(&magic), 
					sizeof (unsigned int));

  if (magic != MAGIC_VERSION_NUM)
	 throw NotRecognizedFileException (file_name);

  /* ler tabelas estaticas */
  /* strings */
  infile.read ( reinterpret_cast<char *>(&string_table_len), 
					 sizeof (unsigned int));
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

  /* numeros */
  infile.read ( reinterpret_cast<char *>(&num_table_len), 
					 sizeof (unsigned int));
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

  /* ler codigo */
  infile.read (reinterpret_cast<char *>(&code_len), 
					sizeof (unsigned int));

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

