/************************************************************************
*
*  Algoritmo de BORUVKA
*  __________________
*
* Copyright 2020 Nivardo Alburquerque, Paulo Bernardo
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in the
* Software without restriction, including without limitation the rights to use, copy,
* modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the
* following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies
* or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*/

//
// Created for a college projetct
// Course: Sistemas Embarcados @ IFCE - Instituto Federal de Educação, Ciência e Tecnologia do Ceará
// Target Platform: Linux
//

#ifndef ENGCOMP_SEMB_UTILS_H
#define ENGCOMP_SEMB_UTILS_H

// ----- PROTOTIPOS ------

void gera_grafo_simetrico(int);
void printar_grafo(int n, int [n][n]);
void print_array(int *lista,int n);

// Funcao utilitaria para printar a matriz de adjacencia do grafo
void printar_grafo(int n, int grafo[MaxDim][MaxDim])
{
    int i,j;
    printf("\nGRAFO: Matriz de Adjacencia\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("%03d ",grafo[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printar_grafo_formatted(int n, int grafo[MaxDim][MaxDim])
{
    int i,j;
    printf("\nGRAFO: Matriz de Adjacencia\n {");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if (j != n-1 || i != n-1)
                printf("{%d, %d, %d}, ", i, j, grafo[i][j]);
            else
                printf("{%d, %d, %d}", i, j, grafo[i][j]);
        }
        printf("\n");
    }
    printf("};\n");
}


// Gera uma matriz de adjacencia de um grafo simetrico com valores de no max 300
void gera_grafo_simetrico(int n)
{
    int i,j;

    printf("\n\nGerando Grafo Aleatorio");

    // Injeta seed com o tempo atual
    srand(time(NULL));
    for(int i = 0; i < n; i++)
    {
        for(int j = i; j < n; j++)
        {
            if(i == j){
                matriz_adjacencia[i][j] = 0;
            }

            else{
                int val = rand() % 300;
                val = val<(int)(300/1.2)?0:val;
                val = val == 0? 0:(rand() % 300);
                if(val)
                    qnt_arestas++;

                matriz_adjacencia[i][j] = val;
                matriz_adjacencia[j][i] = val;
            }

        }
    }

}

// Funcao utilitaria para printar listas
void print_array(int *lista,int n)
{
    int i;
    printf("\n Lista:\n");

    for(i=0; i<n; i++)
    {
        printf("%d ",lista[i]);
    }
    printf("\n");

}


#endif //ENGCOMP_SEMB_UTILS_H
