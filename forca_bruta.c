#include <stdlib.h>
#include <stdio.h>
#include "forca_bruta.h"

// Função auxiliar para copiar arrays
void copiar_array(int* destino, int* origem, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        destino[i] = origem[i];
    }
}

int organizar_mochila(int* pesos, int* valores, int qtdItens, int* mochila, 
                      int capacidade, int passados, int valor, int ocupados) {
    
    printf("chamou\n");
    
    // Condição de parada: se a capacidade é menor ou não há mais itens
    if (capacidade < 0) {
        return -1; // Capacidade negativa indica uma solução inválida
    }
    
    if (passados >= qtdItens) {
        return valor; // Não há mais itens para processar
    }

    // Aloca memória para mochilas temporárias
    int* com = malloc(sizeof(int) * qtdItens);
    int* sem = malloc(sizeof(int) * qtdItens);

    // Copia o conteúdo da mochila atual para as novas mochilas
    copiar_array(com, mochila, qtdItens);
    copiar_array(sem, mochila, qtdItens);

    // Adiciona o item atual (ID) à mochila "com"
    com[ocupados] = passados;

    // Chama recursivamente com e sem o item atual
    int i1 = organizar_mochila(pesos, valores, qtdItens, com, 
                               capacidade - pesos[passados], 
                               passados + 1, valor + valores[passados], ocupados + 1);

    int i2 = organizar_mochila(pesos, valores, qtdItens, sem, 
                               capacidade, passados + 1, valor, ocupados);

    // Escolhe a solução de maior valor
    int maior_valor;
    if (i1 > i2) {
        maior_valor = i1;
        copiar_array(mochila, com, qtdItens); // Atualiza a mochila com os IDs da melhor solução
    } else {
        maior_valor = i2;
    }

    // Libera a memória alocada
    free(com);
    free(sem);

    return maior_valor;
}
