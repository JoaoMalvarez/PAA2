#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX 100

// ==========================================
// 1. INICIADORES (Num sei se é necessário 🫪)
// ==========================================

// 1. Elemento vai ser usado dentro da tabela, já que tem setas dentro e o número
typedef struct Elemento {
    int numero;
    int seta; // 2. Cada número é uma direção: 
             // 0 = nenhuma | 1 = cima(↑) | 2 = esquerda em cima(↖) | 3 = esquerda(←)
} Elemento;

// 3. Criador de Elementos  
Elemento *novo_elem(int numero, int seta) {
    Elemento n;
    n->numero = numero;
    n->seta = seta;
    return n;
}


// ==========================================
// 2. ABORDAGEM BOTTOM-UP (Iterativa)
// ==========================================

// 1. Alguns dados importantes: 
// - 'X[]' é a primeira string e o 'm' é o tamanho dela
// - 'Y[]' é a segunda string e o 'n' é o tamanho dela
Elemento preenche_tabela(char X[], char Y[], int m, int n) {
    // 2. Declarando a tabela como uma matriz bidimensional de Elementos
    Elemento c[MAX];

    // 3. Inicializa a primeira coluna e linha com zeros
    for(int i = 0; i < m; i++) {
        c[i][0] = novo_elem(0, 0); 
    }
    for(int j = 0; j < n; j++) {
        c[0][j] = novo_elem(0, 0);
    }

    // 4. Preenche o resto da tabela
    for(int i = 1; i < m; i++) {
        for(int j = 1; j < n; j++) {
            
            // 5. Funções para a criação
            if(X[i] == Y[j]) {
                c[i][j] = novo_elem(c[i - 1][j - 1].numero + 1, 2);
            } 
            else if(c[i - 1][j].numero >= c[i][j - 1].numero) {
                c[i][j] = novo_elem(c[i-1][j].numero, 1);
            }
            else {
                c[i][j] = novo_elem(c[i][j-1].numero, 3);
            }
        }
    }
    return c;
}

void recupera_SCM(Elemento c[][MAX], char X[], int i, int j) {
    if(i == 0 || j == 0) {  return;  }
    if(c[i][j].seta == 2) {
        recupera_SCM(c, X, i-1, j-1);
        printf("%c", X[i]); 
    } else if(c[i][j].seta == 1) {
        recupera_SCM(c, X, i-1, j);
    } else {
        recupera_SCM(c, X, i, j-1);
    }
}

// ==========================================
// 3. MAIN (Sim! 🥸​​)
// ==========================================
int main() {
    // 1. Vetores de nome
    char X[] = "ATCTGAT";
    char Y[] = "TGCATTA";

    // 2. Tamanho das palavras
    int nX = strlen(X);
    int nY = strlen(Y);

    // 3. Criação da Tabela para a programação dinâmica
    Elemento m[MAX][MAX] = preenche_tabela(X, Y, nX, nY);

    // 4. Imprime as repetições
    printf("Maior Subsequencia Comum: ");
    recupera_SCM(m, X, 0, 0);
    printf("\n");

    // 5. Fim.
    return 0;
}