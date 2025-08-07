#ifndef _ARVORE_H
#define _ARVORE_H
typedef struct Arvore Arvore;
Arvore *criaArvoreVazia();
Arvore *criaArvore(char caracter, int ehletra, int frequencia, Arvore* esq, Arvore* dir);
int getFrequencia(Arvore *arv);
void liberaArvore(Arvore *arv);
void imprimeArvore(Arvore *arv);
#endif