/**
 * @file descompactador.h
 * Definição do TAD descompactador
 * 
 * Criado e desenvolvido por:
 * @author Leonardo Cheregati de Oliveira Roxo 
 * @author Matteo Chisté Carvalho Trento
 * 
 * Parte do 2º Trabalho Prático: Compactador de Huffman, da disciplina Estutura de Dados,
 * lecionada pela Prof Patrícia Dockhorn Costa, do Departamento de Informática - UFES, no período 2025/1
 */

#ifndef _DECOMPACTADOR_H
#define _DECOMPACTADOR_H

#include "arvore.h"
#include "io.h"

/**
 * Estrutura Descompactador, contendo:
 *  Arvore de descompactacao
 *  Arquivo compactado (entrada)
 *  Arquivo descompactado (saida)
 */
typedef struct descompactador Descompactador;

/**
 * @brief Cria um Descompactador, abrindo os arquivos e inicializando as váriáveis necessárias
 * @param caminho string que informa o caminho para o arquivo compactado, onde também será escrito o descompactado
 * @return um Descompactador com os arquivos abertos e variáveis inicializadas
 */
Descompactador *criaDescompactador(char *caminho);

/**
 * @brief Executa a descompactação do arquivo, escrevendo os dados no Descompactado
 * @param winrar Descompactador que contém as informações necessárias
 */
void executaDescompactacao(Descompactador *winrar);

/**
 * @brief Libera um Descompactador da memória, assim como todos seus atributos
 * @param winrar Descompactador que será liberado
 */
void liberaDescompactador(Descompactador *winrar);

#endif