/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-13 22:03:13 BRT>
 */

#include "AsmGen.h"

AsmGen::AsmGen (string _output_file_name) 
  : output_file_name (_output_file_name)
{
  assembled_file = new CompiledBytecode ();
}

AsmGen::~AsmGen ()
{
  delete assembled_file;
  delete output_file;
}

void AsmGen::alloc_instruction_array (int _code_len)
{
  assembled_file->alloc_instructions (_code_len);
}

void AsmGen::write_to_file ()
{
  output_file = new ofstream (output_file_name.c_str(), ios::binary);

  output_file->write (reinterpret_cast<char *>(&assembled_file->magic), sizeof (int));
  output_file->write (reinterpret_cast<char *>(&assembled_file->size), sizeof (int));
  output_file->write (reinterpret_cast<char *>(assembled_file->instructions), assembled_file->size * sizeof (ByteCode));
  output_file->close ();
}

void AsmGen::emit_add ()
{
  assembled_file->add_instruction (ByteCode (ADD));
}

void AsmGen::emit_div ()
{
  assembled_file->add_instruction (ByteCode (DIV));
}

void AsmGen::emit_getop ()
{
  assembled_file->add_instruction (ByteCode (GETOP));
}

void AsmGen::emit_halt ()
{
  assembled_file->add_instruction (ByteCode (HALT));
}

void AsmGen::emit_mult ()
{
  assembled_file->add_instruction (ByteCode (MULT));
}

void AsmGen::emit_nop ()
{
  assembled_file->add_instruction (ByteCode (NOP));
}

void AsmGen::emit_pop ()
{
  assembled_file->add_instruction (ByteCode (POP));
}

void AsmGen::emit_print ()
{
  assembled_file->add_instruction (ByteCode (PRINT));
}

void AsmGen::emit_push (float _operand)
{
  assembled_file->add_instruction (ByteCode (PUSH, _operand));
}

void AsmGen::emit_puts ()
{
  assembled_file->add_instruction (ByteCode (PUTS));
}

void AsmGen::emit_reset ()
{
  assembled_file->add_instruction (ByteCode (RESET));
}

void AsmGen::emit_sub ()
{
  assembled_file->add_instruction (ByteCode (SUB));
}
