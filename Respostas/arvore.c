/**
 * @file arvore.c
 * Implementação do TAD arvore
 *
 * Criado e desenvolvido por:
 * @author Leonardo Cheregati de Oliveira Roxo
 * @author Matteo Chisté Carvalho Trento
 *
 * Parte do 2º Trabalho Prático: Compactador de Huffman, da disciplina Estutura de Dados,
 * lecionada pela Prof Patrícia Dockhorn Costa, do Departamento de Informática - UFES, no período 2025/1
 */

#include "arvore.h"
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

int getFrequencia(Arvore *arv) 
{ 
  return arv->frequencia; 
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

void imprimeArvore(Arvore *arv)
{
  if (arv)
  {
    if (arv->ehletra)
    {
      printf("Caracter: %c // Frequencia: %d\n", arv->caracter,
             arv->frequencia);
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
        printf("    Caracter: %c // Frequencia: %d\n", arv->esq->caracter,
               arv->esq->frequencia);
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
        printf("    Caracter: %c // Frequencia: %d\n", arv->dir->caracter,
               arv->dir->frequencia);
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

Arvore *reconstroiArvore(FILE *compactado, unsigned char *buffer_byte, int *posicao_bit)
{
  int bit = lerBit(compactado, buffer_byte, posicao_bit);

  // Se chegou ao fim do arquivo
  if (bit == -1)
  {
    return NULL;
  }

  // Se bit = 1, é uma folha (caracter)
  if (bit == 1)
  {
    unsigned short int caracter = 0;

    // Lê 9 bits para formar o caracter
    for (int i = 0; i < 9; i++)
    {
      int bit_char = lerBit(compactado, buffer_byte, posicao_bit);
      if (bit_char == -1)
      {
        printf("ERRO: fim inesperado do arquivo ao ler caracter\n");
        return NULL;
      }
      caracter = (caracter << 1) | bit_char;
    }

    return criaArvore(caracter, 1, 0, NULL, NULL);
  }

  // Se bit = 0, é um nó interno
  else
  {
    Arvore *esq = reconstroiArvore(compactado, buffer_byte, posicao_bit);
    Arvore *dir = reconstroiArvore(compactado, buffer_byte, posicao_bit);

    return criaArvore(0, 0, 0, esq, dir);
  }
}

unsigned int descompacta(Arvore *descompactacao, FILE *compactado, unsigned char *buffer_bytes, int *posicao_bits)
{
  Arvore *temp = descompactacao;

  // Verifica se a árvore existe
  if (!temp)
  {
    printf("ERRO: Arvore de descompactação não existe!\n");
    return TAM_ASCII -1;
  }

  // Se a raiz já é uma folha (caso especial para árvore com 1 nó)
  if (temp->ehletra)
  {
    return temp->caracter;
  }

  // Navega pela árvore até encontrar uma folha
  while (temp && !temp->ehletra)
  {
    int bit = lerBit(compactado, buffer_bytes, posicao_bits);

    if (bit == -1)
    {
      // Fim do arquivo
      return 256;
    }

    if (bit == 0)
    {
      temp = temp->esq;
    }
    else
    {
      temp = temp->dir;
    }

    // Verifica se a navegação é válida
    if (!temp)
    {
      printf("ERRO: Arvore inexistente!\n");
      return TAM_ASCII - 1;
    }
  }

  // Se chegou aqui, encontrou uma folha
  if (temp && temp->ehletra)
  {
    return temp->caracter;
  }

  printf("ERRO: não encontrou uma folha válida\n");
  return TAM_ASCII - 1; // Erro
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