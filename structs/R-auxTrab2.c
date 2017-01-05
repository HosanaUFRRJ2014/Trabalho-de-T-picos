#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "peca.h"
#include "lista.h"
#include "arrayPontosCandidatos.h"
//#define true 1
//#define false 0

#ifndef R_H
#define R_H

typedef struct             //comprimento L e largura W.
{
	int W;
	int L;
	int **matriz;

	//Contador de índice da peca em R. A variável será incrementada toda vez que for inserida uma peça em R.
	unsigned int indicePeca;

	//Quantidade de peças em R
	int quantidade;
	//Valor total das peças contidas em R.
	float valorUtilidadeTotal;
	
}R; //qtd de linhas: l e qtd de colunas: w;

inline void preencherComZeros(int **matriz, int l, int w)
{
	int i, j;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < w; j++)
		{
			matriz[i][j] = 0;
		}
	}
}

//a matrizDestino devem, obrigatoriamente, ter W e L igual ao da origem
inline void copiarMatriz(int **matrizDestino, int **matrizOrigem, int L, int W)
{
	int i,j;

	for (i = 0; i < L; i++)
	{
		for (j = 0; j < W; j++)
		{
			matrizDestino[i][j] = matrizOrigem[i][j];
		}
	}

}

inline void imprimirR(int **matriz, int l, int w)
{
	int i, j;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < w; j++)
		{
			printf("%3d",matriz[i][j]); //9
		}

		printf("\n");
	}
}

//Função feita por Lívia.
inline void imprimirVariaveisR(R *r)
{
	printf("----------------Variáveis de R---------------------------\n");
	printf("indicePeca atual: %d\n",r->indicePeca);
	printf("Quantidade de peças presentes: %d\n",r->quantidade);
	printf("Valor de utilidade total: %.2f\n",r->valorUtilidadeTotal);
	printf("Área de R: %d\n",(r->L * r->W));
	printf("---------------------------------------------------------\n");
}

inline R * criarRetanguloR(int l, int w)
{
	R *r = (R *) malloc(sizeof(R));

	int i = 0;

	if(r != NULL)
	{
		r->W = w;
		r->L = l;

		r->matriz = (int **) malloc(l * sizeof(int *));
		
   		for (i = 0; i < l; i++)
   		{        
            r->matriz[i] = (int *) malloc(w * sizeof(int));
 		}
   		
		//preencher retângulo R com zeros
		preencherComZeros(r->matriz,r->L,r->W);
		
		r->indicePeca = 1;
		r->quantidade = 0;
		r->valorUtilidadeTotal = 0;
	}

	return r;
}


/*-------------------Criar funções de preencher retangulo-----------------------------------*/
//verificar se é possível adicionar dada peca em R, em um determinado ponto candidato.
inline int ehPossivelAdicionar(R *r, PECA *nova, PONTO_CANDIDATO *ponto)
{
	int i, j;

	if(!ehPontoCandidato(ponto))
		return false;

	//printf("x: %d y: %d\n", ponto->x, ponto->y);

	for (i = ponto->y; i < ponto->y + nova->w; i++)
	{
		for (j = ponto->x; j < ponto->x + nova->l; j++)
		{
			if(i >= r->W || j >= r->L || r->matriz[i][j] != 0)
				return false;

		}
	}


	return true;

}

//funcao para preencher R com a peça, de fato.
inline void preencherRcomPeca(R *r, PECA *nova, PONTO_CANDIDATO *ponto,int indicePeca)
{
	int i, j;

	int fatorPreenchimento;

	if(indicePeca == -1) //Preenche com o próximo índice salvo em R.
	{
		fatorPreenchimento = r->indicePeca;
		r->indicePeca++;
	}
	else if(indicePeca > 0)//a peça já existe e vamos preenchê-la com o seu índice em R.
		fatorPreenchimento = indicePeca;

	//printf("label 1\n");

	for (i = ponto->y; i < ponto->y + nova->w; i++)
	{
		for (j = ponto->x; j < ponto->x + nova->l; j++)
		{
			if(i >= r->W || j>= r->L)
				printf("ESTOUROU!!\n");

			r->matriz[i][j] = fatorPreenchimento;
		}
	}

	//printf("label 2\n");


	//definição dos pontos candidatos da peça nova
	//lembrete: as noções de L e W são invertidas, na minha opinião, mas respeitei o artigo.
	//se não vai estourar o comprimento do retângulo 
	if(j <= r->L)
	{
        PONTO_CANDIDATO *p1 = criarPontoCandidato(j - 1, ponto->y);
		inserirPontoCandidato(nova->p1,p1);
	}

	//printf("label 3\n");


 //se não vai estourar a largura do retângulo R
	if(i <= r->W)
	{
		PONTO_CANDIDATO *p2 = criarPontoCandidato(j - nova->l, i - 1);
		inserirPontoCandidato(nova->p2,p2);
	
	}

	r->quantidade++;
	r->valorUtilidadeTotal += nova->v;

	//printf("label 5\n");

	return;

}

