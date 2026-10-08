/* 
=================================================================== 
* Imagine que você trabalhe no caixa de um supermercado em uma
* cidade do interior. Sempre que o cliente paga a conta, você deve
* entregar o troco em moedas. Nesta situação, você quer entregar
* o menor número de moedas possível ao cliente.
* Para um valor de troco N, e com um estoque infinito de cada
* uma das M moedas de diferentes valores m1, m2, · · · , mM, quais
* e quantas moedas você deve entregar para o cliente de modo
* que o total de moedas seja o mínimo possível?
=================================================================== 
Escolha gulosa:

Devolver o número mínimo de moedas de mais alto valor cuja
soma total resulta no valor de determinado troco.
=================================================================== 
*/
#include <stdio.h>

int qntdMoedas(int n, int m[], int t) {
    // considerando que mochila esteja ordenado
    if(n == 0) return 0;
    if(m[t] < n) return 1 + qntdMoedas(n - m[t], m, t);
    return qntdMoedas(n, m, t-1);
}

int troco(int C[], int n, int t) {
    int soma = 0;
    int qntd = 1;
    int troco[100];
    while(C != 0 && soma < valor) {
        int m = C[0]; // moeda de maior valor
        for(int i = 0; i < t; i++) {
            if(m < C[i]) m = C[i];
        }
        if(soma + m <= valor) {
            soma = soma + m;
            troco[qntd] = m;
            qntd++;
        } 
    } 
    if (soma == valor) {
        troco[0] = qntd;
        return troco;
    }
    else {
        printf("Não encontrei a solução\n");
        return 0;
    }
}

int main() {
    int total = 3;
    int valor = 12;
    int moedas[total] = {1, 2, 5};
    int quantidade = qntdMoedas(valor, moedas, total - 1);
    int troco[100] = troco(moedas, valor, total);
    printf("Moedas: ");
    for(int i = 1; i < troco[0]; i++) {
        printf("%d, ", troco[i]);
    }
    if(quantidade == troco[0]) printf("Quantidade: %d", quantidade);
    return 0;
}

/* 
===================================================================
Esta estratégia nem sempre é a melhor, exemplo: 
N = 8 |&| M = {1, 4, 6}
===================================================================
*/