#include <stdio.h>
#include <stdlib.h>
#include "heap.h"                                                      // importing libraries and related header files

HEAP createHeap() {
    HEAP H;
    H = (HEAP) malloc(sizeof(heap));
    H->size = 0;
    H->array = (int *) malloc(MAX_SIZE*sizeof(int));
    return H;
}

int findMin(HEAP H) {                                                 // using 1-based indexing
    return H->array[1];
}

void minHeapify(HEAP H, int i) {                                       // recursively swapping values violating heap property
    int smallest = i;
    int left = 2*i;
    int right = 2*i + 1;
    if (left <= H->size && H->array[left] < H->array[smallest]) {
        smallest = left;
    }
    if (right <= H->size && H->array[right] < H->array[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        int temp = H->array[i];
        H->array[i] = H->array[smallest];
        H->array[smallest] = temp;
        minHeapify(H, smallest);
    }
}

HEAP extractMin (HEAP H) {                                             // get the minimum value and heapify 
    if (isEmptyHeap(H)) {
        return NULL;
    }
    int min = H->array[1];
    H->array[1] = H->array[H->size];
    H->size--;
    minHeapify(H, 1);
    return H;
}

HEAP insertHeap(HEAP H, int k) {                                       // insert value into heap and heapify
    if (isFullHeap(H)) {
        return NULL;
    }
    H->size++;
    H->array[H->size] = k;
    int i = H->size;
    while (i > 1 && H->array[i] < H->array[i/2]) {
        int temp = H->array[i];
        H->array[i] = H->array[i/2];
        H->array[i/2] = temp;
        i = i/2;
    }
    return H;
}

int isFullHeap(HEAP H) {
    if (H->size == MAX_SIZE) {
        return 1;
    }
    return 0;
}

int isEmptyHeap(HEAP H) {
    if (H->size == 0) {
        return 1;
    }
    return 0;
}

