#include <stdio.h>
#include "includes.h"
#include "heuristicas/heuristicas.h"

int main()
{
	int i ;
	R *r = criarRetanguloR(20, 20);
	PECA *p[10];
	LISTA_LIGADA *P = criarLista();
	LISTA_LIGADA *B = criarLista();

	p[1] = criarPeca(5, 5, 0, 2, 1.4 ,2);
	p[2] = criarPeca(3, 5, 0, 3, 9.0 ,3);
	p[3] = criarPeca(10, 2, 0, 1, 8 ,1);
	p[4] = criarPeca(5, 3, 0, 4, 15 ,5);

	p[6] = criarPeca(2, 3, 0, 7, 2.3 ,7);

	p[8] = criarPeca(7, 7, 0, 1, 10 ,1);


    inserirPeca(P,p[6]);
    inserirPeca(P,p[4]);
	inserirPeca(P,p[8]);


	 P = ordenarLista(P);


 	criarSolucao(r, P, B);

    printf("\n\n\n\n");
    imprimirR(r->matriz, r->L, r->W);

}