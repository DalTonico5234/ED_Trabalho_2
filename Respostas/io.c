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
    if ((bitmapGetLength(bigmap) + bitmapGetLength(novo)) >= bitmapGetMaxSize(bigmap))
    {
        fwrite(bitmapGetContents(bigmap), sizeof(unsigned char), bitmapGetLength(bigmap), compactado);
        bitmapLibera(bigmap);
        bigmap = NULL;
        imprimeBinarios(bigmap, novo, forcaImpressao, compactado);
    }
    else if (forcaImpressao)
    {
        fwrite(bitmapGetContents(bigmap), sizeof(unsigned char), bitmapGetLength(bigmap), compactado);
        bitmapLibera(bigmap);
        bigmap = NULL;
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
