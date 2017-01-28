#include <stdio.h>
#include <stdlib.h>
#include "peca.h"
#include "arrayPontosCandidatos.h"

#define true 1
#define false 0

/*implementação de uma lista duplamente encadeada*/

#ifndef LISTA_H
#define LISTA_H

typedef struct NO_ NO;
struct NO_{
	PECA *peca;
	NO  *proximo;
	NO  *anterior;
};

typedef struct{
	NO  *inicio;
	NO  *fim;
    int tamanho;
}LISTA_LIGADA;

void imprimirLista(LISTA_LIGADA *l);

inline LISTA_LIGADA *criarLista()
{
	LISTA_LIGADA *lista = (LISTA_LIGADA *) malloc(sizeof(LISTA_LIGADA));

	if (lista != NULL)
	{
		lista->inicio = NULL;
		lista->fim = NULL;
		lista->tamanho = 0;
	}


	return lista;
}


inline int vazia(LISTA_LIGADA *l)
{
	if(l->tamanho == 0)
		return true;

	return false;
}

inline int inserirPeca(LISTA_LIGADA *lista, PECA *aInserir)
{
	NO *pnovo = (NO *) malloc (sizeof(NO));

	NO *aux;

	PECA *peca = (PECA *) malloc(sizeof(PECA));

	copiarPeca(peca, aInserir);

	if(pnovo != NULL)
	{

		pnovo->peca = peca;
		pnovo->anterior = NULL;
        pnovo->proximo = NULL;

        //se for o primeiro nó a ser inserido na lista:
		if(lista->inicio == NULL) 
        {
        	lista->inicio = pnovo;
        	lista->fim = pnovo;
        }
        //se não for, a lista precisará ser percorrida
        else
        {
        	aux = lista->inicio;
	        while(aux != NULL)
	        {
			    //ver se as peças são iguais.
			    if(pecasIguais(aux->peca,peca))
			    {
		    		aux->peca->quantidade += peca->quantidade;

		    		if(peca->p1->fim != NULL && peca->p2->fim != NULL)
		    		{
		    			inserirPontoCandidato(aux->peca->p1, peca->p1->fim->ponto);
	    	        	inserirPontoCandidato(aux->peca->p2, peca->p2->fim->ponto);
		    		}

		    		return true;

			    }

			    //se não, continuar percorrendo a lista   
		    	aux = aux->proximo;

	        }

	        //se chegou ao fim de lista, significa que não tinha nenhuma peça igual. Nesse caso, inserir a nova peça no fim da lista.
	         lista->fim->proximo = pnovo;
	         pnovo->anterior = lista->fim;
	         lista->fim = pnovo;
	         
    	}

   		lista->tamanho++;
    	return true;
		
	}

	return false;
}

inline int inserirPecaOrdenado(LISTA_LIGADA *lista, PECA *aInserir)
{
	NO *pnovo = (NO *) malloc (sizeof(NO));

	NO *aux;

	PECA *peca = (PECA *) malloc(sizeof(PECA));
	copiarPeca(peca, aInserir);

	if(pnovo != NULL)
	{
		pnovo->peca = peca;
		pnovo->anterior = NULL;
        pnovo->proximo = NULL;

        //se for o primeiro nó a ser inserido na lista:
		if(lista->inicio == NULL) 
        {
        	
        	lista->inicio = pnovo;
        	lista->fim = pnovo;
        	lista->tamanho++;
        	return true;
        }

        ///se não for, a lista precisará ser percorrida
        aux = lista->inicio;

        while(aux != NULL)
        {

		    //ver se as peças são iguais. Se sim, só somar sua quantidade.
		    if(pecasIguais(aux->peca,peca))
		    {
		    	aux->peca->quantidade += peca->quantidade;

		    	if(peca->p1->fim != NULL && peca->p2->fim != NULL)
		    	{
		    		inserirPontoCandidato(aux->peca->p1, peca->p1->fim->ponto);
		    		inserirPontoCandidato(aux->peca->p2, peca->p2->fim->ponto);
		    	}


		    	return true;

		    }

		    //se são diferentes, verificar se a peca é maior que a contida em aux
		    //se sim, há 2 possibilidades:
		    if(pecaMaior(peca,aux->peca))
		    {
		    	//1: ser inserida no começo da lista
		    	if(aux->anterior == NULL)
		    	{
		    		pnovo->proximo = aux;
		    		aux->anterior = pnovo;
		    		lista->inicio = pnovo;

		    	
		    	}

		    	//2: ser inserida numa posicao intermediária
		    	else
		    	{
		    		pnovo->proximo = aux;
		    		pnovo->anterior = aux->anterior;

		    		aux->anterior->proximo = pnovo;
		    		aux->anterior = pnovo;
		    		
		    	}

		    	lista->tamanho++;
		    	return true;

		    }

		    //se não for maior , continuar percorrendo a lista
		    aux = aux->proximo;

        }

        //se chegou no fim da lista, adicionar ao final
        lista->fim->proximo = pnovo;
        pnovo->anterior = lista->fim;
        lista->fim = pnovo;
        lista->tamanho++;
        return true;
	}

	return false;

}

