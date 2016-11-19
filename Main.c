#include <stdio.h>
#include <stdlib.h>

/*#include "structs/lista.h"
#include "structs/peca.h"
#include "structs/R.h"
#include "arquivo.h"
#include "heuristicas/heuristicas.h"*/

//Subistitui todos os includes acima
#include "includes.h"
int main(int argc, char const *argv[])
{
	FILE *inst = fopen("instancias-otimo.txt","r");
	R *ret = NULL;
	LISTA_LIGADA *P = criarLista(), *B = criarLista();;
	int qtd_inst, qtd_pecas, valor_otimo, i = 0, num_inst = 0, L, W;
	int *valores_otimos;

	//Leitura da quantidade de instâncias do arquivo
	fscanf(inst," %d\n", &qtd_inst);

	valores_otimos = (int*)malloc(qtd_inst * sizeof(int));

	while(leitura_instancia(inst,&L, &W, &qtd_pecas, &valor_otimo) != EOF)
	{
		//printf("-------------------------------Instancia %d--------------------------------------------\n\n",num_inst + 1);

		ret = criarRetanguloR(L,W);
		valores_otimos[num_inst] = valor_otimo;

		//printf("L = %d e W = %d\n",ret->L,ret->W);
		//printf("Quantidade de peças: %d\n",qtd_pecas);
		//printf("Valor ótimo: %d\n\n",valor_otimo);

		for(i = 0;i < qtd_pecas;i++)
		{
			leitura_peca(inst, P);
		}

		//imprimirLista(lista);

		//imprimirR(ret->matriz,ret->L,ret->W);


		/*-----------------------------Reinício das variáveis---------------------------------------------------*/
		apagarRetanguloR(ret);

		while(!vazia(P))
		{
			removerPeca(P);
		}

		while(!vazia(B))
		{
			removerPeca(B);
		}
		/*-------------------------------------------------------------------------------------------------------*/


		num_inst++;
	}

    fclose(inst);
    free(P);
    free(B);
    free(valores_otimos);
    return 0;
}
