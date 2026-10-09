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

int *salto_sapo(int p[], int n, int delta) {
    int u[0] = p[0];
    int ultima_pos = p[0];
    int x = 1;
    for(int i = 1; i < n; i++) {
        if(p[i] - ultima_pos > delta) {
            ultima_pos = p[i - 1];
            u[x] = p[i - 1];
            x = x + 1;
        }
    }
    u[x] = p[n];
    return u;
}

int *puloSapo(int sapo, int lago[], int local) {
    if(lago[local] == 0) return 0;
    int v[0] = lago[0];
    int pos[local];
    int ultima_pos = lago[0];
    int x = 0;
    bool achou = true;
    for(int i = 0; i < local; i++) {
        if(lago[i] == 1) {
            pos[x] = i;
            x = x + 1;
        } 
    }
    x = 1;
    for(int i = 0; i < local; i++) {
        if(ultima_pos == local) return v;
        if(pos[i] - ultima_pos > sapo) {
            ultima_pos = pos[i - 1];
            v[x] = pos[i - 1];
            x = x + 1;
        }
    }
}

int main() {
    int sapo = 3; // distância maxima do salto
    int lago[9] = {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1}; // se for 1 é pedra
    int outroLago[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int local = 4;
    int solução[10] = puloSapo(sapo, lago, local, 9);
}