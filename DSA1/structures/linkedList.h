#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct NODE {
    int data;
    struct NODE *next;
} NODE;

NODE *createHead();
void insert(NODE *head, int value);
void printList(NODE *head);
void freeList(NODE *head);

#endif
