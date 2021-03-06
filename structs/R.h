#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "peca.h"
#include "lista.h"
#include "arrayPontosCandidatos.h"

#ifndef R_H
#define R_H

#define LIMITE_INDICE_PECA 1000

typedef struct
{
	//comprimento L e largura W.
	int W;
	int L;

	//Matriz que representa a disposição de peças em R.
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

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < l; j++)
		{
			matriz[i][j] = 0;
		}
	}
}

//A matrizDestino deve, obrigatoriamente, ter W e L igual ao da origem
inline void copiarMatriz(int **matrizDestino, int **matrizOrigem, int L, int W)
{
	int i,j;

	for (i = 0; i < W; i++)
	{
		for (j = 0; j < L; j++)
		{
			matrizDestino[i][j] = matrizOrigem[i][j];
		}
	}

}

/*Imprime a matriz contida em R, e as variáveis de R*/
inline void imprimirR(R *r)
{
	int i, j;
     
    printf("\nComprimento(L) na horizontal e Largura(W) na vertical\n\n");
	
	for (i = 0; i < r->W; i++)
	{
		for (j = 0; j < r->L; j++)
		{
			printf("%4d",r->matriz[i][j]); //9
		}

		printf("\n");
	}

	printf("----------------Variáveis de R---------------------------\n");
	printf("indicePeca atual: %d\n",r->indicePeca);
	printf("Quantidade de peças presentes: %d\n",r->quantidade);
	printf("Valor de utilidade total: %.2f\n",r->valorUtilidadeTotal);
    printf("L: %d\n",r->L);
    printf("W: %d\n",r->W);
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

		r->matriz = (int **) malloc(w * sizeof(int *));
   		
   		for (i = 0; i < w; i++)
   		{        
            r->matriz[i] = (int *) malloc(l * sizeof(int));
 		}
   		
		//preencher retângulo R com zeros
		preencherComZeros(r->matriz,r->L,r->W);

		r->indicePeca = 1;
		r->quantidade = 0;
		r->valorUtilidadeTotal = 0;
	}

	return r;
}

