/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-29 19:39:42 BRT>
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

#include "asm_gen.h"

/* aloca espaço para code_section */
void AsmGen::alloc_code_section (const int _code_len)
{
  context.code_section = new Instruction[_code_len];
}

/* aloca espaço para string_table */
void AsmGen::alloc_string_table_section (const int _len)
{
  context.string_table = new char[_len];
}

/* aloca espaço para num_table */
void AsmGen::alloc_num_table_section (const int _len)
{
  context.num_table = new NUMBER[_len];
}

/* copia strings temporarias para o contexto */
void AsmGen::mount_string_table ()
{
  std::vector<StringDec>::iterator i;
  /* calcula tamanho da tabela de strings */
  for (i = string_table.begin();
		 i != string_table.end (); i++)
	 {
		context.header.string_table_len += (strlen ((*i).name.c_str ()) - 2);
	 }

  /* aloca espaço para tabela de strings */
  context.header.string_table_len += string_table.size ();
  alloc_string_table_section (context.header.string_table_len +
										string_table.size ()); /* adiciona espaço para \0 */

  /* copia strings encontradas para tabela de strings que sera gravada no arquivo */
  for (i = string_table.begin();
		 i != string_table.end (); i++)
	 {
		int offset = 0;
		offset = context.add_string((*i).name.c_str ());
		(*i).offset = offset;
	 }
  /* atualiza strings_indexes no codigo */
  update_references_to_string_table ();
}

/* exibe uma informação sobre a tabela de strings */
void AsmGen::report_string_table () const
{
  std::vector<StringDec>::const_iterator i;
  cout << "-------------------- STRING TABLE --------------------" << endl;
  cout << "lenght: " << context.header.string_table_len
		 << " (" << context.header.string_table_len * sizeof (char)
		 << " bytes)" << endl;
  /* imprime tabela de strings */
  for (i = string_table.begin();
		 i != string_table.end (); i++)
	 {
		cout << "offset: " << (*i).offset
			  << ", lenght: " << (*i).name.size () - 2 /* tamanho - aspas */
			  << " - " << (*i).name << endl;
	 }
}

/* exibe informações sobre a tabela de numeros */
void AsmGen::report_num_table () const
{
  std::vector<NumDec>::const_iterator i;
  cout << "-------------------- NUMBER TABLE --------------------" << endl;
  cout << "lenght: " << context.header.num_table_len
		 << " (" << context.header.num_table_len * sizeof (NUMBER)
		 << " bytes)" << endl;
  for (i = num_table.begin();
		 i != num_table.end (); i++)
	 {
		cout << "offset: " << (*i).offset
			  << " - " << (*i).num << endl;
	 }
}

/* copia numeros da tabela temporaria para o contexto */
void AsmGen::mount_num_table ()
{
  std::vector<NumDec>::const_iterator i;

  /* aloca espaço para tabela de numeros */
  context.header.num_table_len = num_table.size ();
  /* cout << context.header.num_table_len << endl; */
  alloc_num_table_section (context.header.num_table_len);

  for (i = num_table.begin();
		 i != num_table.end (); i++)
		context.add_num ((*i).num);
}

/* copia codigo da tabela temporaria para o contexto */
void AsmGen::mount_code_table ()
{
  std::vector<Instruction *>::const_iterator i;
  int index = 0;
  context.header.code_len = instruction_table.size ();
  alloc_code_section (instruction_table.size ());

  for (i = instruction_table.begin ();
		 i != instruction_table.end (); i++)
	 {
		context.code_section[index++] = *(*i);
	 }
}

/* exibe informações sobre os labels */
void AsmGen::report_label_table () const
{
  std::vector<LabelDec>::const_iterator i;
  cout << "-------------------- LABEL TABLE --------------------" << endl;
  cout << "lenght: " << label_table.size () << endl;
  for (i = label_table.begin ();
		 i != label_table.end (); i++)
	 {
		cout << "offset: " << (*i).offset
			  << " - " << (*i).name << endl;
	 }
}

/* exibe informações sobre instruções */
void AsmGen::report_code () const
{
  cout << "-------------------- INSTRUCTIONS TABLE --------------------" << endl;
  cout << "lenght: " << instruction_table.size ()
		 << " (" << instruction_table.size () * sizeof (Instruction)
		 << " bytes)" << endl;
}

/* atualiza as referencias para as strings no codigo */
void AsmGen::update_references_to_string_table ()
{
  std::vector<StringDec>::const_iterator i_string;
  std::vector<Instruction *>::iterator i_code;
  int index = 0;
  for (i_string = string_table.begin ();
		 i_string != string_table.end (); i_string++)
	 {
		for (i_code = instruction_table.begin ();
			  i_code != instruction_table.end (); i_code++)
		  {
			 if (((*i_code)->opcode == OP_STORE_S) &&
				  (*i_code)->A == index)
				{
				  (*i_code)->A = (*i_string).offset;
				}
		  }
		++index;
	 }
}

/* adiciona string à tabela temporaria */
int AsmGen::add_string (const string _name)
{
  std::vector<StringDec>::const_iterator i_string;

  for (i_string = string_table.begin ();
		 i_string != string_table.end (); i_string++)
	 {
		if ((*i_string).name == _name)
		  return (*i_string).offset;
	 }
  string_table.push_back (StringDec (_name, string_table.size ()));
  return string_table.size () - 1; /* offset da string */
}

