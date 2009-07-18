#ifndef _OPCODE_H_
#define _OPCODE_H_
/* #include <cstdlib> */

/* operandos */
/* A -> operando principal - 12 bits unsigned int */
/* B -> operando auxiliar - 12 bits unsigned int */
/* C -> sempre operando de destino - 12 bits unsigned int */

/* obs: Em Store o operando A é um ponteiro para um numero
        ou um ponteiro para uma string nas tabelas de strings
		  e numeros.
		  
		  Em charat_s B é um inteiro.
*/

enum Opcode
{
  /* math */
  OP_ABS_N, 						  /* abs_n   A - C */
  OP_ACOS_N,						  /* acos_n  A - C */
  OP_ADD_N,							  /* add_n   A B C */
  OP_ASIN_N,						  /* asin_n  A - C */
  OP_ATAN_N,						  /* atan_n  A - C */
  OP_CEIL_N,						  /* ceil_n  A - C */
  OP_COS_N,							  /* cos_n   A - C */
  OP_DEC_N,							  /* dec_n   - - C */
  OP_DIV_N,							  /* div_n   A B C */
  OP_FLOOR_N,						  /* floor_n A - C */
  OP_INC_N,							  /* inc_n   - - C */
  OP_LOG_N,							  /* log_n   A - C */
  OP_MOD_N,							  /* mod_n   A B C */
  OP_MULT_N,						  /* mult_n  A B C */
  OP_NEG_N,							  /* neg_n   - - C */
  OP_POW_N,							  /* pow_n   A - C */
  OP_SIN_N,							  /* sin_n   A - C */
  OP_SQRT_N,						  /* sqrt_n  A - C */
  OP_SUB_N,							  /* sub_n   A B C */
  OP_TAN_N,							  /* tan_n   A - C */

  /* genric */
  OP_GOTO,							  /* goto    A - - */
  OP_HALT,							  /* halt    - - - */
  OP_NOP,							  /* nop     - - - */

  /* IO */
  OP_INPUT_N,						  /* input_n - - C */
  OP_INPUT_S,						  /* input_s - - C */
  OP_PRINT_N,						  /* print_n A - - */
  OP_PRINT_S,						  /* print_s A - - */
  OP_PUT_N,							  /* put_n   A - - */
  OP_PUT_S,							  /* put_s   A - - */

  /* registers */
  OP_MOV_N,							  /* mov_n   A - C */
  OP_MOV_S,							  /* mov_s   A - C */
  OP_STORE_N,						  /* store_n A - C */
  OP_STORE_S,						  /* store_s A - C */

  /* string */
  OP_CONCAT_S,						  /* concat_s A B C */
  OP_CHARAT_S,						  /* charat_s A B C */

  /* deprecated */
  /* não usem esses opcodes */
  /* estão presentes apenas para que o projeto compile. */
  OP_ADD,
  OP_CLSP,							  /* limpa a pilha */
  OP_DCARD,						  /* Discarta o topo da pilha */
  OP_DIV,
  OP_GETOP,			// for puts and print
  OP_MULT,
  OP_POP,
  OP_PRINT,
  OP_PUSH,
  OP_PUTS,
  OP_RESET,
  OP_SUB
};

static const char *
mneumonic[] = {
  "abs_n",
  "acos_n",
  "add_n",
  "asin_n",
  "atan_n",
  "ceil_n",
  "cos_n",
  "dec_n",
  "div_n",
  "floor_n",
  "inc_n",
  "log_n",
  "mod_n",
  "mult_n",
  "neg_n",
  "pow_n",
  "sin_n",
  "sqrt_n",
  "sub_n",
  "tan_n",

  "goto",
  "halt",
  "nop",

  "input_n",
  "input_s",
  "print_n",
  "print_s",
  "put_n",
  "put_s",

  "mov_n",
  "mov_s",
  "store_n",
  "store_s",

  "concat_s",
  "charat_s",
  /* deprecated */
  "add",
  "clsp",							  /* limpa a pilha */
  "dcard",						  /* discarta o topo da pilha */
  "div",
  "getop",			// for puts and print
  "mult",
  "pop",
  "print",
  "push",
  "puts",
  "reset",
  "sub"
};

#endif
