#include <stdio.h>
#include <stdlib.h>

/* ========== Nó da árvore ========== */

typedef struct No {
    unsigned char byte;
    unsigned long freq;
    struct No *esq, *dir;
} No;

No *novo_no(unsigned char byte, unsigned long freq, No *esq, No *dir) {
    No *n = malloc(sizeof(No));
    if(!n) {
        perror("malloc");
        exit(1);
    }
    n -> byte = byte;
    n -> freq = freq;
    n -> esq = esq;
    n -> dir = dir;
    return n;
}

int eh_folha(No *n) {
    if(n -> esq == NULL && n -> dir == NULL) return 1;
    return 0;
}

/* ========== Contador de frequencias ========== */


void contar_frequencias(const char *nome_arquivo, unsigned long freq[256]) {
    FILE *f = fopen(nome_arquivo, "rb");
    if (f == NULL) {
        perror("fopen");
        exit(1);
    }
    int c;
    while ((c = fgetc(f)) != EOF) {
        freq[c]++;
    }
    fclose(f);
}

/* ========== Main ========== */

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "Uso: %s arquivo\n", argv[0]);
        return 1;
    }
    unsigned long freq[256] = {0};
    contar_frequencias(argv[1], freq);
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) printf("%d (%c): %lu\n", i, i, freq[i]);
    }
}