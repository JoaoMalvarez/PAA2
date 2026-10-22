#include <stdio.h>

#define INF 1000000

// Função auxiliar para achar o menor entre dois números
int min(int a, int b) {
    return (a < b) ? a : b;
}

// 1. VERSÃO RECURSIVA
int conta_moedas_rec(int M[], int n, int T) {
    if (T == 0) 
        return 0;
    if (T < 0) 
        return INF;
        
    int menor = INF;
    for (int i = 0; i < n; i++) {
        menor = min(menor, conta_moedas_rec(M, n, T - M[i]) + 1);
    }
    return menor;
}

// 2. VERSÃO TOP-DOWN
int conta_moedas_memo_aux(int M[], int n, int T, int memo[]) {
    if (T == 0) 
        return 0;
    if (T < 0) 
        return INF;
        
    if (memo[T] != -1) 
        return memo[T];
        
    int menor = INF;
    for (int i = 0; i < n; i++) {
        int res = conta_moedas_memo_aux(M, n, T - M[i], memo);
        if (res != INF) {
            menor = min(menor, res + 1);
        }
    }
    return memo[T] = menor;
}

int conta_moedas_memo(int M[], int n, int T) {
    int memo[T + 1];
    for (int i = 0; i <= T; i++) {
        memo[i] = -1;
    }
    return conta_moedas_memo_aux(M, n, T, memo);
}

// 3. VERSÃO BOTTOM-UP
int conta_moedas_tab(int M[], int n, int T) {
    int troco[T + 1];
    
    for (int i = 0; i <= T; i++) {
        troco[i] = INF;
    }
    troco[0] = 0;
    
    for (int i = 1; i <= T; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= M[j]) {
                if (troco[i - M[j]] != INF) {
                    troco[i] = min(troco[i], troco[i - M[j]] + 1);
                }
            }
        }
    }
    
    return (troco[T] == INF) ? -1 : troco[T];
}

int main() {
    int moedas[] = {1, 3, 4}; // Exemplo de conjunto de moedas
    int n = sizeof(moedas) / sizeof(moedas[0]);
    int T = 6; // Valor do troco desejado

    printf("=== Problema do Troco (T = %d) ===\n", T);
    printf("Moedas disponiveis: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", moedas[i]);
    }
    printf("\n\n");

    printf("1. Recursiva: %d moedas\n", conta_moedas_rec(moedas, n, T));
    printf("2. Memoization: %d moedas\n", conta_moedas_memo(moedas, n, T));
    printf("3. Tabulation: %d moedas\n", conta_moedas_tab(moedas, n, T));

    return 0;
}