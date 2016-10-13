#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int l;
	int w;
	int p;
	int q;
	int v;
}PECA;

typedef struct{
	int L;
	int W;
}RETANGULO;

//l = comprimento e w = largura

int main()
{
	FILE *inst = fopen("inst1.txt","r");
	//fscanf(arq,"%c %c %c\n", &ch1, &ch2, &ch3))!=EOF
	//int qtd_inst, qtd_pecas, otimo, l, w, P, Q, v, L, W;
	int qtd_pecas;
	int i = 0;

	RETANGULO R;
	PECA pecas[5];

	//fscanf(inst, " %d\n", &qtd_inst);

	while(fscanf(inst," %d\n %d %d\n", &qtd_pecas, &R.L, &R.W) != EOF)
	{
		//fscanf(inst," %d\n %d %d\n", &qtd_pecas, &R.L, &R.W);

		for(i = 0;i < qtd_pecas;i++)
		{
			fscanf(inst," %d %d %d %d %d\n", &pecas[i].l, &pecas[i].w, &pecas[i].p, &pecas[i].q, &pecas[i].v);
		}
	}

	printf("\n");

	printf("Qtd_pecas: %d\nDimensoes R: %d %d\n", qtd_pecas, R.L, R.W);

	for(i = 0;i < qtd_pecas;i++)
	{
		printf("%d: %d %d %d %d %d\n",i,pecas[i].l, pecas[i].w, pecas[i].p, pecas[i].q, pecas[i].v);
	}

    fclose(inst);
    return 0;
}