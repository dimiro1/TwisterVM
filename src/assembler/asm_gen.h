/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-27 16:27:10 BRT>
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

#ifndef _ASM_GEN_H_
#define _ASM_GEN_H_

#include "../exec_context.h"
#include "../instruction.h"

#include <iostream>
using std::ios;
using std::endl;
using std::cout;
using std::cerr;

#include <fstream>
using std::ofstream;
using std::ifstream;

#include <string>
using std::string;

#include <vector>
#include <algorithm>

/* declaração temporaria de label */
class LabelDec {
public:
  LabelDec ()
	 : name (NULL),
		offset (NULL),
		defined (false),
		i (NULL){}

  LabelDec (string _name)
	 : name (_name),
		offset (NULL),
		defined (false),
		i (NULL){}

  LabelDec (string _name, int _offset)
	 : name (_name),
		offset (_offset),
		defined (false),
		i (NULL){}

  LabelDec (string _name, int _offset, bool _defined)
	 : name (_name),
		offset (_offset),
		defined (_defined),
		i (NULL) {}

  LabelDec (string _name, int _offset, bool _defined, int _i)
	 : name (_name),
		offset (_offset),
		defined (_defined),
		i (_i) {}

  int i;
  string name;
  int offset;
  bool defined;
};

/* declaração temporaria de string */
class StringDec {
public:
  StringDec ()
	 : name (NULL),
		offset (NULL){}

  StringDec (string _name)
	 : name (_name),
		offset (NULL) {}

  StringDec (string _name, int _offset)
	 : name (_name),
		offset (_offset){}

  string name;
  int offset;
};

/* declaração temporaria de string */
class NumDec {
public:
  NumDec ()
	 : num (NULL),
		offset (NULL) {}

  NumDec (NUMBER _num)
	 : num (_num),
		offset (NULL) {}

  NumDec (NUMBER _num, int _offset)
	 : num (_num),
		offset (_offset) {}

  NUMBER num;
  int offset;
};

class AsmGen {
public:
  AsmGen (string _output_file_name)
	 : output_file_name (_output_file_name),
		default_extension (".twc"),
		current_code_line (0),
		current_label_index (0) {}

  ~AsmGen ()
  {
	 delete output;
  }

  void assemble ();
  void set_output_file_name (const char *_file_name);

  /* adiciona string à tabela de strings temporaria */
  int add_string (string _name);

  /* adiciona num à tabela de num temporaria */
  int add_num (double _num);

  /* atualiza as referencias anteriores */
  /* deve atualizar todas as instruções que fazem goto */
  void update_references_to_label_table (string _name);

  /* adiciona um novo label */
  bool add_label (string _name);
  bool add_label (string _name, bool _defined);

  /* retorna o offset do label */
  int get_label_offset (string _name);

  inline void add_instruction (unsigned int _opcode, int _A, int _C)
  {
	 instruction_table.push_back (Instruction (_opcode, _A, _C));
  }

  inline void add_instruction (unsigned int _opcode, int _A, int _B, int _C)
  {
	 instruction_table.push_back (Instruction (_opcode, _A, _B, _C));
  }

  inline void add_instruction (unsigned int _opcode, int _A)
  {
	 instruction_table.push_back (Instruction (_opcode, _A));
  }

  inline void add_instruction (unsigned int _opcode)
  {
	 instruction_table.push_back (Instruction (_opcode));
  }

  inline void add_instruction (unsigned int _opcode, int _A, int _B, string _label_name)
  {
	 if (label_defined (_label_name))
		{
		  Instruction i (_opcode, _A, _B, get_label_offset (_label_name));
		  i.label_defined = true;
		  instruction_table.push_back (i);
		}
	 else
		{
		  Instruction i (_opcode, _A, _B, get_label_index (_label_name));
		  i.label_defined = false;
		  instruction_table.push_back (i);
		}
  }

  inline void add_instruction (unsigned int _opcode, int _A, string _label_name)
  {
	 if (label_defined (_label_name))
		{
		  Instruction i (_opcode, _A, get_label_offset (_label_name));
		  i.label_defined = true;
		  instruction_table.push_back (i);
		}
	 else
		{
		  Instruction i (_opcode, _A, get_label_index (_label_name));
		  i.label_defined = false;
		  instruction_table.push_back (i);
		}
  }

  inline void add_instruction (unsigned int _opcode, string _label_name)
  {
	 if (label_defined (_label_name))
		{
		  Instruction i (_opcode, get_label_offset (_label_name));
		  i.label_defined = true;
		  instruction_table.push_back (i);
		}
	 else
		{
		  Instruction i (_opcode, get_label_index (_label_name));
		  i.label_defined = false;
		  instruction_table.push_back (i);
		}
  }


  inline void inc_code_line () { current_code_line++; }
  inline void dec_code_line () { current_code_line--; }

  inline int get_code_line () { return current_code_line; }

  bool label_defined (string _name);
  int get_label_index (string _name);

private:
  int current_code_line;		  /* atual linha de codigo. */
  int current_label_index;
  string output_file_name;
  ofstream *output;
  string default_extension;
  ExecContext context;

  /* tabelas temporarias */
  std::vector<StringDec> string_table;
  std::vector<NumDec> num_table;
  std::vector<LabelDec> label_table;
  std::vector<Instruction> instruction_table;

  /* pega strings de StringDec e as coloca no arquivo. */
  void mount_string_table ();
  void report_string_table ();
  void mount_num_table ();
  void report_num_table ();
  void report_label_table ();
  void mount_code_table ();
  void report_code ();

  /* aloca espaço para as tabelas */
  void alloc_string_table_section (int _len);
  void alloc_num_table_section (int _len);
  void alloc_code_section (int _code_len);


  /* forward references */
  void update_references_to_string_table ();
};


#endif /* _ASM_GEN_H_ */
