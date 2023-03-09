#include <stdio.h>                                                     // including standard libraries and dependencies
#include <stdlib.h>
#include "llist.h"
#include "stack.h"

STACK createStack () {
    STACK S = (STACK) malloc(sizeof(NODE));
    S->value = 0;
    S->next = NULL;
    return S;
}

int isEmptySTACK (STACK S) {
    if (S->next == NULL) {
        return 1;
    }
    return 0;
}

STACK push(STACK S, int k) {
    return insertAtFront(S, k);                                  // pushing is equivalent to inserting at front of llist
}

STACK pop(STACK S, int *k) {
    return deleteFromFront(S, k);                                // popping is equivalent to deleting from front of llist
}

void printStack(STACK S) {
    STACK p = S->next;
    while (p != NULL) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
    
}

int peekStack(STACK S) {        
    return S->next->value;
}

