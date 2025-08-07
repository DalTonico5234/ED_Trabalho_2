#include "arvore.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  Arvore *a1 = criaArvore('e', 1, 2, criaArvoreVazia(), criaArvoreVazia());
  Arvore *a2 = criaArvore('s', 1, 2, criaArvoreVazia(), criaArvoreVazia());
  Arvore *a3 = criaArvore(' ', 1, 2, criaArvoreVazia(), criaArvoreVazia());
  Arvore *a4 = criaArvore('b', 1, 3, criaArvoreVazia(), criaArvoreVazia());
  Arvore *a5 = criaArvore('o', 1, 3, criaArvoreVazia(), criaArvoreVazia());
  Arvore *a6 = criaArvore('m', 1, 3, criaArvoreVazia(), criaArvoreVazia());
  Lista *lista = criaListaVazia();
  insereLista(lista, a4);
  insereLista(lista, a6);
  insereLista(lista, a3);
  insereLista(lista, a1);
  insereLista(lista, a2);
  insereLista(lista, a5);
  imprimeLista(lista);
  return 0;
}