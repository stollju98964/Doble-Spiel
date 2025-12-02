#include <string.h>
#include "stack.h"
#include "bintree.h"

//TODO: binären Suchbaum implementieren
/*  * `addToTree`: fügt ein neues Element in den Baum ein (rekursiv),
    * `clearTree`: gibt den gesamten Baum frei (rekursiv),
    * `treeSize`: zählt die Knoten im Baum (rekursiv),
    * `nextTreeData`: Traversierung mit Hilfe des zuvor implementierten Stacks. */

// Adds a copy of data's pointer destination to the tree using compareFct for ordering. Accepts duplicates
// if isDuplicate is NULL, otherwise ignores duplicates and sets isDuplicate to 1 (or to 0 if a new entry is added).
TreeNode *addToTree(TreeNode *root, const void *data, size_t dataSize, CompareFctType compareFct, int *isDuplicate)
{
    if (!root) {
        TreeNode *node = malloc(sizeof(TreeNode));
        if (!node) return NULL;
        node->data = malloc(dataSize);
        if (!node->data) {
            free(node);
            return NULL;
        }
        memcpy(node->data, data, dataSize);
        node->left = node->right = NULL;
        if (isDuplicate) *isDuplicate = 0;
        return node;
    }

    int cmp = compareFct(data, root->data);
    if (cmp < 0) {
        root->left = addToTree(root->left, data, dataSize, compareFct, isDuplicate);
    } else if (cmp > 0) {
        root->right = addToTree(root->right, data, dataSize, compareFct, isDuplicate);
    } else { /* cmp == 0 */
        if (isDuplicate) {
            *isDuplicate = 1;
            /* ignore duplicate insertion */
        } else {
            /* duplicates allowed: insert to the right subtree */
            root->right = addToTree(root->right, data, dataSize, compareFct, isDuplicate);
        }
    }
    return root;
}

// Iterates over the tree given by root. Follows the usage of strtok. If tree is NULL, the next entry of the last tree given is returned in ordering direction.
// Use your implementation of a stack to organize the iterator. Push the root node and all left nodes first. On returning the next element,
// push the top node and push all its left nodes.
void *nextTreeData(TreeNode *root)
{
    static StackNode *stk = NULL;
    static TreeNode *current = NULL;
    static int initialized = 0;

    if (root != NULL) {
        /* start a new traversal for this root */
        clearStack(stk);
        stk = NULL;
        current = root;
        /* push root and all left descendants */
        while (current) {
            stk = push(stk, current);
            current = current->left;
        }
        initialized = 1;
    } else if (!initialized) {
        /* no traversal started yet */
        return NULL;
    }

    if (!stk) return NULL;

    /* pop top node and return its data, then push its right child's left spine */
    TreeNode *node = (TreeNode *)top(stk);
    stk = pop(stk);
    void *ret = node->data;

    current = node->right;
    while (current) {
        stk = push(stk, current);
        current = current->left;
    }

    return ret;
}

// Releases all memory resources (including data copies).
void clearTree(TreeNode *root)
{
    if (!root) return;
    clearTree(root->left);
    clearTree(root->right);
    free(root->data);
    free(root);
}

// Returns the number of entries in the tree given by root.
unsigned int treeSize(const TreeNode *root)
{
    if (!root) return 0;
    return 1U + treeSize(root->left) + treeSize(root->right);
}