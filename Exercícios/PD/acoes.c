#include <stdio.h>
#include <stdbool.h>
#define N 6

int media(int ate, int precos[]) {
    int soma = 0;
    for(int j = 0; j <= ate; j++){
        soma += precos[j];
    }
    return soma / (ate + 1);
}

bool compra(int valor, int media) {
    if(valor <= 0) return true; 
    else {
        if(valor < media) { 
            return true; 
        }
    }
    return false;
}

bool vende(int valor, int media, int valor_da_compra) {
    if(valor < valor_da_compra) return false; // Evita vender com prejuízo
    else {
        if(valor > media) { 
            return true; 
        }
    }
    return false;
}

int main() {
    int precos[] = {7, 1, 5, 3, 6, 4};

    bool comprou = false;
    bool vendeu = false;
    int valor[] = {0, 0, 0, 0}; // [0]=Preço compra, [1]=Dia compra, [2]=Preço venda, [3]=Dia venda
    int media_atual = 0;

    for(int i = 0; i < N; i++) {
        media_atual = media(i, precos);

        if(!comprou) { // Tentando comprar
            comprou = compra(precos[i], media_atual);
            if(comprou) {
                valor[0] = precos[i];
                valor[1] = i;
                printf("Comprou no dia %d por %d (Media: %d)\n", i, precos[i], media_atual);
            }
        }
        else { // Já comprou, tentando vender
            vendeu = vende(precos[i], media_atual, valor[0]);
            if(vendeu) {
                valor[2] = precos[i];
                valor[3] = i;
                printf("Vendeu no dia %d por %d (Media: %d)\n", i, precos[i], media_atual);
                break; // Encerra o loop após a venda bem-sucedida
            }
        }
    }

    // Exibição do resumo final
    if (comprou && vendeu) {
        int lucro = valor[2] - valor[0];
        printf("\nResumo:\n");
        printf("Preco de Compra: %d (Dia %d)\n", valor[0], valor[1]);
        printf("Preco de Venda: %d (Dia %d)\n", valor[2], valor[3]);
        printf("Lucro Final: %d\n", lucro);
    } else if (comprou && !vendeu) {
        printf("\nComprou no dia %d por %d, mas nao encontrou oportunidade de venda até o final.\n", valor[0], valor[1]);
    } else {
        printf("Nenhuma compra foi realizada.\n");
    }

    return 0;
}