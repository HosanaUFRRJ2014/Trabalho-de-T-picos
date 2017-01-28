#include <stdio.h>
#include <stdlib.h>

#include "structs/lista.h"
#include "structs/peca.h"
#include "structs/R.h"

#ifndef ARQUIVO_H
#define ARQUIVO_H

//Lê as informações de R, respeitando a ordem delas no arquivo de instâncias utilizado.
int leitura_instancia(FILE *arq, int *L, int *W, int *qtd_pecas, int *valor_otimo)
{
	if(fscanf(arq," %d\n %d %d\n %d\n", qtd_pecas, L, W, valor_otimo) == EOF)
		return EOF;
	else
		return 1;
}

//Lê cada peça da instância(um tipo de peça por linha)
void leitura_peca(FILE *arq, LISTA_LIGADA *lista)
{
	int l, w, P, Q, v;

	int lido = fscanf(arq," %d %d %d %d %d\n", &l, &w, &P, &Q, &v);
	
    if(lido == false)
    {
    	printf("Uma peça não foi lida.\n");
    	exit(1);
    }
	
	PECA *nova_peca = criarPeca(l,w,P,Q,v,Q);

	inserirPecaOrdenado(lista, nova_peca);
};

#endif