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

	//SÓ PARA TESTES. RETIRAR DEPOIS!
	//double distOrg;
	//------------------------------

}PECA;

//criar peca de um determinado tipo.
inline PECA *criarPeca(int l, int w, int P, int Q, float v, int qtd)
{
	PECA *i = (PECA *) malloc(sizeof(PECA));

	if(i != NULL /*&& (qtd >= P && qtd <= Q)*/)
	{
		i->l = l;
		i->w = w;
		i->P = P;
		i->Q = Q;
		i->v = v;
		i->p1 = criarArrayPontosCandidatos();
		i->p2 = criarArrayPontosCandidatos();
		i->quantidade = qtd;

		//SÓ PARA TESTES. RETIRAR DEPOIS!
		//i->distOrg = 0;
		//-------------------------------
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
	float f = (float) a->v/(a->l * a->w);
	printf("Custo beneficio da peça(v/l*w): %f\n", f);
	
}

//função para copiar os valores de uma peca para a outra, Só que a qtd de destino é setada para 1
//Organizar tudo em seus devidos lugares!!!
inline void copiarPeca(PECA *pecaDestino, PECA *pecaOrigem)
{
	pecaDestino->l = pecaOrigem->l;
	pecaDestino->w = pecaOrigem->w;
	pecaDestino->P = pecaOrigem->P;
	pecaDestino->Q = pecaOrigem->Q;
	pecaDestino->v = pecaOrigem->v;
	pecaDestino->p1 = criarArrayPontosCandidatos();
	
	//pertence a arrayPontoCandidato.h **
	NO_Pt *aux_Pt1;
	aux_Pt1 = pecaOrigem->p1->inicio;
	while(aux_Pt1 != NULL)
	{
		PONTO_CANDIDATO *novo;
		novo = criarPontoCandidato(aux_Pt1->ponto->x, aux_Pt1->ponto->y);
		inserirPontoCandidato(pecaDestino->p1,novo);

		aux_Pt1 = aux_Pt1->proximo;
	}

	pecaDestino->p2 = criarArrayPontosCandidatos();
	NO_Pt *aux_Pt2;
	aux_Pt2 = pecaOrigem->p2->inicio;
	while(aux_Pt2 != NULL)
	{
		PONTO_CANDIDATO *novo;
		novo = criarPontoCandidato(aux_Pt2->ponto->x, aux_Pt2->ponto->y);
		inserirPontoCandidato(pecaDestino->p2,novo);

		aux_Pt2 = aux_Pt2->proximo;
	}

	pecaDestino->quantidade = pecaOrigem->quantidade;

	//**

}

inline void imprimirPeca(PECA *p)
{
	printf("Quantidade: %d\n", p->quantidade);
	printf("largura(w): %d\n", p->l);
	printf("comprimento(l): %d\n",p->w );
	printf("qtd min(P): %d\n",p->P );
	printf("qtd max(Q): %d\n",p->Q );
	printf("valor da peca(v): %f\n",p->v);
	printf("pontos candidatos p1:\n");
	imprimirArrayPontosCandidatos(p->p1);
	printf("pontos candidatos p2:\n");
	imprimirArrayPontosCandidatos(p->p2);
	printf("\n");
}

/*Função feita por Lívia*/
//Copia uma peça, mas deixa de copiaos arrays de pontos candidatos. Necessario para inserir esta peça em P novamente.
//Usada na função "remocaoAleatoria" de R.h.
inline void copiarPecaParaP(PECA *pecaDestino, PECA *pecaOrigem)
{
	pecaDestino->l = pecaOrigem->l;
	pecaDestino->w = pecaOrigem->w;
	pecaDestino->P = pecaOrigem->P;
	pecaDestino->Q = pecaOrigem->Q;
	pecaDestino->v = pecaOrigem->v;
	
	//if(pecaDestino->p1 == NULL && pecaDestino->p1 == NULL)
	//{
	//	pecaDestino->p1 = criarArrayPontosCandidatos();
	//	pecaDestino->p2 = criarArrayPontosCandidatos();
	//}

	pecaDestino->quantidade = 1;
}

/*Função feita por Lívia.*/
inline PONTO_CANDIDATO* coordenadaOrigemPeca(PECA *peca, PONTO_CANDIDATO *p1, PONTO_CANDIDATO *p2)
{
	PONTO_CANDIDATO *origemPeca = criarPontoCandidato(-1,-1);
	/*
	origemPeca->x = p2->y - (peca->w - 1);
	origemPeca->y = p1->x - (peca->l - 1);
	*/

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


/*Função feita por Lívia.
inline PONTO_CANDIDATO* coordenadaOrigemOpostaPeca(PECA *peca, PONTO_CANDIDATO *p1, PONTO_CANDIDATO *p2)
{
	//PONTO_CANDIDATO *origemPeca = coordenadaOrigemPeca(peca,p1,p2);
	PONTO_CANDIDATO *origemOpostaPeca = criarPontoCandidato(-1,-1);

	origemOpostaPeca->x = p1->x;
	origemOpostaPeca->y = p1->y + (peca->w - 1);

	//PONTO_CANDIDATO *origemOpostaPeca = criarPontoCandidato(origemPeca->x + (peca->l - 1),origemPeca->y + (peca->w - 1));

	return origemOpostaPeca;
}
*/

/*Função feita por Lívia.*/
/*
void definirPontoCandidato(PONTO_CANDIDATO *ondeInseriuP1,PONTO_CANDIDATO *ondeInseriuP2,PECA *pecaInserida,PONTO_CANDIDATO *destinoP1,PONTO_CANDIDATO *destinoP2)
{
	if(ondeInseriuP1 != NULL)
	{
		destinoP1->x = ondeInseriuP1->x + pecaInserida->l;
		destinoP1->y = ondeInseriuP1->y;
		destinoP2->x = ondeInseriuP1->x + 1;
		destinoP2->y = ondeInseriuP1->y + (pecaInserida->w - 1);

		return;
	}
	else if(ondeInseriuP2 != NULL)
	{
		destinoP1->x = ondeInseriuP2->x + (pecaInserida->l - 1);
		destinoP1->y = ondeInseriuP2->y + 1;
		destinoP2->x = ondeInseriuP2->x;
		destinoP2->y = ondeInseriuP2->y + pecaInserida->w;

		return;
	}

	printf("Os dois são null! Reveja os parâmetros.\n");
	return;
}
*/

//Função feita por Lívia.
//Para ordenar as peças de acordo com a distância até a origem.
inline void mergeSort(PECA *vetor, int posicaoInicio, int posicaoFim) 
{
	//aux_origemPeca = coordenadaOrigemPeca(aux->peca,aux_pt1->ponto,aux_pt2->ponto);
	//sqrt(pow(aux_origemPeca->x,2) + pow(aux_origemPeca->y,2));
    int i, j, k, metadeTamanho;
    PECA *vetorTemp;

    if(posicaoInicio == posicaoFim) 
    	return;
   
    // ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
   
    mergeSort(vetor, posicaoInicio, metadeTamanho);
    mergeSort(vetor, metadeTamanho + 1, posicaoFim);


    // intercalacao no vetor temporario t
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
            	//distI = sqrt(pow(aux_origemPecaI->x,2) + pow(aux_origemPecaI->y,2)); 
            	//distJ = sqrt(pow(aux_origemPecaJ->x,2) + pow(aux_origemPecaJ->y,2));
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
}


#endif
