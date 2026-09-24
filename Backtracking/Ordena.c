#include <stdio.h>
#define N 10

void print(int v[]) {
    for(int i = 0; i < N; i++)  {
        if(i == N -1) printf("%d\n\n", v[i]);
        else printf("%d, ", v[i]);
    }
}

void ordenar(int v[]) {
    int aux;
    for(int i = 0; i < N - 1; i++) {
        for(int j = 0; j < N - i - 1; j++) {
            // Se o elemento atual for maior que o próximo, troca de lugar
            if (v[j] > v[j + 1]) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;  
            }
        }
    }
}

int estaOrdenado(int v[], int i) {
    if(i >= N - 1) return 1; // 1 = true
    if (v[i] < v[i + 1]) estaOrdenado(v, i + 1);
    else return 0; // 0 = false
}

int backtracking(int v[], int inicio) {
    if (inicio == N) {
        return estaOrdenado(v, 0);
    }

    for (int i = inicio; i < N; i++) {
        // 1. Escolha
        int aux = v[inicio];
        v[inicio] = v[i];
        v[i] = aux;

        // 2. Recursão (Avança)
        if (backtracking(v, inicio + 1)) {
            return 1;
        }

        // 3. Backtrack (Desfaz a escolha para tentar outro caminho)
        aux = v[inicio];
        v[inicio] = v[i];
        v[i] = aux;
    }

    return 0;
}

int main() {
    int v[N] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int vetor[N] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    printf("Ordenado Sem Backtracking:\n");
    ordenar(v);
    print(v);

    printf("Ordenado Com Backtracking:\n");
    backtracking(vetor, 0);
    print(vetor);
    
    return 0;
}