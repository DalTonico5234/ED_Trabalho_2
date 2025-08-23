#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arvore
{
  unsigned short int caracter;
  Arvore *esq;
  Arvore *dir;
  unsigned short int ehletra;
  unsigned int frequencia;
};

Arvore *criaArvoreVazia() { return NULL; }

Arvore *criaArvore(unsigned short int caracter, unsigned short int ehletra, unsigned int frequencia, Arvore *esq, Arvore *dir)
{
  Arvore *arv = (Arvore *)malloc(sizeof(Arvore));
  arv->caracter = caracter;
  arv->esq = esq;
  arv->dir = dir;
  arv->ehletra = ehletra;
  arv->frequencia = frequencia;
  return arv;
}

void criaBitmaps(Arvore *compactacao, bitmap **tabela, int posicao_vetor, unsigned short int caminho[TAM_MAX_CARACTER])
{
  if (!compactacao)
  {
    return;
  }
  if (compactacao->ehletra) // chegou a um nó
  {
    bitmap *sequencia = bitmapInit(posicao_vetor);
    for (int i = 0; i < posicao_vetor; i++)
    {
      bitmapAppendLeastSignificantBit(sequencia, (unsigned char)caminho[i]);
    }
    tabela[compactacao->caracter] = sequencia;
  }
  if (compactacao->esq) // recursao para a esquerda
  {
    caminho[posicao_vetor] = 0;
    posicao_vetor++;
    criaBitmaps(compactacao->esq, tabela, posicao_vetor, caminho);
    posicao_vetor--;
  }
  if (compactacao->dir) // recursao para a direita
  {
    caminho[posicao_vetor] = 1;
    posicao_vetor++;
    criaBitmaps(compactacao->dir, tabela, posicao_vetor, caminho);
  }
}

void liberaArvore(Arvore *arv)
{
  if (arv != NULL)
  {
    liberaArvore(arv->esq);
    liberaArvore(arv->dir);
    free(arv);
    arv = NULL;
  }
}

int getFrequencia(Arvore *arv)
{
  return arv->frequencia;
}

void imprimeArvore(Arvore *arv)
{
  if (arv)
  {
    if (arv->ehletra)
    {
      printf("Caracter: %c // Frequencia: %d\n", arv->caracter, arv->frequencia);
    }
    else
    {
      printf("Frequencia: %d\n", arv->frequencia);
    }

    printf("Esquerda: \n");
    if (arv->esq)
    {
      if (arv->esq->ehletra)
      {
        printf("    Caracter: %c // Frequencia: %d\n", arv->esq->caracter, arv->esq->frequencia);
      }
      else
      {
        printf("    Frequencia: %d\n", arv->esq->frequencia);
      }
    }
    else
    {
      printf("NULL\n");
    }

    printf("Direita: \n");
    if (arv->dir)
    {
      if (arv->dir->ehletra)
      {
        printf("    Caracter: %c // Frequencia: %d\n", arv->dir->caracter, arv->dir->frequencia);
      }
      else
      {
        printf("    Frequencia: %d\n", arv->dir->frequencia);
      }
    }
    else
    {
      printf("NULL\n");
    }

    if (arv->esq)
    {
      imprimeArvore(arv->esq);
    }
    if (arv->dir)
    {
      imprimeArvore(arv->dir);
    }
  }
}

void binario(int n, bitmap *bigmap)
{
  if (n)
  {
    binario(n / 2, bigmap);
    bitmapAppendLeastSignificantBit(bigmap, n % 2);
  }
}

void imprimeArvoreNoArquivo(Arvore *arv, FILE *compactado, bitmap *bigmap)
{
  if (!arv)
  {
    return;
  }

  if (arv->ehletra)
  {
    bitmapAppendLeastSignificantBit(bigmap, 1);
    unsigned short int caracter = arv->caracter;
    for (int i = 8; i >= 0; i--)
    {
      unsigned char bit = (caracter >> i) & 1;
      bitmapAppendLeastSignificantBit(bigmap, bit);
    }
  }
  else
  {
    bitmapAppendLeastSignificantBit(bigmap, 0);
  }

  imprimeArvoreNoArquivo(arv->esq, compactado, bigmap);
  imprimeArvoreNoArquivo(arv->dir, compactado, bigmap);
}