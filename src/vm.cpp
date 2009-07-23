/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-22 10:19:33 BRT>
 */

#include "vm.h"

VM::~VM ()
{
  delete current_context;
}

void VM::execute ()
{
  dispatch ();
}

/* load code_section into memory */
void VM::load (string progname)
{
  current_context = new ExecContext ();

  try {
	 current_context->load_file (progname);
  }
  catch (BadFileException e) {
	 cerr << e.what () << endl;
	 abort ();
  }
  catch (NotRecognizedFileException e) {
	 cerr << e.what () << endl;
	 abort ();
  }
  catch (bad_alloc e) {
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
          case OP_LT_S:
          case OP_GT_S:
          case OP_LTE_S:
          case OP_GTE_S:
          case OP_EQ_S:
          case OP_NOT_LT_S:
          case OP_NOT_GT_S:
          case OP_NOT_LTE_S:
          case OP_NOT_GTE_S:
          case OP_NOT_EQ_S:
          case OP_LT_N:
          case OP_GT_N:
          case OP_LTE_N:
          case OP_GTE_N:
          case OP_EQ_N:
          case OP_NOT_LT_N:
          case OP_NOT_GT_N:
          case OP_NOT_LTE_N:
          case OP_NOT_GTE_N:
          case OP_NOT_EQ_N:
            cout  << "$" << current.A
                  << " $" << current.B
                  << " " << current_context->get_label (current.C);
            break;
        }
        cout << endl;
    }
}

void VM::dispatch ()
{
  STRING s_aux1;
  STRING s_aux2;
  char *ch_aux1;
  STRING input_s;
  NUMBER input_d;
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

  CASE (NEG_N)            /* TODO: melhorar esse neg */
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
    exit (0);                /* sai normalmente */
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
       STRING (current_context->get_string(executing.A)));
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

    try {
		sprintf (ch_aux1, "%c", s_aux1.at(executing.B));
    }
    catch (out_of_range e) {
		error_emitter.emit (OUT_OF_RANGE);
		current_context->pc++;
	 }

    RS(executing.C, STRING (ch_aux1));
    current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  /* condicionais */
  CASE (LT_S)
    #ifdef DEBUG
    puts ("lt_s");
    #endif
    if (current_context->get_string (executing.A) <
        current_context->get_string (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (GT_S)
    #ifdef DEBUG
    puts ("gt_s");
    #endif
    if (current_context->get_string (executing.A) >
        current_context->get_string (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (LTE_S)
    #ifdef DEBUG
    puts ("lte_s");
    #endif
    if (current_context->get_string (executing.A) <=
        current_context->get_string (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (GTE_S)
    #ifdef DEBUG
    puts ("gte_s");
    #endif
    if (current_context->get_string (executing.A) >=
        current_context->get_string (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (EQ_S)
    #ifdef DEBUG
    puts ("eq_s");
    #endif
    if (current_context->get_string (executing.A) ==
        current_context->get_string (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (LT_N)
    #ifdef DEBUG
    puts ("lt_n");
    #endif
    if (current_context->get_num (executing.A) <
        current_context->get_num (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;

    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (GT_N)
    #ifdef DEBUG
    puts ("gt_n");
    #endif
    if (current_context->get_num (executing.A) >
        current_context->get_num (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (LTE_N)
    #ifdef DEBUG
    puts ("lte_n");
    #endif
    if (current_context->get_num (executing.A) <=
        current_context->get_num (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (GTE_N)
    #ifdef DEBUG
    puts ("gte_n");
    #endif
    if (current_context->get_num (executing.A) >=
        current_context->get_num (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (EQ_N)
    #ifdef DEBUG
    puts ("eq_n");
    #endif
    if (current_context->get_num (executing.A) ==
        current_context->get_num (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  /* relacionais falso */
  CASE (NOT_LT_S)
    #ifdef DEBUG
    puts ("not_lt_s");
    #endif
    if (current_context->get_string (executing.A) >=
        current_context->get_string (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (NOT_GT_S)
    #ifdef DEBUG
    puts ("not_gt_s");
    #endif
    if (current_context->get_string (executing.A) <=
        current_context->get_string (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (NOT_LTE_S)
    #ifdef DEBUG
    puts ("not_lte_s");
    #endif
    if (current_context->get_string (executing.A) >
        current_context->get_string (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (NOT_GTE_S)
    #ifdef DEBUG
    puts ("not_gte_s");
    #endif
    if (current_context->get_string (executing.A) <
        current_context->get_string (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (NOT_EQ_S)
    #ifdef DEBUG
    puts ("not_eq_s");
    #endif
    if (current_context->get_string (executing.A) !=
        current_context->get_string (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (NOT_LT_N)
    #ifdef DEBUG
    puts ("not_lt_n");
    #endif
    if (current_context->get_num (executing.A) >=
        current_context->get_num (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;

    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (NOT_GT_N)
    #ifdef DEBUG
    puts ("not_gt_n");
    #endif
    if (current_context->get_num (executing.A) <=
        current_context->get_num (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (NOT_LTE_N)
    #ifdef DEBUG
    puts ("not_lte_n");
    #endif
    if (current_context->get_num (executing.A) >
        current_context->get_num (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (NOT_GTE_N)
    #ifdef DEBUG
    puts ("not_gte_n");
    #endif
    if (current_context->get_num (executing.A) <
        current_context->get_num (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

  CASE (NOT_EQ_N)
    #ifdef DEBUG
    puts (not_"eq_n");
    #endif
    if (current_context->get_num (executing.A) !=
        current_context->get_num (executing.B))
        current_context->pc = current_context->get_label (executing.C);
    else
        current_context->pc++;
    GOTO_NEXT_INSTR
    BREAK
  END_CASE

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

inline STRING VM::RS (int i)
{ 
	 return s_registers[i]; 
}

inline NUMBER VM::RN (int i)
{ 
	 return n_registers[i];
}

/* registers sets */
inline void VM::RS (int i, STRING s)
{ 
	 s_registers[i] = s; 
}

inline void VM::RN (int i, NUMBER n) 
{ 
	 n_registers[i] = n;
}

