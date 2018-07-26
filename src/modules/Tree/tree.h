#ifndef TREE_H
#include <stdlib.h>
#define TREE_H


typedef void *Tree;


Tree createNode(void *data);
Tree  tree_insert(Tree t, void *data, int (*compare)(void *, void *));
Tree newTree(void *data);
void printInOrder(Tree t, void (*display)(void *));
void display_tree(Tree t, void (*display)(void *));
void printPreOrder(Tree t, void (displayFn)(void *));
Tree leftRotate(Tree t);
Tree rightRotate(Tree t);
int getBalance(Tree t);
int height(Tree t);
int max(int a, int b) ;   
#endif
