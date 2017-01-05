#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "includes.h"
#include "heuristicas/heuristicas.h"

#define TAM_PECAS 6

//Escolha o índice referente ao elemento.
#define ESCOLHA_PECA 0
#define ESCOLHA_PC 1

int main()
{
    //FILE *inst = fopen("inst1.txt","r");
    FILE *inst = fopen("inst8.txt","r");
    //FILE *inst = fopen("inst10.txt","r");

    R *r = NULL;
    LISTA_LIGADA *P = criarLista(), *B = criarLista();
    int qtd_pecas, valor_otimo, i = 0, num_inst = 0, L, W;
    int *valores_otimos;

    srand(time(NULL));

    leitura_instancia(inst,&L, &W, &qtd_pecas, &valor_otimo);

    r = criarRetanguloR(L,W);
    
    for(i = 0;i < qtd_pecas;i++)
        leitura_peca(inst, P);
    

    //---------Imprimindo P e B da instância lida---------
    /*
    printf("---------------Lista P inst ----------------------------\n");
    imprimirLista(P);
    printf("--------------------------------------------------------\n");
    printf("---------------Lista B inst ----------------------------\n");
    imprimirLista(B);
    printf("--------------------------------------------------------\n\n");
    */
    //----------------------------------------------------

    //Para seed dos aleatórios.
    srand(time(NULL));

    criarSolucao(r,P,B);

    printf("-------------------criarSolucao()---------------------------\n");
    imprimirR(r->matriz,r->L,r->W);
    imprimirVariaveisR(r);

     //---------Imprimindo P e B(criarSolucao())---------
    /*
    printf("---------------Lista P criarSolucao----------------------------\n");
    imprimirLista(P);
    printf("---------------------------------------------------------------\n");
    printf("---------------Lista B criarSolucao----------------------------\n");
    imprimirLista(B);
    printf("-------------------------------------------------------------\n\n");
    */
    //----------------------------------------------------

    //-------------Escolhendo peças e PC específicos na lista B-----------
    /*
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
    */
    //--------------------------------------------------------------------

    //-----------Em R.h-----------------------

    remocaoAleatoria(r,P,B,0.35);

    printf("-------------------remocaoAleatoria()---------------------------\n");
    imprimirR(r->matriz,r->L,r->W);
    imprimirVariaveisR(r);

    //---------Imprimindo P e B(remocaoAleatoria())---------    
    printf("---------------Lista P remocaoAleatoria----------------------------\n");
    imprimirLista(P);
    printf("-------------------------------------------------------------------\n");
    printf("---------------Lista B remocaoAleatoria----------------------------\n");
    imprimirLista(B);
    printf("-----------------------------------------------------------------\n\n");

    deslocarPecas(r,B);

    printf("-------------------deslocarPecas()---------------------------\n");
    imprimirR(r->matriz,r->L,r->W);
    imprimirVariaveisR(r);

    //---------Imprimindo P e B(deslocarPecas())---------    
    printf("---------------Lista P deslocarPecas-------------------------------\n");
    imprimirLista(P);
    printf("-------------------------------------------------------------------\n");
    printf("---------------Lista B deslocarPecas-------------------------------\n");
    imprimirLista(B);
    printf("-----------------------------------------------------------------\n\n");
    
    //----------------------------------------------------

    //-----------------------------------------

    printf("--------------------------------------------------------------------------------------------------------------------\n\n");

    fclose(inst);
    apagarLista(P);
    apagarLista(B);
    free(P);
    free(B);
}