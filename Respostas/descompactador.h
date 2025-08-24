

#ifndef descompactador_h
#define descompactador_h

#include "arvore.h"
#include <stdio.h>

typedef struct descompactador Descompactador;

Descompactador *criaDescompactador(char *caminho);

void executaDescompactacao(Descompactador *winrar);

void liberaDescompactador(Descompactador *winrar);

#endif