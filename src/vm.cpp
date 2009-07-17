/*
 * vm.cpp
 * Copyright (c) 2009 Claudemiro Alves Feitosa Neto
 * Edited in emacs.
 */

#include "vm.h"

VM::~VM ()
{
  reset ();
}


/* load code_section into memory */
int 
VM::load (char *progname) throw (BadFileException, NotRecognizedFileException)
{
  running_file_name = progname;
  current_context = new ExecContext ();
  ifstream infile (running_file_name, ios::binary);
  
  if (!infile) 
	 throw BadFileException (progname);

  /* tenta pegar o numero mágico */
  infile.read (reinterpret_cast<char *>(&current_context->magic), sizeof (unsigned int));
  if (current_context->magic != MAGIC_VERSION_NUM)
	 throw NotRecognizedFileException (progname);

  /* ler tabelas estaticas */
  /* strings */
  infile.read ( reinterpret_cast<char *>(&current_context->string_table_len), sizeof (unsigned int));
  /* TODO: testar se ocorreu alocação correta */
  current_context->string_table = new char[current_context->string_table_len];
  infile.read ( reinterpret_cast<char *>(current_context->string_table), current_context->string_table_len * sizeof (char));
  /* numeros */
  infile.read ( reinterpret_cast<char *>(&current_context->num_table_len), sizeof (unsigned int));
  /* TODO: testar se ocorreu alocação correta */
  current_context->num_table = new double[current_context->num_table_len];
  infile.read ( reinterpret_cast<char *>(current_context->num_table), current_context->num_table_len * sizeof (double));

  /* ler codigo */
  infile.read (reinterpret_cast<char *>(&current_context->code_len), sizeof (int));
  /* TODO: testar se ocorreu alocação correta */
  current_context->code_section = new Instruction[current_context->code_len];
  infile.read (reinterpret_cast<char *>(current_context->code_section), current_context->code_len * sizeof (Instruction));
  return 0;
}


void 
VM::list ()
{
  cout << " " << running_file_name 
		 << " (" << current_context->code_len
		 << " instructions, " 
		 << sizeof (current_context->code_section) * current_context->code_len 
		 << " bytes at " 
		 << hex << current_context->code_section << ")" << endl;
  /* genric */

  /* IO */

  /* registers */

  for (int i = 0; i < current_context->code_len; ++i)
	 {
		cout << i << ": " << mneumonic[current_context->code_section[i].opcode] << " ";
		switch (current_context->code_section[i].opcode)
		  {
		  case OP_STORE_S:
			 cout << "\"" << current_context->get_string(current_context->code_section[i].A) << "\" $" << current_context->code_section[i].C;
			 break;
		  case OP_PUT_S: case OP_PRINT_S:
			 cout << "$" << current_context->code_section[i].A;
			 break;
		  case OP_STORE_N:
			 cout  << current_context->num_table[current_context->code_section[i].A] << " $" << current_context->code_section[i].C;
			 break;
		  case OP_PUT_N: case OP_PRINT_N:
			 cout << "$" << current_context->code_section[i].A;
			 break;
		  case OP_CONCAT_S:
			 cout  << "$" << current_context->code_section[i].A 
					 << " $" << current_context->code_section[i].B 
					 << " $" << current_context->code_section[i].C ;
			 break;
		  case OP_MOV_N:
			 break;
		  case OP_MOV_S:
			 break;
		  case OP_INPUT_N:
			 break;
		  case OP_INPUT_S:
			 break;
		  case OP_NOP:
			 break;
		  case OP_GOTO:
			 break;
		  case OP_HALT:
			 break;
		  case OP_ADD_N:
			 break;
		  case OP_SUB_N:
			 break;
		  case OP_MULT_N:
			 break;
		  case OP_DIV_N:
			 break;
		  case OP_MOD_N:
			 break;
		  case OP_POW_N:
			 break;
		  case OP_NEG_N:
			 break;
		  case OP_ABS_N:
			 break;
		  case OP_SIN_N:
			 break;
		  case OP_COS_N:
			 break;
		  case OP_TAN_N:
			 break;
		  case OP_ASIN_N:
			 break;
		  case OP_ACOS_N:
			 break;
		  case OP_ATAN_N:
			 break;
		  case OP_LOG_N:
			 break;
		  case OP_SQRT_N:
			 break;
		  case OP_CEIL_N:
			 break;
		  case OP_FLOOR_N:
			 break;
		  }
		cout << endl;
	 }
}

