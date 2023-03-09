typedef NODE* QUEUE;                                          // defining queue as pointer to head node

extern QUEUE createQueue();                                   // creating and returning empty queue with head node
extern int isEmptyQueue(QUEUE q);                             // returns 1 if queue is empty and 0 otherwise
extern QUEUE enqueue(QUEUE Q, int k);                         // add node with value k to queue
extern QUEUE dequeue(QUEUE Q, int*k);                         // remove top node from queue, storing value through pointer
extern void printQueue(QUEUE Q);                              // printing queue for debugging purposes
extern int peekQueue(QUEUE Q);                                // get top value of queue without removing node