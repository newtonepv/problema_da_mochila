#include "mochila.h"
#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 5000

struct mochila{
    float peso;
    float capacidade;
    float valortotal;
    int tam;
    ITEM *itens[MAX];
};

MOCHILA *mochila_criar(float capacidade)
{
    MOCHILA *mochila = (MOCHILA *) malloc(sizeof(MOCHILA));
    if (mochila == NULL) return NULL;

    mochila->peso = 0;
    mochila->tam = 0;
    mochila->valortotal = 0;
    mochila->capacidade = capacidade;
    return mochila;
}

bool mochila_push(MOCHILA *mochila, ITEM *item)
{
    if (mochila == NULL || item == NULL) return false;

    if (mochila->peso + item_get_peso(item) < mochila->capacidade)
    {
        mochila->itens[mochila->tam++] = item;
        mochila->valortotal += item_get_valor(item);
        mochila->peso += item_get_peso(item);
        return true;
    }
    else return false;
}

ITEM *mochila_pop(MOCHILA *mochila)
{
    if (mochila == NULL) return NULL;

    mochila->tam--;
    mochila->peso -= item_get_peso(mochila->itens[mochila->tam]);
    mochila->valortotal -= item_get_valor(mochila->itens[mochila->tam]);
    return mochila->itens[mochila->tam]; 
}

