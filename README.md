# Trabalho-de-T-picos
Repositório para o trabalho de Tópicos Especiais em Otimização

Para compilar, usar : 

gcc FILE -o m -I /path/until/trabTop -lm

Exemplo:

gcc Main.c -o Main -I /home/hosana/git/Trabalho-de-T-picos -O3 -lm

A diretiva -I fará com que o arquivo includes.h seja incluido em qualquer outro arquivo dentro de qualquer pasta.
Consulte: 
https://gcc.gnu.org/onlinedocs/cpp/Search-Path.html#Search-Path 
para mais informações.

A diretiva -O3 fará com que o código seja otimizado pelo compilador.

A diretiva -lm permitirá que funções da bibliotema math.h sejam usadas.

************Notas adicionais para testes e debug no gdb: ***************

Para compilar na forma de debug:
-Dentro da pasta testes, no terminal, digite o comando:
gcc testesFuncoes.c -g -o tt -I /home/hosana/git/Trabalho-de-T-picos -lm

A diretiva -g ajuda o debugger a indicar e criar breakpoint e a indicar em qual função e linha ocorreu algum possível segmentation fault.

não se esqueça de trocar o endereço do comando pelo seu endereço de diretório!!!

-para executar normalmente:
./tt inst[x].txt

lembrando que [x] assume valores de 1 a 21;

-para debugar no gdb:
	Digite gdb no terminal
	digite  file tt
	agora digite run inst[x].txt
