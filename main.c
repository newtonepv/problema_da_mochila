// #include "forca_bruta.h"
#include "item.h"
#include "mochila.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 5000
#define INFINITY 9999999.9

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
void forca_bruta(MOCHILA *mochila_original, ITEM **itens, int n);
void greedy(MOCHILA *mochila_original, ITEM **itens, int n);
void copiar_mochila(MOCHILA *destino, MOCHILA *origem);

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

    //forca_bruta(mochila, itens, qtdItens);
    greedy(mochila, itens, qtdItens);
    libera_itens(itens, qtdItens);
    
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

void copiar_mochila(MOCHILA *destino, MOCHILA *origem) {
    destino->peso = origem->peso;
    destino->valortotal = origem->valortotal;
    destino->tam = origem->tam;
    for (int i = 0; i < origem->tam; i++) {
        destino->itens[i] = origem->itens[i];
    }
}

void greedy(MOCHILA *mochila_original, ITEM **itens, int n)
{
    while (mochila_original->peso < mochila_original->capacidade) {
        ITEM *melhoritem = NULL;
        int melhor_index = -1;
        
        for (int i = 0; i < n; i++) {
            if (itens[i] != NULL) {
                if (melhoritem == NULL || item_raciona(itens[i]) > item_raciona(melhoritem)) {
                    melhoritem = itens[i];
                    melhor_index = i;
                }
            }
        }
        //printf("\n\nMELHOR ITEM: Peso: %.2f Valor: %.2f\n", melhoritem->peso, melhoritem->valor);
        if (melhoritem == NULL) {
            break;
        }
        mochila_push(mochila_original, melhoritem);
        itens[melhor_index] = NULL;
    }

    printf("Melhor valor encontrado: %.2f\n", mochila_original->valortotal);
    printf("Peso da melhor combinacao: %.2f\n", mochila_original->peso);
    printf("Itens na melhor combinacao:\n");
    for (int i = 0; i < mochila_original->tam; i++) {
        printf("Item %d - Peso: %.2f, Valor: %.2f\n", i + 1, mochila_original->itens[i]->peso, mochila_original->itens[i]->valor);
    }
}
void forca_bruta(MOCHILA *mochila_original, ITEM **itens, int n)
{
    // Aqui nós criamos a mochila que será a melhor mochila. Inicialmente ela terá a mesma capacidade que a mochila que foi enviada
    // mas os outros atributos são zerados no começo.
    MOCHILA melhor_mochila = {0, mochila_original->capacidade, 0, 0, {NULL}};

    //Testa todas as combinações possiveis com AND binário
    for (int mascara = 0; mascara < (1 << n); mascara++) {
        MOCHILA combinacao_atual = {0, mochila_original->capacidade, 0, 0, {NULL}};

        for (int i = 0; i < n; i++) {
            if (mascara & (1 << i)) {
                combinacao_atual.peso += itens[i]->peso;
                combinacao_atual.valortotal += itens[i]->valor;
                combinacao_atual.itens[combinacao_atual.tam++] = itens[i];
            }
        }

        // Verifica se a mochila é válida e se é melhor que a antiga melhor
        if (combinacao_atual.peso <= mochila_original->capacidade && combinacao_atual.valortotal > melhor_mochila.valortotal) {
            copiar_mochila(&melhor_mochila, &combinacao_atual);
        }
    }

    printf("Melhor valor encontrado: %.2f\n", melhor_mochila.valortotal);
    printf("Peso da melhor combinacao: %.2f\n", melhor_mochila.peso);
    printf("Itens na melhor combinacao:\n");
    for (int i = 0; i < melhor_mochila.tam; i++) {
        printf("Item %d - Peso: %.2f, Valor: %.2f\n", i, melhor_mochila.itens[i]->peso, melhor_mochila.itens[i]->valor);
    }
}