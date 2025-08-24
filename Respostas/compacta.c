/**
 * @file compacta.c
 * Arquivo principal do programa Compacta
 *
 * Criado e desenvolvido por:
 * @author Leonardo Cheregati de Oliveira Roxo
 * @author Matteo Chisté Carvalho Trento
 *
 * Parte do 2º Trabalho Prático: Compactador de Huffman, da disciplina Estutura de Dados,
 * lecionada pela Prof Patrícia Dockhorn Costa, do Departamento de Informática - UFES, no período 2025/1
 */

#include "compactador.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Faz todas as etapas da compactação, desde a procura do caminho até a liberação final
int main(int argc, char *argv[])
{
  char caminho[MAX_STRING];
  strcpy(caminho, "./");
  strcat(caminho, argv[argc - 1]);

  clock_t ini, fim;

  ini = clock();

  Compactador *compact = criaCompactador(caminho);

  preencheCompacator(compact);

  executaCompactacao(compact);

  liberaCompactador(compact);

  fim = clock();

  printf("Tempo para compactacao: %Lf s\n\n", (long double)(fim - ini) / CLOCKS_PER_SEC);

  return 0;
}