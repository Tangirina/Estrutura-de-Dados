#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cidades.h"

Estrada *getEstrada(const char *cidades)
{
    FILE *file = fopen(cidades, "r");
    if (!file)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", cidades);
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    fscanf(file, "%d", &estrada->T);
    fscanf(file, "%d", &estrada->N);

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    for (int i = 0; i < estrada->N; i++)
    {
        fscanf(file, "%d %[^\n]", &estrada->C[i].Posicao, estrada->C[i].Nome);
    }

    fclose(file);
    return estrada;
}

double calcularVizinhanca(Estrada *estrada, int indiceCidade)
{
    double vizinhanca = 0;
    int posicaoCidade = estrada->C[indiceCidade].Posicao;
    double mediaPosicoes = 0;

    for (int i = 0; i < estrada->N; i++)
    {
        mediaPosicoes += estrada->C[i].Posicao;
    }
    mediaPosicoes /= estrada->N;

    vizinhanca += fabs(posicaoCidade - mediaPosicoes);

    vizinhanca += fmin(posicaoCidade, estrada->T - posicaoCidade);

    return vizinhanca;
}

double calcularMenorVizinhanca(const char *cidades)
{
    Estrada *estrada = getEstrada(cidades);
    if (!estrada)
        return -1;

    double menorVizinhanca = -1;

    for (int i = 0; i < estrada->N; i++)
    {
        double vizinhanca = calcularVizinhanca(estrada, i);

        if (menorVizinhanca == -1 || vizinhanca < menorVizinhanca)
        {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *cidades)
{
    Estrada *estrada = getEstrada(cidades);
    if (!estrada)
        return NULL;

    double menorVizinhanca = -1;
    char *cidade = NULL;

    for (int i = 0; i < estrada->N; i++)
    {
        double vizinhanca = calcularVizinhanca(estrada, i);

        if (menorVizinhanca == -1 || vizinhanca < menorVizinhanca)
        {
            menorVizinhanca = vizinhanca;
            cidade = estrada->C[i].Nome;
        }
    }

    char *resultado = (char *)malloc((strlen(cidade) + 1) * sizeof(char));
    strcpy(resultado, cidade);

    free(estrada->C);
    free(estrada);
    return resultado;
}