/*Função feita por Lívia*/
inline void despreencherR(R* r,PECA *aRemover,PONTO_CANDIDATO *p1,PONTO_CANDIDATO *p2)
{
	int i, j;

	PONTO_CANDIDATO *origemPeca = coordenadaOrigemPeca(aRemover,p1,p2);

	if(ehPontoCandidato(origemPeca))
	{
		for (i = origemPeca->y; i < origemPeca->y + aRemover->w; i++)
		{
			for (j = origemPeca->x; j < origemPeca->x + aRemover->l; j++)
			{
				r->matriz[i][j] = 0;
			}
		}
	}
	else
	{
		printf("Peca ou ponto inválido para ser removido.\n");
		return;
	}

	r->quantidade--;
	r->valorUtilidadeTotal -= aRemover->v;
}

//linha 3 do algoritmo 1 do artigo
inline int adicionarPecaAoRetangulo(R *r, LISTA_LIGADA *B , PECA *nova, int indicePeca) //sem o "indicePeca"
{
	/*------------------------------------------------------*/
	NO *aux_Q = B->inicio;

	while(aux_Q != NULL)
	{
		if(pecasIguais(aux_Q->peca,nova))
		{
			if(aux_Q->peca->quantidade < aux_Q->peca->Q)
				break;
			else
				return false;
		}

		aux_Q = aux_Q->proximo;
	}
	/*------------------------------------------------------*/
	
	//verificando primeiro a origem
	PONTO_CANDIDATO *origem = criarPontoCandidato(0,0);
	if(ehPossivelAdicionar(r, nova, origem))
	{
		preencherRcomPeca(r, nova, origem, indicePeca);
		return true;
	}
	
	//se não, verificar cada ponto candidato de cada peça em B
	NO *aux = B->inicio;

	//setado como -1 e -1 caso não exista
	//é ponto mais próximo da origem, que sempre será armazenado caso exista.
	PONTO_CANDIDATO *atual = criarPontoCandidato(-1, -1);

	//Variável que irá guardar o ponto p1(+ direita e + acima) que está mais próximo da origem.
	//Estes pontos candidatos possuem prioridade de inserção.
	PONTO_CANDIDATO *prioridadeAdireita = criarPontoCandidato(-1,-1);

	while(aux != NULL)
	{
		int cont = 0;
		//printf("Varrendo lista B---> nós\n");
		while(cont < aux->peca->quantidade)
		{
		//	printf("Lendo peca a peca\n");
			//varrer o array de pontos candidatos e, para cada ponto,
			//conferir se dá para adicionar em p1 e p2 e salvar o mais próximo da origem
			NO_Pt *aux_pt1, *aux_pt2;
			aux_pt1 = aux->peca->p1->inicio;
			aux_pt2 = aux->peca->p2->inicio;

			while(aux_pt1 != NULL && aux_pt2 != NULL)
			{
				PONTO_CANDIDATO *p1Ainserir = criarPontoCandidato(aux_pt1->ponto->x + 1,aux_pt1->ponto->y);
				PONTO_CANDIDATO *p2Ainserir = criarPontoCandidato(aux_pt2->ponto->x, aux_pt2->ponto->y + 1);
		//		printf("Enquanto existe pontos candidatos em uma peca em B\n");
				if(ehPossivelAdicionar(r,nova,p1Ainserir))
				{
					/*-------------------------------------------------------------------------*/
					//Vendo o ponto factível p1 mais próximo da origem já encontrado.
					prioridadeAdireita = primeiroPontoFactivel(p1Ainserir,prioridadeAdireita);
					/*-------------------------------------------------------------------------*/

					//comparar qual deles está mais pŕoximo da origem. O que está mais próximo é armazenado
					atual = primeiroPontoFactivel(atual,p1Ainserir);
			
				}
				else if(ehPossivelAdicionar(r,nova,p2Ainserir))
				{
					//comparar qual deles está mais pŕoximo da origem. O que está mais próximo é armazenado
					atual = primeiroPontoFactivel(atual,p2Ainserir);				
					
				}

				aux_pt1 = aux_pt1->proximo;
				aux_pt2 = aux_pt2->proximo;
			}


			cont++;
		}

		aux = aux->proximo;
	}

	//Se não foi encontrado nenhum ponto candidato que permitisse a peça ser adicionada, o "atual" nunca foi modificado desde sua alocação.
	if(!ehPontoCandidato(atual) || atual == NULL)
		return false;

	/*------------------------------------------------*/
	if(ehPontoCandidato(prioridadeAdireita))
		atual = prioridadeAdireita;
	/*------------------------------------------------*/

	if(!ehPossivelAdicionar(r,nova,atual))
		return false;

	else
		preencherRcomPeca(r,nova,atual,indicePeca);

	return true;

}

