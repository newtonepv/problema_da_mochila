#ifndef MOCHILA_
    #define MOCHILA_
    #include "item.h"

    typedef struct mochila MOCHILA;

    MOCHILA *mochila_criar(float capacidade);
    bool mochila_push(MOCHILA *mochila, ITEM *item);
    ITEM *mochila_pop(MOCHILA *mochila);
    void mochila_exibir(MOCHILA *mochila);
    bool mochila_excluir(MOCHILA **mochila);
    

#endif