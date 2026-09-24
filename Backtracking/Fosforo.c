#include <stdio.h>
#define N 12

void mochila(v) {

}

bool verifica(v) {
    int aux;
    for (int i = 0; i < N; i++) {
        aux += v[i];
    }
    if (aux % 4 == 0) return true;
    else return false;
}

int main() {
    palitos_de_fosforos[N] = {4, 5, 8, 8, 4, 5, 5, 8, 4};
    bool ver = verifica(palitos_de_fosforos);
    if(!ver) printf("Não é possivel fazer um quadrado com os palitos disponiveis!");
    else {
        mochila(palitos_de_fosforos);
        
    }

}