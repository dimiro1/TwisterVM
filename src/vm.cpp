/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-21 09:59:05 BRT>
 */

#include "vm.h"

VM::~VM ()
{
  delete current_context;
}

/* load code_section into memory */
void VM::load (string progname)
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


void VM::list ()
{
  Instruction current;

  cout << " twisterc v" << current_context->header.major_version
		 << "." << current_context->header.minor_version 
		 << " (" << current_context->header.code_len
		 << " instructions)" << endl;
  
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
		  case OP_GOTO:
			 cout << current_context->get_label(current.A);
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

void VM::dispatch ()
{  
  string s_aux1;
  string s_aux2;
  char *ch_aux1;
  string input_s;
  double input_d;
  Instruction executing;

  /* see opcodes.h */
  BEGIN_SWITCH

  CASE (ADD_N)
	 #ifdef DEBUG
	 puts ("add_n");
	 #endif
	 RN(executing.C,
		 current_context->get_num (executing.A) +
		 current_context->get_num (executing.B));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (SUB_N)
	 #ifdef DEBUG
	 puts ("sub_n");
	 #endif
	 RN(executing.C,
		 current_context->get_num (executing.A) -
		 current_context->get_num (executing.B));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (MULT_N)
	 #ifdef DEBUG
	 puts ("mult_n");
	 #endif
	 RN(executing.C,
		 current_context->get_num (executing.A) *
		 current_context->get_num (executing.B));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (DIV_N)
	 #ifdef DEBUG
	 puts ("div_n");
	 #endif
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
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (MOD_N)
	 #ifdef DEBUG
	 puts ("mod_n");
	 #endif
	 RN(executing.C,
		 static_cast<int>(current_context->get_num (executing.A)) %
		 static_cast<int>(current_context->get_num (executing.B)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE(POW_N)
	 #ifdef DEBUG
	 puts ("pow_n");
	 #endif
	 RN(executing.C, pow (current_context->get_num (executing.A),
								 current_context->get_num (executing.B)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (NEG_N)			  /* TODO: melhorar esse neg */
	 #ifdef DEBUG
	 puts ("neg_n");
	 #endif
	 RN(executing.A, -current_context->get_num (executing.A));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (ABS_N)
	 #ifdef DEBUG
	 puts ("abs_n");
	 #endif
	 RN(executing.A, fabs (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (SIN_N)
	 #ifdef DEBUG
	 puts ("sin_n");
	 #endif
	 RN(executing.C, sin (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (COS_N)
	 #ifdef DEBUG
	 puts ("cos_n");
	 #endif
	 RN(executing.C, cos (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (TAN_N)
	 #ifdef DEBUG
	 puts ("tan_n");
	 #endif
	 RN(executing.C, tan (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (ASIN_N)
	 #ifdef DEBUG
	 puts ("asin_n");
	 #endif
	 RN(executing.C, asin (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (ACOS_N)
	 #ifdef DEBUG
	 puts ("acos_n");
	 #endif
	 RN(executing.C, acos (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (ATAN_N)
	 #ifdef DEBUG
	 puts ("atan_n");
	 #endif
	 RN(executing.C, atan (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (LOG_N)
	 #ifdef DEBUG
	 puts ("log_n");
	 #endif
	 RN(executing.C, log (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (SQRT_N)
	 #ifdef DEBUG
	 puts ("sqrt_n");
	 #endif
	 RN(executing.C, sqrt (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (CEIL_N) 
	 #ifdef DEBUG
	 puts ("ceil_n");
	 #endif
	 RN(executing.C, ceil (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (FLOOR_N)
	 #ifdef DEBUG
	 puts ("floor_n");
	 #endif
	 RN(executing.C, floor (current_context->get_num (executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (INC_N)
	 #ifdef DEBUG
	 puts ("inc_n");
	 #endif
	 RN(executing.A, RN(executing.A) + 1);
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (DEC_N)
	 #ifdef DEBUG
	 puts ("dec_n");
	 #endif
	 RN(executing.A, RN(executing.A) - 1);
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  /* fim opcodes aritmetica numeros */

  /* generic */
  CASE (NOP)
	 #ifdef DEBUG
	 puts ("nop");
	 #endif
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (GOTO)
	 #ifdef DEBUG
	 puts ("goto");
	 #endif
	 current_context->pc = current_context->get_label (executing.A);
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (HALT)
	 #ifdef DEBUG
	 puts ("halt");
	 #endif
	 exit (0);					  /* sai normalmente */
	 BREAK
  END_CASE
  /* fim generic */

  /* IO */
  CASE (PRINT_S)
	 #ifdef DEBUG
	 puts ("print_s");
	 #endif
	 cout << RS(executing.A);
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (PRINT_N)
	 #ifdef DEBUG
	 puts ("print_n");
	 #endif
	 cout << RN(executing.A);
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (PUT_S)
	 #ifdef DEBUG
	 puts ("put_s");
	 #endif
	 cout << RS(executing.A) << endl;
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (PUT_N)
	 #ifdef DEBUG
	 puts ("put_n");
	 #endif
	 cout << RN(executing.A) << endl;
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (INPUT_S)
	 #ifdef DEBUG
	 puts ("input_s");
	 #endif
	 cin >> input_s;
	 RS(executing.C, input_s);
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE
			 
  CASE (INPUT_N)
	 #ifdef DEBUG
	 puts ("input_n");
	 #endif
	 cin >> input_d;
	 RN(executing.C, input_d);
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE
  /* end IO */

  /* REgisters manipulation */
  CASE (MOV_N)
	 #ifdef DEBUG
	 puts ("mov_n");
	 #endif
	 RN(executing.B, current_context->get_num (executing.A));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (MOV_S)
	 #ifdef DEBUG
	 puts ("mov_s");
	 #endif
	 RS(executing.B, current_context->get_string(executing.A));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (STORE_S)
	 #ifdef DEBUG
	 puts ("store_s");
	 #endif
	 RS(executing.C, 
		 string (current_context->get_string(executing.A)));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  CASE (STORE_N)
	 #ifdef DEBUG
	 puts ("store_n");
	 #endif
	 RN(executing.C, 
		 current_context->get_num (executing.A));
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE
  /* fim Registers manipulation */

  /* string */

  CASE (CONCAT_S)
	 #ifdef DEBUG
	 puts ("concat_s");
	 #endif
	 s_aux1 = RS(executing.A);
	 s_aux2 = RS(executing.B);
	 RS(executing.C, s_aux1 + s_aux2);
	 current_context->pc++;
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE
  /* store_s "hello" $1 */
  /* charat_s $1 1 $0 */

  CASE (CHARAT_S)
	 #ifdef DEBUG
	 puts ("charat_s");
	 #endif
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
	 GOTO_NEXT_INSTR
	 BREAK
  END_CASE

  /* fim string */
  /* opcodes antigos. */
  CASE (ADD)
	 BREAK
  END_CASE

  CASE (CLSP)
	 BREAK
  END_CASE

  CASE (DCARD)
	 BREAK
  END_CASE

  CASE (DIV)
	 BREAK
  END_CASE

  CASE (GETOP)
	 BREAK
  END_CASE

  CASE (MULT)
	 BREAK
  END_CASE

  CASE (POP)
	 BREAK
  END_CASE

  CASE (PRINT)
	 BREAK
  END_CASE

  CASE (PUSH)
	 BREAK
  END_CASE

  CASE (PUTS)
	 BREAK
  END_CASE

  CASE (RESET)
	 BREAK
  END_CASE

  CASE (SUB)
	 BREAK
  END_CASE

  END_SWITCH
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

