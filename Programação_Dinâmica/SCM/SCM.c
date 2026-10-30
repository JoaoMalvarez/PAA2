#include <stdio.h>
#include <string.h>

#define MAX 100

// ==========================================
// 1. INICIADORES (Num sei se seria necessário 🫪)
// ==========================================

// Elemento usado dentro da tabela (armazena o número e a seta)
typedef struct Elemento {
    int numero;
    int seta; // 0 = nenhuma | 1 = cima(↑) | 2 = diagonal(↖) | 3 = esquerda(←)
} Elemento;

// Criador de Elementos  
Elemento novo_elem(int numero, int seta) {
    Elemento n;
    n.numero = numero;
    n.seta = seta;
    return n;
}

// ==========================================
// 2. ABORDAGEM BOTTOM-UP (Iterativa)
// ==========================================

// Preenche a tabela recebendo a matriz por parâmetro
void preenche_tabela(char X[], char Y[], int m, int n, Elemento c[MAX][MAX]) {
    // 1. Inicializa a primeira coluna e linha com zeros
    for(int i = 0; i <= m; i++) {
        c[i][0] = novo_elem(0, 0); 
    }
    for(int j = 0; j <= n; j++) {
        c[0][j] = novo_elem(0, 0);
    }

    // 2. Preenche o resto da tabela
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(X[i - 1] == Y[j - 1]) {
                c[i][j] = novo_elem(c[i - 1][j - 1].numero + 1, 2); // 3. Diagonal (↖)
            } 
            else if(c[i - 1][j].numero >= c[i][j - 1].numero) {
                c[i][j] = novo_elem(c[i - 1][j].numero, 1); // 4. Cima (↑)
            }
            else {
                c[i][j] = novo_elem(c[i][j - 1].numero, 3); // 5. Esquerda (←)
            }
        }
    }
}

void recupera_SCM(Elemento c[][MAX], char X[], int i, int j) {
    if(i == 0 || j == 0) {  
        return;  
    }
    if(c[i][j].seta == 2) { // 1. Diagonal
        recupera_SCM(c, X, i - 1, j - 1);
        printf("%c", X[i - 1]); 
    } 
    else if(c[i][j].seta == 1) { // 2. Cima
        recupera_SCM(c, X, i - 1, j);
    } 
    else { // 3. Esquerda
        recupera_SCM(c, X, i, j - 1);
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

    // 3. Criação da tabela para a programação dinâmica
    Elemento m[MAX][MAX];
    preenche_tabela(X, Y, nX, nY, m);

    // 4. Imprime as repetições (começando do final da string)
    printf("Maior Subsequencia Comum: ");
    recupera_SCM(m, X, nX, nY);
    printf("\n");

    // 5. Fim. 
    return 0;
}