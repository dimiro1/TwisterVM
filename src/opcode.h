/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-21 10:41:23 BRT>
 */

/* sempre inclua dispatch, não inclua opcode.h diretamente */

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

/* #define OPCODES OP (ABS_N),\							  /\* abs_n	 A - C *\/	\ */
/*   OP (ACOS_N),\						  /\* acos_n	 A - C *\/ */
/*   OP (ADD_N),\							  /\* add_n	 A B C *\/ */
/*   OP (ASIN_N),\						  /\* asin_n	 A - C *\/ */
/*   OP (ATAN_N),\						  /\* atan_n	 A - C *\/ */
/*   OP (CEIL_N),\						  /\* ceil_n	 A - C *\/ */
/*   OP (COS_N),\							  /\* cos_n	 A - C *\/ */
/*   OP (DEC_N),\							  /\* dec_n	 - - C *\/ */
/*   OP (DIV_N),\							  /\* div_n	 A B C *\/ */
/*   OP (FLOOR_N),\						  /\* floor_n A - C *\/ */
/*   OP (INC_N),\							  /\* inc_n	 - - C *\/ */
/*   OP (LOG_N),\							  /\* log_n	 A - C *\/ */
/*   OP (MOD_N),\							  /\* mod_n	 A B C *\/ */
/*   OP (MULT_N),\						  /\* mult_n	 A B C *\/ */
/*   OP (NEG_N),\							  /\* neg_n	 - - C *\/ */
/*   OP (POW_N),\							  /\* pow_n	 A - C *\/ */
/*   OP (SIN_N),\							  /\* sin_n	 A - C *\/ */
/*   OP (SQRT_N),\						  /\* sqrt_n	 A - C *\/ */
/*   OP (SUB_N),\							  /\* sub_n	 A B C *\/ */
/*   OP (TAN_N),\							  /\* tan_n	 A - C *\/ */

/*   /\* genric *\/ */
/*   OP (GOTO_T),\						  /\* goto	 A - - *\/ */
/*   OP (HALT),\							  /\* halt	 - - - *\/ */
/*   OP (NOP),\							  /\* nop		 - - - *\/ */

/*   /\* IO *\/ */
/*   OP (INPUT_N),\						  /\* input_n - - C *\/ */
/*   OP (INPUT_S),\						  /\* input_s - - C *\/ */
/*   OP (PRINT_N),\						  /\* print_n A - - *\/ */
/*   OP (PRINT_S),\						  /\* print_s A - - *\/ */
/*   OP (PUT_N),\							  /\* put_n	 A - - *\/ */
/*   OP (PUT_S),\							  /\* put_s	 A - - *\/ */

/*   /\* registers *\/ */
/*   OP (MOV_N),\							  /\* mov_n	 A - C *\/ */
/*   OP (MOV_S),\							  /\* mov_s	 A - C *\/ */
/*   OP (STORE_N),\						  /\* store_n A - C *\/ */
/*   OP (STORE_S),\						  /\* store_s A - C *\/ */

/*   /\* string *\/ */
/*   OP (CONCAT_S),\						  /\* concat_s A B C *\/ */
/*   OP (CHARAT_S),\						  /\* charat_s A B C *\/ */

/*   /\* deprecated *\/ */
/*   /\* não usem esses opcodes *\/ */
/*   /\* estão presentes apenas para que o projeto compile. *\/ */
/*   OP (ADD),\ */
/*   OP (CLSP),\							  /\* limpa a pilha *\/ */
/*   OP (DCARD),\						  /\* Discarta o topo da pilha *\/ */
/*   OP (DIV),\ */
/*   OP (GETOP),\			// for puts and print */
/*   OP (MULT),\ */
/*   OP (POP),\ */
/*   OP (PRINT),\ */
/*   OP (PUSH),\ */
/*   OP (PUTS),\ */
/*   OP (RESET),\ */
/*   OP (SUB) */


#define OP(op) OP_##op

#define OPCODES OP (ABS_N),							\
        /* Math */                              \
        OP (ACOS_N),                            \
        OP (ADD_N),                             \
        OP (ASIN_N),                            \
        OP (ATAN_N),                            \
        OP (CEIL_N),                            \
        OP (COS_N),                             \
        OP (DEC_N),                             \
        OP (DIV_N),                             \
        OP (FLOOR_N),                           \
        OP (INC_N),                             \
        OP (LOG_N),                             \
        OP (MOD_N),                             \
        OP (MULT_N),                            \
        OP (NEG_N),                             \
        OP (POW_N),                             \
        OP (SIN_N),                             \
        OP (SQRT_N),                            \
        OP (SUB_N),                             \
        OP (TAN_N),                             \
        /* generic */                           \
        OP (GOTO),                              \
        OP (HALT),                              \
        OP (NOP),                               \
        /* io */                                \
        OP (INPUT_N),                           \
        OP (INPUT_S),                           \
        OP (PRINT_N),                           \
        OP (PRINT_S),                           \
        OP (PUT_N),                             \
        OP (PUT_S),                             \
        /* register */                          \
        OP (MOV_N),                             \
        OP (MOV_S),                             \
        OP (STORE_N),                           \
        OP (STORE_S),                           \
        /* string */                            \
        OP (CONCAT_S),                          \
        OP (CHARAT_S),                          \
        /* relational */                        \
        OP (LT_S),                              \
        OP (GT_S),                              \
        OP (LTE_S),                             \
        OP (GTE_S),                             \
        OP (EQ_S),                              \
        OP (LT_N),                              \
        OP (GT_N),                              \
        OP (LTE_N),                             \
        OP (GTE_N),                             \
        OP (EQ_N),                              \
        OP (NOT_LT_S),                          \
        OP (NOT_GT_S),                          \
        OP (NOT_LTE_S),                         \
        OP (NOT_GTE_S),                         \
        OP (NOT_EQ_S),                          \
        OP (NOT_LT_N),                          \
        OP (NOT_GT_N),                          \
        OP (NOT_LTE_N),                         \
        OP (NOT_GTE_N),                         \
        OP (NOT_EQ_N),                          \
        /* old */                               \
        OP (ADD),                               \
        OP (CLSP),                              \
        OP (DCARD),                             \
        OP (DIV),                               \
        OP (GETOP),                             \
        OP (MULT),                              \
        OP (POP),                               \
        OP (PRINT),                             \
        OP (PUSH),                              \
        OP (PUTS),                              \
        OP (RESET),                             \
        OP (SUB)

enum Opcode { OPCODES };

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

    "lt_s",                       /* lt_s $1 $2 LABEL */
    "gt_s",
    "lte_s",
    "gte_s",
    "eq_s",
    "lt_n",
    "gt_n",
    "lte_n",
    "gte_n",
    "eq_n",

    "not_lt_s",                       /* lt_s $1 $2 LABEL */
    "not_gt_s",
    "not_lte_s",
    "not_gte_s",
    "not_eq_s",
    "not_lt_n",
    "not_gt_n",
    "not_lte_n",
    "not_gte_n",
    "not_eq_n",

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
