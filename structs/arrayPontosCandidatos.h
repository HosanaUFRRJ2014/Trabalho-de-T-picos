#include <stdio.h>
#include <stdlib.h>
#include "ponto.h"

#define true 1
#define false 0

#ifndef ARRAY_PONTOS_CANDIDATOS_H
#define ARRAY_PONTOS_CANDIDATOS_H


typedef struct NOPt NO_Pt;
struct NOPt{
	PONTO_CANDIDATO *ponto;
	NO_Pt  *proximo;
	NO_Pt  *anterior;
};

typedef struct{
	NO_Pt  *inicio;
	NO_Pt  *fim;
    int tamanho;
}ARRAY_PONTOS_CANDIDATOS;


inline ARRAY_PONTOS_CANDIDATOS *criarArrayPontosCandidatos()
{
	ARRAY_PONTOS_CANDIDATOS *array = (ARRAY_PONTOS_CANDIDATOS *) malloc(sizeof(ARRAY_PONTOS_CANDIDATOS));

	if (array != NULL)
	{
		array->inicio = NULL;
		array->fim = NULL;
		array->tamanho = 0;
	}


	return array;
}

inline int vazio(ARRAY_PONTOS_CANDIDATOS *l)
{
	if(l->tamanho == 0)
		return true;

	return false;
}

inline int inserirPontoCandidato(ARRAY_PONTOS_CANDIDATOS *array, PONTO_CANDIDATO *ponto)
{
	//printf("ponto 5.0.1\n");
	NO_Pt *pnovo = (NO_Pt *) malloc (sizeof(NO_Pt));


	if(array == NULL)
	{
		printf("O array é nulo!!\n");
	}

	if(pnovo != NULL)
	{
		//printf("label 5.1\n");
		pnovo->ponto = ponto;
		pnovo->anterior = NULL;
        pnovo->proximo = NULL;

        //se for o primeiro nó a ser inserido na array:
		if(array->inicio == NULL) 
        {
        	
        	//printf("label 5.2\n");
        	array->inicio = pnovo;
        	   //  array->fim = pnovo;

        
        }
        else
        { //  printf("label 5.3\n");
	         array->fim->proximo = pnovo;
	         pnovo->anterior = array->fim;
	       //  array->fim = pnovo;
	         
    	}

    	array->fim = pnovo;

   		array->tamanho++;
    	return true;
		
	}

	return false;
}

inline int removerPontoCandidato(ARRAY_PONTOS_CANDIDATOS *array)
{
	if(!vazio(array))
	{
		NO_Pt *aRemover = array->inicio;
		
		array->inicio = aRemover->proximo;

        if(aRemover == array->fim)
        	array->fim = aRemover->anterior;

	    array->tamanho--;

	    free(aRemover->ponto);
	    free(aRemover);

	    return true;       
	}

	return false;
}
/*Função feita por Lívia*/
inline void removePontoCandidato(ARRAY_PONTOS_CANDIDATOS *arrayP1,ARRAY_PONTOS_CANDIDATOS *arrayP2,NO_Pt *aRemoverP1, NO_Pt *aRemoverP2)
{
	//Remover o ponto candidato no array de pontos candidatos.
	if(aRemoverP1 == arrayP1->inicio && aRemoverP2 == arrayP2->inicio)
	{
		removerPontoCandidato(arrayP1);
		removerPontoCandidato(arrayP2);
		return;
	}
	else if(aRemoverP1 != arrayP1->inicio && aRemoverP2 != arrayP2->inicio)
	{
		aRemoverP1->anterior->proximo = aRemoverP1->proximo;
		aRemoverP2->anterior->proximo = aRemoverP2->proximo;
	}

	if(aRemoverP1 == arrayP1->fim && aRemoverP2 == arrayP2->fim)
	{
		arrayP1->fim = aRemoverP1->anterior;
		arrayP2->fim = aRemoverP2->anterior;
	}
	else if(aRemoverP1 != arrayP1->fim && aRemoverP2 != arrayP2->fim)
	{
		aRemoverP1->proximo->anterior = aRemoverP1->anterior;
		aRemoverP2->proximo->anterior = aRemoverP2->anterior;
	}

	/*	
	if(aRemoverP1 == arrayP1->fim && aRemoverP2 == arrayP2->fim)
	{
		arrayP1->fim = aRemoverP1->anterior;
		arrayP2->fim = aRemoverP2->anterior;
	}
	else if(aRemoverP1 != arrayP1->fim && aRemoverP2 != arrayP2->fim)
	{
		//Fazer as alterações normais
		aRemoverP1->anterior->proximo = aRemoverP1->proximo;
		aRemoverP2->anterior->proximo = aRemoverP2->proximo;

		aRemoverP1->proximo->anterior = aRemoverP1->anterior;
		aRemoverP2->proximo->anterior = aRemoverP2->anterior;
	}
	*/

	arrayP1->tamanho--;
	arrayP2->tamanho--;

	free(aRemoverP1->ponto);
	free(aRemoverP1);
	free(aRemoverP2->ponto);
	free(aRemoverP2);
	return;
}
/*Função feita por Lívia*/
inline int removerPontoCandidatoDadoPontoCandidato(ARRAY_PONTOS_CANDIDATOS *arrayP1,ARRAY_PONTOS_CANDIDATOS *arrayP2,PONTO_CANDIDATO *pontoP1,PONTO_CANDIDATO *pontoP2)
{
	if(!vazio(arrayP1) && !vazio(arrayP2))
	{
		NO_Pt *auxP1 = arrayP1->inicio;
		NO_Pt *auxP2 = arrayP2->inicio;

		while(auxP1 != NULL && auxP2 != NULL)
		{
			if( (auxP1->ponto->x == pontoP1->x && auxP1->ponto->y == pontoP1->y) && (auxP2->ponto->x == pontoP2->x && auxP2->ponto->y == pontoP2->y))
			{
				removePontoCandidato(arrayP1,arrayP2,auxP1,auxP2);
				return true;
			}

			auxP1 = auxP1->proximo;
			auxP2 = auxP2->proximo;
		}
	}

	//Não existe este ponto candidato para removê-lo
	return false;
}


inline void imprimirArrayPontosCandidatos(ARRAY_PONTOS_CANDIDATOS *p)
{
	NO_Pt *aux = p->inicio;

	while(aux != NULL)
	{
		imprimirPontoCandidato(aux->ponto);
		aux = aux->proximo;
	}
}



#endif