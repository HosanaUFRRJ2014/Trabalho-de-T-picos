#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "includes.h"

#ifndef HEURISTICA_H
#define HEURISTICA_H

//Função do algoritmo 1
R* criarSolucao(R *solucaoNova, LISTA_LIGADA *P, LISTA_LIGADA *B)
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

R* trocarSolucao(R *nova, LISTA_LIGADA *P, LISTA_LIGADA *B, float gamma)
{
	//Remover gamma da área de R;
	//Adicionar peças removidas a P;
	remocaoAleatoria(nova,P,B,gamma);

	//Deslocar peças restantes para esquerda;
	deslocarPecas(nova, B);
	
	criarSolucao(nova,P,B);
	return nova;
}

int Simulated_Annealing(float T, float T_c, int It_max, float alpha, R *atual, LISTA_LIGADA *P, LISTA_LIGADA *B)
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

	srand((double)time(NULL));

	while(T > T_c)
	{
		while(iterT > It_max)
		{
			iterT++;
			nova = trocarSolucao(atual,P,B,0.35);
			//-------------------------------------------------------*

			//delta = f(atual) - f(nova);
			delta = atual->valorUtilidadeTotal - nova->valorUtilidadeTotal;

			if(delta < 0)
			{
				atual = nova;

				//if(f(nova) > f(melhor))
				if(nova->valorUtilidadeTotal > atual->valorUtilidadeTotal)
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
	return melhor->valorUtilidadeTotal;
}
//*/

#endif