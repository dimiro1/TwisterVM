     // Gerado por tools/opcode_gen.rb
     // modifique instructions.rb
    #ifndef _OPCODE_H_
    #define _OPCODE_H_
    #define HAVE_COMPUTED_GOTO
    enum Opcode { OP_ABS_N,OP_ACOS_N,OP_ADD_N,OP_ASIN_N,OP_ATAN_N,OP_CEIL_N,OP_COS_N,OP_DEC_N,OP_DIV_N,OP_FLOOR_N,OP_INC_N,OP_LOG_N,OP_MOD_N,OP_MULT_N,OP_NEG_N,OP_POW_N,OP_SIN_N,OP_SQRT_N,OP_SUB_N,OP_TAN_N,OP_RAND_N,OP_GOTO,OP_HALT,OP_NOP,OP_SYSTEM_S,OP_GETENV_S,OP_INPUT_N,OP_INPUT_S,OP_PRINT_N,OP_PRINT_S,OP_PUT_N,OP_PUT_S,OP_MOV_N,OP_MOV_S,OP_STORE_N,OP_STORE_S,OP_CONCAT_S,OP_CHARAT_S,OP_LT_S,OP_GT_S,OP_LTE_S,OP_GTE_S,OP_EQ_S,OP_LT_N,OP_GT_N,OP_LTE_N,OP_GTE_N,OP_EQ_N,OP_NOT_LT_S,OP_NOT_GT_S,OP_NOT_LTE_S,OP_NOT_GTE_S,OP_NOT_EQ_S,OP_NOT_LT_N,OP_NOT_GT_N,OP_NOT_LTE_N,OP_NOT_GTE_N,OP_NOT_EQ_N,OP_ZERO_N,OP_NOT_ZERO_N, };

    static const char *
    mneumonic[] = {
      "abs_n","acos_n","add_n","asin_n","atan_n","ceil_n","cos_n","dec_n","div_n","floor_n","inc_n","log_n","mod_n","mult_n","neg_n","pow_n","sin_n","sqrt_n","sub_n","tan_n","rand_n","goto","halt","nop","system_s","getenv_s","input_n","input_s","print_n","print_s","put_n","put_s","mov_n","mov_s","store_n","store_s","concat_s","charat_s","lt_s","gt_s","lte_s","gte_s","eq_s","lt_n","gt_n","lte_n","gte_n","eq_n","not_lt_s","not_gt_s","not_lte_s","not_gte_s","not_eq_s","not_lt_n","not_gt_n","not_lte_n","not_gte_n","not_eq_n","zero_n","not_zero_n",
    };
    #endif
