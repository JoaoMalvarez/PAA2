/*
Problema da mochila fracionária:
Os objetos podem ser particionados, ou seja, você pode colocar 
uma fração do objeto na mochila.
ex.: ouro em pó
*/
#include <stdio.h>
#define N 3

void ordena(int peso[], int valor[]){
    int i;
    while(i < N) {
        if(valor[i] / peso[i] < valor[i+1] / peso[i + 1]) {
            int valaux = valor[i];
            int pesaux = peso[i];
            valor[i] = valor[i+1];
            peso[i] = peso[i+1];
            valor[i+1] = valaux;
            peso[i+1] = pesaux;
            if(i > 0) i = i - 1;
            else i = i +1;
        }
    }
}

int mochila(int capacidade, int peso[], int valor[]) {
    ordena(int peso, int valor);
    int mochila[N];
    int i = 0;
    while(i <= N && capacidade > 0) {
        if(peso[i] <= capacidade) {
            mochila[i] = 1;
            capacidade = capacidade - peso[i];
            i = i + 1;
        } else {
            mochila[i] = capacidade / peso[i];
            capacidade = 0;
        }
    }
    return mochila;
}

int main() {
    int valor[N] = {60, 100, 120};
    int peso[N] = {10, 20, 30};
    int capacidade = 50;
    int mochila[N] = mochila(capacidade, peso, valor);
}