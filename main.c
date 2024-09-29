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
void matriz_dp(int W, int peso[], int valor[], int n);
int main(){
    printf("Digite que algoritmo quer usar: 1 guloso, 2 força bruta, 3 programação dinamica\n");
    int tipo;
    scanf("%d", &tipo);
    if(tipo<3){
    int qtdItens;
    float capacidade;

    printf("Digite a capacidade da mochila: ");
    scanf("%f", &capacidade);
    MOCHILA *mochila = mochila_criar(capacidade);
    printf("Digite quantos itens serão inseridos: ");
    scanf("%i", &qtdItens);

    float w, v;

    ITEM **itens = malloc(sizeof(ITEM*) * qtdItens);
    if (itens == NULL) return -1;
    printf("digite, um por um, os itens a seguir, primeiro o peso do item, e depois o valor do item\n");
    for(int i = 0; i < qtdItens; i++)
    {
        scanf("%f %f", &w, &v);
        itens[i] = item_criar(w, v);
    }

    if(tipo==2){
        forca_bruta(mochila, itens, qtdItens);
    }else{
        greedy(mochila, itens, qtdItens);
    }
    libera_itens(itens, qtdItens);
    
    }else if(tipo==3){
        int qtdItens;
        int capacidade;

        printf("Digite a capacidade da mochila: ");
        scanf("%d", &capacidade);
        printf("Digite quantos itens serão inseridos: ");
        scanf("%d", &qtdItens);

        int w=0, v=0;
        int* peso = malloc(sizeof(int)*qtdItens);
        int* valor = malloc(sizeof(int)*qtdItens);

        printf("digite, um por um, os itens a seguir, primeiro o peso do item, e depois o valor do item\n");
        for(int i = 0; i < qtdItens; i++)
        {
            scanf("%d %d", &w, &v);
            peso[i]=w;
            valor[i]=v;
        }
        matriz_dp(capacidade,peso,valor,qtdItens);
    }
    
    
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
void matriz_dp(int W, int peso[], int valor[], int n) {
    int i, w;
    int dp[n+1][W+1];

    // Construindo a tabela dp
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                //a primeira linha e a primeira coluna é 0 em tudo
                dp[i][w] = 0;
            else if (peso[i-1] <= w)
                /*a ""recursividade"" esta em que se quando procuramos pelo valor max caso nao pegarmos
                um item, seria o valor max da mochila se avaliarmos os primeiros "i-1" itens com a mesma capacidade
                */ 
                /*assim como a forca bruta, esse algoritimo avalia a melhor possibilidade vendo se 
                pegar ou nao pegar o item é o melhor, o valor caso pegarmos o item é, {o maior valor 
                quando analizamos i-1 itens com a capacidade menos esse item} + o valor desse item
                */
                dp[i][w] = (valor[i-1] + dp[i-1][w - peso[i-1]] > dp[i-1][w]) ?
                            valor[i-1] + dp[i-1][w - peso[i-1]] : dp[i-1][w];
            else
                dp[i][w] = dp[i-1][w];
            //aumenta a capacidade da mochila em 1
        }
    }

    // O valor máximo estará em dp[n][W]
    printf("Melhor valor encontrado: %d\n", dp[n][W]);
}
/*Forca Bruta Primitiva
void copiar_array(int* destino, int* origem, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        destino[i] = origem[i];
    }
}

int organizar_mochila(int* pesos, int* valores, int qtdItens, int* mochila, 
                      int capacidade, int passados, int valor, int* ocupados) {
    
    
    // Condição de parada: se a capacidade é menor do que o proximo item ou não há mais itens
    printf("ocupados =%d ", *ocupados);
    if (passados >= qtdItens) {
        printf("parou, passados = %d, qtdItens = %d\n",passados,qtdItens);
        return valor; // Não há mais itens para processar
    }
    if (capacidade < pesos[passados]) {
        printf("parou, passados = %d, capacidade = %d, valor = %d\n", passados, capacidade, valor);
        return valor; // Capacidade negativa indica uma solução inválida
    }
    
    printf("chamou, passados = %d, capacidade = %d, valor = %d\n", passados, capacidade, valor);
    
    //alloca memoria para os ocupados temporarios ( vao ser modificados na recursao por cada chamada,
    // a que tiver mais valor vai prevalecer)
    int* ocupados1 = malloc(sizeof(int));
    int* ocupados2 = malloc(sizeof(int));
    *ocupados1 = (*ocupados) + 1;
    *ocupados2 = *ocupados;

    // Aloca memória para mochilas temporárias
    int* com = malloc(sizeof(int) * qtdItens);
    int* sem = malloc(sizeof(int) * qtdItens);
    // Copia o conteúdo da mochila atual para as novas mochilas
    copiar_array(com, mochila, qtdItens);
    copiar_array(sem, mochila, qtdItens);

    // Adiciona o item atual (ID) à mochila "com"
    com[(*ocupados)] = passados;

    // Chama recursivamente com e sem o item atual
    int i1 = organizar_mochila(pesos, valores, qtdItens, com, 
                               capacidade - pesos[passados], 
                               passados + 1, valor + valores[passados], ocupados1);

    int i2 = organizar_mochila(pesos, valores, qtdItens, sem, 
                               capacidade, passados + 1, valor, ocupados2);

    // Escolhe a solução de maior valor
    int maior_valor;
    if (i1 > i2) {
        maior_valor = i1;
        copiar_array(mochila, com, qtdItens); // Atualiza a mochila com os IDs da melhor solução
        *ocupados = *ocupados1;
    } else {
        maior_valor = i2;
        copiar_array(mochila, sem, qtdItens); // Atualiza a mochila com os IDs da melhor solução
        *ocupados = *ocupados2;
    }

    // Libera a memória alocada
    free(com);
    free(sem);

    return maior_valor;
}
*/