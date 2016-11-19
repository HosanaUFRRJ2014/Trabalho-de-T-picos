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

void imprimirLista(LISTA_LIGADA *l);

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


int vazia(LISTA_LIGADA *l)
{
	if(l->tamanho == 0)
		return true;

	return false;
}

int inserirPeca(LISTA_LIGADA *lista, PECA *peca)
{
	NO *pnovo = (NO *) malloc (sizeof(NO));

	NO *aux;

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

        ///se não for, a lista precisará ser percorrida
        else
        {
        	aux = lista->inicio;

	        while(aux != NULL)
	        {

			    //ver se as peças são iguais. Se sim, só somar sua quantidade. Não estou checando os limites!!
			    if(pecasIguais(aux->peca,peca))
			    {
			    	aux->peca->quantidade += peca->quantidade;
			    	//break;
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

	printf("NAO INSERIU\n");

	return false;
}

int inserirPecaOrdenado(LISTA_LIGADA *lista, PECA *peca)
{
	NO *pnovo = (NO *) malloc (sizeof(NO));

	NO *aux;

//	lista->tamanho++;

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

	//como incrementei o tamamnho da lista antes de de fato adicionar algum elemento, estou decrementando, caso não adicione
//	lista->tamanho--;
	return false;

}

PECA  *removerPeca(LISTA_LIGADA *lista)
{
	if(!vazia(lista))
	{
		NO *aRemover = lista->inicio;

		PECA *retorno =  (PECA *) malloc (sizeof(PECA));
		*retorno =  *aRemover->peca; //copia do ponteiro aRemover->peca para o retorno;


		
		if(aRemover->peca->quantidade == 1)
		{
			lista->inicio = aRemover->proximo;

			if(aRemover != lista->fim)
	        	aRemover->proximo->anterior = aRemover->anterior;

	        	else
	        		lista->fim = aRemover->anterior;

	        lista->tamanho--;

	 //       printf("Só uma peça, removendo o nó...");

	        free(aRemover);

        }

        else
        {
			retorno->quantidade  = 1;

		//	printf("quantidade pecas pont retorno %d\n", retorno->quantidade);

			aRemover->peca->quantidade --;

		//	printf("quantidade pecas pont aRemover %d\n", aRemover->peca->quantidade);
        }
      
        return retorno;	
       
	}

	return NULL;
}

//Jeito muito muito feio de fazer isso, mas hoje é sexta feira(sexta é dia de maldade) e não estou com saco de consertar o algoritmo de ordenação.
LISTA_LIGADA * ordenarLista(LISTA_LIGADA *lista)
{
	LISTA_LIGADA *listaOrdenada = criarLista();

	NO *aux = lista->inicio;

	while(aux != NULL)
	{
		inserirPecaOrdenado(listaOrdenada, aux->peca);
		aux = aux->proximo;
	}

	return listaOrdenada;

	//listaOrdenada = NULL;

	// while(atual1->proximo != NULL)
	// {
	// 	atual2 = lista->inicio;
	// 	while(i < lista->tamanho || atual2->proximo != NULL)
	// 	{
	// 		//printf("Contador : %d\n", contador);
	// 		//se a pŕoxima peça for maior que a atual, realizar o swap
	// 		if(pecaMaior(atual2->proximo->peca, atual2->peca))
	// 		{
	// 			//printf("Entrou no swap\n");
	// 			aux = atual1;
	// 			atual1 = atual2->proximo;
	// 			atual2->proximo = aux;
	// 		//	printf("Saiu do swap\n");
	// 		}


	// 		atual2 = atual2->proximo;
	// 		i++;
	// 	}
	// 	//printf("Saiu do inner while\n");


	// 	atual1 = atual1->proximo;
	// 	contador++;
	// }
}

void imprimirLista(LISTA_LIGADA *l)
{
	NO *aux = (NO *) malloc (sizeof(NO));

	aux = l->inicio;

	while(aux != NULL)
	{
		custoBeneficio(aux->peca);
		imprimirPeca(aux->peca);
		aux = aux->proximo;
	}



}

#endif

/*FAVOR NÃO APAGAR, A NÃO SER QUE JÁ SEJA PARA ENTREGAR O CÓDIGO A ÁDRIA. NUNCA SE SABE SE ESSES CÓDIGOS SERÃO IMPORTANTES.*/

/*int inserirPecaOrdenado(LISTA_LIGADA *lista, PECA *peca)
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

}*/

/*Remover sempre a primeira peça da lista*/
//verificar se a qtd da peça será zerada
	//se sim, remover o nó
	//se não, só decrementar a quantidade dela
/*PECA  *removerPeca(LISTA_LIGADA *lista)
{
	if(!vazia(lista))
	{
		NO *aRemover = lista->inicio;

		PECA *retorno;
		
		if(aRemover->peca->quantidade == 1)
		{
			lista->inicio = aRemover->proximo;

			if(aRemover != lista->fim)
	        	aRemover->proximo->anterior = aRemover->anterior;

	        	else
	        		lista->fim = aRemover->anterior;

	        lista->tamanho--;

	        *retorno =  *aRemover->peca; //copia do ponteiro aRemover->peca para o retorno;

	        retorno->quantidade = 1;


	       

	        free(aRemover);

	        

        }

        else
        {
			retorno->peca->quantidade  = 1;

			printf("quantidade pecas pont retorno %d\n", retorno->peca->quantidade);

			aRemover->peca->quantidade --;

			printf("quantidade pecas pont aRemover %d\n", aRemover->peca->quantidade);


			
        	
        }
      
        return retorno->peca;	
       
	}

	return NULL;
}*/