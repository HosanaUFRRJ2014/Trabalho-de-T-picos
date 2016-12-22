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

	//O elemento i,j da matriz corresponde se o ponto candidato i,j está presente em R. Se 1, está presente, 0 caso contrário.	
	//int **pontosCandidatos;

	//Contador de índice da peca em R. A variável será incrementada toda vez que for inserida uma peça em R.
	unsigned int indicePeca;

	//Quantidade de peças em R
	int quantidade;

	//Área já preenchida de R.
	//int areaOcupada;

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

inline void imprimirR(int **matriz, int l, int w)
{
	int i, j;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < w; j++)
		{
			printf("%-5d",matriz[i][j]);
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

	int i = 0; //Variável inutilizada "j" ---> linha 51.

	if(r != NULL)
	{
		r->W = w;
		r->L = l;

		r->matriz = (int **) malloc(l * sizeof(int *));
		//r->pontosCandidatos = (int **) malloc(l * sizeof(int *));
   		
   		for (i = 0; i < l; i++)
   		{        
            r->matriz[i] = (int *) malloc(w * sizeof(int));
            //r->pontosCandidatos[i] = (int *) malloc(w * sizeof(int));
 		}
   		
		//preencher retângulo R com zeros
		preencherComZeros(r->matriz,r->L,r->W);
		//preencherComZeros(r->pontosCandidatos,r->L,r->W);
		//r->pontosCandidatos[0][0] = 1;

		r->indicePeca = 1;
		r->quantidade = 0;
		r->valorUtilidadeTotal = 0;
		//r->areaOcupada = 0;


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

	else //a peça já existe e vamos preenchê-la com o seu índice em R.
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

	//r->indicePeca++;
	r->quantidade++;
	r->valorUtilidadeTotal += nova->v;
	//r->areaOcupada += (nova->l * nova->w);

	return;

}

/*Função feita por Lívia*/
inline void despreencherR(R* r,PECA *aRemover,PONTO_CANDIDATO *p1,PONTO_CANDIDATO *p2)
{
	int i, j;
	//Definindo a coordenada de ínicio da peça em R. Poderia ser feito com p2 tbm, mas defini como padrão usando apenas o ponto 
	//p1(Mais a direita e acima)
	//int origem_peca_em_R_x = p2->y - (aRemover->w - 1);
	//int origem_peca_em_R_y = p1->x - (aRemover->l - 1);

	PONTO_CANDIDATO *origemPeca = coordenadaOrigemPeca(aRemover,p1,p2);

	//imprimirPontoCandidato(origemPeca);

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
	}

	/*
	if(origem_peca_em_R_x >= 0 && origem_peca_em_R_y >= 0)
	{
		for (i = origem_peca_em_R_x; i < origem_peca_em_R_x + aRemover->w; i++)
		{
			for (j = origem_peca_em_R_y; j < origem_peca_em_R_y + aRemover->l; j++)
			{
				r->matriz[i][j] = 0;
			}
		}
	}
	else
	{
		printf("Peca ou ponto inválido para ser removido.\n");
	}
	*/

	//Retirar os pontos candidatos

	r->quantidade--;
	r->valorUtilidadeTotal -= aRemover->v;
	//r->areaOcupada -= (aRemover->l * aRemover->w);
}

//linha 3 do algoritmo 1 do artigo
inline int adicionarPecaAoRetangulo(R *r, LISTA_LIGADA *B , PECA *nova)
{
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

	//senão
	preencherRcomPeca(r,nova,atual,-1);

	return true;


}

//Função feita por Lívia.
inline void remocaoAleatoria(R *r, LISTA_LIGADA *P, LISTA_LIGADA *B, float gamma)
{
	//srand((unsigned int)time(NULL));
	//x = rand() % 10

	float areaSerRemovida = ((r->L * r->W) * gamma), areaJaRemovida = 0.0;

	//printf("%f porcento de %d é = %lf\n",(gamma * 100),(r->L * r->W),areaSerRemovida);

	srand((unsigned int)time(NULL));

	int indiceTipoPecaSerRemovida, indicePecaSerRemovida, count, iter = 0;

	NO *aux_B;
	NO_Pt *aux_pt1, *aux_pt2;
	PECA *novaPeca = criarPeca(0,0,0,0,0.0,0);

	//(PECA*) malloc(sizeof(PECA));
	
	//Evitar que aloquemos vários espaços de memórias desnecessários...
	//novaPeca->p1 = criarArrayPontosCandidatos();
	//novaPeca->p2 = criarArrayPontosCandidatos();

	while(areaJaRemovida < areaSerRemovida)
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

		//Copia tudo menos o array de pontos candidadatos.
		copiarPecaParaP(novaPeca, aux_B->peca);

		//Insere a nova peça em P.
		inserirPeca(P,novaPeca);

		//Remover a peça em R.
		despreencherR(r,aux_B->peca,aux_pt1->ponto,aux_pt2->ponto);

		//Remove a peça de B.
		removerPecaDadoPeca(B, aux_B->peca, aux_pt1->ponto,aux_pt2->ponto);
	}
}