//verificar se é possível adicionar dada peca em R, em um determinado ponto candidato.
//verficando também se o limite superior Q não estourou
inline int ehPossivelAdicionar(R *r, PECA *nova, PONTO_CANDIDATO *ponto)
{
	int i, j;

	if(!ehPontoCandidato(ponto))
		return false;

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

//função para a verificação do limite superior Q.
inline int dentroDoLimiteSuperior(LISTA_LIGADA *B, PECA *nova ,int qtdAsomar)
{
	//verificar se a peça já existe em B, para o tratamento do limite superior
    NO *temp = B->inicio;
	PECA *pecaJaExistenteEmR;

	while(temp != NULL)
	{
		if(pecasIguais(temp->peca,nova))
		{
			pecaJaExistenteEmR = temp->peca;
			break;
		}

		temp = temp->proximo;
	}

	if(temp == NULL) //significa que a peça nem está em R. Logo, não ultrapassa o limite superior
		return true;

	if(pecaJaExistenteEmR->quantidade + qtdAsomar <= pecaJaExistenteEmR->Q)
		return true;
	
	return false;
}

//funcao para preencher R com a peça, de fato.
inline void preencherRcomPeca(R *r, PECA *nova, PONTO_CANDIDATO *ponto,int indicePeca)
{
	int i, j;

	int fatorPreenchimento;

    //Para não haverem peças com indíces muito grandes, o que atrapalha a leitura do resultado em R 
	if(r->indicePeca == LIMITE_INDICE_PECA)
		r->indicePeca = 1;

	if(indicePeca == -1) //Preenche com o próximo índice salvo em R.
	{
		fatorPreenchimento = r->indicePeca;
		r->indicePeca++;
	}
	else if(indicePeca > 0)//a peça já existe e vamos preenchê-la com o seu índice em R.
		fatorPreenchimento = indicePeca;

	for (i = ponto->y; i < ponto->y + nova->w; i++)
	{
		for (j = ponto->x; j < ponto->x + nova->l; j++)
		{
			r->matriz[i][j] = fatorPreenchimento;
		}
	}

	//definição dos pontos candidatos da peça nova
	//lembrete: as noções de L e W são invertidas, na minha opinião, mas respeitei o artigo.
	//se não vai estourar o comprimento do retângulo 
	if(j <= r->L)
	{
        PONTO_CANDIDATO *p1 = criarPontoCandidato(j - 1, ponto->y);
		inserirPontoCandidato(nova->p1,p1);
	}

 	//se não vai estourar a largura do retângulo R
	if(i <= r->W)
	{
		PONTO_CANDIDATO *p2 = criarPontoCandidato(j - nova->l, i - 1);
		inserirPontoCandidato(nova->p2,p2);
	}

	r->quantidade++;
	r->valorUtilidadeTotal += nova->v;

	return;
}

inline void despreencherRcomPeca(R* r,PECA *aRemover,PONTO_CANDIDATO *p1,PONTO_CANDIDATO *p2)
{
	int i, j;

	PONTO_CANDIDATO *origemPeca = coordenadaOrigemPeca(aRemover,p1,p2);

	if(!ehPontoCandidato(origemPeca))
	{ 	
		free(origemPeca);
	    origemPeca = NULL;
		return;
	}

	for (i = origemPeca->y; i < origemPeca->y + aRemover->w; i++)
	{
		for (j = origemPeca->x; j < origemPeca->x + aRemover->l; j++)
		{
			r->matriz[i][j] = 0;
		}
	}

	r->quantidade--;
	r->valorUtilidadeTotal -= aRemover->v;
	free(origemPeca);
	origemPeca = NULL;

}

inline int adicionarPecaAoRetangulo(R *r, LISTA_LIGADA *B , PECA *nova)
{
	//verificar se a peça já existe em B, para o tratamento do limite superior
    if(!dentroDoLimiteSuperior(B, nova ,1))
    	return false;

    //se está dentro do limite superior, o algoritmo continua
	//verificando primeiro a origem
	PONTO_CANDIDATO *origem = criarPontoCandidato(0,0);

	if(ehPossivelAdicionar(r, nova, origem))
	{
		preencherRcomPeca(r, nova, origem, -1);
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

	int cont = 0;

	while(aux != NULL)
	{
		for(cont = 0;cont < aux->peca->quantidade;cont++)
		{
			//varrer o array de pontos candidatos e, para cada ponto,
			//conferir se dá para adicionar em p1 e p2 e salvar o mais próximo da origem
			NO_Pt *aux_pt1, *aux_pt2;
			aux_pt1 = aux->peca->p1->inicio;
			aux_pt2 = aux->peca->p2->inicio;

			while(aux_pt1 != NULL && aux_pt2 != NULL)
			{
				PONTO_CANDIDATO *p1Ainserir = criarPontoCandidato(aux_pt1->ponto->x + 1,aux_pt1->ponto->y);
				PONTO_CANDIDATO *p2Ainserir = criarPontoCandidato(aux_pt2->ponto->x, aux_pt2->ponto->y + 1);

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

			free(aux_pt1);
			free(aux_pt2);
			aux_pt1 = NULL;
			aux_pt2 = NULL;

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
		preencherRcomPeca(r,nova,atual,-1);

	return true;
}

inline void removerPecaDoRetangulo(R *r,LISTA_LIGADA *P,LISTA_LIGADA *B, PECA *aRemover, PONTO_CANDIDATO *p1, PONTO_CANDIDATO *p2)
{
	PECA *novaPeca = criarPeca(0,0,0,0,0.0,0);

	//Copia tudo menos o array de pontos candidadatos.
	copiarPecaParaP(novaPeca, aRemover);

	//Insere a nova peça em P.
	inserirPeca(P,novaPeca);

	//Remover a peça em R.
	despreencherRcomPeca(r,aRemover,p1,p2);

	//Remove a peça de B.
	removerPecaDadoPeca(B,aRemover,p1,p2);

	free(novaPeca);
	novaPeca = NULL;
}

inline void remocaoAleatoria(R *r, LISTA_LIGADA *P, LISTA_LIGADA *B, float gamma)
{
	float areaSerRemovida = ((r->L * r->W) * gamma), areaJaRemovida = 0.0;

	int indiceTipoPecaSerRemovida, indicePecaSerRemovida, count, iter = 0;

	NO *aux_B;
	NO_Pt *aux_pt1, *aux_pt2;

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
	}	
}

//Esta função ordena as peças presentes em R em uma lista ordenada pela distância da origem da peça em R até a origem e desloca-as
//para o ponto candidato factível mais próximo da origem de R, dentre as peças já deslocadas.
inline void deslocarPecas(R *r, LISTA_LIGADA *B)
{
	//Será ordenado de acordo com a distância mais próxima da origem.
	PECA *arrayPecas = (PECA *) malloc(sizeof(PECA) * r->quantidade);
	NO *aux = B->inicio;
	NO_Pt *aux_pt1,*aux_pt2;
	PONTO_CANDIDATO *aux_p1,*aux_p2;
	int count = 0;

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
			count++;

			//Para esvaziar a lista B que será preenchida novamente. 
			removerPeca(B);
		}

		aux = B->inicio;
	}
	
	//Ordenação do vetor de acordo com a distância da origem da peça com (0,0).
	if(r->quantidade > 1)
	  mergeSort(arrayPecas,0,r->quantidade - 1);

	//----------------------------------------------------------------------------------------------------

	//Início do deslocamento das peças para esquerda e depois para cima.

	//Criar a nova lista B que será considerada.
	PONTO_CANDIDATO *pontoEscolhido,*aux_pontoEscolhido,*aux_origemPeca;
	int countB, indicePeca;
	
	pontoEscolhido = (PONTO_CANDIDATO*)malloc(sizeof(PONTO_CANDIDATO));
	aux_pontoEscolhido = (PONTO_CANDIDATO*)malloc(sizeof(PONTO_CANDIDATO));

	//Inicializando o ponto de origem.
	pontoEscolhido->x = 0;
	pontoEscolhido->y = 0;

	//Segundo passo: deslocar as peças restantes de acordo com a ordem do vetor ordenado.
	for (count = 0; count < r->quantidade; count++)
	{
		indicePeca = r->matriz[arrayPecas[count].p1->inicio->ponto->y][arrayPecas[count].p1->inicio->ponto->x];

		//Verificar o ponto candidato mais próximo da origem dentre as peças anteriormente deslocadas na lista ordenada.
		despreencherRcomPeca(r,&arrayPecas[count],arrayPecas[count].p1->inicio->ponto,arrayPecas[count].p2->inicio->ponto);

		//Varrendo as peças anteriormente deslocadas.
		for(countB = 0;countB < count;countB++)
		{
			//Testando o ponto candidato P1
			//Se a distância do PC até a origem for menor que a já encontrada, este será o novo ponto onde a peça será inserida.
			if(distanciaEntreDoisPontos(arrayPecas[countB].p1->inicio->ponto->x,arrayPecas[countB].p1->inicio->ponto->y,0,0) < 
				distanciaEntreDoisPontos(pontoEscolhido->x,pontoEscolhido->y,0,0))
			{
				aux_pontoEscolhido->x = pontoEscolhido->x;
				aux_pontoEscolhido->y = pontoEscolhido->y;

				pontoEscolhido->x = arrayPecas[countB].p1->inicio->ponto->x + 1;
				pontoEscolhido->y = arrayPecas[countB].p1->inicio->ponto->y;

				//Reseta a variável com o último ponto escolhido.
				if(!(ehPossivelAdicionar(r, &arrayPecas[count], pontoEscolhido)))
				{
					pontoEscolhido->x = aux_pontoEscolhido->x;
					pontoEscolhido->y = aux_pontoEscolhido->y;
				}
			}

			//Testando o ponto candidato P1
			//Se a distância do PC até a origem for menor que a já encontrada, este será o novo ponto onde a peça será inserida.
			if(distanciaEntreDoisPontos(arrayPecas[countB].p2->inicio->ponto->x,arrayPecas[countB].p2->inicio->ponto->y,0,0) < 
			   distanciaEntreDoisPontos(pontoEscolhido->x,pontoEscolhido->y,0,0))
			{
				aux_pontoEscolhido->x = pontoEscolhido->x;
				aux_pontoEscolhido->y = pontoEscolhido->y;

				pontoEscolhido->x = arrayPecas[countB].p2->inicio->ponto->x;
				pontoEscolhido->y = arrayPecas[countB].p2->inicio->ponto->y + 1;

				//Reseta a variável com a último ponto escolhido.
				if(!(ehPossivelAdicionar(r, &arrayPecas[count], pontoEscolhido)) )
				{
					pontoEscolhido->x = aux_pontoEscolhido->x;
					pontoEscolhido->y = aux_pontoEscolhido->y;
				}
			}
		}

		aux_origemPeca = coordenadaOrigemPeca(&arrayPecas[count],arrayPecas[count].p1->inicio->ponto,
											  arrayPecas[count].p2->inicio->ponto);

		//Removendo os pontos desatualizados.
		removerPontoCandidato(arrayPecas[count].p1);
		removerPontoCandidato(arrayPecas[count].p2);

		//Encontrado o ponto candidato mais próximo da origem, vamos inserir a peça atual neste ponto.
		if(ehPossivelAdicionar(r, &arrayPecas[count], pontoEscolhido)) //SEMPRE VERDADEIRO!(ou não...)
		{
			//Preenchendo no ponto escolhido e atualizando(dentro da função) o ponto candidato atual.
			preencherRcomPeca(r,&arrayPecas[count],pontoEscolhido,indicePeca);
		}
		else
		{
			preencherRcomPeca(r,&arrayPecas[count],aux_origemPeca,indicePeca);
			free(aux_origemPeca);
		}

		//Inserindo a peça em B(que começou vazia).
		inserirPeca(B,&arrayPecas[count]);

		//Resetando o ponto escolhido
		pontoEscolhido->x = r->L + 1;
		pontoEscolhido->y = r->W + 1;

	}

	free(pontoEscolhido);
	pontoEscolhido = NULL;
	free(aux_pontoEscolhido);
	aux_pontoEscolhido = NULL;
	free(arrayPecas);
	arrayPecas = NULL;
}

//se não funcionar, varrer a matriz dando free
inline void apagarRetanguloR(R *r)
{
	int i = 0;

	for (i = 0; i < r->W; i++)
	{
		free(r->matriz[i]);
		r->matriz[i] = NULL;
	}

	free(r->matriz);
	free(r);

	r = NULL;
}

#endif
