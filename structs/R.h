#include <stdio.h>
#include <stdlib.h>

//#define true 1
//#define false 0

#ifndef R_H
#define R_H

typedef struct             //comprimento L e largura W.
{
	int W;
	int L;
	int **matriz;
	
}R;

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
   		
   		for (i = 0; i < l; i++)
   		{        
            r->matriz[i] = (int *) malloc(w * sizeof(int));
 		}

		//preencher retângulo R com zeros
		preencherComZeros(r->matriz,r->L,r->W);

		//imprimirR(r->matriz,r->L,r->W); //COmentar esta parte da impressão

	}

	return r;
}


//criar funções de preencher retangulo



//se não funcionar, dar varrer a matriz dando free
void apagarRetanguloR(R *r)
{
	free(r->matriz);
	/*free(r->W);
	free(r->L);*/

	free(r);

}


#endif