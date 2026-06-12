#include <stdio.h>

/*There are many ways to implement a hash table
 * one of them is linear search thats not good at all, it may
 * cause many conflicts*/

typedef struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    int size;
    int *table;
} HashTable;

int main() { return 0; }
