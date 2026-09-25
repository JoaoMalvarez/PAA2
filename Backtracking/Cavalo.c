#include <stdio.h>
#include <stdbool.h>

#define N 8 // Tabuleiro 8x8

// Vetores de deslocamento para os 8 movimentos possíveis do Cavalo
int mov_x[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
int mov_y[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

// Função de Backtracking
bool resolver_passeio(int tabuleiro[N][N], int x, int y, int passo) {
    // CASO BASE: Se o passo for N * N, visitamos todas as casas!
    if (passo == N * N) {
        return true;
    }

    // Tenta os 8 movimentos possíveis a partir da posição (x, y)
    for (int i = 0; i < 8; i++) {
        int proximo_x = x + mov_x[i];
        int proximo_y = y + mov_y[i];

        // Verifica se a nova posição está dentro do tabuleiro e ainda não foi visitada (== 0)
        if (proximo_x >= 0 && proximo_x < N && proximo_y >= 0 && proximo_y < N && tabuleiro[proximo_x][proximo_y] == 0) {
            
            // 1. FAZ A ESCOLHA (marca o número do passo na casa)
            tabuleiro[proximo_x][proximo_y] = passo + 1;

            // 2. APROFUNDA (chama recursivamente para o próximo passo)
            if (resolver_passeio(tabuleiro, proximo_x, proximo_y, passo + 1)) {
                return true;
            }

            // 3. DESFAZ A ESCOLHA (BACKTRACK: se deu errado, limpa a casa)
            tabuleiro[proximo_x][proximo_y] = 0;
        }
    }

    return false; // Se tentou os 8 movimentos e nenhum deu certo, retorna falso
}

int main() {
    int tabuleiro[N][N];

    // Inicializa o tabuleiro inteiro com 0 (não visitado)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    int linha, coluna;
    printf("Digite a linha inicial (0 a 7): ");
    scanf("%d", &linha);
    printf("Digite a coluna inicial (0 a 7): ");
    scanf("%d", &coluna);

    // O cavalo começa na posição escolhida, sendo o passo 1
    tabuleiro[linha][coluna] = 1;

    if (resolver_passeio(tabuleiro, linha, coluna, 1)) {
        printf("\n[SUCESSO] Passeio do Cavalo encontrado!\n\n");
        // Imprime o tabuleiro numerado com a ordem dos passos
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%2d ", tabuleiro[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("\n[FALHOU] Nao e possivel completar o passeio a partir desta posicao.\n");
    }

    return 0;
}
