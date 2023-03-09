#include <stdio.h>
#include <stdlib.h>
#include "union_find.h"

UNION_FIND createUF(int n) {
    
    UNION_FIND F = (UNION_FIND) malloc(sizeof(union_find));   // creating a structure with an array of empty nodes
    F->capacity = n;
    F->size = 0;
    
    F->nodes = (NODE_PTR*)malloc(n * sizeof(NODE_PTR));
    
    for (int i = 0; i < n; i++) {
        
        F->nodes[i] = (NODE_PTR)malloc(sizeof(_NODE));
        F->nodes[i]->data = -1;
        F->nodes[i]->size = 0;
        F->nodes[i]->parent = NULL;
        
    }
    return F;
}

UNION_FIND makeSetUF(UNION_FIND F, int x, int *i) {           // adds node if not at full capacity
    if (F->size == F->capacity) {
        printf("Error: Union-Find is full.\n");
        return F;
    }
    F->nodes[F->size]->data = x;
    F->nodes[F->size]->parent = F->nodes[F->size];
    F->nodes[F->size]->size = 1;
    *i=F->size;
    F->size++;
    return F;
}

NODE_PTR findUF(UNION_FIND F, int i) {                        //  recursively finds parent node of given node
    NODE_PTR node = F->nodes[i];
    while (node != node->parent) {
        node = node->parent;
    }
    return node;
}

void unionUF(UNION_FIND F, int i, int j) {                    // performs union of sets of nodes at indices i and j, giving priority to size of set
    NODE_PTR node_i = findUF(F, i);
    NODE_PTR node_j = findUF(F, j);
    if (node_i->size >= node_j->size) {
        node_j->parent = node_i;
        node_i->size += node_j->size;
        node_j->size = node_i->size;
    }
    else {
        node_i->parent = node_j;
        node_j->size += node_i->size;
        node_i->size = node_j->size;
    } 
}

void printUF(UNION_FIND F) {                                  // prints data and size of set of node, and list of parents
    for (int i = 0; i < F->size; i++) {
        printf("%d:%d,%d,", i,F->nodes[i]->data, F->nodes[i]->size);
        NODE_PTR node = F->nodes[i];
        while (node != node->parent) {
            printf("%d,", node->parent->data);
            node = node->parent;
        }
        printf("\n");
    }
    printf("\n");
}

