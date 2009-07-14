/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-14 09:34:22 BRT>
 */

#include "AsmGen.h"

AsmGen::AsmGen (string _output_file_name) 
  : output_file_name (_output_file_name), 
	 default_extension (".twc")
{
  assembled_file = new TwcFile ();
}

AsmGen::~AsmGen ()
{
  delete assembled_file;
  delete output_file;
}

void AsmGen::alloc_instruction_section (int _code_len)
{
  assembled_file->alloc_instruction_section (_code_len);
}

void AsmGen::write_to_file ()
{
  output_file = new ofstream (output_file_name.c_str(), ios::binary);

  output_file->write (reinterpret_cast<char *>(&assembled_file->magic), sizeof (int));
  output_file->write (reinterpret_cast<char *>(&assembled_file->code_len), sizeof (int));
  output_file->write (reinterpret_cast<char *>(assembled_file->instructions), assembled_file->code_len * sizeof (Instruction));
  output_file->close ();
}

/* Colocará o nome do arquivo */
void AsmGen::set_output_file_name (const char *_file_name)
{
  output_file_name = _file_name;
  output_file_name += default_extension;
}

void AsmGen::emit_add ()
{
  assembled_file->add_instruction (Instruction (ADD));
}

void AsmGen::emit_div ()
{
  assembled_file->add_instruction (Instruction (DIV));
}

void AsmGen::emit_getop ()
{
  assembled_file->add_instruction (Instruction (GETOP));
}

void AsmGen::emit_halt ()
{
  assembled_file->add_instruction (Instruction (HALT));
}

void AsmGen::emit_mult ()
{
  assembled_file->add_instruction (Instruction (MULT));
}

void AsmGen::emit_nop ()
{
  assembled_file->add_instruction (Instruction (NOP));
}

void AsmGen::emit_pop ()
{
  assembled_file->add_instruction (Instruction (POP));
}

void AsmGen::emit_print ()
{
  assembled_file->add_instruction (Instruction (PRINT));
}

void AsmGen::emit_push (float _operand)
{
  assembled_file->add_instruction (Instruction (PUSH, _operand));
}

void AsmGen::emit_puts ()
{
  assembled_file->add_instruction (Instruction (PUTS));
}

void AsmGen::emit_reset ()
{
  assembled_file->add_instruction (Instruction (RESET));
}

void AsmGen::emit_sub ()
{
  assembled_file->add_instruction (Instruction (SUB));
}
