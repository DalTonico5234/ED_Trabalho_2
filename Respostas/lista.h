#ifndef _LISTA_H
#define _LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"


typedef struct Lista Lista;

Lista *criaListaVazia();

void insereLista(Lista *lista, Arvore *arv);

void removeLista(Lista *lista, Arvore *arv);

void liberaLista(Lista *lista);

int ehListaUnica(Lista *lista);

Arvore *criaArvoreHuffman(Lista *caracteres);

void imprimeLista(Lista *lista);

#endif