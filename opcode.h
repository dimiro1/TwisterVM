#ifndef OPCODE_H
#define OPCODE_H
#include <cstdlib>

enum Opcode {
    PUSH,
    ADD,
    SUB,
    MULT,
    DIV,
    POP,
    PRINT,
    PUTS,
    NOP, // no operation
    RESET,
    GETOP, // for puts and print
    HALT
};

/* used in showBytecodes */
static const char *opcodeName[] = {
    "PUSH",
    "ADD",
    "SUB",
    "MULT",
    "DIV",
    "POP",
    "PRINT",
    "PUTS",
    "NOP", // no operation
    "RESET",
    "GETOP",
    "HALT"
};

#endif

