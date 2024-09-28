#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct item{
    float peso;
    float valor;
};

ITEM *item_criar(float peso, float valor)
{
    if (peso < 0 || valor < 0) return NULL;
    
    ITEM *item = (ITEM*) malloc(sizeof(ITEM));

    if (item == NULL) return NULL;
    item->peso = peso;
    item->valor = valor;
    return item;
}

bool item_apagar(ITEM **item)
{
    if (*item == NULL) return false;
    free(*item);
    *item = NULL;
    return true;
}

float item_get_peso(ITEM *item)
{
    if (item == NULL) return -1;

    return item->peso;
}

float item_get_valor(ITEM *item)
{
    if (item == NULL) return -1;

    return item->valor;
}

float item_raciona(ITEM *item)
{
    if (item == NULL || item->peso == 0) return -1;

    return item->valor / item->peso;
}