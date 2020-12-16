//
// Created by paulo on 15/12/2020.
//

#ifndef ENGCOMP_SEMB_BORUVKA_H
#define ENGCOMP_SEMB_BORUVKA_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MaxDim  45
#define qnt_vertices 45

// ------ STRUCTS ------
struct Grupo
{
    int pai, nivel;
};

struct Aresta
{
    int origem, destino, peso;
};

// ----- PROTOTIPOS ------

int encontrar_raiz_grupo(struct Grupo grupos[qnt_vertices], int i);
void unir_grupos(struct Grupo grupos[], int x, int y);

int boruvka(int vertices, int [MaxDim][MaxDim], struct Aresta[MaxDim]);

// ----- GLOBAIS ------

int matriz_adjacencia[MaxDim][MaxDim];
int qnt_arestas = 2025;

//----------------------


int boruvka(int vertices, int matriz_adjacencia_aux[MaxDim][MaxDim], struct Aresta resposta[MaxDim])
{
    if (vertices > MaxDim) {
        return -1;
    }
    // Inicializacao de variaveis auxiliares
    int menores_distancias_vertices[qnt_vertices];
    struct Aresta arestas[qnt_arestas];
    struct Grupo grupos[qnt_vertices];



    int resp_index = 0;
    int iteracoes = 0;
    int qnt_grupos = vertices - 1;
    int agm_peso = 0;
    int qnt_arestas_aux = 0;

    // Procura todas as arestas da matriz de adjacencia e salva no array
    int i,j;

    for(i=0; i<vertices; i++)
    {
        // j <= i , pois temos um grafo simetrico
        for(j=0; j<=i; j++)
        {
            matriz_adjacencia[i][j] = matriz_adjacencia_aux[i][j];
            if(matriz_adjacencia[i][j])
            {
                struct Aresta aresta;
                aresta.origem = i;
                aresta.destino = j;
                aresta.peso = matriz_adjacencia[i][j];

                arestas[qnt_arestas_aux++] = aresta;
            }
        }
    }


    // Inicializa todos os grupos e seta a menor distancia deles como -1
    for (int v = 0; v < vertices; ++v)
    {
        struct Grupo grupo;
        grupo.nivel = 0;
        grupo.pai = v;
        grupos[v] = grupo;
    }

    // Enquanto houver mais de um grupo de arestas
    while(qnt_grupos > 0){
        if (iteracoes == vertices) {
            return -1;
        } else {
            iteracoes++;
        }

        // Seta todas as os vertices com menores distancias como -1
        for (int i = 0; i < vertices; i++)
        {
            menores_distancias_vertices[i] = -1;
        }


        for (int i=0; i < qnt_arestas_aux; i++)
        {

            int raiz_grupo1 = encontrar_raiz_grupo(grupos, arestas[i].origem);
            int raiz_grupo2 = encontrar_raiz_grupo(grupos, arestas[i].destino);

            if (raiz_grupo1 == raiz_grupo2)
                continue;

                // Checa se o peso da aresta atual eh menor que o menor peso dos grupos
            else
            {
                if (menores_distancias_vertices[raiz_grupo1] == -1 ||
                    arestas[menores_distancias_vertices[raiz_grupo1]].peso > arestas[i].peso)
                    menores_distancias_vertices[raiz_grupo1] = i;

                if (menores_distancias_vertices[raiz_grupo2] == -1 ||
                    arestas[menores_distancias_vertices[raiz_grupo2]].peso > arestas[i].peso)
                    menores_distancias_vertices[raiz_grupo2] = i;
            }
        }


        for (int i=0; i < vertices; i++)
        {
            // Checa se a menor distacia do grupo ja existe
            if (menores_distancias_vertices[i] != -1)
            {
                int raiz_grupo1 = encontrar_raiz_grupo(grupos, arestas[menores_distancias_vertices[i]].origem);
                int raiz_grupo2 = encontrar_raiz_grupo(grupos, arestas[menores_distancias_vertices[i]].destino);

                if (raiz_grupo1 == raiz_grupo2)
                    continue;
                agm_peso += arestas[menores_distancias_vertices[i]].peso;

                struct Aresta aresta;
                aresta.origem = arestas[menores_distancias_vertices[i]].origem;
                aresta.destino = arestas[menores_distancias_vertices[i]].destino;
                aresta.peso = arestas[menores_distancias_vertices[i]].peso;
                resposta[resp_index++] = aresta;

                // Une os grupos 1 e 2 e diminui a quantidade de grupos
                unir_grupos(grupos, raiz_grupo1, raiz_grupo2);
                qnt_grupos--;
            }
        }

    }

    return agm_peso;
}

// Funcao para realizar um Find em um grupo(arvore), ela encontra a raiz da arvore
int encontrar_raiz_grupo(struct Grupo grupos[qnt_vertices], int i)
{

    int lista_aux[qnt_vertices];
    int index = 0;
    int aux = i;
    lista_aux[index++] = aux;

    while (grupos[aux].pai != aux) {
        aux = grupos[aux].pai;
        lista_aux[index++] = aux;
    }

    for (int ix = 0; ix < index; ix++) {
        grupos[lista_aux[ix]].pai = aux;
    }

    return grupos[i].pai;
}

// Funcao utilitaria para realizar uma Union em dois grupos(arvores), ela eh feita por nivel
void unir_grupos(struct Grupo grupos[], int x, int y)
{

    int raiz_grupo_x = encontrar_raiz_grupo(grupos, x);
    int raiz_grupo_y = encontrar_raiz_grupo(grupos, y);



    if (grupos[raiz_grupo_x].nivel < grupos[raiz_grupo_y].nivel)
        grupos[raiz_grupo_x].pai = raiz_grupo_y;

    else if (grupos[raiz_grupo_x].nivel > grupos[raiz_grupo_y].nivel)
        grupos[raiz_grupo_y].pai = raiz_grupo_x;

        // se estiverem no mesmo nivel escolhe um grupo aleatorio para ser o pai
    else
    {
        grupos[raiz_grupo_y].pai = raiz_grupo_x;
        grupos[raiz_grupo_x].nivel++;
    }
}

#endif //ENGCOMP_SEMB_BORUVKA_H
