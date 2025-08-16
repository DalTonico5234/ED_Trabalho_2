#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Arvore
{
  char caracter;
  Arvore *esq;
  Arvore *dir;
  int ehletra;
  int frequencia;
};

Arvore *criaArvoreVazia() { return NULL; }

Arvore *criaArvore(char caracter, int ehletra, int frequencia, Arvore *esq,
                   Arvore *dir)
{
  Arvore *arv = (Arvore *)malloc(sizeof(Arvore));
  arv->caracter = caracter;
  arv->esq = esq;
  arv->dir = dir;
  arv->ehletra = ehletra;
  arv->frequencia = frequencia;
  return arv;
}

void criaBitmaps(Arvore *compactacao, bitmap **tabela, int posicao_vetor, unsigned short int caminho[8])
{
  static int posicao_tabela = 0;

  if (compactacao->ehletra)
  {
    printf("%c ", compactacao->caracter);
  }
  else
  {
    printf("%d ", compactacao->frequencia);
  }
  for (int i = 0; i < posicao_vetor; i++)
  {
    printf("%d", caminho[i]);
  }
  printf("\n\n");

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
    tabela[posicao_tabela] = sequencia;
    posicao_tabela++;
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