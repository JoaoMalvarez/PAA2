#include <stdio.h>

int melhor(int x, int y, int custo[], int i) { // pega o de menor preço
    if(x < y) return i;  // se x for menor retorna ele
    else return i + 1; // se y for menor ou igual retorna ele
}

int main() {
    int custo[10,15,20] = {} // tmb tem: {1,100,1,1,1,100,1,1,100,1}

    int comeca = melhor(custo[0], custo[1], custo, 0);
    
    while(true) {
        break;
    }
    return 0;
}