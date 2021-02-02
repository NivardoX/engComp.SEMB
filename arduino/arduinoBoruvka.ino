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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MaxDim  4
#define qnt_vertices 4

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

int boruvka();

// ----- GLOBAIS ------

// Matriz adjacencia MaxDim x MaxDim
int matriz_adjacencia[MaxDim][MaxDim] =  { { 0, 10,  6,  5},
            {10,  0,  0, 15},
            { 6,  0,  0,  4},
            { 5, 15,  4,  0}
  };

// Variável que guarda o máximo de arestas possíveis
int qnt_arestas = MaxDim * MaxDim;

// Criando a AGM que guardará a resposta
    struct Aresta resposta[MaxDim];

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
int boruvka() {
    
    // Inicializacao de variaveis auxiliares
    int menores_distancias_vertices[qnt_vertices];
    struct Aresta arestas[qnt_arestas];
    struct Grupo grupos[qnt_vertices];

    // Guarda o index da proxima aresta a ser adicionada na AGM resposta
    int resp_index = 0;
    // Contador de iterações aceitáveis - Evitando loop infinito em grafos desconectos
    int iteracoes = 0;
    // Quantidade de grupos atuais, inicia com o número de vertices pois todos os vertices na primeira iteração são grupos individuais
    int qnt_grupos = MaxDim;
    // Somador do peso da AGM
    int agm_peso = 0;
    // Guarda a quantidade de arestas presentes no grafo
    int qnt_arestas_aux = 0;

    // Auxiliares nos loops
    int i, j;

    // Procura todas as arestas da matriz de adjacencia e salva no array
    for (i = 0; i < MaxDim; i++) {
        // j <= i , pois temos um grafo simetrico
        for (j = 0; j <= i; j++) {
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
    for (i = 0; i < MaxDim; ++i) {
        struct Grupo grupo;
        grupo.nivel = 0;
        grupo.pai = i;
        grupos[i] = grupo;
    }

    // Enquanto houver mais de um grupo de arestas
    while (qnt_grupos > 1) {
        // Verifica se o número de iterações é igual ao vertice, o que segnifica que o AGM não será mais encontrada.
        if (iteracoes == MaxDim) {
            return -1;
        } else {
            iteracoes++;
        }

        // Seta todas as os vertices com menores distancias como -1
        for (i = 0; i < MaxDim; i++) {
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


        for (i = 0; i < MaxDim; i++) {
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


// Funcao utilitaria para printar a matriz de adjacencia do grafo
void printar_grafo(int n, int grafo[MaxDim][MaxDim])
{
    int i,j;
     Serial.println("\nGRAFO: Matriz de Adjacencia\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
             Serial.print(grafo[i][j]);
             Serial.print(" ");
        }
         Serial.println("\n");
    }
     Serial.println("\n");
}

int feito = 0;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

   Serial.println("Teste");
}

void loop() {
   //
    // Testes de checagem do algoritmo boruvka
    // USO: Descomente o teste desejado e deixe comentado os que não serão utilizados
    //

    /*     Teste 1
          10
        0---------1
        |  \     |
      6 |   5\   |15
        |      \ |
        2--------3
   //          4           
   // int vertices = 4;
   // int matriz_adjacencia2[MaxDim][MaxDim] = {
   //         { 0, 10,  6,  5},
   //         {10,  0,  0, 15},
   //         { 6,  0,  0,  4},
   //         { 5, 15,  4,  0}
   // };

    /*  Teste 2   */
//        int vertices = 9;
//        int matriz_adjacencia2[MaxDim][MaxDim] = {
//                {0, 4,  0, 0,  0,  0,  0, 8,  0},
//                {4, 0,  8, 0,  0,  0,  0, 11, 0},
//                {0, 8,  0, 7,  0,  4,  0, 0,  2},
//                {0, 0,  7, 0,  9,  14, 0, 0,  0},
//                {0, 0,  0, 9,  0,  10, 0, 0,  0},
//                {0, 0,  4, 14, 10, 0,  2, 0,  0},
//                {0, 0,  0, 0,  0,  2,  0, 1,  6},
//                {8, 11, 0, 0,  0,  0,  1, 0,  7},
//                {0, 0,  2, 0,  0,  0,  6, 7,  0}
//        };

    /*  Teste 3  */
//    int vertices = 20;
//    int matriz_adjacencia2[MaxDim][MaxDim] = {
//            {0,  0, 15, 0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  11, 0},
//            {0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  0, 0,  0,  4,  0,  0},
//            {15, 0, 0,  0,  0,  0,  0,  5,  0,  33, 0,  0,  0,  0,  0, 0,  0,  0,  0,  2},
//            {0,  0, 0,  0,  0,  0,  0,  0,  55, 12, 0,  0,  0,  0,  0, 0,  9,  0,  0,  0},
//            {0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  25, 0,  0, 0,  0,  0,  0,  0},
//            {4,  0, 0,  0,  0,  0,  0,  0,  0,  0,  16, 0,  0,  0,  0, 0,  0,  0,  0,  0},
//            {0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  10, 0, 0,  0,  0,  8,  0},
//            {0,  0, 5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 0,  37, 0,  0,  0},
//            {0,  0, 0,  55, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0},
//            {0,  0, 33, 12, 0,  0,  0,  0,  0,  0,  15, 0,  0,  0,  0, 0,  0,  0,  0,  0},
//            {0,  0, 0,  0,  0,  16, 0,  0,  0,  15, 0,  0,  0,  0,  0, 0,  0,  0,  0,  0},
//            {0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  60, 0,  0, 0,  0,  0,  0,  0},
//            {0,  6, 0,  0,  25, 0,  0,  0,  0,  0,  0,  60, 0,  0,  0, 0,  0,  0,  0,  0},
//            {0,  0, 0,  0,  0,  0,  10, 0,  0,  0,  0,  0,  0,  0,  0, 13, 0,  0,  0,  0},
//            {0,  0, 0,  0,  0,  0,  0,  3,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0},
//            {0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13, 0, 0,  0,  0,  0,  0},
//            {0,  0, 0,  9,  0,  0,  0,  37, 0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0},
//            {0,  4, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  20},
//            {11, 0, 0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0},
//            {0,  0, 2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  20, 0,  0},
//    };

  if (!feito) {
    // Exibindo a grafo (Matriz de adjacencia)
    printar_grafo(MaxDim, matriz_adjacencia);

    // Iniciando o Boruvka
     Serial.println("<Boruvka> \n\n");

    // Rodando o algoritimo
    int agm_peso = boruvka();

    // Ocorreu um erro ao procurar AGM
    if (agm_peso == -1) {
         Serial.println("Erro ao procurar AGM\n");
        return 0;
    }

    // Checando os valores obtidos por meio do peso da agm (previamente conhecido)
    switch (MaxDim) {
        case 4:
            if (agm_peso != 19) {
                 Serial.println("Erro ao procurar AGM\n");
                return 0;
            }
            break;
        case 9:
            if (agm_peso != 37) {
                 Serial.println("Erro ao procurar AGM\n");
                return 0;
            }
            break;
        case 20:
            if (agm_peso != 293) {
                 Serial.println("Erro ao procurar AGM\n");
                return 0;
            }
            break;
        case 45:
            if (agm_peso != 2212) {
                 Serial.println("Erro ao procurar AGM\n");
                return 0;
            }
            break;
        default:
            break;
    }

    // Exibindo o valores encontrados
     Serial.println("AGM:\n");
    for (int v = 0; v < MaxDim - 1; ++v) {
         Serial.print(resposta[v].origem);
         Serial.print(" --> ");
         Serial.print(resposta[v].destino);
         Serial.print(" | Peso: ");
         Serial.println(resposta[v].peso);
    }

     Serial.println("\nO Peso da AGM eh: %d \n");
     Serial.println(agm_peso);

     feito = 1;
  }
    return (0);
}
