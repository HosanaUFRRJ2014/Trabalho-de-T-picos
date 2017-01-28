#include <stdio.h>
#include <stdlib.h>
#include "arrayPontosCandidatos.h"
#include "ponto.h"
#define true 1
#define false 0

#ifndef PECA_H
#define PECA_H

//comprimento l e largura w, 
//v o valor da peça.
//P e Q representam a quantidade mínima e máxima, respectivamente, de cada peça.
typedef struct             
{						   
	int l;	//na horizontal  (Não concordo, mas é como está no artigo.)
	int w; //na vertical
	int P; //qtd mínima
	int Q; //qtd máxima
	float v;
	int quantidade;   //quantidade existente da peça
	ARRAY_PONTOS_CANDIDATOS *p1; //mais a direita e mais acima
	ARRAY_PONTOS_CANDIDATOS *p2; //mais a esquerda e mais abaixo
}PECA;

//criar peca de um determinado tipo.
inline PECA *criarPeca(int l, int w, int P, int Q, float v, int qtd)
{
	PECA *i = (PECA *) malloc(sizeof(PECA));

	if(i != NULL)
	{
		i->l = l;
		i->w = w;
		i->P = P;
		i->Q = Q;
		i->v = v;
		i->p1 = criarArrayPontosCandidatos();
		i->p2 = criarArrayPontosCandidatos();
		i->quantidade = qtd;
	}

	return i;
}

//verificar se são peças iguais. Se sim, retornar true. Caso contrário, retornar false.
inline int pecasIguais(PECA *x, PECA *y)
{
	if(x->l == y->l && x->w == y->w && x->P == y->P && x->Q == y->Q && x->v == y->v)
		return true;

	return false;
}

//dado uma peca a, verificar se esta é maior que a peca b, seguindo os critérios de majoritariedade do artigo 
inline int pecaMaior(PECA *a, PECA *b)
{
	if(( (float)a->v/(a->l * a->w) ) > ( (float)b->v/(b->l * b->w) ) )
		return true;

	return false;
}

inline void custoBeneficio(PECA *a)
{
	printf("Custo beneficio da peça(v/l*w): %f\n", (float) a->v/(a->l * a->w));	
}

//função para copiar os valores de uma peca para a outra, Só que a qtd de destino é setada para 1
inline void copiarPeca(PECA *pecaDestino, PECA *pecaOrigem)
{
	pecaDestino->l = pecaOrigem->l;
	pecaDestino->w = pecaOrigem->w;
	pecaDestino->P = pecaOrigem->P;
	pecaDestino->Q = pecaOrigem->Q;
	pecaDestino->v = pecaOrigem->v;
	
	//pertence a arrayPontoCandidato.h **
	//cópia dos pontos candidatos de pecaOrigem para pecaDestino
	NO_Pt *aux_Pt1;
	pecaDestino->p1 = criarArrayPontosCandidatos();
	aux_Pt1 = pecaOrigem->p1->inicio;

	NO_Pt *aux_Pt2;
	pecaDestino->p2 = criarArrayPontosCandidatos();
	aux_Pt2 = pecaOrigem->p2->inicio;

	while(aux_Pt1 != NULL && aux_Pt2 != NULL)
	{
		inserirPontoCandidato(pecaDestino->p1, criarPontoCandidato(aux_Pt1->ponto->x, aux_Pt1->ponto->y) );
		aux_Pt1 = aux_Pt1->proximo;

		inserirPontoCandidato(pecaDestino->p2, criarPontoCandidato(aux_Pt2->ponto->x, aux_Pt2->ponto->y) );
		aux_Pt2 = aux_Pt2->proximo;		
	}

	pecaDestino->quantidade = pecaOrigem->quantidade;

	free(aux_Pt1);
	free(aux_Pt2);
	//**
}

inline void apagarPeca(PECA **p)
{
	//apagarArrayPontosCandidatos( &p->(&p1),&p.(&p2) );
	free(*p);
}

