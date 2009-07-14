; versão otimizada do exemplo1
.options
   @size 2 ; quantidade de instruções
           ; não é nem muito necessario
           ; so coloque essa opção
           ; pois preciso do tamanho para
           ; alocar o segmento de codigo
           ; bem simples mudar isso no assembler

           ; basta ler todas as instruções
           ; numa lista, por exemplo e depois pegar 
           ; o tamanho da lista para alocar o espaço
           ; de codigo.
.end
		  
.code
  push 9356.2
  puts
.end

