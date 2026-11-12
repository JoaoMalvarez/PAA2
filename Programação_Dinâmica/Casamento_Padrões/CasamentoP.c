/*===============================
  Casamento de Padrões: 
  - Força Bruta
  - KMP (Knuth-Morris-Pratt)
===============================*/ 

#include <stdio.h>
#include <string.h>

// 1. Algoritmo de Casamento de Padrões por Força Bruta
// Percorre o texto 'T' testando todas as posições possíveis para encontrar o padrão 'P'.
int Forca_Bruta(char T[], char P[]) {
    size_t n = strlen(T); // Comprimento do texto
    size_t m = strlen(P); // Comprimento do padrão
    int c = 0;            // Contador de ocorrências

    // Percorre o texto até o ponto onde o padrão ainda cabe
    for(size_t i = 0; i <= n - m; i++) {
        size_t j = 0;
        // Compara cada caractere do padrão com o texto correspondente
        while(j < m && P[j] == T[i + j]) {
            j++;
        }
        // Se j chegou ao fim do padrão, significa que encontramos uma ocorrência completa
        if(j == m) {
            c++;
        }
    }
    return c; // Retorna o número total de ocorrências encontradas
}

// 2. Computa a Função Prefixo (tabela LPS - Longest Prefix Suffix) para o algoritmo KMP
// Pré-processa o padrão para evitar comparações redundantes.
void Computa_Funcao_Prefixo(char P[], int pi[]) {
    size_t m = strlen(P);
    pi[0] = 0; // O primeiro elemento da tabela prefixo é sempre 0
    int k = 0;

    for (size_t q = 1; q < m; q++) {
        // Se houver mismatch, retrocede o k usando os valores já computados
        while (k > 0 && P[k] != P[q]) {
            k = pi[k - 1];
        }
        // Se os caracteres coincidem, avançamos o prefixo comum
        if (P[k] == P[q]) {
            k++;
        }
        pi[q] = k; // Armazena o valor do prefixo na tabela
    }
}

// 3. Algoritmo de Casamento de Padrões KMP
// Utiliza a tabela de prefixos para buscar o padrão no texto com eficiência O(n + m).
void Casamento_Padroes_KMP(char T[], char P[]) {
    size_t n = strlen(T);
    size_t m = strlen(P);
    int pi[100]; // Vetor para armazenar a função prefixo (tamanho máximo seguro para o exemplo)
    
    Computa_Funcao_Prefixo(P, pi);
    
    int q = 0; // Número de caracteres do padrão já casados
    for (size_t i = 0; i < n; i++) {
        // Se houver mismatch, retrocede o q usando a tabela pi
        while (q > 0 && P[q] != T[i]) {
            q = pi[q - 1];
        }
        // Se os caracteres coincidem, avança o ponteiro do padrão
        if (P[q] == T[i]) {
            q++;
        }
        // Se q alcança o tamanho do padrão, encontramos uma ocorrência
        if (q == m) {
            // Imprime o índice inicial onde o padrão ocorre no texto
            printf("P ocorre em T com deslocamento (indice): %zu\n", i - m + 1);
            q = pi[q - 1]; // Prepara para buscar próximas ocorrências
        }
    }
}

// Função Principal
int main() {
    char Texto[] = "abracadabra";
    char Padrao[] = "bra";

    // Testando o algoritmo de Força Bruta    
    printf("Resultados do algoritmo de Força Bruta:\n");
    int FB = Forca_Bruta(Texto, Padrao);
    printf("Forca Bruta encontrou %d ocorrencia(s).\n\n", FB);

    // Divisória
    printf("=====================================================\n\n");

    // Testando o algoritmo KMP
    printf("Resultados do algoritmo de KMP:\n");
    Casamento_Padroes_KMP(Texto, Padrao);

    return 0;
}