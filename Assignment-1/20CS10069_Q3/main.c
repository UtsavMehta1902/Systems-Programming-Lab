#include<stdio.h>
#include<stdlib.h>
#include<graph.h>

int main()
{
    char *FName = (char *)malloc(sizeof(char) * 50);
    printf("Enter the name of the file: ");
    scanf("%s", FName);

    GRAPH G = readGraph(FName);
    printf("\n");
    DFS(G);
    printf("\n");
    BFS(G);
    printf("\n");
    MST(G);
    printf("\n");
}