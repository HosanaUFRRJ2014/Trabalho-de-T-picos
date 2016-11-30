#include <stdio.h>
#include <stdlib.h>
#include "arrayPontosCandidatos.h"
#include "ponto.h"
#define true 1
#define false 0

#ifndef PECA_H
#define PECA_H


//comprimento l e largura w, 
//v o valor da peça.
//P e Q representam a quantidade mínima e máxima, respectivamente, de cada peça.
typedef struct             
{						   
	int l;	//na horizontal  (Não concordo, mas é como está no artigo.)
	int w; //na vertical
	int P; 
	int Q;
	float v;
	int quantidade;   //quantidade existente da peça
	ARRAY_PONTOS_CANDIDATOS *p1; //mais a direita e mais acima
	ARRAY_PONTOS_CANDIDATOS *p2; //mais a esquerda e mais abaixo


	
	
}PECA;

//criar peca de um determinado tipo.
PECA *criarPeca(int l, int w, int P, int Q, float v, int qtd)
{
	PECA *i = (PECA *) malloc(sizeof(PECA));

	if(i != NULL /*&& (qtd >= P && qtd <= Q)*/)
	{
		i->l = l;
		i->w = w;
		i->P = P;
		i->Q = Q;
		i->v = v;
		i->p1 = criarArrayPontosCandidatos();
		i->p2 = criarArrayPontosCandidatos();
		i->quantidade = qtd;
	} 


	return i;

}

//verificar se são peças iguais. Se sim, retornar true. Caso contrário, retornar false.
int pecasIguais(PECA *x, PECA *y)
{
	if(x->l == y->l && x->w == y->w && x->P == y->P && x->Q == y->Q && x->v == y->v)
		return true;

	return false;
}

//dado uma peca a, verificar se esta é maior que a peca b, seguindo os critérios de majoritariedade do artigo 
int pecaMaior(PECA *a, PECA *b)
{
	if(( (float)a->v/(a->l * a->w) ) > ( (float)b->v/(b->l * b->w) ) )
		return true;

	return false;

}

// //função para a verificação do limite inferior P. Note que , caso se deseje remover uma peça, o valor de qtdAsomar será negativo
// int dentroDoLimiteInferior(PECA *peca, int qtdAsomar)
// {

// 	if(peca->quantidade + qtdAsomar >= peca->P)
// 		return true;

// 	printf("Limite inferior violado\n");

// 	return false;

// }

// //função para a verificação do limite superior Q.
// int dentroDoLimiteSuperior(PECA *peca, int qtdAsomar)
// {
// 	if(peca->quantidade + qtdAsomar <= peca->Q)
// 		return true;

// 	printf("Limite superior violado\n");

// 	return false;

// }

// //futuramente, colocar tudo dentro dessa função. Não deixar mais separado.
// int dentroDosLimites(PECA *peca, int qtdAsomar)
// {
// 	if(dentroDoLimiteInferior(peca, qtdAsomar) && dentroDoLimiteSuperior(peca, qtdAsomar))
// 		return true;

// 	return false;
// }

void custoBeneficio(PECA *a)
{
	float f = (float) a->v/(a->l * a->w);
	printf("Custo beneficio da peça(v/l*w): %f\n", f);
	
}

//função para copiar os falores de uma peca para a outra
//Organizar tudo em seus devidos lugares!!!
void copiarPeca(PECA *pecaDestino, PECA *pecaOrigem)
{
	pecaDestino->l = pecaOrigem->l;
	pecaDestino->w = pecaOrigem->w;
	pecaDestino->P = pecaOrigem->P;
	pecaDestino->Q = pecaOrigem->Q;
	pecaDestino->v = pecaOrigem->v;
	pecaDestino->p1 = criarArrayPontosCandidatos();
	
	//pertence a arrayPontoCandidato.h **
	NO_Pt *aux_Pt1;
	aux_Pt1 = pecaOrigem->p1->inicio;
	while(aux_Pt1 != NULL)
	{
		PONTO_CANDIDATO *novo;
		novo = criarPontoCandidato(aux_Pt1->ponto->x, aux_Pt1->ponto->y);
		inserirPontoCandidato(pecaDestino->p1,novo);

		aux_Pt1 = aux_Pt1->proximo;
	}

	pecaDestino->p2 = criarArrayPontosCandidatos();
	NO_Pt *aux_Pt2;
	aux_Pt2 = pecaOrigem->p2->inicio;
	while(aux_Pt2 != NULL)
	{
		PONTO_CANDIDATO *novo;
		novo = criarPontoCandidato(aux_Pt2->ponto->x, aux_Pt2->ponto->y);
		inserirPontoCandidato(pecaDestino->p2,novo);

		aux_Pt2 = aux_Pt2->proximo;
	}

	pecaDestino->quantidade = pecaOrigem->quantidade;

	//**

}

void imprimirPeca(PECA *p)
{
	printf("Quantidade: %d\n", p->quantidade);
	printf("largura(w): %d\n", p->l);
	printf("comprimento(l): %d\n",p->w );
	printf("qtd min(P): %d\n",p->P );
	printf("qtd max(Q): %d\n",p->Q );
	printf("valor da peca(v): %f\n",p->v);
	printf("pontos candidatos p1:\n");
	imprimirArrayPontosCandidatos(p->p1);
	printf("pontos candidatos p2:\n");
	imprimirArrayPontosCandidatos(p->p2);
	printf("\n");


}

#endif
