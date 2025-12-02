#ifndef STACK_H
#define STACK_H

/* A stack is a special type of queue which uses the LIFO (last in, first out) principle. 
This means that with each new element all other elements are pushed deeper into the stack. 
The latest element is taken from the stack. */

#include <stdlib.h>

// Datentyp für einen Stack-Knoten
typedef struct StackNode {
    void *data;
    struct StackNode *next;
} StackNode;

// Pushes data as pointer onto the stack.
StackNode *push(StackNode *stack, void *data);

// Deletes the top element of the stack (latest added element) and releases its memory. (Pointer to data has to be
// freed by caller.)
StackNode *pop(StackNode *stack);

// Returns the data of the top element.
void *top(StackNode *stack);

// Clears stack and releases all memory.
void clearStack(StackNode *stack);

#endif