//Função feita por Lívia.
inline void removerPecaDoRetangulo(R *r,LISTA_LIGADA *P,LISTA_LIGADA *B, PECA *aRemover, PONTO_CANDIDATO *p1, PONTO_CANDIDATO *p2)
{
	PECA *novaPeca = criarPeca(0,0,0,0,0.0,0);

	if(P != NULL)
	{
		//Copia tudo menos o array de pontos candidadatos.
		copiarPecaParaP(novaPeca, aRemover);

		//Insere a nova peça em P.
		inserirPeca(P,novaPeca);
	}

	//Remover a peça em R.
	despreencherR(r,aRemover,p1,p2);

	//Remove a peça de B.
	removerPecaDadoPeca(B,aRemover,p1,p2);

	free(novaPeca);
}

//Função feita por Lívia.
inline void remocaoAleatoria(R *r, LISTA_LIGADA *P, LISTA_LIGADA *B, float gamma)
{
	float areaSerRemovida = ((r->L * r->W) * gamma), areaJaRemovida = 0.0;

	int indiceTipoPecaSerRemovida, indicePecaSerRemovida, count, iter = 0;

	NO *aux_B;
	NO_Pt *aux_pt1, *aux_pt2;
	//PECA *novaPeca = criarPeca(0,0,0,0,0.0,0);

	while(areaJaRemovida < areaSerRemovida && B->tamanho != 0)
	{
		aux_B = B->inicio;

		indiceTipoPecaSerRemovida = rand() % B->tamanho;

		//Varrendo a lista B para alcançar a peça do determinado índice.
		for(count = 0;count < indiceTipoPecaSerRemovida;count++)
		{
			aux_B = aux_B->proximo;
		}
		
		//Encontrado este tipo de peça, precisamos escolher uma delas em R para remover.
		indicePecaSerRemovida = rand() % aux_B->peca->quantidade;

		aux_pt1 = aux_B->peca->p1->inicio;
		aux_pt2 = aux_B->peca->p2->inicio;

		for(count = 0;count < indicePecaSerRemovida;count++)
		{
			aux_pt1 = aux_pt1->proximo;
			aux_pt2 = aux_pt2->proximo; 
		}

		//Temos a peca a ser removida. Vamos removê-la.
		
		//Soma a área que iremos remover.
		areaJaRemovida += (aux_B->peca->l * aux_B->peca->w);

		removerPecaDoRetangulo(r,P,B,aux_B->peca,aux_pt1->ponto,aux_pt2->ponto);

		/*
		//Copia tudo menos o array de pontos candidadatos.
		copiarPecaParaP(novaPeca, aux_B->peca);

		//Insere a nova peça em P.
		inserirPeca(P,novaPeca);

		//Remover a peça em R.
		despreencherR(r,aux_B->peca,aux_pt1->ponto,aux_pt2->ponto);

		//Remove a peça de B.
		removerPecaDadoPeca(B, aux_B->peca, aux_pt1->ponto,aux_pt2->ponto);
		*/
	}
	
}

