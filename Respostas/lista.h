/**
 * @file lista.h
 * Definição do TAD lista
 * 
 * Criado e desenvolvido por:
 * @author Leonardo Cheregati de Oliveira Roxo 
 * @author Matteo Chisté Carvalho Trento
 * 
 * Parte do 2º Trabalho Prático: Compactador de Huffman, da disciplina Estutura de Dados,
 * lecionada pela Prof Patrícia Dockhorn Costa, do Departamento de Informática - UFES, no período 2025/1
 */

#ifndef _LISTA_H
#define _LISTA_H

#include "arvore.h"
#include <stdio.h>

/**
 * Estrutura do tipo Lista, contendo:
 * Sentinela:
 *      Primeira Celula
 *      Ultima Celula
 *  Celula:
 *      Arvore
 *      Proxima Celula
 */
typedef struct lista Lista;

/**
 * @brief Cria uma lista sem nenhum elemento e a retorna
 * @return uma lista vazia
 */
Lista *criaListaVazia();

/**
 * @brief Insere determinada árvore na lista, já fazendo a ordenação necessária
 * @param lista Lista onde será inserida
 * @param arv Arvore que será inserida
 */
void insereLista(Lista *lista, Arvore *arv);

/**
 * @brief Remove determinada árvore da lista
 * @param lista Lista de onde será retirada
 * @param arv Arvore que será retirada
 */
void removeLista(Lista *lista, Arvore *arv);

/**
 * @brief Determina se a lista tem um único elemento
 * @param lista Lista que será verificada
 * @return 1 se a lista só tiver um elemento, 0 caso contrário
 */
int ehListaUnica(Lista *lista);

/**
 * @brief Imprime determinada lista na saída padrão, elemento por elemento
 * @param lista Lista que será impressa
 */
void imprimeLista(Lista *lista);

/**
 * @brief Cria toda a Arvore de compactação de Huffman a partir da lista de árvores de caracteres e a retorna
 * @param caracteres Lista de árvores contendo apenas os caracteres
 * @return A Arvore de compactação ótima de Huffman para aquela lista
 */
Arvore *criaArvoreHuffman(Lista *caracteres);

/**
 * @brief Libera uma Lista da memória, mas não seus elementos
 * @param lista Lista que será liberada
 */
void liberaLista(Lista *lista);

#endif