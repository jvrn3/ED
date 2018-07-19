#ifndef TREE_H
#include <stdlib.h>
#define TREE_H


typedef void *Tree;


Tree createNode(void *data);
Tree  tree_insert(Tree t, void *data, int (*compare)(void *, void *));
Tree newTree(void *data);
void printInOrder(Tree t, void (*display)(void *));
void display_tree(Tree t, void (*display)(void *));
#endif