//Função feita por Lívia.
/*Esta função ordena as peças presentes em R em uma lista ordenada pela distância da origem da peça em R até a origem e desloca-as
para o ponto candidato factível mais próximo da origem de R, dentre as peças já deslocadas.*/
inline void deslocarPecas(R *r, LISTA_LIGADA *B)
{
	//Será ordenado de acordo com a distância mais próxima da origem.
	PECA *arrayPecas = (PECA *) malloc(sizeof(PECA) * r->quantidade);

	////////////////////////////////////////////////////////////////
	int *indicesPecas = (int *) malloc(sizeof(int) * r->quantidade);
	////////////////////////////////////////////////////////////////

	NO *aux = B->inicio;
	NO_Pt *aux_pt1,*aux_pt2;
	PONTO_CANDIDATO *aux_p1,*aux_p2;
	int count = 0;

	//--------------------------
	int qtd_r_anterior = r->quantidade;
	//--------------------------

	//Criando o vetor de peças para ser ordenado.
	while(aux != NULL)
	{
		aux_pt1 = aux->peca->p1->inicio;
		aux_pt2 = aux->peca->p2->inicio;

		while(aux_pt1 != NULL && aux_pt2 != NULL)
		{
			arrayPecas[count].l = aux->peca->l;
			arrayPecas[count].w = aux->peca->w;
			arrayPecas[count].P = aux->peca->P;
			arrayPecas[count].Q = aux->peca->Q;
			arrayPecas[count].v = aux->peca->v;
			arrayPecas[count].p1 = criarArrayPontosCandidatos();
			arrayPecas[count].p2 = criarArrayPontosCandidatos();
			arrayPecas[count].quantidade = 1;

			aux_p1 = criarPontoCandidato(aux_pt1->ponto->x, aux_pt1->ponto->y);
			aux_p2 = criarPontoCandidato(aux_pt2->ponto->x, aux_pt2->ponto->y);

			inserirPontoCandidato(arrayPecas[count].p1, aux_p1);
			inserirPontoCandidato(arrayPecas[count].p2, aux_p2);

			aux_pt1 = aux_pt1->proximo;
			aux_pt2 = aux_pt2->proximo;

			///////////////////////////////////////////////////////
			indicesPecas[count] = r->matriz[arrayPecas[count].p1->inicio->ponto->y][arrayPecas[count].p1->inicio->ponto->x];
			///////////////////////////////////////////////////////

			count++;

			//Para esvaziar a lista B que será preenchida novamente.
			removerPecaDoRetangulo(r,NULL,B,aux->peca,arrayPecas[count - 1].p1->inicio->ponto,arrayPecas[count - 1].p2->inicio->ponto); 
			//removerPeca(B);
		}

		//aux = aux->proximo;
		aux = B->inicio;
	}
		
	//Ordenação do vetor de acordo com a distância da origem da peça com (0,0).
	mergeSort(arrayPecas,indicesPecas,0,qtd_r_anterior - 1); //r->quantidade

/*----------------------------------------------------------------------------------------------------*/

	//Início do deslocamento das peças para esquerda e depois para cima.

	int deuCerto;

	/*-----------------------------------------*/
	
	for (count = 0; count < qtd_r_anterior; count++)
	{
		//Removendo os pontos desatualizados.
		removerPontoCandidato(arrayPecas[count].p1);
		removerPontoCandidato(arrayPecas[count].p2);

		deuCerto = adicionarPecaAoRetangulo(r,B,&arrayPecas[count],indicesPecas[count]);

		if(!deuCerto)
		{
			printf("//////////////////////////////////////////////////////////////////////////////////////\n");
			printf("PARECE QUE EXISTIU UM CASO QUE INVALIDOU SUA IDEIA...TRISTE FIM DE ALGO BRILHANTE :(\n\n");
			printf("//////////////////////////////////////////////////////////////////////////////////////\n");
			return;
		}

		inserirPeca(B,&arrayPecas[count]);
	}
	
	///////////////////////////////////
	free(indicesPecas);
	free(arrayPecas);
	////////////////////////////////////
}
//*/
//se não funcionar, dar varrer a matriz dando free
inline void apagarRetanguloR(R *r)
{
	int i = 0;

	for (i = 0; i < r->L; i++)
	{
		free(r->matriz[i]);
	}

	free(r->matriz);

	free(r);
}


#endif
