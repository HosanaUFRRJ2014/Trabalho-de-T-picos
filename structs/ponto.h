#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define true 1
#define false 0

#ifndef PONTO_CANDIDATO_H
#define PONTO_CANDIDATO_H

/*Definição da struct para pontos canditatos.
	Lembrando que:
	P1 é o ponto mais à direita e mais acima em relação a R
	P2 é o ponto mais à esquerda e mais abaixo em relação a R
*/

typedef struct
{
	int x;
	int y;
	
}PONTO_CANDIDATO;

//criar struct ponto candidato. Inicialmente ao ser definido em peça, ele será (-1,-1), pois não estará definido em relação a R.
inline PONTO_CANDIDATO *criarPontoCandidato(int x, int y)
{
	PONTO_CANDIDATO *p = (PONTO_CANDIDATO *) malloc(sizeof(PONTO_CANDIDATO));

	if(p != NULL)
	{
		p->x = x;
		p->y = y;
	} 

	return p;
}

//função para a verificação de existencia de ponto. Para os casos em que podem não existir p1 ou p2 pois os mesmos ultrapassariam W e/ou L de R
inline int ehPontoCandidato(PONTO_CANDIDATO *p)
{

if(p != NULL)
{
	if(p->x != -1 && p->y != -1)
		return true;
}
    

	return false;
}

//função para a verificação do ponto mais próximo da origem (0,0)
inline PONTO_CANDIDATO * primeiroPontoFactivel(PONTO_CANDIDATO * a, PONTO_CANDIDATO *b)
{
	//otimizar esse trecho
	// se nenhum dos dois é ponto candidato. Existem peças que podem não ter um pt. cand. ou não ter os dois.
	if(!ehPontoCandidato(a) && !ehPontoCandidato(b)) // ( !(P || Q) ) equiv. a (!P && !Q) 
	 	return NULL;

	//se apenas um dos dois não for
	if(!ehPontoCandidato(a))
		return b;
	
	if(!ehPontoCandidato(b))
		return a;
	//fim do trecho

	//se 'a' está mais próximo da origem que 'b'
	if( sqrt(pow(a->x,2) + pow(a->y,2)) <= sqrt(pow(b->x,2) + pow(b->y,2)) )
		return a;
	else
		return b;

}

inline void imprimirPontoCandidato(PONTO_CANDIDATO *p)
{
	if(p == NULL)
	{
		printf("x: -1\n");
		printf("y: -1\n");

	}
	else
	{
		printf("x: %d\n", p->x);
		printf("y: %d\n",p->y);
	}

}

//Função feita por Lívia.
inline double distanciaEntreDoisPontos(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow((x1 - x2),2) + pow((y1 - y2),2)));
}

#endif