
#ifndef _COMPACTADOR_H
#define _COMPACTADOR_H

#include "arvore.h"
#include "bitmap.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct compactador Compactador;

Compactador *criaCompactador(char *caminho);

void preencheCompacator(Compactador *compact);

void executaCompactacao(Compactador *compact);

void liberaCompactador(Compactador *compact);

#endif