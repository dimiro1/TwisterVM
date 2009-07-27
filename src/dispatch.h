/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-27 07:58:17 BRT>
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

#ifndef _DISPATCH_H_
#define _DISPATCH_H_

#include "opcode.h"

/* GNUC suport computed goto */
#ifdef __GNUC__
#define HAVE_COMPUTED_GOTO
#endif

#ifdef HAVE_COMPUTED_GOTO
/*
  Dispatch de instruções.
  Computed Goto

  Este arquivo é o coração do sistema de dispatch via computed goto.

  goto computado é um recurso de alguns compiladores c que trata labels como
  data que pode ser armazenado em ponteiros void*.

  Cada opcode é apenas um label, armazenado em um enorme vetor.
  executar uma instrução é apenas usar o indice do opcode e executar o label, realizando o goto.

  Isto é incrivelmente mais rápido que usar o grande switch.

  Obs: compiled goto não é um recurso a ser usado caso deseja-se atingir o nivel ansi/iso c
*/

/* This is only used in vm.cpp, never use this in other place */
#ifdef OP
#undef OP

#define OP(op) &&LOP_ ## op
#endif

/* This is only used in vm.cpp, never use this in other place */
#define GOTO_NEXT_INSTR executing = current_context->code_section[current_context->pc]; \
  goto *label_targets[executing.opcode];

#define BEGIN_SWITCH static const void				\
  *label_targets[] = {									\
	 OPCODES													\
  };															\
  GOTO_NEXT_INSTR

/* This is only used in vm.cpp, never use this in other place */
#define CASE(op) LOP_ ## op:								\
    {

#define END_SWITCH  /* nothing */
#define BREAK 	     /* nothing */

#else	 /* NOT HAVE_COMPUTED_GOTO */

#define BEGIN_SWITCH while (true)	{									   \
  executing = current_context->code_section[current_context->pc];	\
  switch (executing.opcode)													\
	 {

#define CASE(op) case OP_ ## op:							\
    {

#define BREAK break;
#define GOTO_NEXT_INSTR /* nothing */

#define END_SWITCH } } 			  /* while, case */

#endif /* HAVE_COMPUTED_GOTO */

#define END_CASE }

#endif /* _DISPATCH_H_ */
