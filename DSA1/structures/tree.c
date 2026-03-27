#include <stdio.h>
#include <stdlib.h>

typedef long KeyType;
typedef struct REGISTER {
    KeyType Key;
} REGISTER;

typedef struct NODE {
    REGISTER Reg;
    struct NODE *left, *right;
} NODE;

void init(NODE **root);
NODE *search(KeyType key, NODE *node);
void add(REGISTER reg, NODE **node);
void delete(KeyType key, NODE **node);

int main() {
    NODE *tree = NULL;

    REGISTER r1 = {10};
    REGISTER r2 = {5};
    REGISTER r3 = {15};

    add(r1, &tree);
    add(r2, &tree);
    add(r3, &tree);

    NODE *result = search(5, tree);

    if (result != NULL) {
        printf("REGISTER found: %ld\n", result->Reg.Key);
    } else {
        printf("REGISTER not found.\n");
    }

    return 0;
}

void init(NODE **root) { *root = NULL; }

NODE *search(KeyType key, NODE *node) {
    if (node == NULL)
        return NULL;

    if (key < node->Reg.Key)
        return search(key, node->left);

    if (key > node->Reg.Key)
        return search(key, node->right);

    return node;
}

void add(REGISTER reg, NODE **node) {
    if (*node == NULL) {
        *node = (NODE *)malloc(sizeof(NODE));
        (*node)->Reg = reg;
        (*node)->left = NULL;
        (*node)->right = NULL;
        return;
    }

    if (reg.Key < (*node)->Reg.Key)
        add(reg, &((*node)->left));
    else if (reg.Key > (*node)->Reg.Key)
        add(reg, &((*node)->right));
    else
        printf("Error: REGISTER already exists\n");
}

void delete(KeyType key, NODE **node) {}
