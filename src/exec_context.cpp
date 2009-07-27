/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-27 07:58:38 BRT>
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

#include "exec_context.h"

ExecContext::~ExecContext ()
{
  if (header.string_table_len > 0)
	 delete string_table;
  if (header.num_table_len > 0)
	 delete num_table;
  if (header.code_len > 0)
	 delete code_section;
}

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
		try {
		  string_table = new char[header.string_table_len];
		}
		catch (bad_alloc e) {
		  cerr << "Unable to allocate memory to string_table!" << endl;
		  abort ();
		}
		infile.read ( reinterpret_cast<char *>(string_table),
						  header.string_table_len * sizeof (char));
	 }

  /* numeros */
  if (header.num_table_len > 0)
	 {
		try {
		  num_table = new NUMBER[header.num_table_len];
		}
		catch (bad_alloc e) {
		  cerr << "Unable to allocate memory to num_table!" << endl;
		  abort ();
		}

		infile.read ( reinterpret_cast<char *>(num_table),
						  header.num_table_len * sizeof (NUMBER));
	 }

  /* ler codigo */
  try {
	 code_section = new Instruction[header.code_len];
  }
  catch (bad_alloc e) {
	 cerr << "Unable to allocate memory to code_section!" << endl;
	 abort ();
  }

  infile.read (reinterpret_cast<char *>(code_section),
					header.code_len * sizeof (Instruction));

  infile.close ();
}
