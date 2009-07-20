/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-20 13:14:46 BRT>
 */

#include "vm.h"

VM::~VM ()
{
  delete current_context;
}

/* load code_section into memory */
void
VM::load (string progname)
{
  current_context = new ExecContext ();
  try
	 {
		current_context->load_file (progname);
	 }
  catch (BadFileException e)
	 {
		cerr << e.what () << endl;
		abort ();
	 }
  catch (NotRecognizedFileException e)
	 {
		cerr << e.what () << endl;
		abort ();
	 }
  catch (bad_alloc e)
	 {
		cerr << e.what () << endl;
		abort ();
	 }
}


void 
VM::list ()
{
  Instruction current;

  cout << " (" << current_context->header.code_len
		 << " instructions, " 
		 << sizeof (current_context->code_section) * current_context->header.code_len 
		 << " bytes at " 
		 << hex << current_context->code_section << ")" << dec << endl;
  for (int i = 0; i < current_context->header.code_len; i++)
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
		  case OP_GOTO_T:
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
		  case OP_CHARAT_S:
			 cout << current_context->get_string (current.A)
					<< " " << current.B << " $" << current.C;
			 break;

		  }
		cout << endl;
	 }
}

void VM::execute ()
{
#ifdef HAVE_COMPUTED_GOTO
  dispatch_goto ();
#else
  dispatch_switch ();
#endif
}

int VM::dispatch_goto ()
{  
  string s_aux1;
  string s_aux2;
  char *ch_aux1;
  string input_s;
  double input_d;
  Instruction executing;

  /* see opcodes.h */
  SWITCH_OPCODES;
  GOTO_NEXT_INSTR;

  CASE (add_n)
  {
	 RN(executing.C,
		 current_context->get_num (executing.A) +
		 current_context->get_num (executing.B));
    current_context->pc++;
    GOTO_NEXT_INSTR;
  }

  CASE (sub_n)
  {
	 RN(executing.C,
		 current_context->get_num (executing.A) -
		 current_context->get_num (executing.B));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (mult_n)
  {
	 RN(executing.C,
		 current_context->get_num (executing.A) *
		 current_context->get_num (executing.B));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (div_n)
  {
	 /* Colocar como exception */
	 if (current_context->get_num (executing.B) == 0)
		{
		  error_emitter.emit (ZERO_DIVISION);
		  abort ();
		}
	 RN(executing.C,
		 current_context->get_num (executing.A) /
		 current_context->get_num (executing.B));

	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (mod_n)
  {
	 RN(executing.C,
		 static_cast<int>(current_context->get_num (executing.A)) %
		 static_cast<int>(current_context->get_num (executing.B)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
	 CASE(pow_n)
		RN(executing.C, pow (current_context->get_num (executing.A),
									current_context->get_num (executing.B)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (neg_n)			  /* todo: melhorar esse neg */
  {
	 RN(executing.A, -current_context->get_num (executing.A));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (abs_n)
  {
	 RN(executing.A, fabs (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (sin_n)
  {
	 RN(executing.C, sin (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (cos_n)
  {
	 RN(executing.C, cos (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (tan_n)
  {
	 RN(executing.C, tan (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (asin_n)
  {
	 RN(executing.C, asin (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (acos_n)
  {
	 RN(executing.C, acos (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (atan_n)
  {
	 RN(executing.C, atan (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (log_n)
  {
	 RN(executing.C, log (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (sqrt_n)
  {
	 RN(executing.C, sqrt (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (ceil_n) 
  {
	 RN(executing.C, ceil (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (floor_n)
  {
	 RN(executing.C, floor (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (inc_n) 
  {
	 RN(executing.A, RN(executing.A) + 1);
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (dec_n)
  {
	 RN(executing.A, RN(executing.A) - 1);
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  /* fim opcodes aritmetica numeros */

  /* generic */
  CASE (nop)
  {
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (goto_t)
  {
	 GOTO_NEXT_INSTR;
  }

  CASE (halt)
	 exit (0);					  /* sai normalmente */
  /* fim generic */

  /* IO */
  CASE (print_s)
  {
	 cout << RS(executing.A);
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (print_n)
  {
	 cout << RN(executing.A);
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (put_s)
  {
	 cout << RS(executing.A) << endl;
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (put_n)
  {
	 cout << RN(executing.A) << endl;
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (input_s)
  {
	 cin >> input_s;
	 RS(executing.C, input_s);
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }
			 
  CASE (input_n)
  {
	 cin >> input_d;
	 RN(executing.C, input_d);
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }
  /* end IO */

  /* REgisters manipulation */
  CASE (mov_n)
  {
	 RN(executing.B, current_context->get_num (executing.A));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (mov_s)
  {
	 RS(executing.B, current_context->get_string(executing.A));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (store_s)
  {
	 RS(executing.C, 
		 string (current_context->get_string(executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }

  CASE (store_n)
  {
	 RN(executing.C, 
		 current_context->get_num (executing.A));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }
  /* fim Registers manipulation */

  /* string */

  CASE (concat_s)
  {
	 s_aux1 = RS(executing.A);
	 s_aux2 = RS(executing.B);
	 RS(executing.C, s_aux1 + s_aux2);
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }
  /* store_s "hello" $1 */
  /* charat_s $1 1 $0 */

  CASE (charat_s)
  {
	 s_aux1 = RS(executing.A);
	 ch_aux1 = new char[2];

	 try
		{
		  sprintf (ch_aux1, "%c", s_aux1.at(executing.B));
		}
	 catch (out_of_range e)
		{
		  error_emitter.emit (OUT_OF_RANGE);
		  current_context->pc++;
		}

	 RS(executing.C, string (ch_aux1));
	 current_context->pc++;
	 GOTO_NEXT_INSTR;
  }
  /* fim string */

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

