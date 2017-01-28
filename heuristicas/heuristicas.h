#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "includes.h"

#ifndef HEURISTICA_H
#define HEURISTICA_H

inline void imprimirSolucao(R *solucao,LISTA_LIGADA *B);

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
				removerPecaDadoPeca(P,aux->peca,NULL,NULL);
		
				PECA *aInserir = (PECA *) malloc (sizeof(PECA));

				copiarPeca(aInserir,aux->peca);

				aInserir->quantidade = 1;

			 	inserirPeca(B, aInserir);
			 	
			}

			cont++;
		}

		aux = aux->proximo;
	}

	free(aux);
	aux = NULL;
	apagarLista(&listaAuxliar);
	free(listaAuxliar);
	listaAuxliar = NULL;
    
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

inline void trocarSolucao(R *atual, LISTA_LIGADA *P, LISTA_LIGADA *B, float gamma)
{
	//Remover gamma da área de R;
	//Adicionar peças removidas a P;
	remocaoAleatoria(atual,P,B,gamma);
	//Deslocar peças restantes para esquerda;
	deslocarPecas(atual, B); 	
	criarSolucao(atual,P,B);
}

inline float Simulated_Annealing(float T, float T_c, int It_max, float alpha, R *atual, LISTA_LIGADA *P, LISTA_LIGADA *B, double *tempo)
{
	R *nova,*melhor;

	/*-----Criando as listas P e B de cada ret do algoritmo------------------*/
	LISTA_LIGADA *P_nova = criarLista(), *B_nova = criarLista();
	LISTA_LIGADA *P_melhor = criarLista(), *B_melhor = criarLista();
	/*-----------------------------------------------------------------------*/

	int iterT = 0, delta;
	double x;
	float aux_result;

	//A lista P recebida aqui já estará ordenada.
	criarSolucao(atual,P,B);
	
	//Inicializando "nova" e "melhor"
	nova = criarRetanguloR(atual->L, atual->W);
	melhor = criarRetanguloR(atual->L, atual->W);

	/*------Copiando as listas recebidas como parâmetro----------------------*/
	copiarLista(P_nova,P);
	copiarLista(B_nova,B);
	copiarLista(P_melhor,P);
	copiarLista(B_melhor,B);
	/*-----------------------------------------------------------------------*/

	copiarSolucao(melhor,atual);

	//Inicializando a matriz "nova" como atual.
	copiarSolucao(nova,atual);

	//Contagem de tempo
	double comeco = (double) clock () / CLOCKS_PER_SEC;

	while(T > T_c)
	{
		while(iterT < It_max)
		{
			iterT++;
			copiarSolucao(nova,atual); 
			copiarLista(P_nova,P);
			copiarLista(B_nova,B);
			trocarSolucao(nova,P_nova,B_nova,0.35);

			delta = atual->valorUtilidadeTotal - nova->valorUtilidadeTotal;

			if(delta < 0)
			{
				copiarSolucao(atual,nova);
				copiarLista(P,P_nova);
				copiarLista(B,B_nova);

				if(nova->valorUtilidadeTotal > melhor->valorUtilidadeTotal)
				{	
					copiarSolucao(melhor,nova);
					copiarLista(P_melhor,P_nova);
					copiarLista(B_melhor,B_nova);
				}
			}
			else
			{	
				//Gerar números aleátórios entre 0 e 1.
    			x = ((double)(rand())/RAND_MAX);

				if(x < exp(-1 * (delta/T)))
				{
					copiarSolucao(atual,nova); 
					copiarLista(P,P_nova); 
					copiarLista(B,B_nova);
				}
			}
		}

		T = alpha * T;
		iterT = 0;
	}

	//Fim contagem de tempo
    double fim = (double) clock () / CLOCKS_PER_SEC;

    *tempo = fim - comeco;

    //Cópia da melhor solução para a varável recebida como parâmetro.
	copiarLista(P,P_melhor);
	copiarLista(B,B_melhor);
	copiarSolucao(atual,melhor);
	aux_result = melhor->valorUtilidadeTotal;

	//Liberando memória
	apagarRetanguloR(nova);
	apagarLista(&P_nova);
	free(P_nova);
	apagarLista(&B_nova);
	free(B_nova);

	apagarRetanguloR(melhor);
	apagarLista(&P_melhor);
	free(P_melhor);
	apagarLista(&B_melhor);
	free(B_melhor);

	return aux_result;
}

inline void imprimirParametrosDeEntradaSA(float T, float T_c, int It_max, float alpha)
{
	printf("\n-------------> Parâmetros de entrada do SA <-------------\n");
    printf("Temperatura inicial (T): %f\n", T);
    printf("Temperatura de congelamento (T_c): %f\n", T_c);
    printf("Número máximo de iterações (It_max): %d\n", It_max);
    printf("Taxa de resfriamento (alpha): %f \n\n", alpha);
    printf("----------------------------------------------------\n\n");

}

#endif