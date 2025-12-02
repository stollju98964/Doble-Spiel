#include <stdlib.h>
#include "stack.h"

//TODO: grundlegende Stackfunktionen implementieren:
/*  * `push`: legt ein Element oben auf den Stack,
    * `pop`: entfernt das oberste Element,
    * `top`: liefert das oberste Element zurück,
    * `clearStack`: gibt den gesamten Speicher frei. */

// Pushes data as pointer onto the stack.
StackNode *push(StackNode *stack, void *data)
{
    StackNode *node = malloc(sizeof(StackNode));
    if (!node) {
        /* Allocation failed: return original stack unchanged */
        return stack;
    }
    node->data = data;
    node->next = stack;
    return node;
}

// Deletes the top element of the stack (latest added element) and releases its memory. (Pointer to data has to be
// freed by caller.)
StackNode *pop(StackNode *stack)
{
    if (!stack) return NULL;
    StackNode *next = stack->next;
    free(stack);
    return next;
}

// Returns the data of the top element.
void *top(StackNode *stack)
{
    return stack ? stack->data : NULL;
}

// Clears stack and releases all memory.
void clearStack(StackNode *stack)
{
    while (stack) {
        StackNode *next = stack->next;
        free(stack);
        stack = next;
    }
}