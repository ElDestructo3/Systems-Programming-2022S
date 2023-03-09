#define MAX_SIZE 101

typedef struct {                                             // defining heap as an structure with an array for values and size of heap
    int size; 
    int *array;
} heap;

typedef heap* HEAP;                                          // defining heap pointer 

extern HEAP createHeap();                                    // creating and returning empty heap
extern int findMin(HEAP H);                                  // return minimum value of heap
extern void minHeapify(HEAP H, int i);                       // applies heapify procedure to make array into min-heap
extern HEAP extractMin (HEAP H);                             // removes minimum value from heap, maintaining heap property
extern HEAP insertHeap(HEAP H, int k);                       // insert value into heap, maintaining heap property            
extern int isFullHeap(HEAP H);                               // returns 1 if heap is full and 0 otherwise
extern int isEmptyHeap(HEAP H);                              // returns 1 if heap is empty and 0 otherwise