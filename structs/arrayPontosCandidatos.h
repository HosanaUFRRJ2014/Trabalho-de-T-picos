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


ARRAY_PONTOS_CANDIDATOS *criarArrayPontosCandidatos()
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

int vazio(ARRAY_PONTOS_CANDIDATOS *l)
{
	if(l->tamanho == 0)
		return true;

	return false;
}

int inserirPontoCandidato(ARRAY_PONTOS_CANDIDATOS *array, PONTO_CANDIDATO *ponto)
{
	NO_Pt *pnovo = (NO_Pt *) malloc (sizeof(NO_Pt));

	NO_Pt *aux;

	if(pnovo != NULL)
	{

		pnovo->ponto = ponto;
		pnovo->anterior = NULL;
        pnovo->proximo = NULL;

        //se for o primeiro nó a ser inserido na array:
		if(array->inicio == NULL) 
        {
        	
        	
        	array->inicio = pnovo;
        	   //  array->fim = pnovo;

        
        }
        else
        {   
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

int removerPontoCandidato(ARRAY_PONTOS_CANDIDATOS *array)
{
	if(!vazio(array))
	{
		NO_Pt *aRemover = array->inicio;
		
	
			array->inicio = aRemover->proximo;

        	if(aRemover == array->fim)
        		array->fim = aRemover->anterior;

	        array->tamanho--;

	        free(aRemover);

	        return true;

       
       
	}

	return false;
}



void imprimirArrayPontosCandidatos(ARRAY_PONTOS_CANDIDATOS *p)
{
	NO_Pt *aux = p->inicio;

	while(aux != NULL)
	{
		imprimirPontoCandidato(aux->ponto);
		aux = aux->proximo;
	}

}



#endif