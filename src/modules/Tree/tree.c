#include "tree.h"
#include <stdio.h>
typedef struct node{
    void *data;
    struct node *left;
    struct node *right;
    int height;

}Node;

// AVL TREE 


Tree newTree(void *data){
	Tree t = malloc(sizeof(Node));
	Node *n = (Node *) t;
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	n->height = 1;
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
void printPreOrder(Tree t, void (*displayFn)(void *)){
    Node *n = (Node *) t;

    if(n == NULL){
	return;
    }
    displayFn(n->data);
    if(n->left)
	printPreOrder(n->left, displayFn);
    if(n->right)
	printPreOrder(n->right, displayFn);

}
int max(int a, int b){
    return (a > b) ? a : b;

}
int height(Tree t){
    Node *n = (Node *) t;
    if(n == NULL)
	return 0;
    return n->height;
}
void display_tree(Tree t, void (*displayFn) (void *)){
    Node *n = (Node *) t;
    printInOrder(n, displayFn);

}
int getBalance(Tree t){
    Node *n = (Node *) t;
    if(n == NULL)
	return 0;
    return height(n->left) - height(n->right);

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
    n->height = 1 + max(height(n->left), height(n->right));


    int balance = getBalance(n);

    //LL
    if(balance > 1 && compare(data, n->left->data)){
	return rightRotate(n);
    }
    //LR
    if(balance > 1 && compare(data, n->left->data)){
	 n->left =  leftRotate(n->left);
	return rightRotate(n);
    }
    //RL
    if(balance < -1 && compare(data, n->right->data)){
	return leftRotate(n);
    }

    //RR
    if(balance < -1 && compare(n->right->data, data)){
	n->right = rightRotate(n->right);
	return leftRotate(n);

    }
    return n;
}

//need to implement deletion
//
//
Tree rightRotate(Tree t){
    Node *y = (Node *) t;
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right))+1;
    return x;
}

Tree leftRotate(Tree t){
    Node *x = (Node *) t;
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
