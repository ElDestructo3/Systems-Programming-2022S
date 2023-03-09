typedef NODE* STACK;                                 // defining stack as pointer to head of linked list

extern STACK createStack ();                         // create and return stack with only head node (empty)
extern int isEmptySTACK (STACK S) ;                  // check if stack is empty
extern STACK push (STACK S, int k) ;                 // push a node with value k into the stack
extern STACK pop (STACK S, int *k);                  // pop a node from the stack and returning value through pointer
extern int peekStack (STACK S);                      // return value of top node of the stack without removing it
extern void printStack(STACK S);                     // print the stack for debugging
