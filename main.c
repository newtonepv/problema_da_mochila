#include "forca_bruta.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>

struct item{
    float peso;
    float valor;
};

void exibe_itens(ITEM **itens, int n);
void libera_itens(ITEM **itens, int n);


int main(){

    int qtdItens;
    float *pesos, *valores;

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

    exibe_itens(itens, qtdItens);
    libera_itens(itens, qtdItens);
    
    return 0;

    qtdItens = 3;
    pesos = malloc(sizeof(int)*qtdItens);
    valores = malloc(sizeof(int)*qtdItens);
    pesos[0]=1;pesos[1]=1;pesos[2]=2;
    valores[0]=200;valores[1]=300;valores[2]=300;

    int* mochila = malloc(sizeof(int)*qtdItens);
    //printf("%d", organizar_mochila(pesos,valores, 2,mochila,2,0,0,0));
    printf(" %d, %d", mochila[0],mochila[1]);

    free(pesos);
    free(valores);
    free(mochila);
    return 0;
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