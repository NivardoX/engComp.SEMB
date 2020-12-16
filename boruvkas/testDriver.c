//
// Created by paulo on 15/12/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "boruvka.h"
#include "utils.h"


int main() {
//    Teste 1
//    int vertices = 9;
//    int matriz_adjacencia2[MaxDim][MaxDim] = {
//            {0, 4,  0, 0,  0,  0,  0, 8,  0},
//            {4, 0,  8, 0,  0,  0,  0, 11, 0},
//            {0, 8,  0, 7,  0,  4,  0, 0,  2},
//            {0, 0,  7, 0,  9,  14, 0, 0,  0},
//            {0, 0,  0, 9,  0,  10, 0, 0,  0},
//            {0, 0,  4, 14, 10, 0,  2, 0,  0},
//            {0, 0,  0, 0,  0,  2,  0, 1,  6},
//            {8, 11, 0, 0,  0,  0,  1, 0,  7},
//            {0, 0,  2, 0,  0,  0,  6, 7,  0}
//    };


//    Teste 2
//    /*   10
//    0---------1
//    |  \     |
//  6 |   5\   |15
//    |      \ |
//    2--------3
//        4           */
//    int vertices = 4;
//    int matriz_adjacencia2[MaxDim][MaxDim] = {
//            {0,  10, 6, 5},
//            {10, 0,  0, 15},
//            {6,  0,  0, 4},
//            {5,  15, 4, 0}
//    };

//Teste 3
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

//    Teste 4
    int vertices = 45;
    int matriz_adjacencia2[MaxDim][MaxDim] = {
            {0,   0,   140, 0,   0,   0,   70,  0,   0,   0,   0,   0,   0,   276, 0,   0,   0,   0,   0,   198, 0,   115, 250, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   247, 0,   0,   0,   0,   0,   0,   298, 0,   0},
            {0,   0,   0,   0,   0,   159, 0,   0,   261, 0,   0,   0,   0,   0,   0,   152, 0,   169, 0,   0,   0,   0,   269, 10,  126, 0,   222, 0,   82,  0,   117, 126, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {140, 0,   0,   0,   0,   0,   3,   0,   0,   0,   0,   0,   44,  0,   0,   38,  0,   0,   52,  0,   51,  137, 0,   0,   0,   0,   0,   159, 83,  0,   147, 0,   0,   44,  0,   0,   188, 0,   0,   255, 0,   0,   0,   0,   0},
            {0,   0,   0,   0,   0,   0,   274, 0,   0,   0,   0,   0,   195, 0,   95,  0,   0,   0,   42,  0,   0,   236, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   59},
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   132, 0,   0,   160, 0,   59,  163, 125, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   236, 0,   89,  0,   0,   0,   198, 0,   235, 122, 68,  0,   0,   0,   55,  0},
            {0,   159, 0,   0,   0,   0,   0,   0,   0,   230, 0,   0,   0,   0,   0,   0,   0,   0,   0,   117, 0,   0,   0,   0,   0,   0,   0,   0,   86,  0,   0,   0,   0,   0,   0,   111, 0,   244, 0,   0,   0,   0,   25,  0,   0},
            {70,  0,   3,   274, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   214, 0,   0,   0,   16,  0,   71,  0,   0,   0,   0,   0,   124, 0,   0,   0,   0,   0,   0,   199, 0,   0,   126, 0},
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   26,  0,   0,   0,   0,   0,   0,   165, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   280, 0,   0,   0,   0},
            {0,   261, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   105, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   31,  0,   0,   0,   0,   0,   0,   203, 167, 0,   0,   0,   0},
            {0,   0,   0,   0,   0,   230, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   211, 0,   0,   0,   0,   0,   0,   0,   0,   90,  0,   0,   0,   0,   0,   183, 0,   0,   0,   0,   0,   0,   0,   68,  0,   0,   0,   0},
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   210, 0,   0,   0,   0,   0,   0,   28,  0,   0,   0,   0,   0,   0,   0,   0,   165, 0,   0,   0,   0,   0,   0,   0,   135, 0,   0,   0,   189, 0,   0,   0},
            {0,   0,   0,   0,   132, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   59,  0,   61,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   181, 104, 216, 0,   105, 0,   0,   0,   0,   268, 0,   0,   0,   0,   0,   0},
            {0,   0,   44,  195, 0,   0,   0,   26,  0,   0,   0,   0,   0,   73,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {276, 0,   0,   0,   0,   0,   0,   0,   0,   0,   210, 0,   73,  0,   0,   249, 81,  0,   0,   0,   0,   0,   0,   0,   147, 33,  0,   0,   0,   0,   0,   50,  0,   0,   21,  0,   0,   0,   0,   0,   0,   34,  156, 0,   0},
            {0,   0,   0,   95,  160, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   298, 0,   0,   0,   0,   0,   0,   0,   31,  188, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {0,   152, 38,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   249, 0,   0,   0,   0,   0,   0,   0,   198, 0,   0,   0,   81,  219, 0,   0,   16,  0,   0,   200, 0,   0,   0,   0,   196, 0,   0,   0,   0,   0,   0,   0},
            {0,   0,   0,   0,   59,  0,   0,   0,   0,   0,   0,   59,  0,   81,  0,   0,   0,   0,   0,   0,   0,   0,   45,  0,   0,   0,   0,   267, 0,   0,   0,   148, 203, 0,   0,   10,  0,   0,   0,   0,   0,   0,   163, 285, 25},
            {0,   169, 0,   0,   163, 0,   0,   0,   0,   211, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   106, 0,   0,   0,   0,   199, 0,   0,   0,   0,   0,   0,   0,   0},
            {0,   0,   52,  42,  125, 0,   0,   0,   0,   0,   0,   61,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   185, 0,   0,   0,   0,   0,   0,   0,   62,  88,  0,   40,  0,   0,   221, 0,   0,   0,   0},
            {198, 0,   0,   0,   0,   117, 0,   165, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   217, 0,   0,   46,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {0,   0,   51,  0,   0,   0,   0,   0,   105, 0,   28,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   74,  0,   0,   0,   0,   0,   0,   0,   119, 98,  0,   0,   0,   0},
            {115, 0,   137, 236, 0,   0,   214, 0,   0,   0,   0,   0,   0,   0,   0,   198, 0,   0,   0,   0,   0,   0,   0,   206, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   284, 0,   155, 0},
            {250, 269, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   298, 0,   45,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   85,  101, 0,   0,   84,  72,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {0,   10,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   217, 0,   206, 0,   0,   0,   176, 0,   0,   135, 0,   0,   0,   0,   0,   0,   0,   0,   231, 0,   0,   0,   0,   0,   0,   0},
            {0,   126, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   147, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 0,   0,   0,   158, 215, 0,   50,  0,   0,   0,   85,  0,   297, 0,   251, 0,   0},
            {0,   0,   0,   0,   0,   0,   16,  0,   0,   0,   0,   0,   0,   33,  0,   81,  0,   0,   0,   0,   0,   0,   0,   176, 0,   0,   158, 212, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   51,  0,   0,   0,   0,   0,   0},
            {0,   222, 0,   0,   0,   0,   0,   0,   0,   90,  0,   0,   0,   0,   0,   219, 0,   0,   185, 46,  0,   0,   0,   0,   0,   158, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {0,   0,   159, 0,   0,   0,   71,  0,   0,   0,   0,   0,   0,   0,   0,   0,   267, 0,   0,   0,   0,   0,   0,   0,   128, 212, 0,   0,   0,   283, 39,  77,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   163, 0,   0},
            {0,   82,  83,  0,   0,   86,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   135, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   86,  0,   122, 0,   107, 146, 0,   0},
            {0,   0,   0,   0,   236, 0,   0,   0,   0,   0,   165, 181, 0,   0,   0,   16,  0,   0,   0,   0,   0,   0,   85,  0,   0,   0,   0,   283, 0,   0,   0,   55,  165, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   292},
            {0,   117, 147, 0,   0,   0,   0,   0,   0,   0,   0,   104, 0,   0,   31,  0,   0,   0,   0,   0,   0,   0,   101, 0,   0,   0,   0,   39,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {0,   126, 0,   0,   89,  0,   0,   0,   0,   0,   0,   216, 0,   50,  188, 0,   148, 106, 0,   0,   74,  0,   0,   0,   158, 0,   0,   77,  0,   55,  0,   0,   0,   0,   0,   0,   0,   80,  0,   0,   131, 0,   0,   0,   125},
            {0,   0,   0,   0,   0,   0,   0,   0,   31,  183, 0,   0,   0,   0,   0,   200, 203, 0,   0,   0,   0,   0,   0,   0,   215, 0,   0,   0,   0,   165, 0,   0,   0,   0,   0,   0,   0,   51,  0,   0,   0,   0,   0,   0,   46},
            {0,   0,   44,  0,   0,   0,   124, 0,   0,   0,   0,   105, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   84,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   21,  0,   0,   0,   0,   62,  0,   0,   0,   72,  0,   50,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   163, 0,   0,   229, 226, 0,   0},
            {247, 0,   0,   0,   198, 111, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   10,  0,   88,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   30,  0,   0},
            {0,   0,   188, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   199, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   160, 0,   0,   0},
            {0,   0,   0,   0,   235, 244, 0,   0,   0,   0,   135, 0,   0,   0,   0,   196, 0,   0,   40,  0,   0,   0,   0,   231, 0,   0,   0,   0,   86,  0,   0,   80,  51,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   105},
            {0,   0,   0,   0,   122, 0,   0,   0,   0,   0,   0,   268, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   85,  51,  0,   0,   0,   0,   0,   0,   0,   0,   163, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {0,   0,   255, 0,   68,  0,   0,   0,   203, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   119, 0,   0,   0,   0,   0,   0,   0,   122, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {0,   0,   0,   0,   0,   0,   199, 280, 167, 68,  0,   0,   0,   0,   0,   0,   0,   0,   221, 0,   98,  0,   0,   0,   297, 0,   0,   0,   0,   0,   0,   131, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   189, 0,   0,   34,  0,   0,   0,   0,   0,   0,   0,   284, 0,   0,   0,   0,   0,   0,   107, 0,   0,   0,   0,   0,   229, 0,   160, 0,   0,   0,   0,   0,   223, 0,   83},
            {298, 0,   0,   0,   0,   25,  0,   0,   0,   0,   0,   0,   0,   156, 0,   0,   163, 0,   0,   0,   0,   0,   0,   0,   251, 0,   0,   163, 146, 0,   0,   0,   0,   0,   226, 30,  0,   0,   0,   0,   0,   223, 0,   0,   0},
            {0,   0,   0,   0,   55,  0,   126, 0,   0,   0,   0,   0,   0,   0,   0,   0,   285, 0,   0,   0,   0,   155, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0},
            {0,   0,   0,   59,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   25,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   292, 0,   125, 46,  0,   0,   0,   0,   105, 0,   0,   0,   83,  0,   0,   0}
    };


//  Teste Aleatório 45 x 45
//    int vertices = 25;
//    int i, j;
//    int matriz_adjacencia2[MaxDim][MaxDim];
//    gera_grafo_simetrico(vertices);
//    for (i = 0; i < vertices; i++) {
//        for (j = 0; j < vertices; j++) {
//            if (i == j) {
//                matriz_adjacencia2[i][j] =  0;
//            } else
//            matriz_adjacencia2[i][j] = matriz_adjacencia[i][j];
//        }
//    }


    struct Aresta resposta[MaxDim];

    printar_grafo(MaxDim, matriz_adjacencia2);

    printf("<Boruvka> \n\n");

    // Rodando o algoritimo
    int agm_peso = boruvka(vertices, matriz_adjacencia2, resposta);

    // Ocorreu um erro ao procurar AGM
    if (agm_peso == -1) {
        printf("Erro ao procurar AGM\n");
        return 0;
    }

    printf("AGM:\n");
    for (int v = 0; v < vertices - 1; ++v) {
        printf("%d --> %d, %d\n", resposta[v].origem, resposta[v].destino, resposta[v].peso);
    }

    printf("\nO Peso da AGM eh: %d \n", agm_peso);
    return (0);
}
