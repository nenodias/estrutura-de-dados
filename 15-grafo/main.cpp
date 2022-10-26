#include <stdio.h>
#include <iostream>

using namespace std;
#define MAXNODES 4

int adj[MAXNODES][MAXNODES];
int adjn[MAXNODES][MAXNODES];
int ft[MAXNODES][MAXNODES];

// O n da notação é o MAXNODES que representa o número de Vértices
// A ordem de complexidade é O(n^3)

// A Adjacencia pode ser definida com um limite máximo sendo esse o número de vértices do grafo.
// Pois  passado por todos os vértices, só se obtém caminhos repetidos

/*

adj1          adj2           adj3           adj4         Fechamento Transitivo
|0,1,0,0|  +  |0,0,1,0|  +  |1,0,0,0|  +   |0,1,0,0|  =  |1,1,1,0|
|0,0,1,0|  +  |1,0,0,0|  +  |0,1,0,0|  +   |0,0,1,0|  =  |1,1,1,0|
|1,0,0,0|  +  |0,1,0,0|  +  |0,0,1,0|  +   |1,0,0,0|  =  |1,1,1,0|
|0,0,1,1|  +  |1,0,1,1|  +  |1,1,1,1|  +   |1,1,1,1|  =  |1,1,1,1|

*/

/***
 *	Produto booleano entre duas matrizes de adjacencia
 */
void prodbool(const int m1[][MAXNODES], const int m2[][MAXNODES], int m3[][MAXNODES])
{
    int i, j, k, f;
    for (i = 0; i < MAXNODES; i++)
    {
        for (j = 0; j < MAXNODES; j++)
        {
            f = 0;
            for (k = 0; k < MAXNODES; k++)
            {
                f = f || m1[i][k] && m2[k][j];
                m3[i][j] = f;
            }
        }
    }
}

void join(int a, int b)
{
    adj[a][b] = true;
}

void remv(int a, int b)
{
    adj[a][b] = false;
}

/*

N(N(1)) + N(  N^3 + N( N(1) ) )
N^2 + N( N^3 + N^2 )
N^2 + N^4 + N^3
N^4 + N^3 + N^2

*/
void transclose()
{
    int a, b, i;
    int adjm[MAXNODES][MAXNODES];
    for (a = 0; a < MAXNODES; a++)
    {
        for (b = 0; b < MAXNODES; b++)
        {
            adjn[a][b] = adj[a][b];
            ft[a][b] = adj[a][b];
        }
    }
    for (i = 1; i < MAXNODES; ++i)
    {
        prodbool(adjn, adj, adjm);
        cout << "Matriz de adjacencia" << (i + 1);
        mostrar(adjm);
        for (int a = 0; a < MAXNODES; a++)
        {
            for (int b = 0; b < MAXNODES; b++)
            {
                ft[a][b] = ft[a][b] || adjm[a][b];
                adjn[a][b] = adjm[a][b];
            }
        }
    }
    cout << "Fechamento transitivo:" << endl;
    mostrar(ft);
}

void warshall()
{
    int i, j, k;
    for (int i = 0; i < MAXNODES; i++)
    {
        for (int j = 0; j < MAXNODES; j++)
        {
            ft[i][k] = adj[i][j];
        }
    }
    for (int k = 0; k < MAXNODES; k++)
    {
        for (int i = 0; i < MAXNODES; i++)
        {
            if (ft[i][k] == true)
            {
                for (int j = 0; j < MAXNODES; j++)
                {
                    ft[i][j] = adj[i][j] || ft[k][j];
                }
            }
        }
    }
}

int main()
{
    cout << "Teste" << endl;
    return 0;
}