inline void imprimirPeca(PECA *p)
{
	printf("Quantidade: %d\n", p->quantidade);
	printf("largura(w): %d\n", p->w);
	printf("comprimento(l): %d\n",p->l);
	printf("qtd min(P): %d\n",p->P );
	printf("qtd max(Q): %d\n",p->Q );
	printf("valor da peca(v): %f\n",p->v);
	printf("pontos candidatos p1:\n");
	imprimirArrayPontosCandidatos(p->p1);
	printf("pontos candidatos p2:\n");
	imprimirArrayPontosCandidatos(p->p2);
	printf("\n");
}

//Copia uma peça, mas deixa de copiar os arrays de pontos candidatos. Necessário para inserir esta peça em P novamente.
//Usada na função "remocaoAleatoria" de R.h.
inline void copiarPecaParaP(PECA *pecaDestino, PECA *pecaOrigem)
{
	pecaDestino->l = pecaOrigem->l;
	pecaDestino->w = pecaOrigem->w;
	pecaDestino->P = pecaOrigem->P;
	pecaDestino->Q = pecaOrigem->Q;
	pecaDestino->v = pecaOrigem->v;
	
	pecaDestino->quantidade = 1;
}

inline PONTO_CANDIDATO* coordenadaOrigemPeca(PECA *peca, PONTO_CANDIDATO *p1, PONTO_CANDIDATO *p2)
{
	PONTO_CANDIDATO *origemPeca = criarPontoCandidato(-1,-1);

	origemPeca->x = p1->x - (peca->l - 1);
	origemPeca->y = p1->y;

	if(origemPeca->x >= 0 && origemPeca->y >= 0)
		return origemPeca;
	else
	{
		origemPeca->x = -1;
		origemPeca->y = -1;
		return origemPeca;
	}
}

//Para ordenar as peças de acordo com a distância até a origem.
inline void mergeSort(PECA *vetor, int posicaoInicio, int posicaoFim) 
{
    int i, j, k, metadeTamanho;
    PECA *vetorTemp;

    if(posicaoInicio == posicaoFim) 
    	return;
   
    //ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
   
    mergeSort(vetor, posicaoInicio, metadeTamanho);
    mergeSort(vetor, metadeTamanho + 1, posicaoFim);

    //intercalacao no vetor temporario t
    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;

    vetorTemp = (PECA *) malloc(sizeof(PECA) * (posicaoFim - posicaoInicio + 1));
    double distI, distJ;

    while(i < metadeTamanho + 1 || j  < posicaoFim + 1) 
    {
        // i passou do final da primeira metade, pegar v[j]
        if (i == metadeTamanho + 1 ) 
        { 
            vetorTemp[k] = vetor[j];
            j++;
            k++;
        }

        else 
        {
            // j passou do final da segunda metade, pegar v[i]
            if (j == posicaoFim + 1) 
            { 
                vetorTemp[k] = vetor[i];
                i++;
                k++;
            }
        
            else 
            {

                PONTO_CANDIDATO *aux_origemPecaI = coordenadaOrigemPeca(&vetor[i],vetor[i].p1->inicio->ponto,vetor[i].p2->inicio->ponto);
            	PONTO_CANDIDATO *aux_origemPecaJ = coordenadaOrigemPeca(&vetor[j],vetor[j].p1->inicio->ponto,vetor[j].p2->inicio->ponto);
                distI = distanciaEntreDoisPontos(aux_origemPecaI->x,aux_origemPecaI->y,0,0); 
            	distJ = distanciaEntreDoisPontos(aux_origemPecaJ->x,aux_origemPecaJ->y,0,0);

                if(distI < distJ) 
                {
                    vetorTemp[k] = vetor[i];
                    i++;
                    k++;
                }
                
                else 
                {
                    vetorTemp[k] = vetor[j];
                    j++;
                    k++;
                }
            }
        }

    }

    // copia vetor intercalado para o vetor original
    for(i = posicaoInicio; i <= posicaoFim; i++) 
    {
        vetor[i] = vetorTemp[i - posicaoInicio];
    }

    free(vetorTemp);
    vetorTemp = NULL;
}

#endif