inline PECA *removerPeca(LISTA_LIGADA *lista)
{
	if(!vazia(lista))
	{
		NO *aRemover = lista->inicio;

		PECA *retorno =  (PECA *) malloc (sizeof(PECA));

		if(aRemover->peca->quantidade == 1)
		{
			lista->inicio = aRemover->proximo;

	        lista->tamanho--;
			*retorno = *aRemover->peca;

	        free(aRemover);

            //não tirar esse return daqui!! :)
			return retorno;
        }

        if(aRemover->peca->quantidade > 1)
        {

			retorno->quantidade = 1;
			
			*retorno = *aRemover->peca;

			removerPontoCandidato(aRemover->peca->p1);
			removerPontoCandidato(aRemover->peca->p2);

			aRemover->peca->quantidade--;
        }
      
        return retorno;
	}

	return NULL;
}

inline void removePeca(LISTA_LIGADA *lista,NO *aRemover,PONTO_CANDIDATO *ponto_aRemoverP1,PONTO_CANDIDATO *ponto_aRemoverP2)
{
	if(!vazia(lista))
	{		
		if(aRemover->peca->quantidade > 1)
		{
			removerPontoCandidatoDadoPontoCandidato(aRemover->peca->p1,aRemover->peca->p2,ponto_aRemoverP1,ponto_aRemoverP2);
			aRemover->peca->quantidade--;
			return;
		}
		
		if(aRemover->peca->quantidade == 1)
		{
			if(aRemover == lista->inicio)
				lista->inicio = aRemover->proximo;
			else
				aRemover->anterior->proximo = aRemover->proximo;
			
			
			if(aRemover == lista->fim)
				lista->fim = aRemover->anterior;
			else
				aRemover->proximo->anterior = aRemover->anterior;

			lista->tamanho--;
			free(aRemover);
			return;
		}
	}

	printf("Lista vazia...\n");
	return;
}

inline int removerPecaDadoPeca(LISTA_LIGADA *B, PECA *aRemover, PONTO_CANDIDATO *p1,PONTO_CANDIDATO *p2)
{
	NO *aux = B->inicio;

	if(!vazia(B))
	{
		while(aux != NULL)
		{
			if(pecasIguais(aux->peca,aRemover))
			{
				removePeca(B,aux,p1,p2);
				return true;
			}

			aux = aux->proximo;
		}

	}

	//Se não tem essa peça na lista, retornamos NULL.
	return false;
}
 
inline void apagarLista(LISTA_LIGADA **lista)
{
	while(!vazia(*lista))
		removerPeca(*lista);
}

void apagarNo(NO *no) 
{
	apagarPeca(&no->peca);
	free(no);
}

inline void copiarLista(LISTA_LIGADA *destino,LISTA_LIGADA *origem)
{
	NO *aux = origem->inicio;

	if(!vazia(destino))
		apagarLista(&destino);

	if(!vazia(origem))
	{
		while(aux != NULL)
		{
			inserirPeca(destino, aux->peca);
			aux = aux->proximo;
		}
	}
}

inline LISTA_LIGADA * ordenarLista(LISTA_LIGADA *lista)
{
	LISTA_LIGADA *listaOrdenada = criarLista();

	NO *aux = lista->inicio;

	while(aux != NULL)
	{
		inserirPecaOrdenado(listaOrdenada, aux->peca);
		aux = aux->proximo;
	}

    free(aux);
    free(lista);
    aux = NULL;
    lista = NULL;
	return listaOrdenada;

}

inline void imprimirLista(LISTA_LIGADA *l)
{
	NO *aux = (NO *) malloc (sizeof(NO));

	aux = l->inicio;
	printf("Tamanho da lista: %d\n",l->tamanho);
	while(aux != NULL)
	{
		custoBeneficio(aux->peca);
		imprimirPeca(aux->peca);
		aux = aux->proximo;
	}

	free(aux);
	aux = NULL;
}

#endif