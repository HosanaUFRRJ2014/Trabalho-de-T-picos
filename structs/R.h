#include <stdio.h>
#include <stdlib.h>
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

	//O elemento i,j da matriz corresponde se o ponto candidato i,j está presente em R. Se 1, está presente, 0 caso contrário.	
	int **pontosCandidatos;

	//Contador de índice da peca em R. A variável será incrementada toda vez que for inserida uma peça em R.
	unsigned int indicePeca;
	
}R; //qtd de linhas: l e qtd de colunas: w;

void preencherComZeros(int **matriz, int l, int w)
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

void imprimirR(int **matriz, int l, int w)
{
	int i, j;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < w; j++)
		{
			printf("%d    ",matriz[i][j]);
		}

		printf("\n");
	}
}


R * criarRetanguloR(int l, int w)
{
	R *r = (R *) malloc(sizeof(R));

	int i = 0; //Variável inutilizada "j" ---> linha 51.

	if(r != NULL)
	{
		r->W = w;
		r->L = l;

		r->matriz = (int **) malloc(l * sizeof(int *));
		r->pontosCandidatos = (int **) malloc(l * sizeof(int *));
   		
   		for (i = 0; i < l; i++)
   		{        
            r->matriz[i] = (int *) malloc(w * sizeof(int));
            r->pontosCandidatos[i] = (int *) malloc(w * sizeof(int));
 		}
   		
		//preencher retângulo R com zeros
		preencherComZeros(r->matriz,r->L,r->W);
		preencherComZeros(r->pontosCandidatos,r->L,r->W);
		r->pontosCandidatos[0][0] = 1;

		r->indicePeca = 1;


	}

	return r;
}


/*-------------------Criar funções de preencher retangulo-----------------------------------*/
//verificar se é possível adicionar dada peca em R, em um determinado ponto candidato.
int ehPossivelAdicionar(R *r, PECA *nova, PONTO_CANDIDATO *ponto)
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
void preencherRcomPeca(R *r, PECA *nova, PONTO_CANDIDATO *ponto)
{
	int i, j;
	for (i = ponto->y; i < ponto->y + nova->w; i++)
	{
		for (j = ponto->x; j < ponto->x + nova->l; j++)
		{
			r->matriz[i][j] = r->indicePeca;
		}
	}
	//definição dos pontos candidatos da peça nova
	//lembrete: as noções de L e W são invertidas, na minha opinião, mas respeitei o artigo.
	//se não vai estourar o comprimento do retângulo 


	if(j < r->L)
	{
        
        PONTO_CANDIDATO *p1 = criarPontoCandidato(j,ponto->y);
		inserirPontoCandidato(nova->p1,p1);
	}


 //se não vai estourar a largura do retângulo R
	if(i < r->W)
	{
		PONTO_CANDIDATO *p2 = criarPontoCandidato(j - nova->l,i);
	
		inserirPontoCandidato(nova->p2,p2);
	
	}

    

	r->indicePeca++;

	return;

}

//linha 3 do algoritmo 1 do artigo
int adicionarPecaAoRetangulo(R *r, LISTA_LIGADA *B , PECA *nova)
{
	//verificando primeiro a origem
	PONTO_CANDIDATO *origem = criarPontoCandidato(0,0);
	if(ehPossivelAdicionar(r, nova, origem))
	{
		preencherRcomPeca(r, nova, origem);
		return true;
	}
	
	//se não, verificar cada ponto candidato de cada peça em B
	NO *aux = B->inicio;

	//setado como -1 e -1 caso não exista
	//é ponto mais próximo da origem, que sempre será armazenado caso exista.
	PONTO_CANDIDATO *atual = criarPontoCandidato(-1, -1);

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
		//		printf("Enquanto existe pontos candidatos em uma peca em B\n");
				if(ehPossivelAdicionar(r,nova,aux_pt1->ponto))
				{
					//comparar qual deles está mais pŕoximo da origem. O que está mais próximo é armazenado
					atual = primeiroPontoFactivel(atual,aux_pt1->ponto);
			
				}

				if(ehPossivelAdicionar(r,nova,aux_pt2->ponto))
				{
					//comparar qual deles está mais pŕoximo da origem. O que está mais próximo é armazenado
					atual = primeiroPontoFactivel(atual,aux_pt2->ponto);
				
					
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

	//senão
	preencherRcomPeca(r,nova,atual);

	return true;


}

//se não funcionar, dar varrer a matriz dando free
void apagarRetanguloR(R *r)
{
	free(r->matriz);
	/*free(r->W);
	free(r->L);*/

	free(r);

}


#endif
