#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "includes.h"

#ifndef HEURISTICA_H
#define HEURISTICA_H

inline void imprimirSolucao(R *solucao,LISTA_LIGADA *B);

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
		/****************************/
		//aux->peca->quantidade = 1;
		/****************************/
		while(cont < qtdInicial)
		{	
			//printf("aux->peca->Q: %d\n",aux->peca->Q);

			int foiAdicionada = adicionarPecaAoRetangulo(solucaoNova, B , aux->peca);

			if(foiAdicionada)
			{
				
				//removerPeca(P);
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

inline void trocarSolucao(R *atual, LISTA_LIGADA *P, LISTA_LIGADA *B, float gamma) //retornava R*
{

	//Remover gamma da área de R;
	//Adicionar peças removidas a P;
	remocaoAleatoria(atual,P,B,gamma); //nova

		//Deslocar peças restantes para esquerda;
	deslocarPecas(atual, B); //nova
//	printf("--------Solucao com peças deslocadas--------\n");
//	imprimirSolucao(atual,B);
	
	criarSolucao(atual,P,B); //nova
//	printf("--------Nova solucao--------\n");
//	imprimirSolucao(atual,B);

	//return nova;
}

inline float Simulated_Annealing(float T, float T_c, int It_max, float alpha, R *atual, LISTA_LIGADA *P, LISTA_LIGADA *B, double *tempo)
{
	//R *atual, *nova, *melhor;
	R *nova,*melhor,*atualAlg;

	/*-----Criando as listas P e B de cada ret do algoritmo------------------*/

	LISTA_LIGADA *P_nova = criarLista(), *B_nova = criarLista();
	LISTA_LIGADA *P_melhor = criarLista(), *B_melhor = criarLista();
	LISTA_LIGADA *P_atualAlg = criarLista(), *B_atualAlg = criarLista();

	/*-----------------------------------------------------------------------*/


	int iterT = 0, delta; //temp = T
	double x;
	//float temp = T;
	float aux_result;

	//A lista P recebida aqui já estará ordenada.

	criarSolucao(atual,P,B);
	//------------------------------------------*

	//Inicializando "nova" e "melhor"
	nova = criarRetanguloR(atual->L, atual->W);
	melhor = criarRetanguloR(atual->L, atual->W);
	atualAlg = criarRetanguloR(atual->L, atual->W);

	/*------Copiando as listas recebidas como parâmetro----------------------*/
	copiarLista(P_nova,P);
	copiarLista(B_nova,B);
	copiarLista(P_melhor,P);
	copiarLista(B_melhor,B);
	copiarLista(P_atualAlg,P);
	copiarLista(B_atualAlg,B);
	/*-----------------------------------------------------------------------*/

	copiarSolucao(atualAlg,atual);

	//melhor = atual; //LINHA ANTIGA
	copiarSolucao(melhor,atual);

	//Inicializando a matriz "nova" como atual.
	copiarSolucao(nova,atual);

//	srand((double)time(NULL));

	//contagem de tempo
	double comeco = (double) clock () / CLOCKS_PER_SEC;

	while(T > T_c)
	{
		while(iterT < It_max)
		{
			iterT++;
			//nova = trocarSolucao(atual,P,B,0.35); //LINHA ANTIGA
			copiarSolucao(nova,atualAlg);
			copiarLista(P_nova,P_atualAlg);
			copiarLista(B_nova,B_atualAlg);
			trocarSolucao(nova,P_nova,B_nova,0.35);
			// printf("solucaoNova: \n");
			// imprimirVariaveisR(nova);
			// imprimirR(nova);
			// printf("\n\nSolucao atual: \n");
			// imprimirVariaveisR(atual);
			// imprimirR(atual);
			//-------------------------------------------------------*

			//delta = f(atual) - f(nova);
			delta = atualAlg->valorUtilidadeTotal - nova->valorUtilidadeTotal;

		//	printf("delta = %d\n",delta);

			if(delta < 0)
			{
				//atual = nova; //LINHA ANTIGA
				copiarSolucao(atualAlg,nova);
				copiarLista(P_atualAlg,P_nova);
				copiarLista(B_atualAlg,B_nova);

				//printf("DELTA é negativo!\n");

				//if(f(nova) > f(melhor))
				if(nova->valorUtilidadeTotal > melhor->valorUtilidadeTotal)
				{	
		//			printf("Foi melhor!!!\n");
					//melhor = atual; //LINHA ANTIGA
					copiarSolucao(melhor,nova);
					copiarLista(P_melhor,P_nova);
					copiarLista(B_melhor,B_nova);
				}
			}
			else
			{	
				//Gerar números aleátórios entre 0 e 1.
    			x = ((double)(rand())/RAND_MAX);
    			//printf("Não foi\n");
			//	printf("valor entre O e 1: %f\n",x);

				if(x < exp(-1 * (delta/T)))
				{
			//		printf("REALIMENTOU\n");
					//atual = nova; //LINHA ANTIGA
					copiarSolucao(atualAlg,nova);
					copiarLista(P_atualAlg,P_nova);
					copiarLista(B_atualAlg,B_nova);
				}

				//else
				//{
			//		printf("NÃO REALIMENTOU\n");

				//}
			}
		}

		T = alpha * T;
		iterT = 0;
	}

	//fim contagem de tempo
    double fim = (double) clock () / CLOCKS_PER_SEC;

    *tempo = fim - comeco;


/******************************************/
//teste pra ver se o ponteiro que pus estava sendo usado adequadamente. Comparei o resultado de dentro da função com o de fora e deu tudo certo!! :D
//    printf("rsrsrs %f\n",*tempo );
/*******************************************/

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

	apagarRetanguloR(atualAlg);
	apagarLista(&P_atualAlg);
	free(P_atualAlg);
	apagarLista(&B_atualAlg);
	free(B_atualAlg);

	//return melhor->valorUtilidadeTotal;
	return aux_result;
}

inline void imprimirParametrosDeEntradaSA(float T, float T_c, int It_max, float alpha)
{
	printf("\n-------------> Parâmetros de entrada do SA <-------------\n");
    printf("Temperatura inicial (T): %f\n", T);
    printf("Temperatura de congelamento (T_c): %f\n", T_c);
    printf("Número máximo de iterações (It_max): %d\n", It_max);
    printf("Taxa de resfriamento (alpha): %f \n\n", alpha);
    printf("----------------------------------------------------\n");

}

#endif