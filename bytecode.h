#ifndef BYTECODE_H
#define BYTECODE_H

#include "opcode.h"
#include <cstring>
#define MAGIC_VERSION_NUM 0x01 // version 0.1

class ByteCode {
public:
  ByteCode();
  ByteCode(Opcode _opcode);
  ByteCode(Opcode _opcode, float _operand);

  Opcode opcode;
  float operand;
};

class CompiledBytecode {
public:
  CompiledBytecode (int _size);
  CompiledBytecode ();
  virtual ~CompiledBytecode ();

  void add_instruction (ByteCode b);
  int magic;
  int size;
  int pc;
  ByteCode *instructions;
};

#endif

