#include <stdio.h>
#define N 5

// Adicionados os tipos 'int' nos parâmetros das funções
void compra(int precos[], int valor[]) {
    // Começa do 0 para testar todos os elementos
    for(int i = 0; i < N; i++) {
        if(valor[0] > precos[i]) {
            valor[0] = precos[i]; // Menor preço de compra
            valor[1] = i + 1;         // Dia da compra
        }
    }
}

void vende(int precos[], int valor[]) {
    // O ideal é começar a procurar a venda APÓS o dia da compra (valor[1] + 1)
    // Inicializamos o preço de venda com o próprio preço da compra (ou 0)
    valor[2] = valor[0]; 
    valor[3] = valor[1];

    for(int i = valor[1] + 1; i < N; i++) {
        if(precos[i] > valor[2]) {
            valor[2] = precos[i]; // Maior preço de venda após a compra
            valor[3] = i + 1;         // Dia da venda
        }
    }
}

int main() {
    int precos[] = {7, 1, 5, 3, 6, 4};

    // [0]=Preço compra, [1]=Dia compra, [2]=Preço venda, [3]=Dia venda
    // Inicializamos com o primeiro elemento para ter uma base de comparação
    int valor[] = {precos[0], 0, precos[0], 0}; 

    compra(precos, valor);
    vende(precos, valor);

    // Calculando o lucro
    int lucro = valor[2] - valor[0];

    // Exibindo o resultado
    if(lucro == 0) {
        printf("Nesse caso, nenhuma transação é realizada e o lucro máximo é igual a 0.");
        return 0;
    }

    printf("Compre no dia: %d, pelo preço de %d\n", valor[1], valor[0]);
    printf("Venda no dia: %d, pelo preço de %d\n", valor[3], valor[2]);
    printf("Lucro Final: %d\n", lucro);

    return 0;
}