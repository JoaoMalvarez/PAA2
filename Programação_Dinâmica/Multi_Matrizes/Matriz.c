#include <stdio.h>
#include <limits.h>

#define MAX 100

// ==========================================
// 1. ABORDAGEM BOTTOM-UP (Iterativa)
// ==========================================
void preenche_tabela_bottom_up(int p[], int n, int m[MAX][MAX], int s[MAX][MAX]) {
    // 1. As cadeias de tamanho 1 têm custo 0
    for(int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // 2. 'l' é o tamanho da sub-cadeia de matrizes (de 2 até n)
    for(int l = 2; l <= n; l++) {
        for(int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX; // 3. Inicializa o valor infinito

            // 4. Testa todos os pontos de 'k'
            for(int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]; 
                if(q < m[i][j]) {
                    m[i][j] = q; // 5. Salva o menor custo (m)
                    s[i][j] = k; // 6. Salva o melhor ponto do 'k' (s)
                }
            }
        }
    }
}

// ==========================================
// 2. ABORDAGEM TOP-DOWN (Recursiva com Memoização)
// ==========================================
int matrix_chain_memo_aux(int p[], int i, int j, int m[MAX][MAX], int s[MAX][MAX]) {
    // 1. Se o valor já foi calculado, retorna ele direto (evita reprocessamento)
    if(m[i][j] < INT_MAX) {
        return m[i][j];
    }

    // 2. Caso base: matriz única tem custo 0
    if(i == j) {
        return 0;
    }

    // 3. Testa todos os pontos de divisão 'k'
    for(int k = i; k <= j - 1; k++) {
        int q = matrix_chain_memo_aux(p, i, k, m, s) + 
                matrix_chain_memo_aux(p, k + 1, j, m, s) + 
                p[i - 1] * p[k] * p[j]; 

        if(q < m[i][j]) {
            m[i][j] = q; // 4. Salva o menor custo na tabela m
            s[i][j] = k; // 5. Salva o melhor ponto k na tabela s
        }
    }

    return m[i][j];
}

void preenche_tabela_top_down(int p[], int n, int m[MAX][MAX], int s[MAX][MAX]) {
    // 6. Inicializa a tabela 'm' com INFINITO para indicar que não foi calculado
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            if(i == j) m[i][j] = 0;
            else m[i][j] = INT_MAX;
        }
    }
    // 7. Dispara a recursão de cima para baixo para o problema completo (1 até n)
    matrix_chain_memo_aux(p, 1, n, m, s);
}

// ==========================================
// 3. ABORDAGEM RECURSIVA PURA (Força Bruta)
// ==========================================
int matrix_chain_recursivo(int p[], int i, int j) {
    // 1. Caso base: cadeia de tamanho 1 tem custo 0
    if(i == j) {
        return 0;
    }

    int menor_custo = INT_MAX;

    // 2. Testa todas as divisões possíveis de k sem usar tabelas auxiliares
    for(int k = i; k <= j - 1; k++) {
        int custo = matrix_chain_recursivo(p, i, k) + 
                    matrix_chain_recursivo(p, k + 1, j) + 
                    p[i - 1] * p[k] * p[j];

        if(custo < menor_custo) {
            menor_custo = custo; // 3. Guarda o menor custo encontrado
        }
    }

    return menor_custo;
}

// Imprime a ordem ideal dos parênteses recursivamente
void imprime_parenteses_otimo(int s[MAX][MAX], int i, int j, int *contador, int n) {
    if(i == j) {
        // 4. Imprime Ai
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

int main() {
    // 1. Vetor de dimensões: A1 (30x35), A2 (35x15), A3 (15x5)
    int dimensoes[] = {30, 35, 15, 5};
    // 2. Número de matrizes
    int numero = sizeof(dimensoes) / sizeof(dimensoes[0]) - 1;

    // 3. Tabelas para Programação Dinâmica
    int m[MAX][MAX];
    int s[MAX][MAX];

    // --- TESTE DA ABORDAGEM BOTTOM-UP ---
    preenche_tabela_bottom_up(dimensoes, numero, m, s);
    printf("=== ABORDAGEM BOTTOM-UP ===\n");
    printf("Menor número de multiplicações: %d\n", m[1][numero]);
    printf("Parentização Ótima: ");
    int contador = 1;
    imprime_parenteses_otimo(s, 1, numero, &contador, numero);
    printf("\n\n");

    // --- TESTE DA ABORDAGEM TOP-DOWN ---
    preenche_tabela_top_down(dimensoes, numero, m, s);
    printf("=== ABORDAGEM TOP-DOWN (MEMOIZAÇÃO) ===\n");
    printf("Menor número de multiplicações: %d\n", m[1][numero]);
    printf("Parentização Ótima: ");
    contador = 1;
    imprime_parenteses_otimo(s, 1, numero, &contador, numero);
    printf("\n\n");

    // --- TESTE DA ABORDAGEM RECURSIVA PURA ---
    int custo_recursivo = matrix_chain_recursivo(dimensoes, 1, numero);
    printf("=== ABORDAGEM RECURSIVA PURA (FORÇA BRUTA) ===\n");
    printf("Menor número de multiplicações: %d\n", custo_recursivo);
    printf("(Nota: A recursiva pura não preenche a tabela 's', por isso não imprime a parentização diretamente)\n");

    return 0;
}
