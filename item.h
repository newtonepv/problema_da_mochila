#ifndef ITEM_
    #define ITEM_
    #include <stdbool.h>

    typedef struct item ITEM;

    ITEM *item_criar(float peso, float valor);
    bool item_apagar(ITEM **item);
    float item_get_peso(ITEM *item);
    float item_get_valor(ITEM *item);
    float item_raciona(ITEM *item);

#endif