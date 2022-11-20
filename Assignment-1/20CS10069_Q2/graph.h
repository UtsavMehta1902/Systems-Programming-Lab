typedef struct _AdjMat {
    int nodes;
    int edges;
    int **adj;
}AdjMat;

typedef AdjMat* GRAPH;

GRAPH readGraph(char *FName);
void DFS(GRAPH G);
void BFS(GRAPH G);
void swap(int *a, int *b);
void MST(GRAPH G);
