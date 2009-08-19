# opcodes
# use o gerador na pasta tools

using do
  <<-CODE
    STRING s_aux1;
	 STRING s_aux2;
	 char *ch_aux1;
	 STRING input_s;
	 NUMBER input_d;
	 Instruction executing;
  CODE
end

opcode :abs_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("abs_n");
	 #endif
	 RN (executing.A, fabs (RN (executing.A)));
	 current_context->pc++;
  CODE
end

opcode :acos_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("acos_n");
	 #endif
	 RN (executing.C, acos (RN (executing.A)));
	 current_context->pc++;
  CODE
end

opcode :add_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("add_n");
	 #endif
	 RN (executing.C,
		 RN (executing.A) +
		 RN (executing.B));
	 current_context->pc++;
    CODE
end

opcode :asin_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("asin_n");
	 #endif
	 RN (executing.C, asin (RN (executing.A)));
	 current_context->pc++;
  CODE
end

opcode :atan_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("atan_n");
	 #endif
	 RN (executing.C, atan (RN (executing.A)));
	 current_context->pc++;
  CODE
end

opcode :ceil_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("ceil_n");
	 #endif
	 RN (executing.C, ceil (RN (executing.A)));
	 current_context->pc++;
  CODE
end

opcode :cos_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("cos_n");
	 #endif
	 RN (executing.C, cos (RN (executing.A)));
	 current_context->pc++;
  CODE
end

opcode :dec_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("dec_n");
	 #endif
	 RN (executing.A, (RN (executing.A) - 1));
	 current_context->pc++;
  CODE
end

opcode :div_n do
  <<-CODE
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
  CODE
end

opcode :floor_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("floor_n");
	 #endif
	 RN (executing.C, floor (RN (executing.A)));
	 current_context->pc++;
  CODE
end

opcode :inc_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("inc_n");
	 #endif
	 RN (executing.A, (RN (executing.A) + 1));
	 current_context->pc++;
  CODE
end

opcode :log_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("log_n");
	 #endif
	 RN (executing.C, log (RN (executing.A)));
	 current_context->pc++;
  CODE
end

opcode :mod_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("mod_n");
	 #endif
	 RN (executing.C,
		 static_cast<int>(RN (executing.A)) %
		 static_cast<int>(RN (executing.B)));
	 current_context->pc++;
  CODE
end

opcode :mult_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("mult_n");
	 #endif
	 RN (executing.C,
		 RN (executing.A) *
		 RN (executing.B));
	 current_context->pc++;
    CODE
end

opcode :neg_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("neg_n");
	 #endif
	 RN (executing.A, -RN (executing.A));
	 current_context->pc++;
  CODE
end

opcode :pow_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("pow_n");
	 #endif
	 RN (executing.C, pow (RN (executing.A),
								 RN (executing.B)));
	 current_context->pc++;
  CODE
end

opcode :sin_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("sin_n");
	 #endif
	 RN (executing.C, sin (RN (executing.A)));
	 current_context->pc++;
  CODE
end

opcode :sqrt_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("sqrt_n");
	 #endif
	 RN (executing.C, sqrt (RN (executing.A)));
	 current_context->pc++;
  CODE
end

opcode :sub_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("mult_n");
	 #endif
	 RN (executing.C,
		 RN (executing.A) -
		 RN (executing.B));
	 current_context->pc++;
    CODE
end

opcode :tan_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("tan_n");
	 #endif
	 RN (executing.C, tan (RN (executing.A)));
	 current_context->pc++;
  CODE
end

opcode :rand_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("rand_n");
	 #endif
	 srand (time (0));
	 RN (executing.C, rand ());
	 current_context->pc++;
  CODE
end

opcode :goto do
  <<-CODE
	 #ifdef DEBUG
	 puts ("goto");
	 #endif
	 current_context->pc = executing.A;
  CODE
end

opcode :halt do
  <<-CODE
	 #ifdef DEBUG
	 puts ("halt");
	 #endif
	 exit (0);                /* sai normalmente */
  CODE
end

opcode :nop do
  <<-CODE
	 #ifdef DEBUG
	 puts ("nop");
	 #endif
	 current_context->pc++;
  CODE
end

opcode :system_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("system_s");
	 #endif
	 system (RS (executing.A).c_str ());
	 current_context->pc++;
  CODE
end

