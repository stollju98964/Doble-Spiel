#ifndef BINTREE_H
#define BINTREE_H

#include <stdlib.h>

typedef int (*CompareFctType)(const void *arg1, const void *arg2);

typedef struct node
{
    void *data;
    struct node *left;
    struct node *right;
} TreeNode;

// Adds a copy of data's pointer destination to the tree using compareFct for ordering. Accepts duplicates 
// if isDuplicate is NULL, otherwise ignores duplicates and sets isDuplicate to 1 (or to 0 if a new entry is added).
TreeNode *addToTree(TreeNode *root, const void *data, size_t dataSize, CompareFctType compareFct, int *isDuplicate);
// Iterates over the tree given by root. Follows the usage of strtok. If tree is NULL, the next entry of the last tree given is returned in ordering direction.
// Use your implementation of a stack to organize the iterator. Push the root node and all left nodes first. On returning the next element, 
// push the top node and push all its left nodes.
void *nextTreeData(TreeNode *root);
// Releases all memory resources (including data copies).
void clearTree(TreeNode *root);
// Returns the number of entries in the tree given by root.
unsigned int treeSize(const TreeNode *root);

#endif