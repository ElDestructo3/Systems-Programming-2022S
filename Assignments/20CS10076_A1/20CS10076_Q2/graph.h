#define MAX_VERTEX_NUM 100                                       // defining maximum number of vertices

typedef int** GRAPH;                                             // defining graph as adjacency matrix

extern GRAPH createGraph();                                      // creates and returns empty graph
extern GRAPH readGraph(char *FName);                             // reads graph from a file input
extern void DFS(GRAPH G);                                        // runs a depth-first search through the graph and prints path
extern void BFS(GRAPH G);                                        // runs a breadth-first search through the graph and prints path
extern void MST(GRAPH G);                                        // prints the edges of the minimum spanning tree of the graph 