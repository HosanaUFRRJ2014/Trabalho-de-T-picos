#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "includes.h"

#ifndef HEURISTICA_H
#define HEURISTICA_H

//Função do algoritmo 1
R * criarSolucao(R *solucaoNova, LISTA_LIGADA *P, LISTA_LIGADA *B)
{
	NO *aux;

	aux = P->inicio;

	LISTA_LIGADA *listaAuxliar = criarLista();

	while(aux != NULL)
	{
		inserirPeca(listaAuxliar, aux->peca);

		aux = aux->proximo;
	}

	aux = listaAuxliar->inicio;
	while(aux != NULL)
	{
		int cont = 0;
	
		int qtdInicial = aux->peca->quantidade;
	
		while(cont < qtdInicial)
		{
						
			int foiAdicionada = adicionarPecaAoRetangulo(solucaoNova, B , aux->peca);

			if(foiAdicionada)
			{
				PECA *removida;
				removida =  (PECA *) malloc (sizeof(PECA));
			
				removida = removerPeca(P);
		

			 	inserirPeca(B, aux->peca);
			 	
			 }
			 else
			 {
			 	printf("Não foi adicionada!!!!\n");
			 }

			cont++;

		}

		aux = aux->proximo;
	}
//esse retorno não é necessário. Só o mantive para respeitar o formato de algoritmo que já estava aqui.
	return solucaoNova;

}

//*********************************Comentei aqui só para tirar os erros de compilação
/*
R* trocarSolucao(R *nova, LISTA_LIGADA *P, LISTA_LIGADA *B)
{
	//Remover gamma da área de R;
	//Adicionar peças removidas a P;
	//Deslocar peças restantes para esquerda;
	criarSolucao(nova,P,B);
	return nova;
}

int Simulated_Annealing(int T, int T_c, int It_max, double alpha, R *R, LISTA_LIGADA *P, LISTA_LIGADA *B)
{
	R *atual, *nova, *melhor;
	int temp = T, iterT = 0, delta;
	double x;

	//A lista P recebida aqui já estará ordenada.

	criarSolucao(atual);
	/*------------------------------------------*

	melhor = atual;

	srand((double)time(NULL));

	while(temp > T_c)
	{
		while(iterT > It_max)
		{
			iterT++;
			nova = trocarSolucao(atual);
			/*-------------------------------------------------------*

			delta = f(atual) - f(nova);

			if(delta < 0)
			{
				atual = nova;

				if(f(nova) > f(melhor))
					melhor = atual;
			}
			else
			{	
				//Gerar números aleátórios entre 0 e 1.
				x = ((double)(rand())/RAND_MAX);

				if(x < exp(-1 * (delta/T)))
					atual = nova;
			}
		}
		T = alpha * T;
		iterT = 0;
	}
	return melhor;
}
*/

#endif