// #include "forca_bruta.h"
#include "item.h"
#include "mochila.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 5000

struct item{
    float peso;
    float valor;
};

struct mochila{
    float peso;
    float capacidade;
    float valortotal;
    int tam;
    ITEM *itens[MAX];
};
void exibe_itens(ITEM **itens, int n);
void libera_itens(ITEM **itens, int n);
void forca_bruta(MOCHILA *mochila, ITEM **itens, int n);
void mochila_forca_bruta(MOCHILA *mochila_original, ITEM **itens, int n);

int main(){

    int qtdItens;
    float capacidade;
    //float *pesos, *valores;

    printf("Digite a capacidade da mochila: ");
    scanf("%f", &capacidade);
    MOCHILA *mochila = mochila_criar(capacidade);
    printf("Digite quantos itens serão inseridos: ");
    scanf("%i", &qtdItens);

    float w, v;

    ITEM **itens = malloc(sizeof(ITEM*) * qtdItens);
    if (itens == NULL) return -1;

    for(int i = 0; i < qtdItens; i++)
    {
        scanf("%f %f", &w, &v);
        itens[i] = item_criar(w, v);
    }

    mochila_forca_bruta(mochila, itens, qtdItens);
    //exibe_itens(itens, qtdItens);
    //libera_itens(itens, qtdItens);
    
    return 0;

    //qtdItens = 3;
    //pesos = malloc(sizeof(int)*qtdItens);
    //valores = malloc(sizeof(int)*qtdItens);
    //pesos[0]=1;pesos[1]=1;pesos[2]=2;
    //valores[0]=200;valores[1]=300;valores[2]=300;

    //int* mochila = malloc(sizeof(int)*qtdItens);
    //printf("%d", organizar_mochila(pesos,valores, 2,mochila,2,0,0,0));
    //printf(" %d, %d", mochila[0],mochila[1]);

    //free(pesos);
    //free(valores);
    //free(mochila);
    //return 0;
}

void exibe_itens(ITEM **itens, int n)
{
    printf("---------- ITENS ----------\n");
    for(int i = 0; i < n; i++)
    {
        printf("item [%i]: \n", i);
        printf("Peso: %.2f\nValor: %.2f\n", item_get_peso(itens[i]), item_get_valor(itens[i]));
    }
}

void libera_itens(ITEM **itens, int n)
{
    for(int i = 0; i < n; i++)
    {
        free(itens[i]);
        itens[i] = NULL;
    }
    free(itens);
    itens = NULL;
    return;
}

void forca_bruta(MOCHILA *mochila_original, ITEM **itens, int n)
{
    // A melhor combinacao vai ser armazenada num array de itens
    ITEM *melhor_combinacao[n];

    int total = 1 << n;

    // O que vai definir se a combinação é a memlhor possível é se ela tem mais valor e cabe na mochila
    float melhor_peso = 0;
    float melhor_valor = 0;
    // Os novos melhores serao encontrados com um IF, se forem maiores que o antigo maior e couber na mochila
    // trocaremos os melhores valores e o array de itens melhor_combinação

    // Precisamos agora de um array de itens com TODAS as combinações de itens
    ITEM *combinacoes[total];

    // Agora precisamos adicionar todas as combinações possíveis
    // Eis o problema: Como faremos isso?
}
