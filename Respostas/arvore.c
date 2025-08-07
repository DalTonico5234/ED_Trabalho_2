#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Arvore {
  char caracter;
  Arvore *esq;
  Arvore *dir;
  int ehletra;
  int frequencia;
};

Arvore *criaArvoreVazia() { return NULL; }

Arvore *criaArvore(char caracter, int ehletra, int frequencia, Arvore *esq,
                   Arvore *dir) {
  Arvore *arv = (Arvore *)malloc(sizeof(Arvore));
  arv->caracter = caracter;
  arv->esq = esq;
  arv->dir = dir;
  arv->ehletra = ehletra;
  arv->frequencia = frequencia;
  return arv;
}
void liberaArvore(Arvore *arv) {
  if (arv != NULL) {
    liberaArvore(arv->esq);
    liberaArvore(arv->dir);
    free(arv);
    arv = NULL;
  }
}
int getFrequencia(Arvore *arv) { return arv->frequencia; }

void imprimeArvore(Arvore *arv) {
  printf("Caracter: %c // Frequencia: %d\n", arv->caracter, arv->frequencia);
}