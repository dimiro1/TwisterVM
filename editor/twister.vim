if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

syn keyword twisterOpcodes abs_n acos_n add_n asin_n atan_n ceil_n cos_n dec_n div_n floor_n inc_n log_n mod_n mult_n neg_n pow_n sin_n sqrt_n sub_n tan_n
syn keyword twisterOpcodes goto halt nop
syn keyword twisterOpcodes input_n input_s print_n print_s put_n put_s mov_n mov_s
syn keyword twisterOpcodes store_s store_n concat_s charat_s system_s getenv_s
syn keyword twisterBranch lt_s gt_s lte_s gte_s eq_s lt_n gt_n lte_n gte_n eq_n not_lt_s zero_n not_zero_n
syn keyword twisterBranch not_gt_s not_lte_s not_gte_s not_eq_s not_lt_n not_gt_n not_lte_n not_gte_n not_eq_n

syn match twisterDirectiveSub    /\.\(main\|end\|options\|name\)/

syn match twisterWord           /[A-Za-z_][A-Za-z0-9_]*/
syn match twisterComment        /#.*/
syn match twisterLabel          /[A-Za-z0-9_]\+:/he=e-1
syn match twisterDollarRegister /\$[0-9]\+/

syn match twisterNumber         /[+-]\?[0-9]\+\(\.[0-9]*\([Ee][+-]\?[0-9]\+\)\?\)\?/
syn match twisterNumber         /0[xX][0-9a-fA-F]\+/
syn match twisterNumber         /0[oO][0-7]\+/
syn match twisterNumber         /0[bB][01]\+/

syn region twisterString start=/"/ end=/"/
syn region twisterString start=/'/ end=/'/

hi link twisterWord            Normal
hi link twisterComment         Comment
hi link twisterLabel           Constant
hi link twisterDollarRegister  Identifier
hi link twisterString          String
hi link twisterNumber          Number
hi link twisterDirectiveSub    Keyword
hi link twisterBranch          Keyword
hi link twisterOpcodes         Keyword
let b:current_syntax = "twister"

