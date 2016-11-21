#include "includes.h"
//#include "structs/lista.h"

int main(int argc, char const *argv[])
{
	int i ;
	//R *r = criarRetanguloR(10, 5);
	PECA *p[10];

	for (i = 0; i < 10; i++)
	{
		p[i] = criarPeca((i+1) * 3.14 + i * i, (i+1) * 1.1, i * i, (i+1) * 2  + 59 * 12.88/(i+1), 59 * 12.88/(i+1), (i+1)*3);
	}

	/*for (i = 0; i < 10; i++)
	{
		imprimirPeca(p[i]);
	}*/
		

	LISTA_LIGADA *l = criarLista();

	inserirPeca(l, p[7]);
	inserirPeca(l, p[3]);
	inserirPeca(l, p[5]);
	inserirPeca(l, p[2]);
	inserirPeca(l, p[0]);


	printf("-----------------------Lista---------------------------\n");
	imprimirLista(l);
	printf("l->tamanho: %d\n", l->tamanho);

	printf("-----------------------Lista ordenada---------------------------\n");
	l = ordenarLista(l);
	imprimirLista(l);
	printf("l->tamanho: %d\n", l->tamanho);

	
	removerPeca(l);
	removerPeca(l);
	removerPeca(l);

	printf("-----------------------Depois de algumas remoções---------------------------\n");

	imprimirLista(l);

	printf("l->tamanho: %d\n", l->tamanho);

	//apagarRetanguloR(r);
	return 0;
}

/*

*O que já testei:
inserção de peças iguais
inserção de peças diferentes
remoção de peças iguais
remoção de peças diferentes
remoção em número maior do que a quantidade de peças na lista
"ordenação"
coerência da variável tamanho de lista. Verificação da mesma nas três etapas(insersão, ordenação, remoção) realizadas acima

verificação de limite superior
falta fazer a verificação se o limite inferior funciona. No momento, optei por não usar essa notação, pois não sei se é de fato útil
e não sei muito bem onde verificar isso. No artigo, ficou meio perdida essa notação. Eles só falam disso na pág. 2. Sinceramente, achei
desnecessário e acho que poderíamos propor a solução do problema como irrestrito(sem limites inferior e superior).


*/