#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET];
    int isEnd;
} TrieNode;

TrieNode *createNode() {
    TrieNode *node = malloc(sizeof(TrieNode));
    node->isEnd = 0;
    for (int i = 0; i < ALPHABET; i++)
        node->children[i] = NULL;
    return node;
}

void insert(TrieNode *root, char *word) {
    TrieNode *cur = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!cur->children[idx])
            cur->children[idx] = createNode();
        cur = cur->children[idx];
    }
    cur->isEnd = 1;
}

void printAll(TrieNode *node, char *buffer, int depth) {
    if (node->isEnd) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < ALPHABET; i++) {
        if (node->children[i]) {
            buffer[depth] = 'a' + i;
            printAll(node->children[i], buffer, depth + 1);
        }
    }
}

void searchPrefix(TrieNode *root, char *prefix) {
    TrieNode *cur = root;

    for (int i = 0; prefix[i]; i++) {
        int idx = prefix[i] - 'a'; // transform char to index 0-25 (26)
        if (!cur->children[idx]) {
            printf("No words found\n");
            return;
        }
        cur = cur->children[idx];
    }

    char buffer[100];
    strcpy(buffer, prefix);

    printAll(cur, buffer, strlen(prefix));
}

int main() {
    TrieNode *root = createNode();

    insert(root, "mar");
    insert(root, "mare");
    insert(root, "maravilha");
    insert(root, "mesa");

    searchPrefix(root, "mar");

    return 0;
}
