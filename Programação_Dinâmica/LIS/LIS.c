/*===============================
--- Subsequência Crescente Mais Longa ---
Implementar as versões:

- recursiva

- memoization

- tabulation
===============================*/

#include <stdio.h>

// Função auxiliar para achar o maior entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 1. VERSÃO RECURSIVA 
int lis_recursiva(int num[], int i) {
    if (i == 0) {
        return 1;
    } else {
        int maior = 1;
        for (int j = 0; j < i; j++) {
            if (num[j] < num[i]) {
                maior = max(maior, lis_recursiva(num, j) + 1);
            }
        }
        return maior;
    }
}

int subsequencia_crescente_mais_longa_rec(int num[], int n) {
    if (n == 0) return 0;
    int maior = 1;
    for (int i = 0; i < n; i++) {
        maior = max(maior, lis_recursiva(num, i));
    }
    return maior;
}

// 2. VERSÃO TOP-DOWN
int lis_memo(int num[], int i, int L[]) {
    if (L[i] != -1) {
        return L[i];
    } else if (i == 0) {
        return L[i] = 1;
    } else {
        int maior = 1;
        for (int j = 0; j < i; j++) {
            if (num[j] < num[i]) {
                maior = max(maior, lis_memo(num, j, L) + 1);
            }
        }
        return L[i] = maior;
    }
}

int subsequencia_crescente_mais_longa_memo(int num[], int n) {
    if (n == 0) return 0;
    int L[n];
    for (int i = 0; i < n; i++) {
        L[i] = -1; 
    }

    int maior = 1;
    for (int i = 0; i < n; i++) {
        maior = max(maior, lis_memo(num, i, L));
    }
    return maior;
}


// 3. VERSÃO BOTTOM-UP
int subsequencia_crescente_mais_longa_tab(int num[], int n) {
    if (n == 0) return 0;
    
    int L[n];
    for (int i = 0; i < n; i++) {
        L[i] = 1;
    }

    int maior = 0; 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (num[j] < num[i]) {
                L[i] = max(L[i], L[j] + 1);
            }
        }
        maior = max(maior, L[i]);
    }
    return maior;
}

int main() {
    int num[] = {10, 22, 9, 33, 21, 50, 41, 60};
    int n = sizeof(num) / sizeof(num[0]);

    printf("=== Testando LIS para o array ===\n");
    for (int k = 0; k < n; k++) {
        printf("%d ", num[k]);
    }
    printf("\n\n");

    printf("1. Recursiva: %d\n", subsequencia_crescente_mais_longa_rec(num, n));
    printf("2. Memoization: %d\n", subsequencia_crescente_mais_longa_memo(num, n));
    printf("3. Tabulation: %d\n", subsequencia_crescente_mais_longa_tab(num, n));

    return 0;
}