//Função feita por Lívia.
/*Esta função ordena as peças presentes em R em uma lista ordenada pela distância da origem da peça em R até a origem e desloca-as
para o ponto candidato factível mais próximo da origem de R, dentre as peças já deslocadas.*/
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

		//aux = aux->proximo;
		aux = B->inicio;
	}
	
	PONTO_CANDIDATO *aux_ponto,*aux_pontoOp;
	/*
	for (count = 0; count < r->quantidade; count++)
	{
		//SÓ PARAR TESTES. RETIRAR DEPOIS
		aux_ponto = coordenadaOrigemPeca(&arrayPecas[count],arrayPecas[count].p1->inicio->ponto, arrayPecas[count].p2->inicio->ponto);
		arrayPecas[count].distOrg = distanciaEntreDoisPontos(aux_ponto->x,aux_ponto->y,0,0);
		//imprimirPeca(&arrayPecas[count]);
		//printf("DistOrg = %lf\n\n",arrayPecas[count].distOrg);

		//aux_origemOpostaPeca = coordenadaOrigemOpostaPeca(&arrayPecas[count - 1],arrayPecas[count - 1].p1->inicio->ponto,arrayPecas[count - 1].p2->inicio->ponto);
		//aux_origemPeca = coordenadaOrigemPeca(&arrayPecas[count],arrayPecas[count].p1->inicio->ponto,arrayPecas[count].p2->inicio->ponto);

	}
	*/

	//printf("-----------------------------------------------------------------------------\n\n");
	
	//Ordenação do vetor de acordo com a distância da origem da peça com (0,0).
	mergeSort(arrayPecas,0,r->quantidade - 1);

	 /*
	for (count = 0; count < r->quantidade; count++)
	{
		imprimirPeca(&arrayPecas[count]);
		//aux_ponto = coordenadaOrigemPeca(&arrayPecas[count],arrayPecas[count].p1->inicio->ponto, arrayPecas[count].p2->inicio->ponto);
		//aux_pontoOp = coordenadaOrigemOpostaPeca(&arrayPecas[count],arrayPecas[count].p1->inicio->ponto,arrayPecas[count].p2->inicio->ponto);
		//imprimirPontoCandidato(aux_ponto);
		//printf("\n");
		//imprimirPontoCandidato(aux_pontoOp);
		printf("DistOrg = %lf\n\n",arrayPecas[count].distOrg);
	}

	printf("\n\n");
	 */

