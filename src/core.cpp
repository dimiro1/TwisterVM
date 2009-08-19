     // Gerado por tools/opcode_gen.rb
     // modifique instructions.rb
     #include "VM.h"
       void TwisterVM::dispatch ()
       {
             STRING s_aux1;
	 STRING s_aux2;
	 char *ch_aux1;
	 STRING input_s;
	 NUMBER input_d;
	 Instruction executing;

      static const void
      *label_targets[] = {
	     "abs_n","acos_n","add_n","asin_n","atan_n","ceil_n","cos_n","dec_n","div_n","floor_n","inc_n","log_n","mod_n","mult_n","neg_n","pow_n","sin_n","sqrt_n","sub_n","tan_n","rand_n","goto","halt","nop","system_s","getenv_s","input_n","input_s","print_n","print_s","put_n","put_s","mov_n","mov_s","store_n","store_s","concat_s","charat_s","lt_s","gt_s","lte_s","gte_s","eq_s","lt_n","gt_n","lte_n","gte_n","eq_n","not_lt_s","not_gt_s","not_lte_s","not_gte_s","not_eq_s","not_lt_n","not_gt_n","not_lte_n","not_gte_n","not_eq_n","zero_n","not_zero_n",
      };
            executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];

LOP_ABS_N: {
	 #ifdef DEBUG
	 puts ("abs_n");
	 #endif
	 RN (executing.A, fabs (RN (executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_ACOS_N: {
	 #ifdef DEBUG
	 puts ("acos_n");
	 #endif
	 RN (executing.C, acos (RN (executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_ADD_N: {
	 #ifdef DEBUG
	 puts ("add_n");
	 #endif
	 RN (executing.C,
		 RN (executing.A) +
		 RN (executing.B));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_ASIN_N: {
	 #ifdef DEBUG
	 puts ("asin_n");
	 #endif
	 RN (executing.C, asin (RN (executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_ATAN_N: {
	 #ifdef DEBUG
	 puts ("atan_n");
	 #endif
	 RN (executing.C, atan (RN (executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_CEIL_N: {
	 #ifdef DEBUG
	 puts ("ceil_n");
	 #endif
	 RN (executing.C, ceil (RN (executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_COS_N: {
	 #ifdef DEBUG
	 puts ("cos_n");
	 #endif
	 RN (executing.C, cos (RN (executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_DEC_N: {
	 #ifdef DEBUG
	 puts ("dec_n");
	 #endif
	 RN (executing.A, (RN (executing.A) - 1));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_DIV_N: {
	 #ifdef DEBUG
	 puts ("div_n");
	 #endif
	 /* Colocar como exception */
	 if (RN (executing.B) == 0)
		{
		  error_emitter.emit (ZERO_DIVISION);
		  abort ();
		}
	 RN (executing.C,
		 RN (executing.A) /
		 RN (executing.B));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_FLOOR_N: {
	 #ifdef DEBUG
	 puts ("floor_n");
	 #endif
	 RN (executing.C, floor (RN (executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_INC_N: {
	 #ifdef DEBUG
	 puts ("inc_n");
	 #endif
	 RN (executing.A, (RN (executing.A) + 1));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_LOG_N: {
	 #ifdef DEBUG
	 puts ("log_n");
	 #endif
	 RN (executing.C, log (RN (executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_MOD_N: {
	 #ifdef DEBUG
	 puts ("mod_n");
	 #endif
	 RN (executing.C,
		 static_cast<int>(RN (executing.A)) %
		 static_cast<int>(RN (executing.B)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_MULT_N: {
	 #ifdef DEBUG
	 puts ("mult_n");
	 #endif
	 RN (executing.C,
		 RN (executing.A) *
		 RN (executing.B));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NEG_N: {
	 #ifdef DEBUG
	 puts ("neg_n");
	 #endif
	 RN (executing.A, -RN (executing.A));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_POW_N: {
	 #ifdef DEBUG
	 puts ("pow_n");
	 #endif
	 RN (executing.C, pow (RN (executing.A),
								 RN (executing.B)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_SIN_N: {
	 #ifdef DEBUG
	 puts ("sin_n");
	 #endif
	 RN (executing.C, sin (RN (executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_SQRT_N: {
	 #ifdef DEBUG
	 puts ("sqrt_n");
	 #endif
	 RN (executing.C, sqrt (RN (executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_SUB_N: {
	 #ifdef DEBUG
	 puts ("mult_n");
	 #endif
	 RN (executing.C,
		 RN (executing.A) -
		 RN (executing.B));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_TAN_N: {
	 #ifdef DEBUG
	 puts ("tan_n");
	 #endif
	 RN (executing.C, tan (RN (executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_RAND_N: {
	 #ifdef DEBUG
	 puts ("rand_n");
	 #endif
	 srand (time (0));
	 RN (executing.C, rand ());
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_GOTO: {
	 #ifdef DEBUG
	 puts ("goto");
	 #endif
	 current_context->pc = executing.A;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_HALT: {
	 #ifdef DEBUG
	 puts ("halt");
	 #endif
	 exit (0);                /* sai normalmente */
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOP: {
	 #ifdef DEBUG
	 puts ("nop");
	 #endif
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_SYSTEM_S: {
	 #ifdef DEBUG
	 puts ("system_s");
	 #endif
	 system (RS (executing.A).c_str ());
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_GETENV_S: {
	 #ifdef DEBUG
	 puts ("getenv_s");
	 #endif
	 ch_aux1 = getenv (RS (executing.A).c_str ());
	 if (ch_aux1 == NULL)
		error_emitter.emit (ENV_NOT_FOUND);
	 else
		RS (executing.C, STRING (ch_aux1));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_INPUT_N: {
	 #ifdef DEBUG
	 puts ("input_n");
	 #endif
	 read_num (input_d);
	 RN (executing.C, input_d);
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_INPUT_S: {
	 #ifdef DEBUG
	 puts ("input_s");
	 #endif
	 read_string (input_s);
	 RS (executing.C, input_s);
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_PRINT_N: {
	 #ifdef DEBUG
	 puts ("print_n");
	 #endif
	 print_num (RN (executing.A), false);
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_PRINT_S: {
	 #ifdef DEBUG
	 puts ("print_s");
	 #endif
	 print_string (RS (executing.A), false);
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_PUT_N: {
	 #ifdef DEBUG
	 puts ("put_n");
	 #endif
	 print_num (RN (executing.A), true);
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_PUT_S: {
	 #ifdef DEBUG
	 puts ("put_s");
	 #endif
	 print_string (RS (executing.A), true);
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_MOV_N: {
	 #ifdef DEBUG
	 puts ("mov_n");
	 #endif
	 RN (executing.C, RN (executing.A));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_MOV_S: {
	 #ifdef DEBUG
	 puts ("mov_s");
	 #endif
	 RS (executing.C, RS (executing.A));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_STORE_N: {
	 #ifdef DEBUG
	 puts ("store_n");
	 #endif
	 RN (executing.C,
		 current_context->get_num (executing.A));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_STORE_S: {
	 #ifdef DEBUG
	 puts ("store_s");
	 #endif
	 RS (executing.C,
		 STRING (current_context->get_string(executing.A)));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_CONCAT_S: {
	 #ifdef DEBUG
	 puts ("concat_s");
	 #endif
	 s_aux1 = RS (executing.A);
	 s_aux2 = RS (executing.B);
	 RS (executing.C, s_aux1 + s_aux2);
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_CHARAT_S: {
	 #ifdef DEBUG
	 puts ("charat_s");
	 #endif
	 s_aux1 = RS (executing.A);
	 ch_aux1 = new char[2];

	 try {
		/* converte caractere inteiro em char * */
		sprintf (ch_aux1, "%c", s_aux1.at(executing.B));
	 }
	 catch (out_of_range e) {
		error_emitter.emit (OUT_OF_RANGE);
		current_context->pc++;
	 }

	 RS (executing.C, STRING (ch_aux1));
	 current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_LT_S: {
	 #ifdef DEBUG
	 puts ("lt_s");
	 #endif
	 if (RS (executing.A) <
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_GT_S: {
	 #ifdef DEBUG
	 puts ("gt_s");
	 #endif
	 if (RS (executing.A) >
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_LTE_S: {
	 #ifdef DEBUG
	 puts ("lte_s");
	 #endif
	 if (RS (executing.A) <=
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_GTE_S: {
	 #ifdef DEBUG
	 puts ("gte_s");
	 #endif
	 if (RS (executing.A) >=
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_EQ_S: {
	 #ifdef DEBUG
	 puts ("eq_s");
	 #endif
	 if (RS (executing.A) ==
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_LT_N: {
	 #ifdef DEBUG
	 puts ("lt_n");
	 #endif
	 if (RN (executing.A) <
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_GT_N: {
	 #ifdef DEBUG
	 puts ("gt_n");
	 #endif
	 if (RN (executing.A) >
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_LTE_N: {
	 #ifdef DEBUG
	 puts ("lte_n");
	 #endif
	 if (RN (executing.A) <=
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_GTE_N: {
	 #ifdef DEBUG
	 puts ("gte_n");
	 #endif
	 if (RN (executing.A) >=
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_EQ_N: {
	 #ifdef DEBUG
	 puts ("eq_n");
	 #endif
	 /* cout << RN (executing.A) << endl; */
	 /* cout << RN (4) << endl; */
	 /* cout << executing.B << endl; */
	 if (RN (executing.A) ==
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOT_LT_S: {
	 #ifdef DEBUG
	 puts ("not_lt_s");
	 #endif
	 if (RS (executing.A) >=
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOT_GT_S: {
	 #ifdef DEBUG
	 puts ("not_gt_s");
	 #endif
	 if (RS (executing.A) <=
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOT_LTE_S: {
	 #ifdef DEBUG
	 puts ("not_lte_s");
	 #endif
	 if (RS (executing.A) >
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOT_GTE_S: {
	 #ifdef DEBUG
	 puts ("not_gte_s");
	 #endif
	 if (RS (executing.A) <
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOT_EQ_S: {
	 #ifdef DEBUG
	 puts ("not_eq_s");
	 #endif
	 if (RS (executing.A) !=
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOT_LT_N: {
	 #ifdef DEBUG
	 puts ("not_lt_n");
	 #endif
	 if (RN (executing.A) >=
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOT_GT_N: {
	 #ifdef DEBUG
	 puts ("not_gt_n");
	 #endif
	 if (RN (executing.A) <=
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOT_LTE_N: {
	 #ifdef DEBUG
	 puts ("not_lte_n");
	 #endif
	 if (RN (executing.A) >
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOT_GTE_N: {
	 #ifdef DEBUG
	 puts ("not_gte_n");
	 #endif
	 if (RN (executing.A) <
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOT_EQ_N: {
	 #ifdef DEBUG
	 puts ("not_eq_n");
	 #endif
	 if (RN (executing.A) !=
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_ZERO_N: {
	 #ifdef DEBUG
	 puts ("zero_n");
	 #endif
	 if (RN (executing.A) == 0)
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}
LOP_NOT_ZERO_N: {
	 #ifdef DEBUG
	 puts ("zero_n");
	 #endif
	 if (RN (executing.A) != 0)
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
      executing = current_context->code_section[current_context->pc];
      goto *label_targets[executing.opcode];
}

}
