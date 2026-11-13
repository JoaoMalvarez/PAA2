/*===============================
  Casamento de Padrões: 
  - Algoritmo Z - Zvi Galil
===============================*/ 

#include <stdio.h>
#include <string.h>

void funcao_Z(char S[], int Z[]) {
    int n = strlen(S);
    int l = 0, r = 0;
    
    Z[0] = n; // Z[0] pode ser o comprimento de S ou 0
    
    for(int i = 1; i < n; i++) {
        if(i > r) { // Caso 1
            l = i;
            r = i;
            while(r < n && S[r - l] == S[r]) {
                r++;
            }
            Z[i] = r - l;
            r--;
        } else { // Caso 2
            int k = i - l; // k = i'
            if(Z[k] < r - i + 1) { // Caso 2.a
                Z[i] = Z[k];
            } else { // Caso 2.b 
                l = i;
                while(r < n && S[r - l] == S[r]) {
                    r++;
                }
                Z[i] = r - l;
                r--;
            }
        }
    } 
}

int main() {
    char P[] = "ana";
    char T[] = "banana"; 
    
    // Concatenando P + "$" + T
    char S[200];
    snprintf(S, sizeof(S), "%s$%s", P, T);

    int n = strlen(S);
    int Z[200] = {0};

    // Executa a função Z
    funcao_Z(S, Z);

    // Exibição dos resultados
    printf("String S: %s\n", S);
    printf("Vetor Z:  ");
    for(int i = 0; i < n; i++) {
        printf("%d ", Z[i]);
    }
    printf("\n\n");

    // Buscando o padrão P em T
    int len_p = strlen(P);
    printf("Padrao \"%s\" encontrado nas posicoes de T:\n", P);
    for(int i = 0; i < n; i++) {
        // Se o valor de Z[i] for igual ao tamanho do padrão, encontramos uma ocorrência
        if(Z[i] == len_p) {
            // A posição real em T desconta o tamanho de P e o caractere '$' (len_p + 1)
            int pos_T = i - len_p - 1;
            printf("- Indice %d\n", pos_T);
        }
    }

    return 0;
}