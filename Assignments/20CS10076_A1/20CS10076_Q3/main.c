#include <stdio.h>
#include <stdlib.h>
#include <datastruct.h>
#include <mygraph.h>

int main() {
    printf("Enter the name of the file which stores the graph:\n");
    char fname[100];
    scanf("%s", fname);
    GRAPH G = readGraph(fname);
    DFS(G);
    BFS(G);
    MST(G);
}