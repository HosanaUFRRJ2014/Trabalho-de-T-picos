#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "structs/lista.h"
#include "structs/peca.h"
#include "structs/R.h"
#include "arquivo.h"

#ifndef HEURISTICA_H
#define HEURISTICA_H

R* criarSolucao(R *nova, LISTA_LIGADA *P, LISTA_LIGADA *B)
{
	int i = 0,j = 0;
	NO *aux;

	aux = P->inicio;

	while(i < P->tamanho)
	{
		/*Tentar adicionar a peça nova.P[i](aux) ao ponto de origem do estoque
		ou para cada peça em B, tentar adicionar a peça nova.P[i](aux) nos
		pontos candidatos*/

		for(i = 0;i < aux->peca->l,i++)
		{
			for(j = 0;j < aux->peca->w,j++)
			{

			}
		}

		if(a peça foi adicionada)
		{
			PECA *peca = (PECA *) malloc (sizeof(PECA));
			peca = removerPeca(P); //Esta linha é igual ao if-else abaixo:
			inserirPecaOrdenado(B, peca); //B.Adiciona(nova.P[i])

			/*
			se(nova.P[i].quantidade == 1)
			{
				Excluir(nova.P[i])
			}
			então
			{
				nova.P[i].quantidade--;
			}
			*/
		}
		else
		{
			i++;
			aux = aux->proximo;
		}

		//aux = aux->proximo;
	}

	return nova;
};

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

	/*----------Heurística construtiva----------*/
	criarSolucao(atual);
	/*------------------------------------------*/

	melhor = atual;

	srand((double)time(NULL));

	while(temp > T_c)
	{
		while(iterT > It_max)
		{
			iterT++;
			/*------------Heurística da vizinhança(destruição)-------*/
			nova = trocarSolucao(atual);
			/*-------------------------------------------------------*/

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


#endif