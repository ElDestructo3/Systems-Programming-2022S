#include <stdio.h>                                            // including header files including llist file
#include <stdlib.h>
#include "llist.h"                                       


LLIST createList() {                                          
    LLIST l = (LLIST) malloc(sizeof(NODE));
    l->next = NULL;
    l->value = 0;
    return l;
}

int searchValue (LLIST H,int k) {                                                   
    LLIST p = H->next;
    while (p!= NULL) {
        if (p->value == k) {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

LLIST insertAtFront(LLIST H, int k) {                   
    LLIST p = (LLIST) malloc(sizeof(NODE));                   // allocating memory and making head point to the node
    p->value = k;
    p->next = H->next;
    H->next = p;
    return H;
}

LLIST insertAtEnd(LLIST H, int k) {                           
    LLIST p = H;                                              // travelling to end of list
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = (LLIST) malloc(sizeof(NODE));                   // adding node to the end
    p->next->value = k;
    p->next->next = NULL;
    return H;
}

LLIST deleteFromFront(LLIST H, int *k) {                      // returning NULL for cases when there is no node or head node
    if (H==NULL) {                                            // deleting node otherwise
        return NULL;
    }
    if (H->next == NULL) {
        *k = H->value;
        free(H);
        return NULL;
    }
    LLIST p = H->next;
    *k = p->value;
    H->next = p->next;
    free(p);
    return H;
}

LLIST deleteFromEnd(LLIST H, int *k) {                        // returning NULL for cases when there is no node or only head node
    if (H==NULL) {                                            // deleting node otherwise
        return NULL;
    }
    if (H->next == NULL) {
        *k = H->value;
        free(H);
        return NULL;
    }
    LLIST p = H;
    while (p->next->next != NULL) {
        p = p->next;
    }
    *k = p->next->value;
    free(p->next);
    p->next = NULL;
    return H;
}

LLIST deleteList(LLIST H, int k) {                               
    LLIST p = H;
    while (p->next != NULL) {
        if (p->next->value == k) {
            LLIST q = p->next;
            p->next = q->next;
            free(q);
        }
        p = p->next;
    }
    return H;
}

void printList(LLIST H) {                                         
    LLIST p = H->next;
    while (p != NULL) {
        printf("%d ", p->value);
        p = p->next;
    }
    printf("\n");
    
}



