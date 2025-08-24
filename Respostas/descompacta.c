#include "arvore.h"
#include "compactador.h"
#include "descompactador.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100

int main(int argc, char *argv[]) {
  char caminho[MAX_STRING];
  strcpy(caminho, "./");
  strcat(caminho, argv[argc - 1]);

  Descompactador *winrar = criaDescompactador(caminho);
  executaDescompactacao(winrar);
  liberaDescompactador(winrar);
  return 0;
}