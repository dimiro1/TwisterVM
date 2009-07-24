/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-24 20:02:47 BRT>
 */

#include "asm_gen.h"

AsmGen::AsmGen (string _output_file_name)
  : output_file_name (_output_file_name),
	 default_extension (".twc"),
	 current_code_line (0),
	 current_label_index (0)
{
  assembled_file = new TwcFile ();
}

AsmGen::~AsmGen ()
{
  delete assembled_file;
  delete output;
}

void AsmGen::alloc_code_section (int _code_len)
{
  context.code_section = new Instruction[_code_len];
}

void AsmGen::alloc_string_table_section (int _len)
{
  context.string_table = new char[_len];
}

void AsmGen::alloc_num_table_section (int _len)
{
  context.num_table = new NUMBER[_len];
}

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
  alloc_string_table_section (context.header.string_table_len + string_table.size ()); /* adiciona espaço para \0 */

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

void AsmGen::report_string_table ()
{
  std::vector<StringDec>::iterator i;
  cout << "-------------------- STRING TABLE --------------------" << endl;
  cout << "lenght: " << context.header.string_table_len << " (" << context.header.string_table_len * sizeof (char) << " bytes)" << endl;
  /* imprime tabela de strings */
  for (i = string_table.begin();
		 i != string_table.end (); i++)
	 {
		cout << "offset: " << (*i).offset
			  << ", lenght: " << (*i).name.size () - 2 /* tamanho - aspas */
			  << " - " << (*i).name << endl;
	 }
}

void AsmGen::report_num_table ()
{
  std::vector<NumDec>::iterator i;
  cout << "-------------------- NUMBER TABLE --------------------" << endl;
  cout << "lenght: " << context.header.num_table_len << " (" << context.header.num_table_len * sizeof (NUMBER) << " bytes)" << endl;
  for (i = num_table.begin();
		 i != num_table.end (); i++)
	 {
		cout << "offset: " << (*i).offset
			  << " - " << (*i).num << endl;
	 }
}

void AsmGen::mount_num_table ()
{
  std::vector<NumDec>::iterator i;

  /* aloca espaço para tabela de numeros */
  context.header.num_table_len = num_table.size ();
  alloc_num_table_section (context.header.num_table_len);

  for (i = num_table.begin();
		 i != num_table.end (); i++)
	 {
		int offset = 0;
		offset = context.add_num((*i).num);
		(*i).offset = offset;
	 }
  /* update_references_to_num_table (); */
}


void AsmGen::mount_code_table ()
{
  std::vector<Instruction>::const_iterator i;
  int index = 0;
  context.header.code_len = instruction_table.size ();
  alloc_code_section (instruction_table.size ());

  for (i = instruction_table.begin ();
		 i != instruction_table.end (); i++)
	 {
		context.code_section[index++] = (*i);
	 }
}

void AsmGen::report_label_table ()
{
  std::vector<LabelDec>::const_iterator i;
  cout << "-------------------- LABEL TABLE --------------------" << endl;
  cout << "length: " << label_table.size () << endl;
  for (i = label_table.begin ();
		 i != label_table.end (); i++)
	 {
		cout << "offset: " << (*i).offset
			  << " - " << (*i).name << endl;
	 }
}

void AsmGen::update_references_to_string_table ()
{
  std::vector<StringDec>::const_iterator i_string;
  std::vector<Instruction>::iterator i_code;
  int index = 0;
  for (i_string = string_table.begin ();
		 i_string != string_table.end (); i_string++)
	 {
		/* atualiza referencia para o label */
		for (i_code = instruction_table.begin ();
			  i_code != instruction_table.end (); i_code++)
		  {
			 if (((*i_code).opcode == OP_STORE_S || (*i_code).opcode == OP_STORE_N) &&
				  (*i_code).A == index)
				{
				  (*i_code).A = (*i_string).offset;
				}
		  }
		++index;
	 }
}

int AsmGen::add_string (string _name)
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

int AsmGen::add_num (NUMBER _num)
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

void AsmGen::update_references_to_label_table (string _name)
{
  std::vector<LabelDec>::iterator i_label;
  std::vector<Instruction>::iterator i_code;
  int index;
  LabelDec *l_temp;
  index = get_label_index (_name);

  for (i_code = instruction_table.begin ();
		 i_code != instruction_table.end (); i_code++)
	 {
		/* cout << mneumonic[(*i_code).opcode] << " \n"; */
		if ((*i_code).opcode == OP_GOTO && (*i_code).A == index)
		  {
			 (*i_code).A = label_table[index].offset;
		  }
		else if ((*i_code).opcode == OP_EQ_S && (*i_code).C == index)
		  (*i_code).C = label_table[index].offset;
		else if ((*i_code).opcode == OP_EQ_N && (*i_code).C == index)
		  {
			 (*i_code).C = label_table[index].offset;
		  }
	 }
}

int AsmGen::get_label_offset (string _name)
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

bool AsmGen::label_defined (string _name)
{
  std::vector<LabelDec>::iterator i_label;
  for (i_label = label_table.begin ();
		 i_label != label_table.end (); i_label++)
	 {
		if ((*i_label).name == _name && (*i_label).defined == true)
		  return true;
	 }
  return false;
}

int AsmGen::get_label_index (string _name)
{
  std::vector<LabelDec>::iterator i_label;
  for (i_label = label_table.begin ();
		 i_label != label_table.end (); i_label++)
	 {
		if ((*i_label).name == _name)
		  return (*i_label).i;
	 }
  return NULL;
}

bool AsmGen::add_label (string _name)
{
  std::vector<LabelDec>::iterator i_label;
  for (i_label = label_table.begin ();
		 i_label != label_table.end (); i_label++)
	 {
		if ((*i_label).name == _name)
		  return false;
	 }
  label_table.push_back (LabelDec (_name, current_code_line, false, current_label_index));
  current_label_index++;
  return true;
}

bool AsmGen::add_label (string _name, bool _defined)
{
  std::vector<LabelDec>::iterator i_label;
  for (i_label = label_table.begin ();
		 i_label != label_table.end (); i_label++)
	 {
		if ((*i_label).name == _name)
		  {
			 (*i_label).offset = current_code_line;
			 (*i_label).defined = true;
			 return false;
		  }
	 }
  label_table.push_back (LabelDec (_name, current_code_line, _defined, current_label_index));
  current_label_index++;
  return true;
}


void AsmGen::assemble ()
{
  context.header.magic = MAGIC_VERSION_NUM;
  context.header.major_version = VM_VERSION_MAJOR;
  context.header.minor_version = VM_VERSION_MINOR;

  mount_string_table ();
  mount_num_table ();
  mount_code_table ();

  if (context.header.string_table_len > 0)
	 report_string_table ();
  if (context.header.num_table_len > 0)
	 report_num_table ();
  if (label_table.size () > 0)
	 report_label_table ();

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
