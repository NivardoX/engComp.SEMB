#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MaxDim  100
#define qnt_vertices 100

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

void gera_grafo_simetrico(int);
void printar_grafo(int[MaxDim][MaxDim],int n);

void print_array(int *lista,int n);
int encontrar_raiz_grupo(struct Grupo grupos[qnt_vertices], int i);
void unir_grupos(struct Grupo grupos[], int x, int y);

void boruvka();

// ----- GLOBAIS ------

int matriz_adjacencia[MaxDim][MaxDim];
int qnt_arestas = 0;

//----------------------



int main()
{
    // Gerando um grafo aleatorio(o output vai para a variavel global matriz_adjacencia)
    gera_grafo_simetrico(qnt_vertices);

    // Printando o grafo
    printar_grafo(matriz_adjacencia, qnt_vertices);


    printf("<Boruvka> \n");

    // Rodando o algoritimo
    boruvka();

    return(0);
}



void boruvka()  
{
    // Inicializacao de variaveis auxiliares
    int menores_distancias_vertices[qnt_vertices];
    struct Aresta arestas[qnt_arestas];
    struct Grupo grupos[qnt_vertices];


    int qnt_grupos = qnt_vertices - 1;
    int agm_peso = 0;
    int qnt_arestas_aux =0;

    // Procura todas as arestas da matriz de adjacencia e salva no array
    int i,j;

    for(i=0; i<qnt_vertices; i++)
    {
        // j <= i , pois temos um grafo simetrico
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



    // Inicializa todos os grupos e seta a menor distancia deles como -1
    for (int v = 0; v < qnt_vertices; ++v)
    {
        grupos[v].nivel = 0;
        grupos[v].pai = v;
    }


    // Enquanto houver mais de um grupo de arestas
    while(qnt_grupos > 1){

        // Seta todas as os vertices com menores distancias como -1
        for (int i = 0; i < qnt_vertices; i++)
        {
            menores_distancias_vertices[i] = -1;
        }


        for (int i=0; i< qnt_arestas; i++)
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


        for (int i=0; i < qnt_vertices; i++)
        {
            // Checa se a menor distacia do grupo ja existe
            if (menores_distancias_vertices[i] != -1)
            {
                int raiz_grupo1 = encontrar_raiz_grupo(grupos, arestas[menores_distancias_vertices[i]].origem);
                int raiz_grupo2 = encontrar_raiz_grupo(grupos, arestas[menores_distancias_vertices[i]].destino);

                if (raiz_grupo1 == raiz_grupo2)
                    continue;
                agm_peso += arestas[menores_distancias_vertices[i]].peso;

                printf("Incluindo aresta [%d][%d] na AGM, com peso: %d\n",
                       arestas[menores_distancias_vertices[i]].origem,
                       arestas[menores_distancias_vertices[i]].destino,
                       arestas[menores_distancias_vertices[i]].peso);

                // Une os grupos 1 e 2 e diminui a quantidade de grupos
                unir_grupos(grupos, raiz_grupo1, raiz_grupo2);
                qnt_grupos--;
            }
        }

    }
        printf("O Peso da AGM eh: %d \n", agm_peso);

}


// Gera uma matriz de adjacencia de um grafo simetrico com valores de no max 300
void gera_grafo_simetrico(int n)
{
    int i,j;

    printf("\n\n Gerando Grafo Aleatorio");

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



// Funcao utilitaria para printar a matriz de adjacencia do grafo
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