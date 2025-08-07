#include "lista.h"
typedef struct Celula Celula;
struct Celula {
  Arvore *arvore;
  Celula *prox;
};
struct Lista {
  Celula *prim;
  Celula *ult;
};

Lista *criaListaVazia() {
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  lista->prim = NULL;
  lista->ult = NULL;
  return lista;
}

void liberaLista(Lista *lista) {
  Celula *aux = lista->prim;
  while (aux != NULL) {
    Celula *aux2 = aux;
    aux = aux->prox;
    free(aux2);
  }
}

void insereLista(Lista *lista, Arvore *arv) {
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->arvore = arv;
  if (!lista->ult) {
    lista->ult = nova;
    lista->prim = nova;
  } else if (getFrequencia(arv) < getFrequencia(lista->prim->arvore)) {
    nova->prox = lista->prim;
    lista->prim = nova;
  } else if (getFrequencia(arv) > getFrequencia(lista->ult->arvore)) {
    lista->ult->prox = nova;
    lista->ult = nova;
    lista->ult->prox = NULL;
  } else {
    Celula *aux = lista->prim;
    while (aux->prox != NULL &&
           getFrequencia(arv) > getFrequencia(aux->prox->arvore)) {
      aux = aux->prox;
    }
    nova->prox = aux->prox;
    aux->prox = nova;
  }
}

Celula *buscaCelula(Lista *lista, Arvore *arv) {
  Celula *aux = lista->prim;
  while (aux != NULL && aux->arvore != arv) {
    aux = aux->prox;
  }
  return aux;
}

Arvore *removeLista(Lista *lista, Arvore *arv) {
  Celula *aux = buscaCelula(lista, arv);
  if (aux == NULL) {
    return NULL;
  } else if (lista->prim == aux && lista->ult == aux) {
    lista->prim = NULL;
    lista->ult = NULL;
    free(aux);
  } else if (lista->prim == aux) {
    lista->prim = aux->prox;
    free(aux);
  } else if (lista->ult == aux) {
    Celula *aux2 = lista->prim;
    while (aux2->prox != aux) {
      aux2 = aux2->prox;
    }
    lista->ult = aux2;
    lista->ult->prox = NULL;
    free(aux);
  } else {
    Celula *aux2 = lista->prim;
    while (aux2->prox != aux) {
      aux2 = aux2->prox;
    }
    aux2->prox = aux->prox;
    free(aux);
  }
  return aux->arvore;
}

void imprimeLista(Lista *lista) {
  Celula *aux = lista->prim;
  while (aux != NULL) {
    imprimeArvore(aux->arvore);
    aux = aux->prox;
  }
}