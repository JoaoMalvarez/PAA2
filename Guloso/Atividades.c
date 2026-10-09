/* 
===================================================================
Problema da seleção de atividades:

Considere um conjunto {1, 2, · · · , n} de n atividades que 
competem por um recurso, por exemplo uma sala de aula.

Cada atividade tem um início si e um término ti, com si ≤ ti

O intervalo requerido pela atividade é [si, ti]
===================================================================
Duas atividades i e j são compatíveis se os intervalos [si, ti]
[sj, tj] não se interceptam (si ≥ tj ou sj ≥ ti)
===================================================================
Problema: 
    encontrar o conjunto de atividades mutuamente
    compatíveis de tamanho máximo
===================================================================
*/
#include <stdio.h>
#include <stdlib.h>

#define N 11

typedef struct { int id, s, t; } Atividade;

/* Critérios de ordenação, com desempate por id para ficar determinístico */
int cmp_inicio(const void *a, const void *b) {
    const Atividade *x = a, *y = b;
    return x->s != y->s ? x->s - y->s : x->id - y->id;
}
int cmp_duracao(const void *a, const void *b) {
    const Atividade *x = a, *y = b;
    int dx = x->t - x->s, dy = y->t - y->s;
    return dx != dy ? dx - dy : x->id - y->id;
}
int cmp_termino(const void *a, const void *b) {
    const Atividade *x = a, *y = b;
    return x->t != y->t ? x->t - y->t : x->id - y->id;
}

int compativel(Atividade a, Atividade b) {
    return a.s >= b.t || b.s >= a.t;
}

/* Ordena uma cópia pelo critério dado e escolhe cada atividade que seja
   compatível com TODAS as já escolhidas. Retorna a quantidade. */
int selecao(Atividade ativ[], int n,
            int (*cmp)(const void *, const void *), int sel[]) {
    Atividade v[N], esc[N];
    int k = 0;

    for (int i = 0; i < n; i++) v[i] = ativ[i];
    qsort(v, n, sizeof(Atividade), cmp);

    for (int i = 0; i < n; i++) {
        int ok = 1;
        for (int j = 0; j < k; j++)
            if (!compativel(v[i], esc[j])) { ok = 0; break; }
        if (ok) {
            esc[k] = v[i];
            sel[k++] = v[i].id;
        }
    }
    return k;
}

void imprime(const char *nome, int sel[], int k) {
    printf("%-18s %d atividades: ", nome, k);
    for (int i = 0; i < k; i++)
        printf("%d%s", sel[i], i < k - 1 ? ", " : "\n");
}

int main() {
    Atividade ativ[N] = {
        { 1,  1,  4}, { 2,  3,  5}, { 3,  0,  6}, { 4,  5,  7},
        { 5,  3,  9}, { 6,  5,  9}, { 7,  6, 10}, { 8,  8, 11},
        { 9,  8, 12}, {10,  2, 14}, {11, 12, 16}
    };
    int sel[N];
    int k;

    k = selecao(ativ, N, cmp_inicio,  sel); imprime("Comecam primeiro:", sel, k);
    k = selecao(ativ, N, cmp_duracao, sel); imprime("Menos tempo:",      sel, k);
    k = selecao(ativ, N, cmp_termino, sel); imprime("Terminam primeiro:", sel, k);
    return 0;
}