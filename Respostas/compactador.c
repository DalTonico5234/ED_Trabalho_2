
#include "compactador.h"
#include "arvore.h"
#include "bitmap.h"
#include "lista.h"

#define TAM_ASCII 257

struct compactador
{
    FILE *original;
    FILE *compactado;
    Arvore *compactacao;
    bitmap *tabela_compactacao[TAM_ASCII];
    bitmap *bigmap;
    int caracacteres_distintos;
};

void leArquivo(int *caracteres, FILE *original);

Compactador *criaCompactador(char *caminho)
{
    Compactador *compact = (Compactador *)malloc(sizeof(Compactador));

    compact->caracacteres_distintos = 0;
    compact->original = compact->compactado = NULL;
    compact->compactacao = NULL;

    for (int i = 0; i < TAM_ASCII; i++)
    {
        compact->tabela_compactacao[i] = NULL;
    }

    compact->bigmap = NULL;

    compact->original = fopen(caminho, "rb");
    compact->compactado = fopen("./compactado.bin", "wb");

    if (!compact->original || !compact->compactado)
    {
        printf("ERRO NA ABERTURA DOS ARQUIVOS: verifique o caminho passado!\n\n");
        exit(1);
    }

    return compact;
}

void preencheCompacator(Compactador *compact)
{
    Lista *lista_carac = criaListaVazia();

    int caracteres[TAM_ASCII] = {0};

    leArquivo(caracteres, compact->original);

    Arvore *no;
    for (int i = 0; i < TAM_ASCII; i++)
    {
        if (caracteres[i] != 0)
        {
            no = criaArvore(i, 1, caracteres[i], NULL, NULL);
            insereLista(lista_carac, no);
            compact->caracacteres_distintos++;
        }
    }
    no = criaArvore(TAM_ASCII - 1, 1, 1, NULL, NULL);
    insereLista(lista_carac, no);
    compact->caracacteres_distintos++;

    compact->compactacao = criaArvoreHuffman(lista_carac);

    unsigned short int caminho[TAM_MAX_CARACTER] = {0};

    criaBitmaps(compact->compactacao, compact->tabela_compactacao, 0, caminho);

    liberaLista(lista_carac);
}

void testa(Compactador *compact)
{
    for (int j = 0; j < TAM_ASCII; j++)
    {
        if (compact->tabela_compactacao[j])
        {
            printf("MAP %d:\n", j);
            for (unsigned int i = 0; i < bitmapGetLength(compact->tabela_compactacao[j]); i++)
            {
                printf("bit #%d = %0x\n", i, bitmapGetBit(compact->tabela_compactacao[j], i));
            }
            printf("\n");
        }
    }
    imprimeArvore(compact->compactacao);
}

void executaCompactacao(Compactador *compact)
{
    compact->bigmap = bitmapInit(MAX_BIGMAP);

    imprimeArvoreNoArquivo(compact->compactacao, compact->compactado, compact->bigmap);

    testa(compact);
    for (unsigned int j = 0; j < bitmapGetLength(compact->bigmap); j++)
    {
        printf("%0x", bitmapGetBit(compact->bigmap, j));
    }
    printf("\n");
}

void liberaCompactador(Compactador *compact)
{
    if (compact)
    {
        if (compact->compactacao)
        {
            liberaArvore(compact->compactacao);
        }
        if (compact->original)
        {
            fclose(compact->original);
        }
        if (compact->compactado)
        {
            fclose(compact->compactado);
        }

        for (int i = 0; i < TAM_ASCII; i++)
        {
            if (compact->tabela_compactacao[i])
            {
                bitmapLibera(compact->tabela_compactacao[i]);
            }
        }

        free(compact);
    }
}