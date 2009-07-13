; ( 77 * 2 ) * 99 / 5 - 5 + 8.1 * 789
.begin Header
   @size 14 ; quantidade de instruções
.end Header
		  
.begin Code
  push 77
  push 2
  mult
  push 99
  mult
  push 5
  div
  push 5
  sub
  push 8.1
  add
  push 789
  mult
  puts
.end Code

