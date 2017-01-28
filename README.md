# Trabalho de Tópicos Especiais em Otimização
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

4) Para executar o shell script para a execução de um conjunto de testes:

-Dentro da pasta do projeto, no terminal, digite o comando:

	chmod a+x ExecucaoSA.sh

O comando "chmod" altera as permissões ods arquivos com relação ao seu uso. O comando anterior dará permissão de execução do arquivo como um executável. Para executá-lo, basta digitar no terminal(lembrando, dentro da pasta do projeto) o seguinte comando:

	./ExecucaoSA.sh P1 P2 P3 P4 P5 P6 P7
Onde:

P1: Nome do arquivo da instância(ex:inst1.txt);								       	   
P2: Temperatura inicial;					
P3: Temperatura de congelamento(critério de parada);					
P4: Número de Iterações máximas por Temperatura;
P5: Taxa de resfriamento;  					   
P6: Quantidade de vezes que o teste será realizado com a instância;					     
P7: Diretório do projeto(ex: /home/livia/Trabalho-de-Topicos).

Exemplo de execução:

	./ExecucaoSA.sh inst1.txt 10000 0.11 50 0.98 1 /home/livia/Trabalho-de-Topicos

O script gerará uma arquivo log com nome definido de 'testeinst[x].txt' dentro da pasta 'testesInstancias'. Cada execução terá a data da execução juntamente com os testes feitos. Testes realizados com a mesma instância serão salvos no mesmo arquivo referente àquele teste, caso o mesmo já esteja criado.

Qualquer dúvida na execução deste shell script, digite o comando "./ExecucaoSA.sh descricao" no terminal dentro da pasta do projeto.
