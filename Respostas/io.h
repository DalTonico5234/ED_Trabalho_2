

#ifndef io_h
#define io_h

#include "bitmap.h"
#include <stdio.h>

#define MAX_BIGMAP 25165824 // equivale a 3 MB, em bits

void imprimeBinarios(bitmap *bigmap, bitmap *novo, unsigned short int forcaImpressao, FILE *compactado);

void leArquivo(int *caracteres, FILE *original);

#endif