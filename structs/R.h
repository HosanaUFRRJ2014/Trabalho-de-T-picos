#include <stdio.h>
#include <stdlib.h>
#include "peca.h"
//#define true 1
//#define false 0

#ifndef R_H
#define R_H

typedef struct             //comprimento L e largura W.
{
	int W;
	int L;
	int **matriz;

	//O elemento i,j da matriz corresponde se o ponto candidato i,j está presente em R. Se 1, está presente, 0 caso contrário.	
	int **pontosCandidatos;

	//Contador de índice da peca em R. A variável será incrementada toda vez que for inserida uma peça em R.
	unsigned int indicePeca;
	
}R; //qtd de linhas: l e qtd de colunas: w;

void preencherComZeros(int **matriz, int l, int w)
{
	int i, j;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < w; j++)
		{
			matriz[i][j] = 0;
		}
	}
}

void imprimirR(int **matriz, int l, int w)
{
	int i, j;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < w; j++)
		{
			printf("%d    ",matriz[i][j]);
		}

		printf("\n");
	}
}


R * criarRetanguloR(int l, int w)
{
	R *r = (R *) malloc(sizeof(R));

	int i = 0; //Variável inutilizada "j" ---> linha 51.

	if(r != NULL)
	{
		r->W = w;
		r->L = l;

		r->matriz = (int **) malloc(l * sizeof(int *));
		r->pontosCandidatos = (int **) malloc(l * sizeof(int *));
   		
   		for (i = 0; i < l; i++)
   		{        
            r->matriz[i] = (int *) malloc(w * sizeof(int));
            r->pontosCandidatos[i] = (int *) malloc(w * sizeof(int));
 		}
   		
		//preencher retângulo R com zeros
		preencherComZeros(r->matriz,r->L,r->W);
		preencherComZeros(r->pontosCandidatos,r->L,r->W);
		r->pontosCandidatos[0][0] = 1;

		r->indicePeca = 0;

		//imprimirR(r->matriz,r->L,r->W); //COmentar esta parte da impressão

	}

	return r;
}


/*-------------------Criar funções de preencher retangulo-----------------------------------*/

int preencherPecaRetangulo(PECA *peca,R *r,int x, int y)
{
	int i,j;

	if((x + peca->l > R->L) || (y + peca->w > R->W))
		return 0;

	for(i = x;i < x + peca->l;i++)
	{
		for(j = y;j < y + peca->w;j++)
		{
			r->matriz[i][j] = r->indicePeca;
		}
	}

	r->indicePeca++;

	//Adicionando os novos pontos candidatos no retângulo R.
	r->pontosCandidatos[x][(y + peca->w) - 1] = 1; //Mais acima e direita
	r->pontosCandidatos[(x + peca->l) - 1][y] = 1; //Mais abaixo e esquerda

	return 1;
};

void excluirPecaRetangulo(PECA *peca,R *r,int x, int y)
{
	int i,j;

	for(i = x;i < x + peca->l;i++)
	{
		for(j = y;j < y + peca->w;j++)
		{
			r->matriz[i][j] = 0;
		}
	}

	//Removendo os pontos candidatos no retângulo R.
	r->pontosCandidatos[x][(y + peca->w) - 1] = 0; //Mais acima e direita
	r->pontosCandidatos[(x + peca->l) - 1][y] = 0; //Mais abaixo e esquerda
};
/*---------------------------------------------------------------------------------*/

//se não funcionar, dar varrer a matriz dando free
void apagarRetanguloR(R *r)
{
	free(r->matriz);
	/*free(r->W);
	free(r->L);*/

	free(r);

}


#endif
