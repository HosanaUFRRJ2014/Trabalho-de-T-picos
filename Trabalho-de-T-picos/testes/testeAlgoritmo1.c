#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include "includes.h"
#include "heuristicas/heuristicas.h"

int main()
{
	int i ;
	R *r = criarRetanguloR(20, 20); //20 20 
	PECA *p[20]; //10
	LISTA_LIGADA *P = criarLista();
	LISTA_LIGADA *B = criarLista();

	p[1] = criarPeca(5, 5, 0, 2, 1.4 ,2);
	p[2] = criarPeca(3, 5, 0, 3, 9.0 ,3);
	p[3] = criarPeca(10, 2, 0, 1, 8 ,1);
	p[4] = criarPeca(5, 3, 0, 4, 15 ,5);

	p[6] = criarPeca(2, 3, 0, 7, 2.3 ,7);
	//p[6] = criarPeca(2, 3, 0, 2, 2.3 ,7);

	p[8] = criarPeca(7, 7, 0, 1, 10 ,1);

	/*-------------------Teste Lívia-------------------------*/
	//p[6] = criarPeca(3, 3, 0, 1, 10 ,1);
	//p[4] = criarPeca(7, 3, 0, 1, 3 ,1);

	//(int l, int w, int P, int Q, float v, int qtd) l->horizontal e w->vertical

	p[9] = criarPeca(7, 2, 0, 1, 10 ,1);
	p[10] = criarPeca(2, 4, 0, 1, 9 ,1);
	p[11] = criarPeca(2, 2, 0, 2, 5 ,2);
	//p[12] = criarPeca(7, 7, 0, 1, 10 ,1);

    //inserirPeca(P,p[6]);
    //inserirPeca(P,p[4]);
    //inserirPeca(P,p[1]);
    /*------------Teste Lívia---------------------*/
    inserirPeca(P,p[9]);
    inserirPeca(P,p[10]);
    inserirPeca(P,p[11]);

  //  Corrigir o erro de não poder adicionar a mesma peca duas vezes.
	//inserirPeca(P,p[6]);
	/*----------------------Teste Lívia---------------*/
	//inserirPeca(P,p[11]);

    
	//P = ordenarLista(P);
	//imprimirLista(P);

 	criarSolucao(r, P, B);

    printf("\n\n\n\n");
    imprimirLista(B);
    imprimirR(r->matriz, r->L, r->W);

    NO *pnovo = (NO *) malloc (sizeof(NO));

    PECA *teste = criarPeca(5, 5, 0, 2, 1.4 ,2);
    //PECA *teste2;
    //PECA *teste2 = criarPeca(5, 7, 0, 2, 1.4 ,2);

    pnovo->peca = teste;
    //teste2 = teste;

    free(pnovo);
    free(teste);

    //teste = criarPeca(7, 7, 0, 1, 10 ,1);

    imprimirPeca(teste);
    printf("\n");

    /*
    printf("\n\n\n");

    srand((unsigned int)time(NULL));
    int x;

    for(i = 0;i < 10;i++)
    {
    	x = rand() % 1000;
		printf("%d\t",x);
    }

    printf("\n");
	*/

}