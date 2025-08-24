#include "io.h"
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>

void imprimeBinarios(bitmap *bigmap, bitmap *novo,
                     unsigned short int forcaImpressao, FILE *compactado) {
  // condição para inicializar o bigmap
  if (!bigmap) {
    bigmap = bitmapInit(MAX_BIGMAP);
  }

  // Se novo é NULL, apenas força impressão se necessário
  if (!novo) {
    if (forcaImpressao && bitmapGetLength(bigmap) > 0) {
      // Calcula quantos bytes completos escrever
      unsigned int bytesToWrite = (bitmapGetLength(bigmap) + 7) / 8;
      fwrite(bitmapGetContents(bigmap), sizeof(unsigned char), bytesToWrite,
             compactado);
    }
    return;
  }

  // condição para imprimir no arquivo e resetar o bigmap
  if ((bitmapGetLength(bigmap) + bitmapGetLength(novo)) >=
      bitmapGetMaxSize(bigmap)) {
    // Escreve os bytes completos
    unsigned int bytesToWrite = (bitmapGetLength(bigmap) + 7) / 8;
    fwrite(bitmapGetContents(bigmap), sizeof(unsigned char), bytesToWrite,
           compactado);
    bitmapLibera(bigmap);
    bigmap = bitmapInit(MAX_BIGMAP);

    // Adiciona o novo bitmap ao bigmap limpo
    for (unsigned int i = 0; i < bitmapGetLength(novo); i++) {
      bitmapAppendLeastSignificantBit(bigmap, bitmapGetBit(novo, i));
    }
  } else if (forcaImpressao) {
    // Adiciona novo ao bigmap atual
    for (unsigned int i = 0; i < bitmapGetLength(novo); i++) {
      bitmapAppendLeastSignificantBit(bigmap, bitmapGetBit(novo, i));
    }
    // Força impressão
    unsigned int bytesToWrite = (bitmapGetLength(bigmap) + 7) / 8;
    fwrite(bitmapGetContents(bigmap), sizeof(unsigned char), bytesToWrite,
           compactado);
  }
  // condição para imprimir no bigmap
  else {
    for (unsigned int i = 0; i < bitmapGetLength(novo); i++) {
      bitmapAppendLeastSignificantBit(bigmap, bitmapGetBit(novo, i));
    }
  }
}

// Nova função para ler bit por bit
int lerBit(FILE *compactado, unsigned char *buffer_byte, int *posicao_bit) {
  // Se chegou ao final do byte atual, lê o próximo
  if (*posicao_bit >= 8) {
    if (fread(buffer_byte, sizeof(unsigned char), 1, compactado) != 1) {
      return -1; // Fim do arquivo
    }
    *posicao_bit = 0;
  }

  // Extrai o bit na posição atual
  int bit = (*buffer_byte >> (7 - *posicao_bit)) & 1;
  (*posicao_bit)++;

  return bit;
}