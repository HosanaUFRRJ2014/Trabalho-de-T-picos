#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "includes.h"
#include "heuristicas/heuristicas.h"

#define TAM_PECAS 6

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

    //Instância a ser lida do arquivo passado como parâmetro para o programa
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
    
    //Para seed dos aleatórios.
    srand(time(NULL));

    double tempo = 0;

    float resultado = Simulated_Annealing(T,T_c,It_max,alpha,r,P,B,&tempo);
    imprimirR(r);
    printf("Solução encontrada: %.2f\n",resultado);
    printf("Solução ótima: %d\n\n",valor_otimo);
    printf("Tempo para encontrar a solução: %f\n",tempo);
 
    printf("----------------------------------------------------------------------------------------------------------------------\n\n");

    fclose(inst);
    apagarLista(&P);
    apagarLista(&B);
    free(P);
    free(B);
    
    return 0;
}
