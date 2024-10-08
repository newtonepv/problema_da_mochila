// #include "forca_bruta.h"
#include "item.h"
#include "mochila.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 5000

// Criamos as estruturas item e mochila para auxiliar nos algoritmos "greedy" e "forca_bruta".
struct item{
    float peso;
    float valor;
};

// Nas mochilas são adicionadas as características dela, como peso, capacidade e valor total.
struct mochila{
    float peso;
    float capacidade;
    float valortotal;
    int tam;
    ITEM *itens[MAX];
};

// Declaração das funcões auxiliares
void exibe_itens(ITEM **itens, int n);
void libera_itens(ITEM **itens, int n);
void forca_bruta(MOCHILA *mochila_original, ITEM **itens, int n);
void greedy(MOCHILA *mochila_original, ITEM **itens, int n);
void copiar_mochila(MOCHILA *destino, MOCHILA *origem);
void matriz_dp(int W, int peso[], int valor[], int n);

int main() {
    // O usuário escolhe qual abordagem será usada
    printf("Digite que algoritmo quer usar: 1 guloso, 2 força bruta, 3 programação dinamica\n");
    int tipo;
    scanf("%d", &tipo);

    if (tipo < 3) {
        int qtdItens;
        float capacidade;

        printf("Digite a capacidade da mochila: ");
        scanf("%f", &capacidade);
        MOCHILA* mochila = mochila_criar(capacidade);
        printf("Digite quantos itens serão inseridos: ");
        scanf("%d", &qtdItens);

        float w, v;
        ITEM** itens = malloc(sizeof(ITEM*) * qtdItens);
        if (itens == NULL) return -1;

        printf("Digite, um por um, os itens a seguir (peso valor)\n");
        for (int i = 0; i < qtdItens; i++) {
            scanf("%f %f", &w, &v);
            itens[i] = item_criar(w, v);// itens sao armazenados em um vetor
        }

        // Medir o tempo de execução
        clock_t start, end;
        double tempo_gasto;
        
        start = clock();
        
        if (tipo == 2) {
            forca_bruta(mochila, itens, qtdItens);
            end = clock();
            tempo_gasto = ((double)(end - start)) / CLOCKS_PER_SEC;

            // Gravar tempo no arquivo 'tempo_forca_bruta.dat'
            FILE *f = fopen("tempo_forca_bruta.dat", "a");
            fprintf(f, "%d %f\n", qtdItens, tempo_gasto);
            fclose(f);
        } else {
            greedy(mochila, itens, qtdItens);
            end = clock();
            tempo_gasto = ((double)(end - start)) / CLOCKS_PER_SEC;

            // Gravar tempo no arquivo 'tempo_greedy.dat'
            FILE *f = fopen("tempo_greedy.dat", "a");
            fprintf(f, "%d %f\n", qtdItens, tempo_gasto);
            fclose(f);
        }

        libera_itens(itens, qtdItens);
        //estes algoritmos usam vetores de itens portanto precisamos apagar eles

    } else if (tipo == 3) {
        int qtdItens;
        int capacidade;

        printf("Digite a capacidade da mochila: ");
        scanf("%d", &capacidade);
        printf("Digite quantos itens serão inseridos: ");
        scanf("%d", &qtdItens);

        int w = 0, v = 0;
        int* peso = malloc(sizeof(int) * qtdItens);
        int* valor = malloc(sizeof(int) * qtdItens);

        printf("Digite, um por um, os itens a seguir, primeiro o peso do item, e depois o valor do item\n");
        for (int i = 0; i < qtdItens; i++) {
            //diferente dos anteriores, este nao usa um array de itens e 
            //sim dois arrays, um de pesos e outro de valores
        
            scanf("%d %d", &w, &v);
            peso[i] = w;
            valor[i] = v;
        }

        // Medir o tempo de execução
        clock_t start, end;
        double tempo_gasto;
        
        start = clock();
        
        matriz_dp(capacidade, peso, valor, qtdItens);
        
        end = clock();
        tempo_gasto = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Gravar tempo no arquivo 'tempo_programacao_dinamica.dat'
        FILE *f = fopen("tempo_programacao_dinamica.dat", "a");
        fprintf(f, "%d %f\n", qtdItens, tempo_gasto);
        fclose(f);

        free(peso);
        free(valor);
        //precisamos dar liberar os arrays usados
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
    // Realiza o loop enquanto tiver espaço na mochila
    while (mochila_original->peso < mochila_original->capacidade) {
        ITEM *melhoritem = NULL;
        int melhor_index = -1;

        // busca pelo melhor item, tendo como base a razão entre valor e peso.
        // Para facilitar, foi feito o uso de uma função auxiliar, que calcula e retorna essa razão
        for (int i = 0; i < n; i++) {
            if (itens[i] != NULL) {
                if (melhoritem == NULL || item_raciona(itens[i]) > item_raciona(melhoritem)) {
                    // Caso haja um novo melhor, atualizamos esse valor
                    melhoritem = itens[i];
                    melhor_index = i;
                }
            }
        }

        // Caso não haja mais nenhum item para ser adicionado, quebramos o loop
        if (melhoritem == NULL) {
            break;
        }
        
        // Adicionamos o melhor item na mochila original e mudamos seu ponteiro para NULL, para que não sejam adicionados valores repetidos. 
        mochila_push(mochila_original, melhoritem);
        itens[melhor_index] = NULL;
    }

    // Exibe os dados do melhor valor
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

    //Testa todas as combinações possiveis com AND binário e uma máscara
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

    // Exibe a melhor configuração possivel
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
                /*esse algoritimo avalia a melhor possibilidade vendo se 
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
/*Solucao Recursiva
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
        // Não há mais itens para processar
        return valor;
    }
    if (capacidade < pesos[passados]) {
        printf("parou, passados = %d, capacidade = %d, valor = %d\n", passados, capacidade, valor);
        // Capacidade negativa indica uma solução inválida
        return valor; 
    }
    
    printf("chamou, passados = %d, capacidade = %d, valor = %d\n", passados, capacidade, valor);
    
    // aloca memoria para os ocupados temporarios ( vao ser modificados na recursao por cada chamada,
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
         // Atualiza a mochila com os IDs da melhor solução
        copiar_array(mochila, com, qtdItens);
        *ocupados = *ocupados1;
    } else {
        maior_valor = i2;
         // Atualiza a mochila com os IDs da melhor solução
        copiar_array(mochila, sem, qtdItens);
        *ocupados = *ocupados2;
    }

    // Libera a memória alocada
    free(com);
    free(sem);

    return maior_valor;
}
*/
