#include <stdio.h>
#include <stdlib.h>

typedef struct DARRAY {
    int *arrayData;
    int capacity;
    int size;
    int copies;
    char type; // L or E (Linear or Exponential)
} DARRAY;

void initArray(DARRAY *v, char type) {
    v->capacity = 1;
    v->arrayData = (int *)malloc(sizeof(int) * v->capacity);
    v->size = 0;
    v->copies = 0;
    v->type = type;
}

void insertArray(DARRAY *v, int element) {
    if (v->size == v->capacity) {
        int newCapacity;
        if (v->type == 'L') { // Linear
            newCapacity = v->capacity + 100;
        } else if (v->type == 'E') { // Exponential
            newCapacity = v->capacity * 2;
        }

        int *newArrayData = (int *)malloc(sizeof(int) * newCapacity);

        for (int i = 0; i < v->size; i++) {
            newArrayData[i] = v->arrayData[i];
            v->copies++;
        }

        free(v->arrayData);

        v->capacity = newCapacity;
        v->arrayData = newArrayData;
    }

    v->arrayData[v->size] = element;
    v->size++;
}

void freeDArray(DARRAY *v) {
    free(v->arrayData);  // remove ref
    v->arrayData = NULL; // remove data from memory
    v->capacity = 0;
    v->size = 0;
    v->copies = 0;
}

int main() {
    DARRAY vLinear, vExponential;
    int entries = 10000;

    initArray(&vLinear, 'L');
    initArray(&vExponential, 'E');

    for (int i = 0; i < entries; i++) {
        insertArray(&vLinear, i);
        insertArray(&vExponential, i);
    }

    printf("With %d entries\n", entries);
    printf("Linear: %d copies\n", vLinear.copies);
    printf("Exponential: %d copies\n", vExponential.copies);

    freeDArray(&vLinear);
    freeDArray(&vExponential);

    return 0;
}

// With 10000 entries
// Linear: 495100 copies
// Exponential: 16383 copies

// PT/BR
/* Apesar de consumir mais memória, o crescimento Exponencial vai criar menos
 * cópias do array, realizando mais inserções imediatas (inserções O(1)). O
 * que acontece é um tradeoff entre tempo de inserção e memória.
 * */

// ENG/US
/*  Despite consuming more memory, exponential growth will create fewer copies
 * of the array, performing more immediate insertions (O(1) insertions). What
 * happens is a tradeoff between insertion time and memory.
 * */
