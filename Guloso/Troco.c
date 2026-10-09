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

/* Versão recursiva: moedas em ordem crescente, t = índice da maior */
int qntdMoedas(int n, int m[], int t) {
    if (n == 0) return 0;
    if (t < 0)  return -1;                 // sem solução
    if (m[t] <= n) {
        int r = qntdMoedas(n - m[t], m, t);
        return r < 0 ? -1 : 1 + r;
    }
    return qntdMoedas(n, m, t - 1);
}

/* Versão iterativa: preenche res[] com as moedas e retorna a quantidade
   (ou -1 se não houver solução) */
int troco(int C[], int t, int valor, int res[]) {
    int qntd = 0;
    for (int i = t - 1; i >= 0 && valor > 0; i--) {   // C ordenado crescente
        while (C[i] <= valor) {
            valor -= C[i];
            res[qntd++] = C[i];
        }
    }
    return valor == 0 ? qntd : -1;
}

int main() {
    int moedas[] = {1, 2, 5};
    int total = sizeof(moedas) / sizeof(moedas[0]);
    int valor = 12;
    int res[100];

    int quantidade = qntdMoedas(valor, moedas, total - 1);
    int q = troco(moedas, total, valor, res);

    if (q < 0) {
        printf("Não encontrei a solução\n");
        return 1;
    }

    printf("Moedas: ");
    for (int i = 0; i < q; i++)
        printf("%d%s", res[i], i < q - 1 ? ", " : "\n");
    printf("Quantidade: %d (recursiva: %d)\n", q, quantidade);
    return 0;
}
/* 
===================================================================
Esta estratégia nem sempre é a melhor, exemplo: 
N = 8 |&| M = {1, 4, 6}
===================================================================
*/