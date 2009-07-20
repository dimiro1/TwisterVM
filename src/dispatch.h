/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-20 14:31:18 BRT>
 */

#ifndef _DISPATCH_H_
#define _DISPATCH_H_

#ifdef HAVE_COMPUTED_GOTO								\
/*
  Dispatch de instruções.
  Computed Goto

  goto computado é um recurso de alguns compiladores c que trata labels como
  data que pode ser armazenado em ponteiros void*.

  Cada opcode é apenas um label, armazenado em um enorme vetor.
  executar uma instrução é apenas usar o indice do opcode e executar o label, realizando o goto.

  Isto é incrivelmente mais rápido que usar o grande switch.

  Obs: compiled goto não é um recurso a ser usado caso deseja-se atingir o nivel ansi/iso c
*/

/* This is only used in vm.cpp, never use this in other place */
#define BEGIN_SWITCH static const void				\
  *label_targets[] = {									\
	 &&OP_ABS_N,											\
	 &&OP_ACOS_N,											\
	 &&OP_ADD_N,											\
	 &&OP_ASIN_N,											\
	 &&OP_ATAN_N,											\
	 &&OP_CEIL_N,											\
	 &&OP_COS_N,											\
	 &&OP_DEC_N,											\
	 &&OP_DIV_N,											\
	 &&OP_FLOOR_N,											\
	 &&OP_INC_N,											\
	 &&OP_LOG_N,											\
	 &&OP_MOD_N,											\
	 &&OP_MULT_N,											\
	 &&OP_NEG_N,											\
	 &&OP_POW_N,											\
	 &&OP_SIN_N,											\
	 &&OP_SQRT_N,											\
	 &&OP_SUB_N,											\
	 &&OP_TAN_N,											\
	 &&OP_GOTO_T,											\
	 &&OP_HALT,												\
	 &&OP_NOP,												\
	 &&OP_INPUT_N,											\
	 &&OP_INPUT_S,											\
	 &&OP_PRINT_N,											\
	 &&OP_PRINT_S,											\
	 &&OP_PUT_N,											\
	 &&OP_PUT_S,											\
	 &&OP_MOV_N,											\
	 &&OP_MOV_S,											\
	 &&OP_STORE_N,											\
	 &&OP_STORE_S,											\
	 &&OP_CONCAT_S,										\
	 &&OP_CHARAT_S											\
  };

/* This is only used in vm.cpp, never use this in other place */
#define GOTO_NEXT_INSTR executing = current_context->code_section[current_context->pc]; \
  goto *label_targets[executing.opcode];

/* This is only used in vm.cpp, never use this in other place */
#define CASE(op) op:										\
  {

#define END_SWITCH  /* nothing */
#define BREAK 	     /* nothing */

#else	 /* NOT HAVE_COMPUTED_GOTO */

#define BEGIN_SWITCH while (true)	{									   \
  executing = current_context->code_section[current_context->pc];	\
  switch (executing.opcode)													\
	 {

#define CASE(op) case op:								\
  {

#define BREAK break;
#define GOTO_NEXT_INSTR /* nothing */

#define END_SWITCH } } 			  /* while, case */

#endif /* HAVE_COMPUTED_GOTO */

#define END_CASE }

#endif /* _DISPATCH_H_ */
