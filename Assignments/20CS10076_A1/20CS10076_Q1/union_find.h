typedef struct node{
    int data;
    struct node *parent;
    int size;
} _NODE;                                                      // defining node in union-find with parent pointer, size of set containing node and value

typedef _NODE* NODE_PTR;                                      // defining node pointers for each node

typedef struct {
    NODE_PTR *nodes;
    int size;
    int capacity;
} union_find;                                                 // defining union find as array of node pointers, number of nodes and maximum capacity

typedef union_find *UNION_FIND;                               // defining pointer to union-find

extern UNION_FIND createUF(int n);                            // creates an empty union-find structure with maximum capacity n
extern UNION_FIND makeSetUF(UNION_FIND F, int x, int *i);     // makes a new set with value x and adds it to union-find, returning index through pointer
extern NODE_PTR findUF(UNION_FIND F, int i);                  // returns pointer of parent node of node with index i in union-find
extern void unionUF(UNION_FIND F, int i, int j);              // performing union of sets of nodes at indices i and j
extern void printUF(UNION_FIND F);                            // prints union-find for debugging

