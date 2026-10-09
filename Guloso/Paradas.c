/* 
===================================================================
Seleção de paradas

Problema:
    > Viagem da cidade A para a cidade B ao longo
    de uma rodovia
    > Tanque de combustível tem capacidade suficiente
    para cobrir n quilômetros
    > Mapa indica a localização dos postos de
    combustível ao longo do caminho
===================================================================
Objetivo: 
    > minimizar a quantidade de paradas ao longo da viagem
===================================================================
Solução gulosa: 
    Avançar a viagem o máximo que puder antes
    de reabastecer
===================================================================
*/
#include <stdio.h>

/* postos[] em ordem crescente (km desde A). 'destino' é o km de B.
   Preenche paradas[] e retorna a quantidade de paradas (-1 se impossível). */
int solucao(int destino, int postos[], int n, int tanque, int paradas[]) {
    int atual = 0;      // km onde o carro está (começa em A, tanque cheio)
    int qtd = 0;
    int i = 0;          // próximo posto a considerar

    while (destino - atual > tanque) {          // ainda não dá pra chegar em B
        int melhor = -1;
        // avança até o posto mais distante alcançável
        while (i < n && postos[i] - atual <= tanque) {
            melhor = postos[i];
            i++;
        }
        if (melhor == -1) return -1;            // nenhum posto ao alcance
        paradas[qtd++] = melhor;
        atual = melhor;
    }
    return qtd;
}

int main() {
    int caminho = 6;
    int postos[] = {1, 2, 3, 4, 5};             // postos nos km 1..5
    int n = sizeof(postos) / sizeof(postos[0]);
    int tanque = 4;
    int paradas[100];

    int q = solucao(caminho, postos, n, tanque, paradas);

    if (q < 0) {
        printf("Viagem impossivel\n");
        return 1;
    }
    printf("Paradas: %d | Postos: ", q);
    for (int i = 0; i < q; i++)
        printf("%d%s", paradas[i], i < q - 1 ? ", " : "");
    printf("\n");
    return 0;
}