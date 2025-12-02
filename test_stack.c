#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

static int *make_int(int v) {
    int *p = malloc(sizeof(int));
    assert(p != NULL);
    *p = v;
    return p;
}

int main(void) {
    StackNode *stack = NULL;

    // Push 1,2,3
    stack = push(stack, make_int(1));
    stack = push(stack, make_int(2));
    stack = push(stack, make_int(3));

    // Check LIFO order: 3,2,1
    int expected[] = {3,2,1};
    for (size_t i = 0; i < sizeof(expected)/sizeof(expected[0]); ++i) {
        int *topVal = (int *)top(stack);
        assert(topVal != NULL);
        assert(*topVal == expected[i]);
        free(topVal);      // Daten vom Aufrufer freigeben
        stack = pop(stack); // Knoten entfernen
    }

    // Stack ist jetzt leer
    assert(stack == NULL);
    assert(top(stack) == NULL);
    stack = pop(stack); // pop auf leerem Stack darf NULL zurückgeben
    assert(stack == NULL);

    // Test clearStack: push zwei Werte, clear und setze pointer auf NULL
    stack = push(stack, make_int(10));
    stack = push(stack, make_int(20));
    clearStack(stack);
    stack = NULL; // clearStack gibt Speicher frei, setzt Pointer nicht selbst

    printf("Alle Stack-Tests bestanden.\n");
    return 0;
}