/**
 * @file lista.c
 * Implementação do TAD lista
 * 
 * Criado e desenvolvido por:
 * @author Leonardo Cheregati de Oliveira Roxo 
 * @author Matteo Chisté Carvalho Trento
 * 
 * Parte do 2º Trabalho Prático: Compactador de Huffman, da disciplina Estutura de Dados,
 * lecionada pela Prof Patrícia Dockhorn Costa, do Departamento de Informática - UFES, no período 2025/1
 */

#include "lista.h"
#include <stdlib.h>
#include <string.h>

typedef struct Celula Celula;

struct Celula
{
  Arvore *arvore;
  Celula *prox;
};

struct lista
{
  Celula *prim;
  Celula *ult;
};

Lista *criaListaVazia()
{
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  lista->prim = NULL;
  lista->ult = NULL;
  return lista;
}

void liberaLista(Lista *lista)
{
  Celula *temp = lista->prim;
  Celula *prox;
  while (temp != NULL)
  {
    prox = temp->prox;
    free(temp);
    temp = prox;
  }
  free(lista);
}

void insereLista(Lista *lista, Arvore *arv)
{
  if (!arv || !lista)
  {
    return;
  }
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->arvore = arv;
  if (!lista->ult)
  {
    lista->ult = nova;
    lista->prim = nova;
    nova->prox = NULL;
  }
  else if (getFrequencia(arv) < getFrequencia(lista->prim->arvore))
  {
    nova->prox = lista->prim;
    lista->prim = nova;
  }
  else if (getFrequencia(arv) > getFrequencia(lista->ult->arvore))
  {
    lista->ult->prox = nova;
    lista->ult = nova;
    lista->ult->prox = NULL;
  }
  else
  {
    Celula *aux = lista->prim;
    while (aux->prox != NULL &&
           getFrequencia(arv) > getFrequencia(aux->prox->arvore))
    {
      aux = aux->prox;
    }
    nova->prox = aux->prox;
    aux->prox = nova;
  }
}

Celula *buscaCelula(Lista *lista, Arvore *arv)
{
  Celula *aux = lista->prim;
  while (aux != NULL && aux->arvore != arv)
  {
    aux = aux->prox;
  }
  return aux;
}

void removeLista(Lista *lista, Arvore *arv)
{
  Celula *aux = buscaCelula(lista, arv);
  if (aux == NULL)
  {
    return;
  }
  else if (lista->prim == aux && lista->ult == aux)
  {
    lista->prim = NULL;
    lista->ult = NULL;
    free(aux);
  }
  else if (lista->prim == aux)
  {
    lista->prim = aux->prox;
    free(aux);
  }
  else if (lista->ult == aux)
  {
    Celula *aux2 = lista->prim;
    while (aux2->prox != aux)
    {
      aux2 = aux2->prox;
    }
    lista->ult = aux2;
    lista->ult->prox = NULL;
    free(aux);
  }
  else
  {
    Celula *aux2 = lista->prim;
    while (aux2->prox != aux)
    {
      aux2 = aux2->prox;
    }
    aux2->prox = aux->prox;
    free(aux);
  }
}

int ehListaUnica(Lista *lista)
{
  if (!lista)
  {
    return 0;
  }
  return (lista->prim == lista->ult && lista->prim && lista->ult);
}

Arvore *criaArvoreHuffman(Lista *caracteres)
{
  if (!caracteres)
  {
    return NULL;
  }
  Arvore *compactacao;
  while (!ehListaUnica(caracteres))
  {
    compactacao = criaArvore(0, 0, getFrequencia(caracteres->prim->arvore) + getFrequencia(caracteres->prim->prox->arvore), caracteres->prim->arvore, caracteres->prim->prox->arvore);
    removeLista(caracteres, caracteres->prim->arvore);
    removeLista(caracteres, caracteres->prim->arvore);

    insereLista(caracteres, compactacao);
  }
  return compactacao;
}

void imprimeLista(Lista *lista)
{
  Celula *aux = lista->prim;
  while (aux != NULL)
  {
    imprimeArvore(aux->arvore);
    aux = aux->prox;
  }
}