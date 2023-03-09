typedef struct _node {                             // defining node with value and pointer to next
    int value;
    struct _node *next;
} NODE;

typedef NODE* LLIST;                               // defining linked list as a pointer to head node

extern LLIST createList();                         // creating and returning empty list with a head node
extern int searchList(LLIST H, int k);             // searching for value in list, returning 0 if absent and 1 if present
extern LLIST insertAtFront(LLIST H, int k);        // creating node with value k and inserting at front of list
extern LLIST insertAtEnd(LLIST H, int k);          // creating node with value k and inserting at end of list
extern LLIST deleteFromFront(LLIST H, int *k);     // deleting front node and returing value through pointer k
extern LLIST deleteFromEnd(LLIST H, int *k);       // deleting end node and returning value through pointer k
extern LLIST deleteList(LLIST H, int k);           // deleting first node with value k
extern void printList(LLIST H);                    // utility function for printing list values for debugging
