# Trabalho-de-T-picos
Repositório para o trabalho de Tópicos Especiais em Otimização

**Instruções:**

1) Para compilar, use : 

	gcc [file].c -o m -I /path/until/trabTop -O3 -lm

No qual file é o nome do arquivo do tipo C que se deseja compilar.	

Exemplo:

	gcc Main.c -o Main -I /home/hosana/git/Trabalho-de-T-picos -O3 -lm

A diretiva -I fará com que o arquivo includes.h seja incluido em qualquer outro arquivo dentro de qualquer pasta.
Consulte: 
https://gcc.gnu.org/onlinedocs/cpp/Search-Path.html#Search-Path 
para mais informações.

A diretiva -O3 fará com que o código seja otimizado pelo compilador.

A diretiva -lm permitirá que funções da bibliotema math.h sejam usadas.



***************************Para executar********************************
2) Para executar a aplicação, digite :
./[nome_do_programa] [arquivo_de_Teste].txt [temperatura_Inicial] [temperatura_de_congelamento] [num_max_iteracoes] [taxa_resfriamento]

Exemplo de execução:

	./Main testes/inst1.txt 10000 0.11 700 0.98 

Vale ressaltar que as instâncias de teste do programa podem ser encontradas dentro da pasta testes da aplicação.


************Notas adicionais para testes e debug no gdb: ***************

3) Para compilar na forma de debug:
-Dentro da pasta testes, no terminal, digite o comando:
	
	gcc testesFuncoes.c -g -o tt -I /path/until/Trabalho-de-T-picos -lm

A diretiva -g ajuda o debugger a indicar e criar breakpoint e a indicar em qual função e linha ocorreu algum possível segmentation fault.

não se esqueça de trocar o endereço do comando pelo seu endereço de diretório, conforme visto na instrução 1)!!!

-para executar normalmente:

	./tt inst[x].txt

lembrando que [x] deve ser trocado por algum valor entre 1 e 21 inclusive.

-para debugar no gdb:
	Digite gdb no terminal
	Digite  file tt
	Agora digite run inst[x].txt
