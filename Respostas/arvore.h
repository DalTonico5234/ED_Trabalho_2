/**
 * @file arvore.h
 * Definição do TAD arvore
 * 
 * Criado e desenvolvido por:
 * @author Leonardo Cheregati de Oliveira Roxo 
 * @author Matteo Chisté Carvalho Trento
 * 
 * Parte do 2º Trabalho Prático: Compactador de Huffman, da disciplina Estutura de Dados,
 * lecionada pela Prof Patrícia Dockhorn Costa, do Departamento de Informática - UFES, no período 2025/1
 */

#ifndef _ARVORE_H
#define _ARVORE_H

#include "bitmap.h"
#include "compactador.h"
#include "io.h"
#include <stdio.h>

// Tamanho limite, em bits, para um caracter, considerando o uso do pseudo caracter de final de arquivo
#define TAM_MAX_CARACTER 9

/**
 * Estrutura Arvore, contendo:
 *  Caracter
 *  Arvore filha da esquerda
 *  Arvore filha da direita
 *  Informação se o nó é letra/folha ou não
 *  Frequência do caracter ou soma das frequencias de seus filhos
 */
typedef struct arvore Arvore;

/**
 * @brief Cria uma Arvore a partir de todos seus parâmetros e a retorna
 * @param caracter caracter que será inserido no nó, seja da tabela ASCII ou pseudo-caracter
 * @param ehletra Informação se o nó é letra/folha ou não
 * @param frequencia Frequência do caracter ou soma das frequencias de seus filhos
 * @param esq Arvore filha da esquerda
 * @param dir Arvore filha da direita
 * @return a Arvore criada e inicializada
 */
Arvore *criaArvore(unsigned short int caracter, unsigned short int ehletra,  unsigned int frequencia, Arvore *esq, Arvore *dir);

/**
 * @brief Preenche a Tabela de compactação a partir da Arvore de compactacao de Huffman
 * @param compactacao Arvore de compactacao de Huffman
 * @param tabela Tabela de Compactacao que será preenchida
 * @param posicao_vetor posicao no vetor de bits que está sendo criado
 * @param caminho vetor de bits que é preenchido com as informacoes do caminho compactado para cada caracter
 */
void criaBitmaps(Arvore *compactacao, bitmap **tabela, int posicao_vetor, unsigned short int caminho[TAM_MAX_CARACTER]);

/**
 * @brief Imprime a Arvore no cabeçalho do arquivo compactado, imprimindo informações relevantes para reconstruir os caminhos e os nós folha
 * @param arv Arvore de compactacao de Huffman
 * @param compactado arquivo onde serão impressas as informações
 * @param bigmap bitmap buffer que guarda as informações para serem impressas posteriormente
 */
void imprimeArvoreNoArquivo(Arvore *arv, FILE *compactado, bitmap *bigmap);

/**
 * @brief Retorna a frequência de determinado nó da árvore
 * @param arv nó cuja frequência será retornada
 * @return Frequencia de arv
 */
int getFrequencia(Arvore *arv);

/**
 * @brief Imprime um Arvore na saída padrão, em pré-ordem
 * @param arv Arvore que será impressa
 */
void imprimeArvore(Arvore *arv);

/**
 * @brief reconstroi a Arvore de compactacao de Huffman a partir do arquivo já compactado e a retorna
 * @param compactado arquivo cujo cabeçalho contém as informações da Arvore
 * @param buffer_byte byte para leitura, contendo os bits lidos do arquivo
 * @param posicao_bit posicao do bit atual em buffer_byte
 * @return a Arvore de compactacao de Huffman reconstruída na memória
 */
Arvore *reconstroiArvore(FILE *compactado, unsigned char *buffer_byte, int *posicao_bit);

/**
 * @brief Percorre a Arvore a partir de um caminho fornecido pelo arquivo compactado até achar uma folha, daí retorna o caracter correspondente para fazer a descompactação
 * @param descompactacao a Arvore de descompactacao de Huffman
 * @param compactado arquivo compactado contendo os caminhos dos caracteres compactados
 * @param buffer_byte byte para leitura, contendo os bits lidos do arquivo
 * @param posicao_bit posicao do bit atual em buffer_byte
 * @return o caractere correspondente ao caminho lido do arquivo
 */
unsigned int descompacta(Arvore *descompactacao, FILE *compactado, unsigned char *buffer_bytes, int *posicao_bits);

/**
 * @brief Libera uma Arvore (inteira) da memória, assim como todos seus atributos
 * @param arv Arvore que será liberada
 */
void liberaArvore(Arvore *arv);

#endif