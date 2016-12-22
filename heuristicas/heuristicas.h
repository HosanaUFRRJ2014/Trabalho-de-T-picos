#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "includes.h"

#ifndef HEURISTICA_H
#define HEURISTICA_H

//Função do algoritmo 1
inline R* criarSolucao(R *solucaoNova, LISTA_LIGADA *P, LISTA_LIGADA *B)
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
				
				removerPeca(P);
		
				PECA *aInserir = (PECA *) malloc (sizeof(PECA));

				copiarPeca(aInserir,aux->peca);

				aInserir->quantidade = 1;

			 	inserirPeca(B, aInserir);
			 	
			 }
			 // else
			 // {
			 	
			 // 	//printf("Não foi adicionada!!!!\n");
			 // }

			cont++;

		}

		aux = aux->proximo;
	}
//esse retorno não é necessário. Só o mantive para respeitar o formato de algoritmo que já estava aqui.
	return solucaoNova;

}

//função para evitar a sobrescrição de valores de trocarSolucao
inline void copiarSolucao(R *destino, R *origem)
{
	destino->W = origem->W;
	destino->L = origem->L;
	copiarMatriz(destino->matriz,origem->matriz, origem->L, origem->W);
	destino->indicePeca = origem->indicePeca;
	destino->quantidade = origem->quantidade;
	destino->valorUtilidadeTotal = origem->valorUtilidadeTotal;

}

inline R* trocarSolucao(R *atual, LISTA_LIGADA *P, LISTA_LIGADA *B, float gamma)
{
	//copiar a solução para não sobrescrever
	R *nova = criarRetanguloR(atual->L, atual->W);

	copiarSolucao(nova,atual);

	//Remover gamma da área de R;
	//Adicionar peças removidas a P;
	remocaoAleatoria(nova,P,B,gamma);
	//Deslocar peças restantes para esquerda;
	deslocarPecas(nova, B);
	
	criarSolucao(nova,P,B);


	return nova;
}

inline int Simulated_Annealing(float T, float T_c, int It_max, float alpha, R *atual, LISTA_LIGADA *P, LISTA_LIGADA *B)
{
	//R *atual, *nova, *melhor;
	R *nova,*melhor;
	int iterT = 0, delta; //temp = T
	double x;
	//float temp = T;

	//A lista P recebida aqui já estará ordenada.

	criarSolucao(atual,P,B);
	//------------------------------------------*

	melhor = atual;

//	srand((double)time(NULL));

	while(T > T_c)
	{
		while(iterT < It_max)
		{
			iterT++;
			nova = trocarSolucao(atual,P,B,0.35);
			// printf("solucaoNova: \n");
			// imprimirVariaveisR(nova);
			// imprimirR(nova->matriz,nova->L, nova->W);
			// printf("\n\nSolucao atual: \n");
			// imprimirVariaveisR(atual);
			// imprimirR(atual->matriz,atual->L,atual->W);
			//-------------------------------------------------------*

			//delta = f(atual) - f(nova);
			delta = atual->valorUtilidadeTotal - nova->valorUtilidadeTotal;

			printf("delta = %d\n",delta);

			if(delta < 0)
			{
				atual = nova;

				printf("DELTA é negativo!\n");

				//if(f(nova) > f(melhor))
				if(nova->valorUtilidadeTotal > melhor->valorUtilidadeTotal)
				{	
					printf("Foi melhor!!!\n");
					melhor = atual;
				}
			}
			else
			{	
				//Gerar números aleátórios entre 0 e 1.
    			x = ((double)(rand())/RAND_MAX);
    			printf("Não foi\n");
			//	printf("valor entre O e 1: %f\n",x);

				if(x < exp(-1 * (delta/T)))
				{
					printf("REALIMENTOU\n");
					atual = nova;
				}

				else
				{
					printf("NÃO REALIMENTOU\n");

				}
			}
		}
		T = alpha * T;
		iterT = 0;
	}
	return melhor->valorUtilidadeTotal;
}
//*/

#endif