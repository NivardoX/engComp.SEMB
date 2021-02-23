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

#ifndef ENGCOMP_SEMB_BORUVKA_H
#define ENGCOMP_SEMB_BORUVKA_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define MaxDim  45
#define qnt_vertices 45

// ------ STRUCTS ------
struct Grupo {
    int pai, nivel;
};

struct Aresta {
    int origem, destino, peso;
};

// ----- PROTOTIPOS ------

int encontrar_raiz_grupo(struct Grupo grupos[qnt_vertices], int i);

void unir_grupos(struct Grupo grupos[], int x, int y);

int boruvka(int vertices, int [MaxDim][MaxDim], struct Aresta[MaxDim]);

// ----- GLOBAIS ------

// Matriz adjacencia MaxDim x MaxDim
int matriz_adjacencia[MaxDim][MaxDim];

// Variável que guarda o máximo de arestas possíveis
int qnt_arestas = MaxDim * MaxDim;

//----------------------

/*
  Recebe a quantidade de vertices, o grafo e a AGM vazia que será a resposta.
  O algoritmo verifica se o número de vertices é igual ou menor que a quantidade
  máxima possível, caso não, retorna -1. Que significa  que não foi possivel encontar
  a AGM.
  Caso o grafo seja desconecto ou não tenha a AGM, o algoritmo retornará -1 também.
  O algoritmo procura a AGM e retorna o valor do peso da AGM e a resposta de forma impura.

  Parâmetros:
  vertices: tipo inteiro que guarda a quantidade de vertices presentes no grafo
  matriz_adjacencia_aux: matriz de inteiros MaxDim x MaxDim que representa o grafo
  resposta: vetor de struct Aresta de tamanho MaxDim que guardará a resposta da AGM
*/
int boruvka(int vertices, int matriz_adjacencia_aux[MaxDim][MaxDim], struct Aresta resposta[MaxDim]) {
    // Verifica se o valor do vertices é maior que o tamanho máximo
    if (vertices > MaxDim) {
        return -1;
    }
    // Inicializacao de variaveis auxiliares
    int menores_distancias_vertices[qnt_vertices];
    struct Aresta arestas[qnt_arestas];
    struct Grupo grupos[qnt_vertices];

    // Guarda o index da proxima aresta a ser adicionada na AGM resposta
    int resp_index = 0;
    // Contador de iterações aceitáveis - Evitando loop infinito em grafos desconectos
    int iteracoes = 0;
    // Quantidade de grupos atuais, inicia com o número de vertices pois todos os vertices na primeira iteração são grupos individuais
    int qnt_grupos = vertices;
    // Somador do peso da AGM
    int agm_peso = 0;
    // Guarda a quantidade de arestas presentes no grafo
    int qnt_arestas_aux = 0;

    // Auxiliares nos loops
    int i, j;

    // Procura todas as arestas da matriz de adjacencia e salva no array
    for (i = 0; i < vertices; i++) {
        // j <= i , pois temos um grafo simetrico
        for (j = 0; j <= i; j++) {
            matriz_adjacencia[i][j] = matriz_adjacencia_aux[i][j];
            if (matriz_adjacencia[i][j]) {
                struct Aresta aresta;
                aresta.origem = i;
                aresta.destino = j;
                aresta.peso = matriz_adjacencia[i][j];

                arestas[qnt_arestas_aux++] = aresta;
            }
        }
    }


    // Inicializa todos os grupos e seta a menor distancia deles como -1
    for (i = 0; i < vertices; ++i) {
        struct Grupo grupo;
        grupo.nivel = 0;
        grupo.pai = i;
        grupos[i] = grupo;
    }

    // Enquanto houver mais de um grupo de arestas
    while (qnt_grupos > 1) {
        // Verifica se o número de iterações é igual ao vertice, o que segnifica que o AGM não será mais encontrada.
        if (iteracoes == vertices) {
            return -1;
        } else {
            iteracoes++;
        }

        // Seta todas as os vertices com menores distancias como -1
        for (i = 0; i < vertices; i++) {
            menores_distancias_vertices[i] = -1;
        }


        for (i = 0; i < qnt_arestas_aux; i++) {

            int raiz_grupo1 = encontrar_raiz_grupo(grupos, arestas[i].origem);
            int raiz_grupo2 = encontrar_raiz_grupo(grupos, arestas[i].destino);

            if (raiz_grupo1 == raiz_grupo2)
                continue;

            // Checa se o peso da aresta atual eh menor que o menor peso dos grupos
            else {
                if (menores_distancias_vertices[raiz_grupo1] == -1 ||
                    arestas[menores_distancias_vertices[raiz_grupo1]].peso > arestas[i].peso)
                    menores_distancias_vertices[raiz_grupo1] = i;

                if (menores_distancias_vertices[raiz_grupo2] == -1 ||
                    arestas[menores_distancias_vertices[raiz_grupo2]].peso > arestas[i].peso)
                    menores_distancias_vertices[raiz_grupo2] = i;
            }
        }


        for (i = 0; i < vertices; i++) {
            // Checa se a menor distacia do grupo ja existe
            if (menores_distancias_vertices[i] != -1) {
                int raiz_grupo1 = encontrar_raiz_grupo(grupos, arestas[menores_distancias_vertices[i]].origem);
                int raiz_grupo2 = encontrar_raiz_grupo(grupos, arestas[menores_distancias_vertices[i]].destino);

                // Está no mesmo subgrafo, não precisa fazer nada
                if (raiz_grupo1 == raiz_grupo2)
                    continue;

                // Adiciona peso da aresta encontrada no peso da AGM
                agm_peso += arestas[menores_distancias_vertices[i]].peso;

                // Salva aresta encontrada na resposta
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
int encontrar_raiz_grupo(struct Grupo grupos[qnt_vertices], int i) {

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
void unir_grupos(struct Grupo grupos[], int x, int y) {

    int raiz_grupo_x = encontrar_raiz_grupo(grupos, x);
    int raiz_grupo_y = encontrar_raiz_grupo(grupos, y);


    if (grupos[raiz_grupo_x].nivel < grupos[raiz_grupo_y].nivel)
        grupos[raiz_grupo_x].pai = raiz_grupo_y;

    else if (grupos[raiz_grupo_x].nivel > grupos[raiz_grupo_y].nivel)
        grupos[raiz_grupo_y].pai = raiz_grupo_x;

    // se estiverem no mesmo nivel escolhe um grupo aleatorio para ser o pai
    else {
        grupos[raiz_grupo_y].pai = raiz_grupo_x;
        grupos[raiz_grupo_x].nivel++;
    }
}

#endif //ENGCOMP_SEMB_BORUVKA_H
