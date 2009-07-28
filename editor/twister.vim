"" Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
"" <dimiro1@gmail.com>
""
"" this is a simple syntax file for working with twister assembler
""
"" offerings:
""
"" 1) syntax highlighting
""
"" This program is free software: you can redistribute it and/or modify
"" it under the terms of the GNU General Public License as published by
"" the Free Software Foundation, either version 3 of the License, or
"" (at your option) any later version.
""
"" This program is distributed in the hope that it will be useful,
"" but WITHOUT ANY WARRANTY; without even the implied warranty of
"" MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
"" GNU General Public License for more details.
""
"" You should have received a copy of the GNU General Public License
"" along with this program. If not, see <http://www.gnu.org/licences>

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

