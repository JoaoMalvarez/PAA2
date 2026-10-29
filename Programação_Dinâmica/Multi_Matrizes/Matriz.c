#include <stdio.h>
#include <limits.h>

#define MAX 100

// Preenche as Tabelas 'm' e as Tabelas 's'
void preenche_tabela(int p[], int n, int m[MAX][MAX], int s[MAX][MAX]) {
    // 1. As cadeias de tamanho 1 têm custo 0
    for(int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // 2. 'l' é o tamanho da sub-cadeia de matrizes (de 2 até n)
    for(int l = 2; l <= n; l++) {
        for(int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX; // inicializa o valor infinito

            // 3. Testa todos os pontos de 'k'
            for(int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]; 
                if(q < m[i][j]) {
                    m[i][j] = q; // 4. Salva o menor custo (m)
                    s[i][j] = k; // 5. Salva o melhor ponto do 'k' (s)
                }
            }
        }
    }
}

// Imprime a ordem ideal dos parênteses recursivamente
void imprime_parenteses_otimo(int s[MAX][MAX], int i, int j, int *contador, int n) {
    if(i == j) {
        // 6. Imprime Ai
        if((*contador) == n) printf("A%d", i);
        else printf("A%d*", i);
        (*contador)++; 
    } else {
        printf("( ");
        imprime_parenteses_otimo(s, i, s[i][j], contador, n);
        imprime_parenteses_otimo(s, s[i][j] + 1, j, contador, n);
        printf(" )");
    }
}

// Vai calcular o melhor produto
int calcula_produto(int s[MAX][MAX], int i, int j) {
    if(i == j) {
        return i; // 7. Retorna A_i (i)
    } else {
        int x = calcula_produto(s, i, s[i][j]);
        int y = calcula_produto(s, s[i][j], j);
        return x * y;
    }
}

int main() {
    // 8. Vetor de dimensões: A1 (30x35), A2 (35x15), A3 (15x5)
    int dimensoes[] = {30, 35, 15, 5};
    // 9. Número de matrizes
    int numero = sizeof(dimensoes) / sizeof(dimensoes[0]) - 1;

    // 10. Tabelas
    int m[MAX][MAX];
    int s[MAX][MAX];

    // 11. Preenchimento das tabelas criadas
    preenche_tabela(dimensoes, numero, m, s);

    // 12. Imprime qual a forma que multiplicada fica melhor
    int contador = 1;
    printf("Menor número de multiplicações: %d\n", m[1][numero]);
    printf("Parentização Ótima: ");
    imprime_parenteses_otimo(s, 1, numero, &contador, numero);
    printf("\n");

    return 0;
}