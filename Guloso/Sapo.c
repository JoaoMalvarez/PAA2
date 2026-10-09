/* 
===================================================================
Pulo do Sapo:

Existem n pedras numa reta numérica, em posições distintas
p1, p2, · · · , pn. Dizemos que um sapo pode saltar de uma pedra
pi para outra pedra pj desde que a distância entre elas seja menor
ou igual a delta
===================================================================
Considere um sapo localizado inicialmente na pedra p1. Qual
é o menor número de saltos que ele precisa dar para chegar na
pedra pn?
===================================================================
Observe que:

> nunca vale "voltar", pois isso aumentaria a sequência de números
> O sapo deve pular o mais longe possível.
===================================================================
*/

#include <stdio.h>

/* p[] em ordem crescente. Preenche u[] com as pedras visitadas
   e retorna o número de saltos (ou -1 se for impossível). */
int salto_sapo(int p[], int n, int delta, int u[]) {
    int k = 0, i = 0;
    u[k++] = p[0];
    while (i < n - 1) {
        int j = i;
        while (j + 1 < n && p[j + 1] - p[i] <= delta) j++;  // pedra mais longe
        if (j == i) return -1;                              // sapo preso
        i = j;
        u[k++] = p[i];
    }
    return k - 1;
}

/* lago[i] == 1 se há pedra na posição i. Destino: posição 'local'. */
int puloSapo(int delta, int lago[], int local, int u[]) {
    int pos[100], n = 0;
    if (lago[0] != 1 || lago[local] != 1) return -1;
    for (int i = 0; i <= local; i++)
        if (lago[i] == 1) pos[n++] = i;
    return salto_sapo(pos, n, delta, u);
}

void imprime(int u[], int saltos) {
    if (saltos < 0) { printf("Sem solucao\n"); return; }
    printf("Saltos: %d | Caminho: ", saltos);
    for (int i = 0; i <= saltos; i++)
        printf("%d%s", u[i], i < saltos ? " -> " : "\n");
}

int main() {
    int sapo = 3;
    int lago[11] = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1};
    int outroLago[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int solucao[100], solucao2[100];

    imprime(solucao,  puloSapo(sapo, lago, 10, solucao));
    imprime(solucao2, salto_sapo(outroLago, 10, sapo, solucao2));
    return 0;
}