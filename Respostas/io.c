#include "io.h"
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>

void imprimeBinarios(bitmap *bigmap, bitmap *novo, unsigned short int forcaImpressao, FILE *compactado)
{
    // condição para inicializar o bigmap
    if (!bigmap)
    {
        bigmap = bitmapInit(MAX_BIGMAP);
    }
    // condição para imprimir no arquivo e resetar o bigmap
    else if (forcaImpressao || (bitmapGetLength(bigmap) == bitmapGetMaxSize(bigmap)))
    {
        fwrite(bitmapGetContents(bigmap), sizeof(unsigned char), bitmapGetLength(bigmap), compactado);
        bitmapLibera(bigmap);
        bigmap = NULL;
        imprimeBinarios(bigmap, novo, forcaImpressao, compactado);
    }
    // condição para imprimir no bigmap
    else 
    {
        for (unsigned int i=0; i < bitmapGetLength(novo); i++)
        {
            bitmapAppendLeastSignificantBit(bigmap, bitmapGetBit(novo, i));
        }
    }
    
}

void leArquivo(int *caracteres, FILE *original)
{
    char lido;
    while (fread(&lido, sizeof(char), 1, original) == 1)
    {
        caracteres[(int)lido]++;
    }
}