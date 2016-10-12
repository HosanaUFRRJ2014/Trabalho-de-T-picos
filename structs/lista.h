#include <stdio.h>
#include <stdlib.h>
#include "peca.h"

#define true 1
#define false 0

/*implementação de uma lista duplamente encadeada*/

//typedef struct lista_ligada LISTA_LIGADA;

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


LISTA_LIGADA *criarLista()
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

//peça existe, independentemente de a lista existir ou não
//por isso comentei essa parte, pois a mesma faz com que peca só exista se  a lista existir
/*PECA *newPeca(int id_peca, int valor)
{
	NO *no = (NO *) malloc(sizeof(NO));

	no->anterior = NULL;

	no->proximo = NULL;

	PECA *peca = (PECA *) malloc(sizeof(PECA));

	
	peca->id_peca = id_peca;
	peca->valor = valor;

	no->peca = peca;


	return no->peca;
}*/

int vazia(LISTA_LIGADA *l)
{
	if(l->tamanho == 0)
		return true;

	return false;
}

/*inserir peca no inicio da lista*/
/*int inserirPecaInicio(LISTA_LIGADA *lista, PECA *peca)
{

	NO *pnovo = (NO *) malloc (sizeof(NO));

	if(pnovo != NULL)
	{
		pnovo->peca = peca;
        pnovo->anterior = NULL;
        pnovo->proximo = lista->inicio;


        if(lista->inicio == NULL)
        	lista->fim = pnovo;

        else
        	lista->inicio->anterior = pnovo;


        lista->inicio = pnovo;
		lista->tamanho++;
		
		return true;
	}



    return false;	

}*/

int inserirPecaOrdenado(LISTA_LIGADA *lista, PECA *peca)
{
	NO *pnovo = (NO *) malloc (sizeof(NO));

	NO *aux;

	lista->tamanho++;

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

        	return true;
        }

        ///se não for, a lista precisará ser percorrida
        aux = lista->inicio;

        while(aux != NULL)
        {

		    //ver se as peças são iguais. Se sim, só somar sua quantidade. Não estou checando os limites!!
		    if(pecasIguais(aux->peca,peca))
		    {
		    	aux->peca->quantidade += peca->quantidade;
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

		    		return true;
		    	}

		    	//2: ser inserida numa posicao intermediária
		    	else
		    	{
		    		pnovo->proximo = aux;
		    		pnovo->anterior = aux->anterior;

		    		aux->anterior->proximo = pnovo;
		    		aux->anterior = pnovo;

		    		return true;
		    	}

		    }

		    //se não for maior , continuar percorrendo a lista
		    aux = aux->proximo;

        }

        //se chegou no fim da lista, adicionar ao final
        lista->fim->proximo = pnovo;
        pnovo->anterior = lista->fim;
        lista->fim = pnovo;
        return true;

		
	}

	//como incrementei o tamamnho da lista antes de de fato adicionar algum elemento, estou decrementando, caso não adicione
	lista->tamanho--;
	return false;

}

/*Inserir peça ordenadamente*/
//ideia: ao invés de inserir ou no inicio ou no fim, varrer a lista toda procurando
//uma lugar em que o tamamho seja menor 
//
/*int inserirPecaOrdenado(LISTA_LIGADA *lista, PECA *peca)
{

	NO *pnovo = (NO *) malloc (sizeof(NO));

	NO *aux;


	if(pnovo != NULL)
	{
		//pnovo->peca = peca;
       // pnovo->proximo = NULL;
        //pnovo->anterior = lista->fim;


        if(lista->inicio == NULL) //se for o primeiro nó a ser inserido
        {
        	pnovo->peca = peca;
        	lista->inicio = pnovo;
        	lista->fim = pnovo;
        }

        else
        {
        	//lista->fim->proximo = pnovo;
        	aux = lista->inicio;

        	while(aux != NULL)
        	{

        		if( ( peca->v/(peca->l * peca->w) ) > ( aux->v/(peca->l + peca->w) )
        		{
        			//verificar se peca anterior já existe.
        			//se sim, só colocar a quantidade
        			//se não, criar o nó e colocá-lo na frente de aux.

        			if(aux->anterior != NULL)
        			{
        				//se são pecas iguais,é só adicionar a nova quantidade. Não está verificando os limites aqui
        				if( pecasIguais(aux->anterior->peca, peca) )
        					aux->anterior->peca->quantidade += peca->quantidade;

        				else
        				{

        				}


        			}

        			else
        			{
        				pnovo->peca = peca;


        			}
        		}

        		aux = aux->proximo;
        	}

        	//se chegar no fim da lista
        	   //a) comparar com a última peca e ver se são iguais
        	        //subcasos
        	   //só adicionar no fim da lista o novo nó.



        }


       // lista->fim = pnovo;
		lista->tamanho++;
		return true;
	}


    return false;	

}*/

/*Remover sempre a primeira peça da lista*/
//verificar se a qtd da peça será zerada
	//se sim, remover o nó
	//se não, só decrementar a quantidade dela
int removerPeca(LISTA_LIGADA *lista)
{
	if(!vazia(lista))
	{
		NO *aRemover = lista->inicio;

		if(aRemover->peca->quantidade == 1)
		{
			lista->inicio = aRemover->proximo;

			if(aRemover != lista->fim)
	        	aRemover->proximo->anterior = aRemover->anterior;

	        	else
	        		lista->fim = aRemover->anterior;

	        lista->tamanho--;
	        free(aRemover);   //será substituido por apagarNo

        }

        else
        {
        	aRemover->peca->quantidade--; 
        }
      
        return true;	
       
	}

	return false;
}

/*Remover um peca dado um id_peca*/
/*int removerPeca(LISTA_LIGADA *lista, int id_peca)
{
	if(!vazia(lista))
	{
		NO *aRemover = lista->inicio;

		while(aRemover != NULL && aRemover->peca->id_peca != id_peca)
			aRemover = aRemover->proximo;

        
        if(aRemover != NULL)
        {
        	if(aRemover != lista->inicio)
        	    aRemover->anterior->proximo = aRemover->proximo;

        	else
        	    lista->inicio = aRemover->proximo;




        	if(aRemover != lista->fim)
        		aRemover->proximo->anterior = aRemover->anterior;

        	else
        		lista->fim = aRemover->anterior;



        	lista->tamanho--;
            free(aRemover);   //será substituido por apagarNo
            return true;


        }

        return false;



        
	}

	return false;
}*/

void imprimirLista(LISTA_LIGADA *l)
{
	NO *aux = (NO *) malloc (sizeof(NO));

	aux = l->inicio;

	while(aux != NULL)
	{
		imprimirPeca(aux->peca);
		aux = aux->proximo;
	}



}

#endif