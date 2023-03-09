#include <stdio.h>
#include <stdlib.h>
#include "llist.h"
#include "queue.h"

QUEUE createQueue() {
    QUEUE q = (QUEUE) malloc(sizeof(NODE));
    q->next = NULL;
    q->value = 0;
    return q;
}

int isEmptyQueue(QUEUE q) {
    if (q->next == NULL) {
        return 1;
    }
    return 0;
}

QUEUE enqueue(QUEUE Q, int k) {                               // enqueue is equivalent to inserting at end of list
    return insertAtEnd(Q, k);
}

QUEUE dequeue(QUEUE Q, int *k) {                              // dequeue is equivalent to deleting from the front of list
    return deleteFromFront(Q, k);
}

void printQueue(QUEUE Q) {
    QUEUE p = Q->next;
    while (p != NULL) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
}

int peekQueue(QUEUE Q) {
    return Q->next->value;
}

