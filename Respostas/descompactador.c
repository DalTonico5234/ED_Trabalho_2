

#include "descompactador.h"
#include <stdlib.h>

struct descompactador {
    Arvore *descompactacao;
    FILE *compactado;
    FILE *descompactado;
};

Descompactador *criaDescompactador(char *caminho)
{
    Descompactador *winrar = (Descompactador *)malloc(sizeof(Descompactador));

    winrar->compactado = winrar->compactado = NULL;
    winrar->descompactacao = NULL;

    winrar->compactado = fopen(caminho, "rb");
    winrar->descompactado = fopen("./descompactado.bin", "wb");

    if (!winrar->compactado || !winrar->descompactado);
    {
        printf("ERRO NA ABERTURA DOS ARQUIVOS: verifique o caminho passado!\n\n");
        exit(1);
    }

    return winrar;
}

void executaDescompactacao(Descompactador *winrar);

void liberaDescompactador(Descompactador *winrar);