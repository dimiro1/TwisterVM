; ( 77 * 2 ) * 99 / 5 - 5 + 8.1 * 789
; (77 * 2)
; 154 * 99
; 15246 / 5
; 3049.2
; 8 * 789
; 6312
; 3049.2 - 5
; 3044.2 * 6312

.options
   @size 14 ; quantidade de instruções
.end

;.static
;.end
		  
.code
  push 77
  push 2
  mult
  push 99
  mult
  push 5
  div
  push 5
  sub
  push 8
  push 789
  mult
  add
  puts
.end
