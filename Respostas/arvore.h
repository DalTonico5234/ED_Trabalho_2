
#ifndef _ARVORE_H
#define _ARVORE_H

#include "bitmap.h"
#include "compactador.h"
#include "io.h"

#define TAM_MAX_CARACTER 9
#define MAX_ARV

typedef struct arvore Arvore;

Arvore *criaArvoreVazia();

Arvore *criaArvore(unsigned short int caracter, unsigned short int ehletra,
                   unsigned int frequencia, Arvore *esq, Arvore *dir);

void criaBitmaps(Arvore *compactacao, bitmap **tabela, int posicao_vetor,
                 unsigned short int caminho[TAM_MAX_CARACTER]);

void imprimeArvoreNoArquivo(Arvore *arv, FILE *compactado, bitmap *bigmap);

int getFrequencia(Arvore *arv);

void liberaArvore(Arvore *arv);

void imprimeArvore(Arvore *arv);

Arvore *reconstroiArvore(FILE *compactado, unsigned char *buffer_byte,
                         int *posicao_bit);

unsigned int descompacta(Arvore *descompactacao, FILE *compactado,
                         unsigned char *buffer_bytes, int *posicao_bits);
#endif