#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ========== Nó da árvore ========== */

typedef struct No {
    unsigned char byte;
    unsigned long freq;
    struct No *esq, *dir;
} No;

/* ========== Criador de Nó ========== */

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

/* ========== Verificador de Folhas ========== */

int eh_folha(No *n) {
    if(n -> esq == NULL && n -> dir == NULL) return 1;
    return 0;
}

/* ========== Removedor de Nó ========== */

No *remover_menor(No *lista[], int *tam) {
    int menor = 0;
    for(int i = 0; i < *tam; i++) {
        if(lista[i]->freq < lista[menor]->freq) {
            menor = i;
        }
    }
    No *removido = lista[menor];
    lista[menor] = lista[*tam - 1];
    (*tam)--;
    return removido;
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

/* ========== Montador da Árvore ========== */

No *construir_arvore(No *lista[], int *tam) {
    while(*tam > 1) {
        No *menor = remover_menor(lista, tam);
        No *menor2 = remover_menor(lista, tam);
        No *pai = novo_no('0', menor->freq + menor2->freq, menor, menor2);
        (*tam)++;
        lista[*tam - 1] = pai;
    }
    return lista[0];
}

/* ========== Gerador de Código ========== */

void gerar_codigos(No *n, char *caminho, int prof, char codigos[256][257]) {
    if (eh_folha(n)) {
        if(prof == 0) {
            strcpy(codigos[n->byte], "0");     
            return;
        }
        caminho[prof] = '\0';               
        strcpy(codigos[n->byte], caminho);     
        return;
    }

    caminho[prof] = '0';
    gerar_codigos(n->esq, caminho, prof + 1, codigos);  

    caminho[prof] = '1';
    gerar_codigos(n->dir, caminho, prof + 1, codigos);  
}

/* ========== Compactador ========== */

void compactar(const char *entrada, const char *saida, unsigned long freq[256], char codigos[256][257]) {
    FILE *in  = fopen(entrada, "rb");
    if (!in) {
        perror("fopen entrada");
        exit(1);
    }
    FILE *out = fopen(saida, "wb");
    if (!out) {
        perror("fopen saida");
        fclose(in);
        exit(1);
    }

    /* Parte A: cabeçalho */
    for (int i = 0; i < 256; i++) {
        uint32_t f = freq[i];
        fwrite(&f, sizeof(uint32_t), 1, out);
    }

    /* Parte B: os bits */
    unsigned char buffer = 0;
    int nbits = 0;
    int c;
    while ((c = fgetc(in)) != EOF) {
        char *cod = codigos[c];
        for (int k = 0; cod[k] != '\0'; k++) {
            buffer = (buffer << 1);     // abre espaço pra 1 bit (deslocamento à esquerda)
            if (cod[k] == '1') 
                buffer = buffer | 1;    // liga o bit menos significativo
            nbits++;
            if (nbits == 8) {
                fwrite(&buffer, sizeof(unsigned char), 1, out); // grava o byte completo
                buffer = 0;
                nbits = 0;
            }
        }
    }
    // se sobrou nbits > 0: completar com zeros à direita e gravar
    if (nbits > 0) {
        buffer = buffer << (8 - nbits);
        fwrite(&buffer, sizeof(unsigned char), 1, out);
    }

    fclose(in);
    fclose(out);
}

/* ========== Descompactador ========== */

void descompactar(const char *entrada, const char *saida) {
    FILE *in = fopen(entrada, "rb");
    if (!in) {
        perror("fopen entrada compactada");
        exit(1);
    }
    
    FILE *out = fopen(saida, "wb");
    if (!out) {
        perror("fopen saida descompactada");
        fclose(in);
        exit(1);
    }

    /* Passo 1: Ler o cabeçalho (as frequências de 256 bytes) */
    unsigned long freq[256] = {0};
    unsigned long total_bytes = 0; // Quantidade total de caracteres originais no arquivo

    for (int i = 0; i < 256; i++) {
        uint32_t f;
        if (fread(&f, sizeof(uint32_t), 1, in) != 1) {
            fprintf(stderr, "Erro ao ler o cabeçalho do arquivo.\n");
            fclose(in);
            fclose(out);
            exit(1);
        }
        freq[i] = f;
        total_bytes += f;
    }

    // Se o arquivo original estava vazio
    if (total_bytes == 0) {
        fclose(in);
        fclose(out);
        return;
    }

    /* Passo 2: Reconstruir a árvore de Huffman */
    No* lista[256];
    int tamanho = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            lista[tamanho++] = novo_no((unsigned char) i, freq[i], NULL, NULL);
        }
    }

    // Caso especial: se houver apenas um tipo de caractere no arquivo
    No *raiz = NULL;
    if (tamanho == 1) {
        // Se só existe um caractere, criamos uma árvore com um nó pai artificial para o algoritmo não falhar
        raiz = novo_no('0', lista[0]->freq, lista[0], NULL);
    } else {
        raiz = construir_arvore(lista, &tamanho);
    }

    /* Passo 3: Ler os bits e decodificar */
    No *atual = raiz;
    unsigned char buffer;
    unsigned long bytes_decodificados = 0;

    // Lemos byte a byte do arquivo compactado
    while (fread(&buffer, sizeof(unsigned char), 1, in) == 1) {
        // Percorremos os 8 bits do byte da esquerda para a direita (do bit 7 até o 0)
        for (int i = 7; i >= 0; i--) {
            int bit = (buffer >> i) & 1; // Extrai o bit atual

            // Caminha na árvore
            if (bit == 0) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }

            // Se chegamos a uma folha, encontramos o caractere original!
            if (eh_folha(atual)) {
                fputc(atual->byte, out);
                bytes_decodificados++;
                atual = raiz; // Retorna para a raiz para o próximo caractere

                // Se já decodificamos todos os bytes originais, paramos 
                // (isso evita processar os bits de "padding" colocados no final)
                if (bytes_decodificados == total_bytes) {
                    break;
                }
            }
        }
        if (bytes_decodificados == total_bytes) {
            break;
        }
    }

    fclose(in);
    fclose(out);
}

/* ========== Main ========== */

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Uso:\n");
        fprintf(stderr, "  Compactar:   %s -c <arquivo_entrada> <arquivo_saida.huff>\n", argv[0]);
        fprintf(stderr, "  Descompactar: %s -d <arquivo_entrada.huff> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    char *modo = argv[1];
    char *entrada = argv[2];
    char *saida = argv[3];

    if (strcmp(modo, "-c") == 0) {
        unsigned long freq[256] = {0};
        contar_frequencias(entrada, freq);
        
        No* lista[256];
        int tamanho = 0;
        for(int i = 0; i < 256; i++) {
            if(freq[i] > 0) {
                lista[tamanho++] = novo_no((unsigned char) i, freq[i], NULL, NULL);
            }
        }

        if (tamanho == 0) {
            printf("Arquivo vazio.\n");
            return 0;
        }

        No *raiz = construir_arvore(lista, &tamanho);
        char codigos[256][257];
        char caminho[257];
        gerar_codigos(raiz, caminho, 0, codigos);

        compactar(entrada, saida, freq, codigos);
        printf("Arquivo compactado com sucesso!\n");

    } else if (strcmp(modo, "-d") == 0) {
        descompactar(entrada, saida);
        printf("Arquivo descompactado com sucesso!\n");

    } else {
        fprintf(stderr, "Modo desconhecido: %s. Use -c ou -d.\n", modo);
        return 1;
    }

    return 0;
}