//
// Created by paulo on 15/12/2020.
//

#ifndef ENGCOMP_SEMB_UTILS_H
#define ENGCOMP_SEMB_UTILS_H

// ----- PROTOTIPOS ------

void gera_grafo_simetrico(int);
void printar_grafo(int n, int [n][n]);

// Funcao utilitaria para printar a matriz de adjacencia do grafo
void printar_grafo(int n, int grafo[n][n])
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


#endif //ENGCOMP_SEMB_UTILS_H