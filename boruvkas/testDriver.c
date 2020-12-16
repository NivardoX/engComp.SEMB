//
// Created by paulo on 15/12/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "boruvka.h"
#include "utils.h"


int main()
{
//    Teste 1
//    int vertices = 9;
//    int matriz_adjacencia2[MaxDim][MaxDim] = { {0, 4, 0, 0, 0, 0, 0, 8, 0},
//            {4, 0, 8, 0, 0, 0, 0, 11, 0},
//            {0, 8, 0, 7, 0, 4, 0, 0, 2},
//            {0, 0, 7, 0, 9, 14, 0, 0, 0},
//            {0, 0, 0, 9, 0, 10, 0, 0, 0},
//            {0, 0, 4, 14, 10, 0, 2, 0, 0},
//            {0, 0, 0, 0, 0, 2, 0, 1, 6},
//            {8, 11, 0, 0, 0, 0, 1, 0, 7},
//            {0, 0, 2, 0, 0, 0, 6, 7, 0} };



//    Teste 2
    /*   10
    0---------1
    |  \     |
  6 |   5\   |15
    |      \ |
    2--------3
        4           */
    int vertices = 4;
    int matriz_adjacencia2[MaxDim][MaxDim] = { {0, 10, 6, 5},
                                     {10, 0, 0, 15 },
                                     {6, 0, 0, 4 },
                                     {5, 15, 4, 0 }  };

    struct Aresta resposta[MaxDim];


    printar_grafo(vertices, matriz_adjacencia2);

    printf("<Boruvka> \n\n");

    // Rodando o algoritimo
    int agm_peso = boruvka(vertices, matriz_adjacencia2, resposta);

    printf("AGM:\n");
    for (int v = 0; v < vertices - 1; ++v)
    {
        printf("%d --> %d, %d\n", resposta[v].origem, resposta[v].destino, resposta[v].peso);
    }

    printf("\nO Peso da AGM eh: %d \n", agm_peso);
    return(0);
}
