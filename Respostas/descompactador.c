

#include "descompactador.h"
#include <stdlib.h>

struct descompactador
{
  Arvore *descompactacao;
  FILE *compactado;
  FILE *descompactado;
};

Descompactador *criaDescompactador(char *caminho)
{
  Descompactador *winrar = (Descompactador *)malloc(sizeof(Descompactador));

  winrar->compactado = winrar->descompactado = NULL;
  winrar->descompactacao = NULL;

  winrar->compactado = fopen(caminho, "rb");
  caminho[strlen(caminho) - 5] = '\0';
  winrar->descompactado = fopen(caminho, "wb");

  if (!winrar->compactado || !winrar->descompactado)
  {
    printf("ERRO NA ABERTURA DOS ARQUIVOS: verifique o caminho passado!\n\n");
    liberaDescompactador(winrar);
    exit(1);
  }

  return winrar;
}

void executaDescompactacao(Descompactador *winrar)
{
  unsigned char buffer_bytes = 0;
  int posicao_bits = 8;
  winrar->descompactacao =
      reconstroiArvore(winrar->compactado, &buffer_bytes, &posicao_bits);
  // printf("buffer_bytes: %d\n", (unsigned int)buffer_bytes);
  // printf("posicao_bits: %d\n", posicao_bits);
  // imprimeArvore(winrar->descompactacao);
  unsigned char *bigstring = (unsigned char *)malloc(sizeof(unsigned char) * MAX_BIGMAP / 8);
  unsigned int lido = 0;
  int indice = 0;
  while (1)
  {
    lido = descompacta(winrar->descompactacao, winrar->compactado,
                       &buffer_bytes, &posicao_bits);
    if (lido == 256)
    {
      fwrite(bigstring, sizeof(unsigned char), indice, winrar->descompactado);
      free(bigstring);
      return;
    }
    if (indice == MAX_BIGMAP / 8)
    {
      fwrite(bigstring, sizeof(unsigned char), indice, winrar->descompactado);
      free(bigstring);
      bigstring = (unsigned char *)malloc(sizeof(unsigned char) * MAX_BIGMAP / 8);
      indice = 0;
    }
    bigstring[indice] = lido;
    indice++;
  }
}

void liberaDescompactador(Descompactador *winrar)
{
  if (winrar->compactado)
  {
    fclose(winrar->compactado);
  }
  if (winrar->descompactado)
  {
    fclose(winrar->descompactado);
  }
  if (winrar->descompactacao)
  {
    fclose(winrar->descompactado);
  }
  if (winrar->descompactacao)
  {
    liberaArvore(winrar->descompactacao);
  }
  if (winrar)
  {
    free(winrar);
  }
}