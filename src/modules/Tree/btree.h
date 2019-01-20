#ifndef BTREE_H
#define BTREE_H
#include <stdio.h>

typedef void *bTree;
typedef void *btNode;


typedef struct elemento{
  int chave;
  void *data;
}Elemento;
//ordem = grau mínimo
bTree bTree_create(int ordem);


btNode btnew_node(int ordem, int is_leaf);
void bTree_insert(bTree tree, Elemento elemento, FILE *fp);
void print_bTree(bTree t, FILE *fp);
bTree bTree_create(int ordem);

int bTree_search(bTree root, Elemento elemento, int ordem, FILE *fp);
/*
 * Lê informações do disco
 *
 * */
#endif
