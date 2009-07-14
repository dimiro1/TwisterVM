#ifndef OPCODE_H
#define OPCODE_H
#include <cstdlib>

enum Opcode
{
  ADD,
  DIV,
  GETOP,			// for puts and print
  HALT,
  MULT,
  NOP,				// no operation
  POP,
  PRINT,
  PUSH,
  PUTS,
  RESET,
  SUB
};

/* used in showBytecodes */
static const char *opcodeName[] = {
  "add",
  "div",
  "getop",
  "halt",
  "mult",
  "nop",			// no operation
  "pop",
  "print",
  "push",
  "puts",
  "reset",
  "sub"
};

#endif
