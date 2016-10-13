#include <stdio.h>
#include <stdlib.h>

#include "structs/lista.h"
#include "structs/peca.h"
#include "structs/R.h"

int leitura_instancia(FILE *arq, int *L, int *W, int *qtd_pecas, int *valor_otimo)
{
	if(fscanf(arq," %d\n %d %d\n %d\n", qtd_pecas, L, W, valor_otimo) == EOF)
		return EOF;
	else
		return 1;
}


void leitura_peca(FILE *arq, LISTA_LIGADA *lista)
{
	int l, w, P, Q, v;

	fscanf(arq," %d %d %d %d %d\n", &l, &w, &P, &Q, &v);

	PECA *nova_peca = criarPeca(l,w,P,Q,v,Q);

	inserirPecaOrdenado(lista, nova_peca);
};

//l = comprimento e w = largura

int main(int argc, char const *argv[])
{
	FILE *inst = fopen("instancias-otimo.txt","r");
	R *ret = NULL;
	LISTA_LIGADA *lista = criarLista();
	int qtd_inst, qtd_pecas, valor_otimo, i = 0, num_inst = 1, L, W;

	fscanf(inst," %d\n", &qtd_inst);

	printf("Quantidade de instancias: %d\n",qtd_inst);

	while(leitura_instancia(inst,&L, &W, &qtd_pecas, &valor_otimo) != EOF)
	{
		printf("-------------------------------Instancia %d--------------------------------------------\n\n",num_inst);

		ret = criarRetanguloR(L,W);

		printf("L = %d e W = %d\n",ret->L,ret->W);
		printf("Quantidade de peças: %d\n",qtd_pecas);
		printf("Valor ótimo: %d\n\n",valor_otimo);

		for(i = 0;i < qtd_pecas;i++)
		{
			leitura_peca(inst, lista);
		}

		imprimirLista(lista);

		imprimirR(ret->matriz,ret->L,ret->W);
		apagarRetanguloR(ret);

		while(!vazia(lista))
		{
			removerPeca(lista);
		}

		printf("------------------------------------------------------------------------------------------\n");

		num_inst++;
	}

    fclose(inst);
    free(lista);
    return 0;
}