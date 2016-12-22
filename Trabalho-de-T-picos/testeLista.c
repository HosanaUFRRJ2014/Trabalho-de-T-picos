#include <stdio.h>
#include <stdlib.h>

#include "structs/R.h"
#include "structs/lista.h"
#include "structs/peca.h"
#include "arquivo.h"

int main()
{
	LISTA_LIGADA *P = criarLista();

	
	int qtd_inst, qtd_pecas, valor_otimo, i = 0, num_inst = 0, L, W;
	int *valores_otimos;
	FILE *f = fopen("instancias-otimo.txt","r");

	//Leitura da quantidade de instâncias do arquivo
	fscanf(f," %d\n", &qtd_inst);

	

	while(leitura_instancia(f,&L, &W, &qtd_pecas, &valor_otimo) != EOF)
	{
		
		printf("-------------------------------Instancia %d--------------------------------------------\n\n",num_inst + 1);

	//	ret = criarRetanguloR(L,W);
		// = valor_otimo;

		//printf("L = %d e W = %d\n",ret->L,ret->W);
		//printf("Quantidade de peças: %d\n",qtd_pecas);
		//printf("Valor ótimo: %d\n\n",valor_otimo);

		for(i = 0;i < qtd_pecas;i++)
		{
			leitura_peca(f, P);
		}

		imprimirLista(P);

		while(!vazia(P))
		{
			PECA *h = (PECA *) malloc (sizeof(PECA));
			h = removerPeca(P);

			if(h != NULL)
				printf("valor de fora da função remover %d\n", h->quantidade);
		}

		//imprimirR(ret->matriz,ret->L,ret->W);


		/*-----------------------------Reinício das variáveis---------------------------------------------------*/
	//	apagarRetanguloR(ret);
/*

		while(!vazia(B))
		{
			removerPeca(B);
		}*/
		/*-------------------------------------------------------------------------------------------------------*/


		num_inst++;
	}

    fclose(f);
    free(P);
   // free(B);
    
    return 0;
}


