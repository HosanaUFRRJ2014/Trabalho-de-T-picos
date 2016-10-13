#include "structs/R.h"
#include "structs/lista.h"

int main(int argc, char const *argv[])
{
	int i ;
	//R *r = criarRetanguloR(10, 5);
	PECA *p[10];

	for (i = 0; i < 10; i++)
	{
		p[i] = criarPeca((i+1) * 3.14, (i+1) * 1.1, i + 1 , (i+1) * 2 , (i+1) * (i+1), (i+1)*3);
	}

	/*for (i = 0; i < 10; i++)
	{
		imprimirPeca(p[i]);
	}*/
		

	LISTA_LIGADA *l = criarLista();

	inserirPecaOrdenado(l, p[0]);
	inserirPecaOrdenado(l, p[5]);
	inserirPecaOrdenado(l, p[3]);
	inserirPecaOrdenado(l, p[7]);

	removerPeca(l);
	removerPeca(l);
	removerPeca(l);
	imprimirLista(l);

	//apagarRetanguloR(r);
	return 0;
}