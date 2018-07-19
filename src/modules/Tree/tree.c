#include "tree.h"
#include <stdio.h>
typedef struct node{
    void *data;
    struct node *left;
    struct node *right;

}Node;

Tree newTree(void *data){
	Tree t = malloc(sizeof(Node));
	Node *n = (Node *) t;
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	return t;

}
void printInOrder(Tree t, void (*displayFn)(void *)){
    Node *n = (Node *) t;
    if(n == NULL){
	printf("Error\n");
	return;
    }

    
    if(n->left)
	printInOrder(n->left, displayFn);
    displayFn(n->data);
    if(n->right)
	printInOrder(n->right, displayFn);

}
void display_tree(Tree t, void (*displayFn) (void *)){
    Node *n = (Node *) t;
    printInOrder(n, displayFn);

}
Tree tree_insert(Tree t, void *data, int (*compare)(void *, void *)){
    Node *n = (Node *) t;
    /* Node *aux; */

    if(n == NULL){
	return newTree(data);
    }
    if(compare(data, n->data) == 1){
	n->right = tree_insert(n->right, data, compare);
    }
    else if(compare(data, n->data) == -1){
	n->left = tree_insert(n->left, data, compare);
    }
    return n;
}