/* adicionar numero à tabela temporaria */
int AsmGen::add_num (const NUMBER _num)
{
  std::vector<NumDec>::const_iterator i_num;
  for (i_num = num_table.begin ();
		 i_num != num_table.end (); i_num++)
	 {
		if ((*i_num).num == _num)
		  return (*i_num).offset;
	 }
  num_table.push_back (NumDec (_num, num_table.size ()));
  return num_table.size () - 1;
}

/* atualiza referencias aos labels no codigo */
/* é chamando sempre que um label é definido. */
void AsmGen::update_references_to_label_table (const string _name)
{
  LabelDec *label = get_label (_name);
  std::vector<Instruction *>::iterator i_code;
  for (i_code = label->instructions.begin ();
		 i_code != label->instructions.end (); i_code++)
	 {
		switch ((*i_code)->opcode)
		  {
		  case OP_GOTO:
			 (*i_code)->A = label->offset;
			 break;
		  case OP_LT_S:
		  case OP_GT_S:
		  case OP_LTE_S:
		  case OP_GTE_S:
		  case OP_EQ_S:
		  case OP_NOT_LT_S:
		  case OP_NOT_GT_S:
		  case OP_NOT_LTE_S:
		  case OP_NOT_GTE_S:
		  case OP_NOT_EQ_S:
		  case OP_LT_N:
		  case OP_GT_N:
		  case OP_LTE_N:
		  case OP_GTE_N:
		  case OP_EQ_N:
		  case OP_NOT_LT_N:
		  case OP_NOT_GT_N:
		  case OP_NOT_LTE_N:
		  case OP_NOT_GTE_N:
		  case OP_NOT_EQ_N:
		  case OP_ZERO_N:
		  case OP_NOT_ZERO_N:
			 (*i_code)->C = label->offset;
			 break;
		  }
	 }
}

/* retorna o offset do label */
int AsmGen::get_label_offset (const string _name)
{
  std::vector<LabelDec>::const_iterator i_label;
  for (i_label = label_table.begin ();
		 i_label != label_table.end (); i_label++)
	 {
		if ((*i_label).name == _name)
		  return (*i_label).offset;
	 }
  return 0;
}

/* return the declaration label */
LabelDec * AsmGen::get_label (const string _name)
{
  std::vector<LabelDec>::iterator i_label;
  for (i_label = label_table.begin ();
		 i_label != label_table.end (); i_label++)
	 {
		if ((*i_label).name == _name)
		  return &(*i_label);
	 }
}

/* verifica se o label foi definido */
bool AsmGen::label_defined (const string _name)
{
  std::vector<LabelDec>::const_iterator i_label;
  for (i_label = label_table.begin ();
		 i_label != label_table.end (); i_label++)
	 {
		if ((*i_label).name == _name && (*i_label).defined == true)
		  return true;
	 }
  return false;
}

/* adiciona um novo label, não definido */
bool AsmGen::add_label (const string _name)
{
  std::vector<LabelDec>::const_iterator i_label;
  for (i_label = label_table.begin ();
		 i_label != label_table.end (); i_label++)
	 {
		if ((*i_label).name == _name)
		  return false;
	 }
  label_table.push_back (LabelDec (_name, current_code_line, false));
  return true;
}

/* permite adicionar um novo label, informando seu status */
bool AsmGen::add_label (const string _name, const bool _defined)
{
  std::vector<LabelDec>::iterator i_label;
  for (i_label = label_table.begin ();
		 i_label != label_table.end (); i_label++)
	 {
		if ((*i_label).name == _name)
		  {
			 (*i_label).offset = current_code_line;
			 update_references_to_label_table (_name);
			 (*i_label).defined = true;
			 return false;
		  }
	 }
  label_table.push_back (LabelDec (_name, current_code_line, _defined));
  return true;
}

/* escreve os dados no arquivo. */
void AsmGen::assemble ()
{
  context.header.magic = MAGIC_VERSION_NUM;
  context.header.major_version = VM_VERSION_MAJOR;
  context.header.minor_version = VM_VERSION_MINOR;
  context.header.path_version = VM_VERSION_PATH;

  mount_string_table ();
  mount_num_table ();
  mount_code_table ();

  if (context.header.string_table_len > 0)
	 report_string_table ();
  if (context.header.num_table_len > 0)
	 report_num_table ();
  if (label_table.size () > 0)
	 report_label_table ();

  report_code ();

  output = new ofstream (output_file_name.c_str(), ios::binary);

  output->write ( reinterpret_cast<char *>(&context.header), sizeof (Header));

  if (context.header.string_table_len > 0)
	 output->write ( reinterpret_cast<char *>(context.string_table),
						 context.header.string_table_len * sizeof (char));

  if (context.header.num_table_len > 0)
	 output->write ( reinterpret_cast<char *>(context.num_table),
						 context.header.num_table_len * sizeof (NUMBER));

  output->write ( reinterpret_cast<char *>(context.code_section),
						context.header.code_len * sizeof (Instruction));
  output->close ();
}

/* Colocará o nome do arquivo */
void AsmGen::set_output_file_name (const char *_file_name)
{
  output_file_name = _file_name;
  output_file_name += default_extension;
}
