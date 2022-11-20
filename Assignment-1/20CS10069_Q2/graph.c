#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <llist.h>
#include <stack.h>
#include <queue.h>
#include <union_find.h>

GRAPH readGraph(char *FName)
{
    GRAPH G = (GRAPH)malloc(sizeof(AdjMat));
    FILE *file = fopen(FName, "r");

    fscanf(file, "%d", &(G->nodes));
    fscanf(file, "%d", &(G->edges));

    int n = G->nodes;
    int m = G->edges;
    
    int u,v,w;
    
    G->adj = (int **)malloc(n * sizeof(int *));
    for(int i=0; i<n; ++i)
        G->adj[i] = (int *)malloc(n * sizeof(int));

    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            G->adj[i][j] = 0;

    for(int i=0; i<m; ++i)
    {
        fscanf(file, "%d %d %d", &u, &v, &w);
        G->adj[u][v] = w;
        G->adj[v][u] = w;
    }

    fclose(file);
    return G;
}

void DFS(GRAPH G)
{
    STACK S = createStack();
    int n = G->nodes;
    _Bool *visited = (_Bool *)malloc(n * sizeof(_Bool));
    for(int i=0; i<n; ++i)
        visited[i] = 0;
    
    visited[0]=1;
    S = push(S, 0);

    printf("The order of traversal of DFS is: \n");
    while(!isEmptyStack(S))
    {
        int node;
        S = pop(S, &node);

        printf("%d ", node);

        for(int i=0; i<n; ++i)
        {
            if(G->adj[node][i] && !visited[i])
            {
                visited[i] = 1;
                S = push(S, i);
            }
        }
    }

    printf("\n");
    free(visited);
    return;
}

void BFS(GRAPH G)
{
    QUEUE Q = createQueue();
    int n = G->nodes;
    _Bool *visited = (_Bool *)malloc(n * sizeof(_Bool));
    for(int i=0; i<n; ++i)
        visited[i] = 0;
    
    visited[0]=1;
    Q = enqueue(Q, 0);

    printf("The order of traversal of BFS is: \n");
    while(!isEmptyQueue(Q))
    {
        int node;
        Q = dequeue(Q, &node);

        printf("%d ", node);

        for(int i=0; i<n; ++i)
        {
            if(G->adj[node][i] && !visited[i])
            {
                visited[i] = 1;
                Q = enqueue(Q, i);
            }
        }
    }

    printf("\n");
    free(visited);
    return;
}

void swap(int *a, int *b)
{
    int temp[3];
    temp[0]=a[0];
    temp[1]=a[1];
    temp[2]=a[2];

    a[0]=b[0];
    a[1]=b[1];
    a[2]=b[2];

    b[0]=temp[0];
    b[1]=temp[1];
    b[2]=temp[2];
}

void MST(GRAPH G)
{
    int n = G->nodes;

    int m = G->edges;
    int ptr=0;

    int **EdgeWeights = (int **)malloc(m * sizeof(int*));
    for(int i=0; i<m; ++i)
        EdgeWeights[i] = (int *)malloc(3 * sizeof(int));

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<i; ++j)
        {
            if(G->adj[i][j])
            {
                EdgeWeights[ptr][0] = G->adj[i][j];
                EdgeWeights[ptr][1] = i;
                EdgeWeights[ptr][2] = j;
                ptr++;
            }
        }
    }

    for(int i=0; i<m; ++i)
    {
        for(int j=i+1; j<m; ++j)
        {
            if(EdgeWeights[i][0] > EdgeWeights[j][0])
                swap(EdgeWeights[i], EdgeWeights[j]);
        }
    }

    UNION_FIND UF = createUF(n);
    int *index = (int *)malloc(n * sizeof(int));

    for(int i=0; i<n; ++i)
    {
        UF = makeSetUF(UF, i, &index[i]);
    }

    int count=0;
    int totalWeight=0;
    int u,v,w;

    printf("The edges of MST are: \n");
    ptr=0;
    while(count!=(n-1))
    {
        w = EdgeWeights[ptr][0];
        u = EdgeWeights[ptr][1];
        v = EdgeWeights[ptr][2];

        if(findUF(UF, index[u]) != findUF(UF, index[v]))
        {
            printf("%d -> %d : %d\n", u, v, w);
            totalWeight += w;
            unionUF(UF, index[u], index[v]);
            count++;
        }
        ptr++;
    }

    printf("The total weight of MST is: %d\n", totalWeight);

    free(index);
    for(int i=0; i<m; ++i)
    free(EdgeWeights[i]);
    free(EdgeWeights);
    return;
}