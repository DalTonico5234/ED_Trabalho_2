/**
 * @file compactador.h
 * Definição do TAD compactador
 * 
 * Criado e desenvolvido por:
 * @author Leonardo Cheregati de Oliveira Roxo 
 * @author Matteo Chisté Carvalho Trento
 * 
 * Parte do 2º Trabalho Prático: Compactador de Huffman, da disciplina Estutura de Dados,
 * lecionada pela Prof Patrícia Dockhorn Costa, do Departamento de Informática - UFES, no período 2025/1
 */

#ifndef _COMPACTADOR_H
#define _COMPACTADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Estrutura Compactador, contendo:
 *  Arquivo original
 *  Arquivo compactado
 *  Arvore de compactacao
 *  Tabela de compactacao (vetor de bitmaps)
 *  bitmap grande com os dados
 */
typedef struct compactador Compactador;

/**
 * @brief Cria um Compactador, abrindo os arquivos e inicializando as váriáveis necessárias
 * @param caminho string que informa o caminho para o arquivo original, onde também será escrito o compactado
 * @return um Compactador com os arquivos abertos e variáveis inicializadas
 */
Compactador *criaCompactador(char *caminho);

/**
 * @brief Preenche a lista de caracteres, cria a Arvore de compactacao de Huffman e preenche a Tabela de Compactacao
 * @param zip Compactador que será preenchido
 */
void preencheCompacator(Compactador *zip);

/**
 * @brief Executa a compactação do arquivo, escrevendo os dados no Compactado
 * @param zip Compactador que contém as informações necessárias
 */
void executaCompactacao(Compactador *zip);

/**
 * @brief Verifica as informações do Compactador, imprimindo na saída padrão:
 *      Arvore de compactacao
 *      Tabela de compactacao
 *      Bitmap grande contendo a informação a ser escrita
 * @param zip Compactador que tem as informações a serem impressas
 */
void testa(Compactador *zip);

/**
 * @brief Libera um Compactador da memória, assim como todos seus atributos
 * @param zip Compactador que será liberado
 */
void liberaCompactador(Compactador *zip);

#endif