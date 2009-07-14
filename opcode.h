#ifndef _OPCODE_H_
#define _OPCODE_H_
#include <cstdlib>

enum Opcode
{
  OP_ADD,
  OP_DIV,
  OP_GETOP,			// for puts and print
  OP_HALT,
  OP_MULT,
  OP_NOP,				// no operation
  OP_POP,
  OP_PRINT,
  OP_PUSH,
  OP_PUTS,
  OP_RESET,
  OP_SUB
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
