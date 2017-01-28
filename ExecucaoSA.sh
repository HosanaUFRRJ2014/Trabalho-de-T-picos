#!/bin/bash

#Script que será utilizado para executar os testes das instâncias disponíveis do problema.

if [[ $1 = "descricao" && $# -eq 1 ]]
then
	echo "=============================================================================================================================" 
	printf "\nScript feito para executar os conjuntos de testes de instâncias utilizadas para a validação do Trabalho de Tópicos Especiais em Otimização.\n\n"
	echo "Projeto: Resolução do Problema de Corte Bidimensional Não Guilhotinado."
	printf "Integrantes: Hosana Gomes e Lívia de Azevedo.\n\n"
	printf "Descrição: O script gerará uma arquivo log com nome definido de 'testeinst[x].txt' dentro da pasta 'testesInstancias'. Cada execução terá a data da execução juntamente com os testes feitos. Testes realizados com a mesma instância serão salvos no mesmo arquivo referente àquele teste, caso o mesmo já esteja criado.\n\n"
	printf " Descrição dos parâmetros para execução:\n\n"
	echo " Parâmetro 1: Nome do arquivo da instância(ex:inst1.txt)"								       	   
	echo " Parâmetro 2: Temperatura inicial"					
	echo " Parâmetro 3: Temperatura de congelamento(critério de parada)"					
	echo " Parâmetro 4: Número de Iterações máximas por Temperatura"
	echo " Parâmetro 5: Taxa de resfriamento"  					   
	echo " Parâmetro 6: Quantidade de vezes que o teste será realizado com a instância"					     
	printf " Parâmetro 7: Diretório do projeto(ex: /home/livia/Trabalho-de-Topicos)\n\n"
	echo "Exemplo de execução:"
	echo "./ExecucaoSA.sh inst1.txt 10000 0.11 50 0.98 1 /home/livia/Trabalho-de-Topicos"
	echo "============================================================================================================================="
	exit 0
fi

if [ $# -ne 7 ]
then
	echo "----------------------------------------------------------------------------------"
	echo "Número de parâmetros insuficiente. Digite './ExecucaoSA.sh descricao' para mais informações."
	echo "----------------------------------------------------------------------------------"
	exit 1
fi

echo >> testesInstancias/teste$1

echo "==========================================Teste feito em: `date`===============================================" >> testesInstancias/teste$1

echo "|--------------->Parâmetros de entrada do SA<-----------------|" >> testesInstancias/teste$1
echo " Temperatura inicial (T): $2" >> testesInstancias/teste$1 
echo " Temperatura de congelamento (T_c): $3" >> testesInstancias/teste$1
echo " Número máximo de iterações (It_max): $4" >> testesInstancias/teste$1
echo " Taxa de resfriamento (alpha): $5" >> testesInstancias/teste$1
echo "|-------------------------------------------------------------|" >> testesInstancias/teste$1
echo >> testesInstancias/teste$1

gcc Main.c -o Main -I $7 -O3 -lm

for (( i = 1; i <= $6; i++ ))
do
	echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%TESTE $i%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" >> testesInstancias/teste$1
	./Main testes/$1 $2 $3 $4 $5 >> testesInstancias/teste$1
	echo >> testesInstancias/teste$1 

done
