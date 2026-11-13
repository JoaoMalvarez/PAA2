/*===============================
  Casamento de Padrões: 
  - Algoritmo Z - Zvi Galil
===============================*/ 

#include <stdio.h>
#include <string.h>

void funcao_Z(char S[], int Z[]) {
    int n = strlen(S);
    int l = 0, r = 0;
    
    Z[0] = n; 
    
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
            int k = i - l; 
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

    // Exibição dos resultados gerais
    printf("String S: %s\n", S);
    printf("Vetor Z:  ");
    for(int i = 0; i < n; i++) {
        printf("%d ", Z[i]);
    }
    printf("\n\n");

    // Buscando o padrão P em T de forma visual
    int len_p = strlen(P);
    int len_t = strlen(T);
    printf("Padrao \"%s\" encontrado em T:\n\n", P);
    
    int encontradas = 0;
    for(int i = 0; i < n; i++) {
        if(Z[i] == len_p) {
            int pos_T = i - len_p - 1;
            encontradas++;

            printf("Ocorrencia #%d (Indice %d):\n", encontradas, pos_T);
            printf("T: ");
            
            // Imprime o texto T destacando a palavra encontrada em NEGRITO / COR
            for(int j = 0; j < len_t; j++) {
                if(j == pos_T) {
                    printf("["); 
                }
                
                printf("%c", T[j]);
                
                if(j == pos_T + len_p - 1) {
                    printf("]"); 
                }
            }
            printf("\n\n");
        }
    }
    
    if(encontradas == 0) {
        printf("Nenhuma ocorrencia encontrada.\n");
    }

    return 0;
}
