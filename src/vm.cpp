/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-18 12:51:27 BRT>
 */

#include "vm.h"

VM::~VM ()
{
  reset ();
}


/* load code_section into memory */
void
VM::load (string progname)
{
  running_file_name = progname;
  current_context = new ExecContext ();
  current_context->load_file (progname);
}


void 
VM::list ()
{
  Instruction current;

  cout << " (" << current_context->code_len
		 << " instructions, " 
		 << sizeof (current_context->code_section) * current_context->code_len 
		 << " bytes at " 
		 << hex << current_context->code_section << ")" << dec << endl;
  for (int i = 0; i < current_context->code_len; i++)
	 {
		current = current_context->code_section[i];
		cout << " " << i << ": " << mneumonic[current.opcode] << " ";
		switch (current.opcode)
		  {
		  case OP_STORE_S:
			 cout << "\"" << current_context->get_string(current.A) 
					<< "\" $" << current.C;
			 break;
		  case OP_PUT_S: case OP_PRINT_S:
			 cout << "$" << current.A;
			 break;
		  case OP_STORE_N:
			 cout  << current_context->get_num (current.A) 
					 << " $" << current.C;
			 break;
		  case OP_PUT_N: case OP_PRINT_N:
			 cout << "$" << current.A;
			 break;
		  case OP_CONCAT_S:
			 cout  << "$" << current.A 
					 << " $" << current.B 
					 << " $" << current.C ;
			 break;
		  case OP_MOV_N: case OP_MOV_S:
			 cout  << "$" << current.A 
					 << " $" << current.C ;
			 break;
		  case OP_INPUT_N: case OP_INPUT_S:
			 cout  << "$" << current.C;
			 break;
		  case OP_GOTO:
			 cout  << "$" << current.A;
			 break;
		  case OP_ADD_N:  case OP_SUB_N:
		  case OP_MULT_N: case OP_DIV_N:
		  case OP_MOD_N:
			 cout  << "$" << current.A 
					 << " $" << current.B 
					 << " $" << current.C ;
			 break;
		  case OP_POW_N:
			 cout  << "$" << current.A 
					 << " $" << current.C ;
			 break;
		  case OP_NEG_N:
			 cout  << "$" << current.C;
			 break;
		  case OP_ABS_N:  case OP_SIN_N:
		  case OP_COS_N:  case OP_TAN_N:
		  case OP_ASIN_N: case OP_ACOS_N:
		  case OP_ATAN_N: case OP_LOG_N:
		  case OP_SQRT_N: case OP_CEIL_N: 
		  case OP_FLOOR_N:
			 cout  << "$" << current.A 
					 << " $" << current.C ;
			 break;
		  case OP_INC_N:
			 cout  << "$" << current.C;
			 break;
		  case OP_DEC_N:
			 cout  << "$" << current.C;
			 break;
		  }
		cout << endl;
	 }
}

int 
VM::execute ()
{
  string input_s;
  double input_d;
  Instruction executing;
  while (true)
	 {
		executing = current_context->code_section[current_context->pc];
		switch (executing.opcode) 
		  {
			 /* aritmetica opcodes numeros */
		  case OP_ADD_N:
			 RN(executing.C,
				 current_context->get_num (executing.A) +
				 current_context->get_num (executing.B));
			 current_context->pc++;
			 break;
		  case OP_SUB_N:
			 RN(executing.C,
				 current_context->get_num (executing.A) -
				 current_context->get_num (executing.B));
			 current_context->pc++;
			 break;
		  case OP_MULT_N:
			 RN(executing.C,
				 current_context->get_num (executing.A) *
				 current_context->get_num (executing.B));
			 current_context->pc++;
			 break;
		  case OP_DIV_N:
			 RN(executing.C,
				 current_context->get_num (executing.A) /
				 current_context->get_num (executing.B));
			 current_context->pc++;
			 break;
		  case OP_MOD_N:
			 RN(executing.C,
				 static_cast<int>(current_context->get_num (executing.A)) %
				 static_cast<int>(current_context->get_num (executing.B)));
			 current_context->pc++;
			 break;
		  case OP_POW_N:
			 RN(executing.C, pow (current_context->get_num (executing.A),
										 current_context->get_num (executing.B)));
			 current_context->pc++;
			 break;
		  case OP_NEG_N:			  /* TODO: melhorar esse neg */
			 RN(executing.A, -current_context->get_num (executing.A));
			 current_context->pc++;
			 break;
		  case OP_ABS_N:
			 RN(executing.A, fabs (current_context->get_num (executing.A)));
			 current_context->pc++;
			 break;
		  case OP_SIN_N:
			 RN(executing.C, sin (current_context->get_num (executing.A)));
			 current_context->pc++;
			 break;
		  case OP_COS_N:
			 RN(executing.C, cos (current_context->get_num (executing.A)));
			 current_context->pc++;
			 break;
		  case OP_TAN_N:
			 RN(executing.C, tan (current_context->get_num (executing.A)));
			 current_context->pc++;
			 break;
		  case OP_ASIN_N:
			 RN(executing.C, asin (current_context->get_num (executing.A)));
			 current_context->pc++;
			 break;
		  case OP_ACOS_N:
			 RN(executing.C, acos (current_context->get_num (executing.A)));
			 current_context->pc++;
			 break;
		  case OP_ATAN_N:
			 RN(executing.C, atan (current_context->get_num (executing.A)));
			 current_context->pc++;
			 break;
		  case OP_LOG_N:
			 RN(executing.C, log (current_context->get_num (executing.A)));
			 current_context->pc++;
			 break;
		  case OP_SQRT_N:
			 RN(executing.C, sqrt (current_context->get_num (executing.A)));
			 current_context->pc++;
			 break;
		  case OP_CEIL_N:
			 RN(executing.C, ceil (current_context->get_num (executing.A)));
			 current_context->pc++;
			 break;
		  case OP_FLOOR_N:
			 RN(executing.C, floor (current_context->get_num (executing.A)));
			 current_context->pc++;
			 break;
		  case OP_INC_N:
			 RN(executing.A, RN(executing.A) + 1);
			 current_context->pc++;
			 break;
		  case OP_DEC_N:
			 RN(executing.A, RN(executing.A) - 1);
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
			 RS(executing.C, input_s);
			 current_context->pc++;
			 break;
		  case OP_INPUT_N:
			 cin >> ind;
			 RN(executing.C, input_d);
			 current_context->pc++;
			 break;
			 /* end IO */

			 /* REgisters manipulation */
		  case OP_MOV_N:
			 RN(executing.B, current_context->get_num (executing.A));
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
				 current_context->get_num (executing.A));
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

