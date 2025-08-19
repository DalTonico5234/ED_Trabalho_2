
#ifndef _ARVORE_H
#define _ARVORE_H

#include "bitmap.h"

#define TAM_MAX_CARACTER 9

typedef struct Arvore Arvore;

Arvore *criaArvoreVazia();

Arvore *criaArvore(unsigned short int caracter, unsigned short int ehletra, unsigned int frequencia, Arvore *esq, Arvore *dir);

void criaBitmaps(Arvore *compactacao, bitmap **tabela, int posicao_vetor, unsigned short int caminho[TAM_MAX_CARACTER]);

int getFrequencia(Arvore *arv);

void liberaArvore(Arvore *arv);

void imprimeArvore(Arvore *arv);

#endif