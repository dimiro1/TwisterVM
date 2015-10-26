/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-08-19 00:08:47 BRT>
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

/* declaração antecipada de AsmGen */
class AsmGen;

/* Quando é encontrado uma raferencia a um label ainda
	não definido, é criado uma nova referencia de LabelDec
	na tabela de labels, em seguida um ponteiro para a instrução
	que fez a referencia é adicionado na tabela de labels de LabelDec.
	Quando o Label for definido, é atualizado o valor do
	label nas instruções. */
/* declaração temporaria de label */
class LabelDec {
  friend class AsmGen;
public:
  LabelDec ()
	 : name (NULL),
		offset (NULL),
		defined (false) {}

  LabelDec (string _name)
	 : name (_name),
		offset (NULL),
		defined (false) {}

  LabelDec (string _name, int _offset)
	 : name (_name),
		offset (_offset),
		defined (false) {}

  LabelDec (string _name, int _offset, bool _defined)
	 : name (_name),
		offset (_offset),
		defined (_defined) {}

private:
  string name;
  int offset;
  bool defined;
  std::vector<Instruction *> instructions;
};

/* declaração temporaria de string */
class StringDec {
  friend class AsmGen;
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

private:
  string name;
  int offset;
};

/* declaração temporaria de numeros */
class NumDec {
  friend class AsmGen;
public:
  NumDec ()
	 : num (NULL),
		offset (NULL) {}

  NumDec (const NUMBER _num)
	 : num (_num),
		offset (NULL) {}

  NumDec (const NUMBER _num, const int _offset)
	 : num (_num),
		offset (_offset) {}

private:
  NUMBER num;
  int offset;
};

class AsmGen {
public:
  AsmGen (const string _output_file_name)
	 : output_file_name (_output_file_name),
		default_extension (".twc"),
		current_code_line (0) {}

  ~AsmGen () { delete output; }

  void assemble ();
  void set_output_file_name (const char *_file_name);

  /* adiciona string à tabela de strings temporaria */
  int add_string (const string _name);

  /* adiciona num à tabela de num temporaria */
  int add_num (const double _num);

  /* atualiza as referencias anteriores */
  /* deve atualizar todas as instruções que fazem goto */
  void update_references_to_label_table (const string _name);

  /* adiciona um novo label */
  bool add_label (const string _name);
  bool add_label (const string _name, bool _defined);

  /* retorna o offset do label */
  int get_label_offset (const string _name);

  inline void add_instruction (const unsigned int _opcode,
										 const unsigned int _A,
										 const unsigned int _C)
  {
	 Instruction *i = new Instruction (_opcode, _A, _C);
	 instruction_table.push_back (i);
  }

  inline void add_instruction (const unsigned int _opcode,
										 const unsigned int _A,
										 const unsigned int _B,
										 const unsigned int _C)
  {
	 Instruction *i = new Instruction (_opcode, _A, _B, _C);
	 instruction_table.push_back (i);
  }

  inline void add_instruction (const unsigned int _opcode,
										 const unsigned int _A)
  {
	 Instruction *i = new Instruction (_opcode, _A);
	 instruction_table.push_back (i);
  }

  inline void add_instruction (const unsigned int _opcode)
  {
	 Instruction *i = new Instruction (_opcode);
	 instruction_table.push_back (i);
  }

  inline void add_instruction (const unsigned int _opcode,
										 const unsigned int _A,
										 const unsigned int _B,
										 const string _label_name)
  {
	 Instruction *i;
	 LabelDec *label = get_label (_label_name);
	 if (label->defined)
		{
		  i = new Instruction (_opcode, _A, _B, label->offset);
		  instruction_table.push_back (i);
		}
	 else
		{
		  i = new Instruction (_opcode, _A, _B, NULL);
		  label->instructions.push_back (i);
		  instruction_table.push_back (i);
		}
  }

  inline void add_instruction (const unsigned int _opcode,
										 const unsigned int _A,
										 const string _label_name)
  {
	 Instruction *i;
	 LabelDec *label = get_label (_label_name);
	 if (label->defined)
		{
		  i = new Instruction (_opcode, _A, label->offset);
		  instruction_table.push_back (i);
		}
	 else
		{
		  i = new Instruction (_opcode, _A);
		  label->instructions.push_back (i);
		  instruction_table.push_back (i);
		}
  }

  inline void add_instruction (const unsigned int _opcode,
										 const string _label_name)
  {
	 Instruction *i;
	 LabelDec *label = get_label (_label_name);
	 if (label->defined)
		{
		  i = new Instruction (_opcode, label->offset);
		  instruction_table.push_back (i);
		}
	 else
		{
		  i = new Instruction(_opcode);
		  label->instructions.push_back (i);
		  instruction_table.push_back (i);
		}
  }


  inline void inc_code_line () { current_code_line++; }
  inline void dec_code_line () { current_code_line--; }

  inline int get_code_line () { return current_code_line; }

  bool label_defined (const string _name);
  LabelDec * get_label (const string _name);

private:
  int current_code_line;		  /* atual linha de codigo. */
  string output_file_name;
  ofstream *output;
  string default_extension;
  ExecContext context;

  /* tabelas temporarias */
  std::vector<StringDec> string_table;
  std::vector<NumDec> num_table;
  std::vector<LabelDec> label_table;
  std::vector<Instruction *> instruction_table;

  /* pega strings de StringDec e as coloca no arquivo. */
  void mount_string_table ();
  void report_string_table () const;
  void mount_num_table ();
  void report_num_table () const;
  void report_label_table () const;
  void mount_code_table ();
  void report_code () const;

  /* aloca espaço para as tabelas */
  void alloc_string_table_section (const int _len);
  void alloc_num_table_section (const int _len);
  void alloc_code_section (const int _code_len);

  /* forward references */
  void update_references_to_string_table ();
};


#endif /* _ASM_GEN_H_ */