opcode :getenv_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("getenv_s");
	 #endif
	 ch_aux1 = getenv (RS (executing.A).c_str ());
	 if (ch_aux1 == NULL)
		error_emitter.emit (ENV_NOT_FOUND);
	 else
		RS (executing.C, STRING (ch_aux1));
	 current_context->pc++;
  CODE
end

opcode :input_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("input_n");
	 #endif
	 read_num (input_d);
	 RN (executing.C, input_d);
	 current_context->pc++;
  CODE
end

opcode :input_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("input_s");
	 #endif
	 read_string (input_s);
	 RS (executing.C, input_s);
	 current_context->pc++;
  CODE
end

opcode :print_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("print_n");
	 #endif
	 print_num (RN (executing.A), false);
	 current_context->pc++;
  CODE
end

opcode :print_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("print_s");
	 #endif
	 print_string (RS (executing.A), false);
	 current_context->pc++;
  CODE
end

opcode :put_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("put_n");
	 #endif
	 print_num (RN (executing.A), true);
	 current_context->pc++;
  CODE
end

opcode :put_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("put_s");
	 #endif
	 print_string (RS (executing.A), true);
	 current_context->pc++;
  CODE
end

opcode :mov_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("mov_n");
	 #endif
	 RN (executing.C, RN (executing.A));
	 current_context->pc++;
  CODE
end

opcode :mov_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("mov_s");
	 #endif
	 RS (executing.C, RS (executing.A));
	 current_context->pc++;
  CODE
end

opcode :store_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("store_n");
	 #endif
	 RN (executing.C,
		 current_context->get_num (executing.A));
	 current_context->pc++;
  CODE
end

opcode :store_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("store_s");
	 #endif
	 RS (executing.C,
		 STRING (current_context->get_string(executing.A)));
	 current_context->pc++;
  CODE
end

opcode :concat_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("concat_s");
	 #endif
	 s_aux1 = RS (executing.A);
	 s_aux2 = RS (executing.B);
	 RS (executing.C, s_aux1 + s_aux2);
	 current_context->pc++;
  CODE
end

opcode :charat_s do
  <<-CODE
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
  CODE
end

opcode :lt_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("lt_s");
	 #endif
	 if (RS (executing.A) <
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :gt_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("gt_s");
	 #endif
	 if (RS (executing.A) >
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :lte_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("lte_s");
	 #endif
	 if (RS (executing.A) <=
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :gte_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("gte_s");
	 #endif
	 if (RS (executing.A) >=
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :eq_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("eq_s");
	 #endif
	 if (RS (executing.A) ==
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :lt_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("lt_n");
	 #endif
	 if (RN (executing.A) <
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :gt_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("gt_n");
	 #endif
	 if (RN (executing.A) >
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :lte_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("lte_n");
	 #endif
	 if (RN (executing.A) <=
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :gte_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("gte_n");
	 #endif
	 if (RN (executing.A) >=
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :eq_n do
  <<-CODE
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
  CODE
end

opcode :not_lt_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("not_lt_s");
	 #endif
	 if (RS (executing.A) >=
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :not_gt_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("not_gt_s");
	 #endif
	 if (RS (executing.A) <=
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :not_lte_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("not_lte_s");
	 #endif
	 if (RS (executing.A) >
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :not_gte_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("not_gte_s");
	 #endif
	 if (RS (executing.A) <
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :not_eq_s do
  <<-CODE
	 #ifdef DEBUG
	 puts ("not_eq_s");
	 #endif
	 if (RS (executing.A) !=
		  RS (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :not_lt_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("not_lt_n");
	 #endif
	 if (RN (executing.A) >=
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :not_gt_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("not_gt_n");
	 #endif
	 if (RN (executing.A) <=
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :not_lte_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("not_lte_n");
	 #endif
	 if (RN (executing.A) >
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :not_gte_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("not_gte_n");
	 #endif
	 if (RN (executing.A) <
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :not_eq_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("not_eq_n");
	 #endif
	 if (RN (executing.A) !=
		  RN (executing.B))
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :zero_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("zero_n");
	 #endif
	 if (RN (executing.A) == 0)
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end

opcode :not_zero_n do
  <<-CODE
	 #ifdef DEBUG
	 puts ("zero_n");
	 #endif
	 if (RN (executing.A) != 0)
		  current_context->pc = executing.C;
	 else
		  current_context->pc++;
  CODE
end
