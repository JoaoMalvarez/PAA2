#include <stdio.h>
#include <stdbool.h>

#define N 8

// Função recursiva de backtracking
bool dfs(int palitos[], bool usado[], int indice_palito, int lado_atual, int soma_atual, int target) {
    // Se completamos 3 lados com sucesso, o 4º lado fecha automaticamente com o que sobrou
    if (lado_atual == 3) {
        return true;
    }
    
    // Se a soma do lado atual atingiu o target, passamos para o próximo lado
    if (soma_atual == target) {
        return dfs(palitos, usado, 0, lado_atual + 1, 0, target);
    }

    // Tenta encaixar os palitos restantes no lado atual
    for (int i = indice_palito; i < N; i++) {
        if (!usado[i] && soma_atual + palitos[i] <= target) {
            usado[i] = true; // Escolhe o palito
            
            if (dfs(palitos, usado, i + 1, lado_atual, soma_atual + palitos[i], target)) {
                return true; // Se achou a solução, propaga o sucesso
            }
            
            usado[i] = false; // BACKTRACK: Desfaz a escolha se não deu certo
        }
    }
    
    return false;
}

// Função auxiliar apenas para organizar e exibir os lados na tela
void imprimir_quadrado(int palitos[], int target) {
    bool usado[N] = {false};
    
    printf("\n[SUCESSO] É possível formar um quadrado de lado %d!\n\n", target);
    printf("Estrutura dos lados:\n");
    
    for (int lado = 0; lado < 4; lado++) {
        printf("Lado %d: [ ", lado + 1);
        int soma_parcial = 0;
        
        // Aqui pegamos os palitos que ainda não foram usados para formar este lado
        for (int i = 0; i < N; i++) {
            if (!usado[i] && soma_parcial + palitos[i] <= target) {
                usado[i] = true;
                soma_parcial += palitos[i];
                printf("%d ", palitos[i]);
                
                // Se o lado fechou a soma exata, paramos de adicionar neste lado
                if (soma_parcial == target) {
                    break;
                }
            }
        }
        printf("] (Soma: %d)\n", target);
    }
}

int main() {
    int palitos[N] = {4, 4, 4, 4, 2, 2, 2, 2};
    int soma_total = 0;

    for (int i = 0; i < N; i++) {
        soma_total += palitos[i];
    }

    if (soma_total % 4 != 0) {
        printf("Não é possível formar um quadrado (soma total não divisível por 4).\n");
        return 0;
    }

    int target = soma_total / 4;
    bool usado[N] = {false};

    // Testa se existe solução
    if (dfs(palitos, usado, 0, 0, 0, target)) {
        imprimir_quadrado(palitos, target);
    } else {
        printf("Não é possível formar um quadrado com os palitos disponíveis!\n");
    }

    return 0;
}