int 
VM::execute ()
{
  string ins;
  double ind;
  int right; /* its is used in sub or div operations */
  Instruction executing;
  while (true)
	 {
		executing = current_context->code_section[current_context->pc];
		switch (executing.opcode) 
		  {
			 /* aritmetica opcodes numeros */
		  case OP_ADD_N:
			 RN(executing.C,
				 current_context->num_table[executing.A] +
				 current_context->num_table[executing.B]);
			 current_context->pc++;
			 break;
		  case OP_SUB_N:
			 RN(executing.C,
				 current_context->num_table[executing.A] -
				 current_context->num_table[executing.B]);
			 current_context->pc++;
			 break;
		  case OP_MULT_N:
			 RN(executing.C,
				 current_context->num_table[executing.A] *
				 current_context->num_table[executing.B]);
			 current_context->pc++;
			 break;
		  case OP_DIV_N:
			 RN(executing.C,
				 current_context->num_table[executing.A] /
				 current_context->num_table[executing.B]);
			 current_context->pc++;
			 break;
		  case OP_MOD_N:
			 RN(executing.C,
				 static_cast<int>(current_context->num_table[executing.A]) %
				 static_cast<int>(current_context->num_table[executing.B]));
			 current_context->pc++;
			 break;
		  case OP_POW_N:
			 RN(executing.C, pow (current_context->num_table[executing.A],
											 current_context->num_table[executing.B]));
			 current_context->pc++;
			 break;
		  case OP_NEG_N:			  /* TODO: melhorar esse neg */
			 RN(executing.A, -current_context->num_table[executing.A]);
			 current_context->pc++;
			 break;
		  case OP_ABS_N:
			 RN(executing.A, fabs (current_context->num_table[executing.A]));
			 current_context->pc++;
			 break;
		  case OP_SIN_N:
			 RN(executing.C, sin (current_context->num_table[executing.A]));
			 current_context->pc++;
			 break;
		  case OP_COS_N:
			 RN(executing.C, cos (current_context->num_table[executing.A]));
			 current_context->pc++;
			 break;
		  case OP_TAN_N:
			 RN(executing.C, tan (current_context->num_table[executing.A]));
			 current_context->pc++;
			 break;
		  case OP_ASIN_N:
			 RN(executing.C, asin (current_context->num_table[executing.A]));
			 current_context->pc++;
			 break;
		  case OP_ACOS_N:
			 RN(executing.C, acos (current_context->num_table[executing.A]));
			 current_context->pc++;
			 break;
		  case OP_ATAN_N:
			 RN(executing.C, atan (current_context->num_table[executing.A]));
			 current_context->pc++;
			 break;
		  case OP_LOG_N:
			 RN(executing.C, log (current_context->num_table[executing.A]));
			 current_context->pc++;
			 break;
		  case OP_SQRT_N:
			 RN(executing.C, sqrt (current_context->num_table[executing.A]));
			 current_context->pc++;
			 break;
		  case OP_CEIL_N:
			 RN(executing.C, ceil (current_context->num_table[executing.A]));
			 current_context->pc++;
			 break;
		  case OP_FLOOR_N:
			 RN(executing.C, floor (current_context->num_table[executing.A]));
			 current_context->pc++;
			 break;
			 /* fim opcodes aritmetica numeros */

			 /* deprecated opcodes */
		  case OP_ADD:
			 /* push (pop () + pop ()); */
			 /* pc++; */
			 break;
		  case OP_CLSP:
			 /* reset_sp (); */
			 /* pc++; */
			 break;
		  case OP_DIV:
			 /* right = pop (); */
			 /* push (pop () / right); */
			 /* pc++; */
			 break;
		  case OP_DCARD:
			 /* pop (); */
			 /* pc++; */
			 break;
		  case OP_GETOP:				  /* não esta concluida */
			 /* top (); */
			 /* pc++; */
			 break;
		  case OP_MULT:
			 /* push (pop () * pop ()); */
			 /* pc++; */
			 break;
		  case OP_POP:
			 /* pop (); */
			 /* pc++; */
			 break;
		  case OP_PUSH:
			 /* push (running.operand); */
			 /* pc++; */
			 break;
		  case OP_PUTS:
			 /* cout << top () << endl; */
			 /* pc++; */
			 break;
		  case OP_RESET:
			 /* reset (); */
			 /* pc++; */
			 break;
		  case OP_SUB:
			 /* right = pop (); */
			 /* push (pop () - right); */
			 /* pc++; */
			 break;
			 /* fim deprecated opcodes */

			 /* generic */
		  case OP_NOP:
			 current_context->pc++;
			 break;
		  case OP_GOTO:
			 break;
		  case OP_HALT:
			 exit (0);					  /* sai normalmente */
			 break;
			 /* fim generic */

			 /* IO */
		  case OP_PRINT_S:
			 cout << RS(executing.A);
			 current_context->pc++;
			 break;
		  case OP_PRINT_N:
			 cout << RN(executing.A);
			 current_context->pc++;
			 break;
		  case OP_PUT_S:
			 cout << RS(executing.A) << endl;
			 current_context->pc++;
			 break;
		  case OP_PUT_N:
			 cout << RN(executing.A) << endl;
			 current_context->pc++;
			 break;
		  case OP_INPUT_S:
			 cin >> ins;
			 RS(executing.C, ins);
			 current_context->pc++;
			 break;
		  case OP_INPUT_N:
			 cin >> ind;
			 RN(executing.C, ind);
			 current_context->pc++;
			 break;
			 /* end IO */

			 /* REgisters manipulation */
		  case OP_MOV_N:
			 RN(executing.B, current_context->num_table[executing.A]);
			 current_context->pc++;
			 break;
		  case OP_MOV_S:
			 RS(executing.B, current_context->get_string(executing.A));
			 current_context->pc++;
			 break;
		  case OP_STORE_S:
			 RS(executing.C, 
				 string (current_context->get_string(executing.A)));
			 current_context->pc++;
			 break;
		  case OP_STORE_N:
			 RN(executing.C, 
				 current_context->num_table[executing.A]);
			 current_context->pc++;
			 break;
			 /* fim Registers manipulation */

			 /* string */
		  case OP_CONCAT_S:
			 string s1 = RS(executing.A);
			 string s2 = RS(executing.B);
			 RS(executing.C, s1 + s2);
			 current_context->pc++;
			 break;
			 /* fim string */
		  }
	 }
  return 0; // nunca alcançado, espero!
}

// empty the sp
// reset the program counter
inline void 
VM::reset () 
{ 
  /* pc = 0; */
  reset_sp ();
}

inline void
VM::reset_sp ()
{
  while (!sp.empty ())
	 sp.pop ();
}

/* sp manipulation */
/* need changes */
void
VM::list_sp ()
{
  cout << " [ SP ] " << endl;
  while (!sp.empty ())
	 printf(" [%-4g] \n", sp.top ());
  cout << endl;
}

/* inline because the overhead; much faster */
inline void 
VM::push (float value) 
{ 
  sp.push (value); 
}

// returns the element at top of the sp
inline float 
VM::pop () 
{ 
  float element = sp.top (); 
  sp.pop ();
  return element; 
}

inline float 
VM::top () 
{ 
  return sp.top (); 
}

