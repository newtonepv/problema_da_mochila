#include "forca_bruta.h"
#include <stdio.h>
#include <stdlib.h>
int main(){
    int qtdItens = 3;
    
    int* pesos = malloc(sizeof(int)*qtdItens);
    int* valores = malloc(sizeof(int)*qtdItens);
    pesos[0]=1;pesos[1]=1;pesos[2]=2;
    valores[0]=200;valores[1]=300;valores[2]=300;

    int* mochila = malloc(sizeof(int)*qtdItens);
    printf("%d", organizar_mochila(pesos,valores, 2,mochila,2,0,0,0));
    printf(" %d, %d", mochila[0],mochila[1]);
    return 0;
}