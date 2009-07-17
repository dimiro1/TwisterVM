#ifndef _OPCODE_H_
#define _OPCODE_H_
#include <cstdlib>

enum Opcode
{
  /* math */
  OP_ADD_N,
  OP_SUB_N,
  OP_MULT_N,
  OP_DIV_N,
  OP_MOD_N,
  OP_POW_N,
  OP_NEG_N,
  OP_ABS_N,
  OP_SIN_N,
  OP_COS_N,
  OP_TAN_N,
  OP_ASIN_N,
  OP_ACOS_N,
  OP_ATAN_N,
  OP_LOG_N,
  OP_SQRT_N,
  OP_CEIL_N,
  OP_FLOOR_N,

  /* genric */
  OP_NOP,				// no operation
  OP_GOTO,
  OP_HALT,

  /* IO */
  OP_PRINT_S,
  OP_PRINT_N,
  OP_PUT_S,
  OP_PUT_N,
  OP_INPUT_S,
  OP_INPUT_N,

  /* registers */
  OP_MOV_N,
  OP_MOV_S,
  OP_STORE_N,
  OP_STORE_S,

  /* string */
  OP_CONCAT_S,

  /* deprecated */
  OP_CLSP,							  /* limpa a pilha */
  OP_DIV,
  OP_DCARD,						  /* Discarta o topo da pilha */
  OP_GETOP,			// for puts and print
  OP_MULT,
  OP_POP,
  OP_PUSH,
  OP_PUTS,
  OP_RESET,
  OP_SUB,
  OP_PRINT,
  OP_ADD,
};

static const char *mneumonic[] = {
  "add_n",
  "sub_n",
  "nult_n",
  "div_n",
  "mod_n",
  "pow_n",
  "neg_n",
  "abs_n",
  "sin_n",
  "cos_n",
  "tan_n",
  "asin_n",
  "acos_n",
  "atan_n",
  "log_n",
  "sqrt_n",
  "ceil_n",
  "floor_n",
  "nop"
  "goto",
  "halt",
  "print_s",
  "print_n",
  "put_s",
  "put_n",
  "input_s",
  "input_n",
  "mov_n",
  "mov_s",
  "store_n",
  "store_s",
  "concat_s",
  /* deprecated */
  "clsp",							  /* limpa a pilha */
  "div",
  "dcard",						  /* discarta o topo da pilha */
  "getop",			// for puts and print
  "mult",
  "pop",
  "push",
  "puts",
  "reset",
  "sub",
  "print",
  "add",
};

#endif
