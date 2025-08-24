/**
 * @file io.h
 * Definição da biblioteca io
 * 
 * Criado e desenvolvido por:
 * @author Leonardo Cheregati de Oliveira Roxo 
 * @author Matteo Chisté Carvalho Trento
 * 
 * Parte do 2º Trabalho Prático: Compactador de Huffman, da disciplina Estutura de Dados,
 * lecionada pela Prof Patrícia Dockhorn Costa, do Departamento de Informática - UFES, no período 2025/1
 */

#ifndef _IO_H
#define _IO_H

#include "bitmap.h"
#include <stdio.h>

// Tamanho máximo para um bitmap
#define MAX_BIGMAP 25165824 // equivale a 3 MB, em bits

// Tamanho máximo para as strings que representam um caminho de arquivo
#define MAX_STRING 100

// Tamanho da tabela ASCII + 1, para incluir o pseudo caracter de fim de arquivo
#define TAM_ASCII 257

/**
 * @brief Imprime um bitmap dentro de outro, e, quando se atinge determinado limite, imprime o bitmap maior no arquivo compactado
 * @param bigmap bitmap grande que funciona como buffer, guardando as informações que serão impressas
 * @param novo bitmap pequeno que será guardado
 * @param forcaImpressao booleano que permite imprimir as informações no arquivo antes de chegar ao limite, para permitir a impressão quando o arquivo acaba
 * @param compactado arquivo onde devem ser impressas as informações
 */
void imprimeBinarios(bitmap *bigmap, bitmap *novo, unsigned short int forcaImpressao, FILE *compactado);

/**
 * @brief Extrai um bit de um byte lido do arquivo compactado
 * @param compactado arquivo de onde são lidos os bytes
 * @param buffer_byte byte lido
 * @param posicao_bit posicao atual que o códido está no byte
 * @return o bit lido de buffer_byte em posicao_bit
 */
int lerBit(FILE *compactado, unsigned char *buffer_byte, int *posicao_bit);

#endif