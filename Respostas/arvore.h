
#ifndef _ARVORE_H
#define _ARVORE_H

#include "bitmap.h"

typedef struct Arvore Arvore;

Arvore *criaArvoreVazia();

Arvore *criaArvore(char caracter, int ehletra, int frequencia, Arvore* esq, Arvore* dir);

void criaBitmaps(Arvore *compactacao, bitmap **tabela, int posicao_vetor, unsigned short int caminho[8]);

int getFrequencia(Arvore *arv);

void liberaArvore(Arvore *arv);

void imprimeArvore(Arvore *arv);

#endif