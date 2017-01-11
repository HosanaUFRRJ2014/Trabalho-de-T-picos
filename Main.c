#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "includes.h"
#include "heuristicas/heuristicas.h"

#define TAM_PECAS 6

//Escolha o índice referente ao elemento.
#define ESCOLHA_PECA 0
#define ESCOLHA_PC 1

//Função para a validação dos parãmetros inseridos pelo usuário
inline void validar(char const *argv[])
{
    if(argv[1] == NULL ||argv[2] == NULL || argv[3] == NULL || argv[4] == NULL || argv[5] == NULL)
    {
        printf("\n|                                UM ERRO OCORREU!                                |\n");

        printf("\n\nCausa: Existe pelo menos 1 (um) parâmetro faltando. Por favor, verifique a quantidade digitada e tente novamente.\n");
        printf("\n-------------> Parâmetros requeridos <-------------\n");
        printf("Diretório do arquivo que contém a instância de teste\n"); //Tinha posto nome, mas lembrei do William e mudei pra diretório :D
        printf("Temperatura inicial (T)\n");
        printf("Temperatura de congelamento (T_c)\n");
        printf("Número máximo de iterações (It_max)\n");
        printf("Taxa de resfriamento (alpha) \n\n");
        exit(1);

    }

}

inline void imprimirValoresSimmulatedAnnealing();

int main(int argc, char const *argv[])
{

    validar(argv);

    //instância a ser lida do arquivo passado como parâmetro para o programa
    FILE *inst = fopen(argv[1],"r");
    if(inst == NULL)
    {
        printf("\n|                                UM ERRO OCORREU!                                |\n");
        printf("Arquivo %s não encontrado.\n",argv[1]);
        exit(1);
    }

    //Variáveis de entrada para o SA, recebidas como parâmetro para a aplicação

    float T = (float) atof(argv[2]);
    float T_c = (float) atof(argv[3]);
    int It_max = atoi(argv[4]);
    float alpha = (float) atof(argv[5]);

     imprimirParametrosDeEntradaSA(T, T_c, It_max, alpha);

    R *r = NULL;
    LISTA_LIGADA *P = criarLista(), *B = criarLista();
    int qtd_pecas, valor_otimo, i = 0, num_inst = 0, L, W;
    int *valores_otimos;

    leitura_instancia(inst,&L, &W, &qtd_pecas, &valor_otimo);

    r = criarRetanguloR(L,W);
    
    for(i = 0;i < qtd_pecas;i++)
        leitura_peca(inst, P);
    

    //---------Imprimindo P e B da instância lida---------
    
    /*
    printf("---------------Lista P inst ----------------------------\n");
    imprimirLista(P);
    printf("--------------------------------------------------------\n");
    printf("---------------Lista B inst ----------------------------\n");
    imprimirLista(B);
    printf("--------------------------------------------------------\n\n");
    */
    //----------------------------------------------------

    //Para seed dos aleatórios.
    srand(time(NULL));

    double tempo = 0;

    //valores que os autores do artigo usaram:
    //resultados[num_inst] = Simulated_Annealing(10000.0,0.11,700,0.98,ret,P,B);
    float resultado = Simulated_Annealing(T,T_c,It_max,alpha,r,P,B,&tempo);
    imprimirR(r);
    printf("Solução encontrada: %.2f\n",resultado);
    printf("Solução ótima: %d\n\n",valor_otimo);
    printf("Tempo para encontrar a solução: %f\n",tempo);
    printf("-------Lista B------\n");
    imprimirLista(B);
    

    /*
    criarSolucao(r,P,B);

    printf("-------------------criarSolucao()---------------------------\n");
    imprimirR(r->matriz,r->L,r->W);
    */  

     //---------Imprimindo P e B(criarSolucao())---------
    
    /*
    printf("---------------Lista P criarSolucao----------------------------\n");
    imprimirLista(P);
    printf("---------------------------------------------------------------\n");
    printf("---------------Lista B criarSolucao----------------------------\n");
    imprimirLista(B);
    printf("-------------------------------------------------------------\n\n");
    */
    
    //----------------------------------------------------

    //-------------Escolhendo peças e PC específicos na lista B-----------
    /*
    NO *aux = B->inicio;
    NO_Pt *aux_pt1,*aux_pt2;

    for (i = 0; i < ESCOLHA_PECA; i++)
    {
        aux = aux->proximo;
    }

    aux_pt1 = aux->peca->p1->inicio;
    aux_pt2 = aux->peca->p2->inicio;

    for(i = 0; i < ESCOLHA_PC; i++)
    {
        aux_pt1 = aux_pt1->proximo;
        aux_pt2 = aux_pt2->proximo;
    }
    */
    //--------------------------------------------------------------------

    //-----------Em R.h-----------------------
    /*
    remocaoAleatoria(r,P,B,0.35);

    printf("-------------------remocaoAleatoria()---------------------------\n");
    imprimirR(r);

    //---------Imprimindo P e B(remocaoAleatoria())---------    
    printf("---------------Lista P remocaoAleatoria----------------------------\n");
    imprimirLista(P);
    printf("-------------------------------------------------------------------\n");
    printf("---------------Lista B remocaoAleatoria----------------------------\n");
    imprimirLista(B);
    printf("-----------------------------------------------------------------\n\n");

    deslocarPecas(r,B);

    printf("-------------------deslocarPecas()---------------------------\n");
    imprimirR(r);

    //---------Imprimindo P e B(deslocarPecas())---------    
    printf("---------------Lista P deslocarPecas-------------------------------\n");
    imprimirLista(P);
    printf("-------------------------------------------------------------------\n");
    printf("---------------Lista B deslocarPecas-------------------------------\n");
    imprimirLista(B);
    printf("-----------------------------------------------------------------\n\n");
    */
    //----------------------------------------------------

    //-----------------------------------------
    //*/

    printf("--------------------------------------------------------------------------------------------------------------------\n\n");

    fclose(inst);
    apagarLista(&P);
    apagarLista(&B);
    free(P);
    free(B);
    
    return 0;
}
