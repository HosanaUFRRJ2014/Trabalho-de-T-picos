#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include "includes.h"
#include "heuristicas/heuristicas.h"

#define TAM_PECAS 6

//Escolha o índice referente ao elemento.
#define ESCOLHA_PECA 0
#define ESCOLHA_PC 1

int main()
{
	int i;
	R *r = criarRetanguloR(20, 20); //20 20 
	PECA *p[TAM_PECAS]; //10
	LISTA_LIGADA *P = criarLista();
	LISTA_LIGADA *B = criarLista();

	p[0] = criarPeca(5, 5, 0, 2, 1.4 ,2);
	p[1] = criarPeca(3, 5, 0, 3, 9.0 ,3);
	p[2] = criarPeca(10, 2, 0, 1, 8 ,1);
	p[3] = criarPeca(5, 3, 0, 4, 15 ,5);
	p[4] = criarPeca(2, 3, 0, 7, 2.3 ,7);
	p[5] = criarPeca(7, 7, 0, 1, 10 ,1);

    //iniciar com a lista P ordenada.
    for (i = 0; i < TAM_PECAS; i++)
    {
        inserirPecaOrdenado(P,p[i]);        
    }

	//imprimirLista(P);

 	criarSolucao(r, P, B);

    printf("\n\n");
    //imprimirLista(B);
    //imprimirVariaveisR(r);
    //imprimirR(r->matriz, r->L, r->W);
    printf("\n\n");

    /*Inicio dos testes das funções de remoção*/

    /*-----------Em R.h--------------*/

    NO *aux = B->inicio;
    NO_Pt *aux_pt1,*aux_pt2;

    for (i = 0; i < ESCOLHA_PECA; i++)
    {
        aux = aux->proximo;
    }

    aux_pt1 = aux->peca->p1->inicio;
    aux_pt2 = aux->peca->p2->inicio;

    for(i = 0; i < ESCOLHA_PC; i++)
    {
        aux_pt1 = aux_pt1->proximo;
        aux_pt2 = aux_pt2->proximo;
    }

    remocaoAleatoria(r,P,B,0.35); //0.35

    imprimirR(r->matriz, r->L, r->W);
    printf("\n\n\n");

    deslocarPecas(r, B);
 
    //despreencherR(r,aux->peca,aux_pt1->ponto,aux_pt2->ponto);

    //printf("Antes:\n\n");
    //imprimirLista(B);

    //imprimirPontoCandidato(aux_pt1->ponto);
    //imprimirPontoCandidato(aux_pt2->ponto);

    //removerPecaDadoPeca(B,aux->peca,aux_pt1->ponto,aux_pt2->ponto);

    //imprimirLista(B);

    //imprimirVariaveisR(r);
    imprimirR(r->matriz, r->L, r->W);
    //printf("\n\n");

    /*----------------------*/


    /*-----------------------------------------*/
}