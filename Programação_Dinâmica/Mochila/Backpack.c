#include <stdio.h>
#include <stdlib.h>

/* ========== Itens ========== */
typedef struct Item {
    int nome;
    int valor;
    int peso;
} Item;

/* ========== Variáveis Globais para os vetores e matriz de memoization ========== */
int *w; // pesos
int *v; // valores
int **M; // matriz de memoization

/* ========== Criador de Itens ========== */
Item *novo_item(int nome, int valor, int peso) {
    Item *n = malloc(sizeof(Item));
    if(!n) {
        perror("malloc");
        exit(1);
    }
    n->nome = nome;
    n->valor = valor;
    n->peso = peso;
    return n;
}

/* ========== Pega o Peso dos Itens ========== */
int pega_peso(int valor, int item, int peso) {
    return w[item];
}

/* ========== Maior valor entre 2 valores ========== */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Assinaturas antecipadas */
int recursiva(int n, int W);
int memoization(int n, int W);
int tabulation(int n, int W);
int maior_valor(int n, int W);

/* ========== Versão Recursiva Pura ========== */
int recursiva(int n, int W) {
    if(n == 0 || W == 0)
        return 0;
    if(w[n] > W)
        return recursiva(n - 1, W);
    else
        return max(recursiva(n - 1, W), recursiva(n - 1, W - w[n]) + v[n]);
}

/* ========== Versão com Memoization (Top-Down) ========== */
int memoization(int n, int W) {
    if(n == 0 || W == 0)
        return 0;
    if(M[n][W] != -1)
        return M[n][W];
    
    if (w[n] > W)
        M[n][W] = memoization(n - 1, W);
    else
        M[n][W] = max(memoization(n - 1, W), memoization(n - 1, W - w[n]) + v[n]);
        
    return M[n][W];
}

/* ========== Versão com Tabulation (Bottom-Up) ========== */
int tabulation(int n, int W) {
    int **dp = malloc((n + 1) * sizeof(int *));
    for(int i = 0; i <= n; i++) {
        dp[i] = malloc((W + 1) * sizeof(int));
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= W; j++) {
            if(i == 0 || j == 0)
                dp[i][j] = 0;
            else if(w[i] <= j)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    
    int resultado = dp[n][W];

    for(int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return resultado;
}

/* ========== Função para Imprimir a Matriz ========== */
void imprime_matriz(int n, int W) {
    int **dp = malloc((n + 1) * sizeof(int *));
    for(int i = 0; i <= n; i++) {
        dp[i] = malloc((W + 1) * sizeof(int));
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= W; j++) {
            if(i == 0 || j == 0)
                dp[i][j] = 0;
            else if(w[i] <= j)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    printf("\n==============================================================\n");
    printf("             |O:| MATRIZ DE PROGRAMACAO DINAMICA |:P|\n");
    printf("==============================================================\n");
    printf("Itens \\ Cap     |");
    for(int j = 0; j <= W; j++) {
        printf(" W=%-2d |", j);
    }
    printf("\n-----------------------------------------------------------\n");

    for(int i = 0; i <= n; i++) {
        if(i == 0) {
            printf("Item 0 (Base)   |");
        } else {
            printf("Item %d (v:%d,p:%d)|", i, v[i], w[i]);
        }
        for(int j = 0; j <= W; j++) {
            printf("  %-3d |", dp[i][j]);
        }
        printf("\n");
    }
    printf("==============================================================\n\n");

    for(int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
}

/* ========== Pega o Maior Valor ========== */
int maior_valor(int n, int W) {
    int rec, memo, tabu;
    
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= W; j++) {
            M[i][j] = -1;
        }
    }
    rec = recursiva(n, W);
    
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= W; j++) {
            M[i][j] = -1;
        }
    }
    memo = memoization(n, W);
    
    tabu = tabulation(n, W);
    
    if(rec == memo && memo == tabu) {  
        return rec;    
    }
    return memo;
}

/* ========== Main ========== */
int main() {
    
    /* ========== Valores dado em Vetores ========== */
    int qntd_itens = 4;
    int peso_mochila = 5;

    int weight_arr[] = {0, 3, 2, 4, 1};
    int value_arr[]  = {0, 8, 3, 9, 6};
    w = weight_arr;
    v = value_arr;

    /* ========== Inicializador de Itens (Corrigido para ponteiros) ========== */
    Item *A1 = novo_item(1, 8, 3);
    Item *B2 = novo_item(2, 3, 2);
    Item *C3 = novo_item(3, 9, 4);
    Item *D4 = novo_item(4, 6, 1);

    M = malloc((qntd_itens + 1) * sizeof(int *));
    for(int i = 0; i <= qntd_itens; i++) {
        M[i] = malloc((peso_mochila + 1) * sizeof(int));
    }

    /* ========== Print inicial com os dados ========== */
    printf("=== DADOS DA MOCHILA ===\n");
    printf("Quantidade de itens: %d\n", qntd_itens);
    printf("Capacidade maxima da mochila: %d\n\n", peso_mochila);

    for(int i = 1; i <= qntd_itens; i++) {
        printf("Item %d -> Valor: %d | Peso: %d\n", i, v[i], w[i]);
    }

    /* ========== Mostra a Matriz ========== */
    imprime_matriz(qntd_itens, peso_mochila);

    /* ========== Calcula o valor ótimo ========== */
    int otimo = maior_valor(qntd_itens, peso_mochila);
    printf("Maior valor otimo obtido: %d\n", otimo);

    /* ========== Artezinha em ASCII ========== */
    printf("\n");
    printf("            O_      __)(                        \n");
    printf("          ,'  `.   (_\".`.                      \n");
    printf("          :      :   /|`                        \n");
    printf("          |      |  ((|_  ,-.                   \n");
    printf("          ; -   /:,'  `:(( -\\                  \n");
    printf("         /    -' `: ____ \\\\-:                 \n");
    printf("        _\\__  ____|___  \\____|_               \n");
    printf("       ;    |:|        '-`      :               \n");
    printf("      :_____|:|__________________:              \n");
    printf("      ;     |:|                  :              \n");
    printf("     :      |:|                   :             \n");
    printf("     ;______ `'_                  :             \n");
    printf("    :                              :            \n");
    printf("    |______________________________|            \n");
    printf("     `---.--------------------.---'             \n");
    printf("        |____________________|                  \n");
    printf("        |                    |                  \n");
    printf("        |____________________|                  \n");
    printf("        |SSt                 |                  \n");
    printf("      _\\|_\\|_\\/(__\\__)\\__\\//_|(_          \n");
    printf("\n");

    /* ========== Liberação da Matriz ========== */
    for(int i = 0; i <= qntd_itens; i++) {
        free(M[i]);
    }
    free(M);
    
    /* ========== Liberação Correta dos Itens ========== */
    free(A1);
    free(B2);
    free(C3);
    free(D4);

    return 0;
}