#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

NODE *createHead() {
    NODE *head = (NODE *)(malloc(sizeof(NODE)));
    head->next = NULL;
    return head;
}

void insert(NODE *head, int value) {
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->data = value;
    newNode->next = head->next;
    head->next = newNode;
}

void printList(NODE *head) {
    NODE *current = head->next;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
}

void freeList(NODE *head) {
    NODE *current = head;
    while (current) {
        NODE *temp = current;
        current = current->next;
        free(temp);
    }
}
// gcc -c lista.c -o lista.o
// ar rcs libestruturas.a lista.o
// import into the project root to use with #include
