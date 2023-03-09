#include <stdio.h>
#include <stdlib.h>
#include <datastruct.h>                                                // including data structures library created in the first part
#include <limits.h>
#include "graph.h"

GRAPH createGraph() {                                                  // allocating memory, initialising with zeros and returning graph
    GRAPH G = (GRAPH) malloc(MAX_VERTEX_NUM * sizeof(int*));
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        G[i] = (int *) malloc(MAX_VERTEX_NUM * sizeof(int));
        for (int j = 0; j < MAX_VERTEX_NUM; j++) {
            G[i][j] = 0;
        }
    }
    return G;
}

GRAPH readGraph(char *FName) {                                   // opening file and reading graph in the format mentioned in question
    GRAPH G = createGraph();
    FILE *fp = fopen(FName, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file %s.\n", FName);
        return NULL;
    }
    int n, m;
    fscanf(fp, "%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fscanf(fp, "%d %d %d", &u, &v, &w);
        G[u][v] = w;
        G[v][u] = w;
    }
    fclose(fp);
    return G;
}

void DFS(GRAPH G) {                                                      // performing a depth-first search of the graph using stack
    int* visited = (int *) malloc(MAX_VERTEX_NUM * sizeof(int));         // creating array to check if vertex is visited
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        visited[i] = 0;
    }
    int source =-1 ; 
    for (int i=0;i<MAX_VERTEX_NUM;i++) {                                 // finding a source to start the DFS
        for (int j=0;j<MAX_VERTEX_NUM;j++) {
            if (G[i][j]!=0) {
                source = i;
                break;
            }
        }
    }
    printf("Depth-First Search of the graph in order of the vertices is:");
    STACK S = createStack();                                             // creating stack anhd pushing source
    S = push(S, source);
    while (!isEmptySTACK(S)) {                                          
        int k;                                                           // while stack is not empty, pop a vertex and print it
        S = pop(S, &k);                                                 
        if (visited[k] == 0) {
            visited[k] = 1;
            printf("%d ", k);
            
        }
        
        for (int i = 0; i < MAX_VERTEX_NUM; i++) {                       // add all destinations of vertex to stack 
            if (G[k][i] != 0 && visited[i] == 0) {
                
                S = push(S, i);
            }
        }
    }
    printf("\n");

}

void BFS(GRAPH G) {                                                       // performing breadth-first search on the graph using queue
    int* visited = (int *) malloc(MAX_VERTEX_NUM * sizeof(int));          // creating array for checking if nodes are visited
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        visited[i] = -1;
    }
    int source =-1;
    for (int i=0;i<MAX_VERTEX_NUM;i++) {                                  // finding suitable source for BFS
        for (int j=0;j<MAX_VERTEX_NUM;j++) {
            if (G[i][j]!=0) {
                source = i;
                break;
            }
        }
    }
    printf("Breadth-First Search of the graph in order of the vertices is:");
    visited[source] = 1;
    QUEUE Q = createQueue();                                             // creating queue to store vertices
    Q = enqueue(Q, source);
    while(!isEmptyQueue(Q)) {                                            // while queue is not empty
        int k;                                                           // deque vertex, print it in the path, and enqueuing all vertices along breadth
        Q = dequeue(Q, &k);
        printf("%d ", k);
        for (int i=0;i<MAX_VERTEX_NUM;i++) {
            if (G[k][i]!=0 && visited[i]==-1) {
                visited[i] = 1;
                Q = enqueue(Q, i);
            }
        }
        
    }
    printf("\n");
}

void MST(GRAPH G) {                                                      // constructing a minimum-spanning tree using Kruskal's algorithm and union-find
    UNION_FIND UF = createUF(MAX_VERTEX_NUM);                            // creating union-find 
    int min_cost_MST=0, edge_count=0;
    int k;
    for (int i=0;i<MAX_VERTEX_NUM;i++) {                                 // making all vertices as nodes of union-find
        for (int j=0;j<MAX_VERTEX_NUM;j++) {
            if (G[i][j]!=0) {
                UF = makeSetUF(UF, i,&k);
                break;
            }
        }
    }
    printf("List of Edges in MST are:\n");
    while (edge_count<UF->size-1) {                                      // while number of edges in MST is less than (num_vertices)-1
        int min_cost=INT_MAX;
        int u, v;
        for (int i=0;i<MAX_VERTEX_NUM;i++) {
            for (int j=0;j<MAX_VERTEX_NUM;j++) {                         // finding edge of minimum weight not part of found set yet
                if (G[i][j]!=0 && G[i][j]<min_cost && findUF(UF, i)!=findUF(UF, j)) {
                    min_cost = G[i][j];
                    u = i;
                    v = j;
                }
            }
        }
        unionUF(UF, u, v);                                               // adding vetex to found set
        edge_count++;                                                    // incrementing number of edges
        min_cost_MST += min_cost;                                        // adding edge cost to MST
        printf("Edge-%d: Source:%d, Destination:%d, Weight:%d\n", edge_count,u, v, min_cost);  // print edge
    }
    printf("Cost of MST: %d\n", min_cost_MST);                           // printing cost of MST 
}


