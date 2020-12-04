#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MaxDim  100
#define qnt_vertices 10


struct Grupo
{
    int pai, prioridade;
};

struct Aresta
{
    int origem, destino, peso;
};

// ----- PROTOTIPOS ------

void gera_grafo_simetrico(int);
void printar_grafo(int[MaxDim][MaxDim],int n);

void print_array(int *lista,int n);
int encontrar_raiz_grupo(struct Grupo grupos[qnt_vertices], int i);
void unir_grupos(struct Grupo grupos[], int x, int y);

void boruvka( );

// ----- GLOBAIS ------

int matriz_adjacencia[MaxDim][MaxDim];
int qnt_arestas = 0;



int main()
{

    gera_grafo_simetrico(qnt_vertices);
    printar_grafo(matriz_adjacencia, qnt_vertices);


    printf("Boruvka \n");
    boruvka(qnt_vertices );

    return(0);
}



void boruvka()
{
    int menores_distancias[qnt_vertices];


    int qnt_arvores = qnt_vertices - 1;
    int agm_peso = 0;
    int qnt_arestas_aux =0;
    struct Aresta arestas[qnt_arestas];

    // Matriz de adjacencia para arestas
    int i,j;

    for(i=0; i<qnt_vertices; i++)
    {
        for(j=0; j<=i; j++)
        {
            if(matriz_adjacencia[i][j]){
                struct Aresta aresta;
                aresta.origem = i;
                aresta.destino = j;
                aresta.peso = matriz_adjacencia[i][j];

                arestas[qnt_arestas_aux++] = aresta;
            }

        }
    }

    printf("%d arestas Foram encontras\n",qnt_arestas_aux );

    struct Grupo grupos[qnt_vertices];

    for (int v = 0; v < qnt_vertices; ++v)
    {
        grupos[v].pai = v;
        grupos[v].prioridade = 0;
        menores_distancias[v] = 300;
    }


    while(qnt_arvores > 1){

        // Cria todas as menores distancias com o maixmo possivel
        for (int i = 0; i < qnt_vertices; i++)
        {
            menores_distancias[i] = 300;
        }

        for (int i=0; i< qnt_arestas; i++)
        {
            // Find components (or sets) of two corners
            // of current edge
            int grupo1 = encontrar_raiz_grupo(grupos, arestas[i].origem);
            int grupo2 = encontrar_raiz_grupo(grupos, arestas[i].destino);

            // If two corners of current edge belong to
            // same set, ignore current edge
            if (grupo1 == grupo2)
                continue;

                // Else check if current edge is closer to previous
                // cheapest edges of grupo1 and grupo2
            else
            {
                if (menores_distancias[grupo1] == 300 ||
                    arestas[menores_distancias[grupo1]].peso > arestas[i].peso)
                    menores_distancias[grupo1] = i;

                if (menores_distancias[grupo2] == 300 ||
                    arestas[menores_distancias[grupo2]].peso > arestas[i].peso)
                    menores_distancias[grupo2] = i;
            }
        }


        for (int i=0; i < qnt_vertices; i++)
        {
            // Check if cheapest for current set exists
            if (menores_distancias[i] != 300)
            {
                int grupo1 = encontrar_raiz_grupo(grupos, arestas[menores_distancias[i]].origem);
                int grupo2 = encontrar_raiz_grupo(grupos, arestas[menores_distancias[i]].destino);

                if (grupo1 == grupo2)
                    continue;
                agm_peso += arestas[menores_distancias[i]].peso;
                printf("Incluindo aresta [%d][%d] na AGM, com peso: %d\n",
                       arestas[menores_distancias[i]].origem,
                       arestas[menores_distancias[i]].destino,
                       arestas[menores_distancias[i]].peso);

                // Do a union of grupo1 and grupo2 and decrease number
                // of trees
                unir_grupos(grupos, grupo1, grupo2);
                qnt_arvores--;
            }
        }

    }
        printf("O Peso da AGM eh: %d \n", agm_peso);

}



void gera_grafo_simetrico(int n)
{
    int i,j;

    printf("\n\n Gerando Grafo Aleatorio");

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

// A function that does union of two sets of x and y
// (uses union by prioridade)
void unir_grupos(struct Grupo grupos[], int x, int y)
{

    int raiz_grupo_x = encontrar_raiz_grupo(grupos, x);
    int raiz_grupo_y = encontrar_raiz_grupo(grupos, y);



    if (grupos[raiz_grupo_x].prioridade < grupos[raiz_grupo_y].prioridade)
        grupos[raiz_grupo_x].pai = raiz_grupo_y;
    else if (grupos[raiz_grupo_x].prioridade > grupos[raiz_grupo_y].prioridade)
        grupos[raiz_grupo_y].pai = raiz_grupo_x;

        // If prioridades are same, then make one as root and
        // increment its prioridade by one
    else
    {
        grupos[raiz_grupo_y].pai = raiz_grupo_x;
        grupos[raiz_grupo_x].prioridade++;
    }
}



void printar_grafo(int grafo[MaxDim][MaxDim],int n)
{
    int i,j;
    printf("\n GRAFO: Matriz de Adjacencia\n");
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