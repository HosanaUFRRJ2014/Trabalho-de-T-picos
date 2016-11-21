#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#ifndef PECA_H
#define PECA_H

typedef struct             //comprimento l e largura w, 
{						   //v o valor da peça.
	int l;				   //P e Q representam a quantidade mínima e máxima, respectivamente, de cada peça.
	int w;
	int P;
	int Q;
	int v;
	int quantidade;   //quantidade existente da peça

	
	
}PECA;

//cria um tipo de peça. Para controlar a qtd min e  max de peças.
/*PECA *criarTipoPeca(int l, int w, int P, int Q, int v, int id)
{
	PECA *i = (PECA *) malloc(sizeof(PECA));

	if(i != NULL)
	{
		i->l = l;
		i->w = w;
		i->P = P;
		i->Q = Q;
		i->v = v;
		i->id_peca = id;
		i->quantidade = 0;
	} 


	return i;

}*/

//criar peca de um determinado tipo.
PECA *criarPeca(int l, int w, int P, int Q, int v, int qtd)
{
	PECA *i = (PECA *) malloc(sizeof(PECA));

	if(i != NULL /*&& (qtd >= P && qtd <= Q)*/)
	{
		i->l = l;
		i->w = w;
		i->P = P;
		i->Q = Q;
		i->v = v;
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

void imprimirPeca(PECA *p)
{
	printf("Quantidade: %d\n", p->quantidade);
	printf("largura(w): %d\n", p->l);
	printf("comprimento(l): %d\n",p->w );
	printf("qtd min(P): %d\n",p->P );
	printf("qtd max(Q): %d\n",p->Q );
	printf("valor da peca(v): %d\n",p->v);
	printf("\n");


}

#endif