/*----------------------------------------------------------------------------------------------------*/

	//Início do deslocamento das peças para esquerda e depois para cima.

	//Criar a nova lista B que será considerada.
	//LISTA_LIAGDA *novo_B = criarLista();
	PONTO_CANDIDATO *pontoEscolhido,*aux_pontoEscolhido,*aux_origemPeca;//, *aux_origemPeca,*aux_origemOpostaPeca;
	PECA *novaPecaB;
	int countB, indicePeca;

	//Guarda a menor distância da origem da peça até um ponto candidato.
	//double menorDistOrigem;

	//int iterTeste = 0;
	//double distPC, distPE;
	
	pontoEscolhido = (PONTO_CANDIDATO*)malloc(sizeof(PONTO_CANDIDATO));
	aux_pontoEscolhido = (PONTO_CANDIDATO*)malloc(sizeof(PONTO_CANDIDATO));
	//aux_origemPeca = (PONTO_CANDIDATO*)malloc(sizeof(PONTO_CANDIDATO));

	//Inicializando o ponto de origem.
	pontoEscolhido->x = 0;
	pontoEscolhido->y = 0;

	//Primeiro passo: deslocar a peça mais próxima da origem ao ponto de origem (0,0).

	//Determina o índice da peça a ser deslocada. Serve para preservar o índice da mesma já presente em R. 
	indicePeca = r->matriz[arrayPecas[0].p1->inicio->ponto->y][arrayPecas[0].p1->inicio->ponto->x];

	despreencherR(r,&arrayPecas[0],arrayPecas[0].p1->inicio->ponto,arrayPecas[0].p2->inicio->ponto);
	removerPontoCandidato(arrayPecas[0].p1);
	removerPontoCandidato(arrayPecas[0].p2);

	preencherRcomPeca(r,&arrayPecas[0],pontoEscolhido,indicePeca);

	inserirPeca(B,&arrayPecas[0]);

	pontoEscolhido->x = r->L + 1;
	pontoEscolhido->y = r->W + 1;

	//Segundo passo: deslocar as peças restantes de acordo com a ordem do vetor ordenado.
	for (count = 1; count < r->quantidade; count++)
	{
		indicePeca = r->matriz[arrayPecas[count].p1->inicio->ponto->y][arrayPecas[count].p1->inicio->ponto->x];

		//Verificar o ponto candidato mais próximo da origem dentre as peças anteriormente deslocadas na lista ordenada.
		despreencherR(r,&arrayPecas[count],arrayPecas[count].p1->inicio->ponto,arrayPecas[count].p2->inicio->ponto);

		//aux_origemPeca = coordenadaOrigemPeca(&arrayPecas[count],arrayPecas[count].p1->inicio->ponto,arrayPecas[count].p2->inicio->ponto);
		//printf("Origem peça atual:\n");
		//imprimirPontoCandidato(aux_origemPeca);

		//Varrendo as peças anteriormente deslocadas.
		for(countB = 0;countB < count;countB++)
		{
			/*----------------------------------------TESTES----------------------------------------------------------------------*/
			//printf("---------------------------------------Caso %d----------------------------------------------------------\n\n",iterTeste);

			//imprimirPontoCandidato(arrayPecas[countB].p1->inicio->ponto);
			//printf("\n");

			//distPC = distanciaEntreDoisPontos(arrayPecas[countB].p1->inicio->ponto->x,arrayPecas[countB].p1->inicio->ponto->y,0,0);
			//distPE = distanciaEntreDoisPontos(pontoEscolhido->x,pontoEscolhido->y,0,0);

			//printf("Distancia PC: %lf\n",distPC);
			//printf("Distancia PE: %lf\n",distPE);
			/*---------------------------------------------------------------------------------------------------------------------*/

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
				if(!(ehPossivelAdicionar(r, &arrayPecas[count], pontoEscolhido)) )
				{
					pontoEscolhido->x = aux_pontoEscolhido->x;
					pontoEscolhido->y = aux_pontoEscolhido->y;
				}
			}

			/*---------------------------------------------------------------------------------------------------------------------*/
			//imprimirPontoCandidato(arrayPecas[countB].p2->inicio->ponto);
			//printf("\n");

			//distPC = distanciaEntreDoisPontos(arrayPecas[countB].p2->inicio->ponto->x,arrayPecas[countB].p2->inicio->ponto->y,0,0);
			//distPE = distanciaEntreDoisPontos(pontoEscolhido->x,pontoEscolhido->y,0,0);

			//printf("Distancia PC: %lf\n",distPC);
			//printf("Distancia PE: %lf\n",distPE);
			/*---------------------------------------------------------------------------------------------------------------------*/

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

			//Variavel de teste.
			//iterTeste++;

			/*---------------------------------------------------------------------------------------------------------------------*/
			//printf("--------------------------------------------------------------------------------------------------------\n\n");
			/*---------------------------------------------------------------------------------------------------------------------*/
		}

		//printf("\n");
		//imprimirPontoCandidato(pontoEscolhido);
		//printf("\n");

		//Encontrado o ponto candidato mais próximo da origem, vamos inserir a peça atual neste ponto.
		//if(ehPossivelAdicionar(r, &arrayPecas[count], pontoEscolhido)) //SEMPRE VERDADEIRO!
		//{
		//Removendo os pontos desatualizados.
		removerPontoCandidato(arrayPecas[count].p1);
		removerPontoCandidato(arrayPecas[count].p2);

		//Preenchendo no ponto escolhido e atualizando(dentro da função) o ponto candidato atual.
		preencherRcomPeca(r,&arrayPecas[count],pontoEscolhido,indicePeca);

		//Inserindo a peça em B(que começou vazia).
		inserirPeca(B,&arrayPecas[count]);

		//Resetando o ponto escolhido
		pontoEscolhido->x = r->L + 1;
		pontoEscolhido->y = r->W + 1;

		//}
		//else
		//{
		//	printf("Parece que existiu um caso que invalidou sua ideia...Triste fim de algo brilhante :(\n\n");
		//	return;
		//}
	}

	free(pontoEscolhido);
	free(aux_pontoEscolhido);
	//free(aux_origemPeca);
	//free(B);
	//return novo_B;
}
//*/
//se não funcionar, dar varrer a matriz dando free
inline void apagarRetanguloR(R *r)
{
	free(r->matriz);
	/*free(r->W);
	free(r->L);*/

	free(r);

}


#endif
