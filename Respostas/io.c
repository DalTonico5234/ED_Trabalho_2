#include "io.h"
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>

void imprimeBinarios(bitmap *bigmap, bitmap *novo,
                     unsigned short int forcaImpressao, FILE *compactado)
{
  if (!novo)
  {
    printf("ERRO: bitmap não pode ser inserido aqui!\n");
    return;
  }
  // condição para inicializar o bigmap
  if (!bigmap)
  {
    bigmap = bitmapInit(MAX_BIGMAP);
  }
  // condição para imprimir no arquivo e resetar o bigmap
  if ((bitmapGetLength(bigmap) + bitmapGetLength(novo)) >=
      bitmapGetMaxSize(bigmap))
  {
    fwrite(bitmapGetContents(bigmap), sizeof(unsigned char),
           bitmapGetLength(bigmap), compactado);
    bitmapLibera(bigmap);
    bigmap = NULL;
    imprimeBinarios(bigmap, novo, forcaImpressao, compactado);
  }
  else if (forcaImpressao)
  {
    imprimeBinarios(bigmap, novo, 0, compactado);
    fwrite(bitmapGetContents(bigmap), sizeof(unsigned char),
           bitmapGetLength(bigmap), compactado);
  }
  // condição para imprimir no bigmap
  else
  {
    for (unsigned int i = 0; i < bitmapGetLength(novo); i++)
    {
      bitmapAppendLeastSignificantBit(bigmap, bitmapGetBit(novo, i));
    }
  }
}

// Nova função para ler bit por bit
int lerBit(FILE *compactado, unsigned char *buffer_byte, int *posicao_bit)
{
  // Se chegou ao final do byte atual, lê o próximo
  if (*posicao_bit >= 8)
  {
    if (fread(buffer_byte, sizeof(unsigned char), 1, compactado) != 1)
    {
      return -1; // Fim do arquivo
    }
    *posicao_bit = 0;
  }

  // Extrai o bit na posição atual
  int bit = (*buffer_byte >> (7 - *posicao_bit)) & 1;
  (*posicao_bit)++;

  return bit;
}