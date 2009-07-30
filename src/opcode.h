/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-29 22:53:24 BRT>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licences>
 */

/* sempre inclua dispatch, não inclua opcode.h diretamente */

#ifndef _OPCODE_H_
#define _OPCODE_H_

#define OP(op) OP_##op

#define OPCODES OP (ABS_N),							\
	 OP (ACOS_N),											\
	 OP (ADD_N),											\
	 OP (ASIN_N),											\
	 OP (ATAN_N),											\
	 OP (CEIL_N),											\
	 OP (COS_N),											\
	 OP (DEC_N),											\
	 OP (DIV_N),											\
	 OP (FLOOR_N),											\
	 OP (INC_N),											\
	 OP (LOG_N),											\
	 OP (MOD_N),											\
	 OP (MULT_N),											\
	 OP (NEG_N),											\
	 OP (POW_N),											\
	 OP (SIN_N),											\
	 OP (SQRT_N),											\
	 OP (SUB_N),											\
	 OP (TAN_N),											\
	 OP (RAND_N),											\
	 /* generic */											\
	 OP (GOTO),												\
	 OP (HALT),												\
	 OP (NOP),												\
	 OP (SYSTEM_S),										\
	 OP (GETENV_S),										\
	 /* io */												\
	 OP (INPUT_N),											\
	 OP (INPUT_S),											\
	 OP (PRINT_N),											\
	 OP (PRINT_S),											\
	 OP (PUT_N),											\
	 OP (PUT_S),											\
	 /* register */										\
	 OP (MOV_N),											\
	 OP (MOV_S),											\
	 OP (STORE_N),											\
	 OP (STORE_S),											\
	 /* string */											\
	 OP (CONCAT_S),										\
	 OP (CHARAT_S),										\
	 /* relational */										\
	 OP (LT_S),												\
	 OP (GT_S),												\
	 OP (LTE_S),											\
	 OP (GTE_S),											\
	 OP (EQ_S),												\
	 OP (LT_N),												\
	 OP (GT_N),												\
	 OP (LTE_N),											\
	 OP (GTE_N),											\
	 OP (EQ_N),												\
	 OP (NOT_LT_S),										\
	 OP (NOT_GT_S),										\
	 OP (NOT_LTE_S),										\
	 OP (NOT_GTE_S),										\
	 OP (NOT_EQ_S),										\
	 OP (NOT_LT_N),										\
	 OP (NOT_GT_N),										\
	 OP (NOT_LTE_N),										\
	 OP (NOT_GTE_N),										\
	 OP (NOT_EQ_N),										\
	 OP (ZERO_N),											\
	 OP (NOT_ZERO_N)

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
  "rand_n",

  "goto",
  "halt",
  "nop",
  "system_s",
  "getenv_s",

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
  "zero_n",
  "not_zero_n"
};

#endif
