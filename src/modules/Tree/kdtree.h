#ifndef KDTREE_H
#define KDTREE_H
#include <stdio.h>
#include <stdlib.h>
#include "../Geometry/geometry.h"
#include "../Lista/linked_list.h"

typedef void *KdTree;
typedef struct kdnode{
    int used;
    void *data;
    float point[2];
    struct kdnode *left;
    struct kdnode *right;
}KdNode;
/* 2d Tree */
/* uma árvore kd é uma árvore binária que armazena pontos*/

// cria uma árvore
KdTree newKdTree(void *, float point[]);

//inserção na árvore kd 
KdTree kd_insert_aux(KdTree t, void *data, float point[], int cd);
KdTree kd_insert(KdTree kd, void *data, float point[]);

//printar, dado uma função para lidar com void *
void printInOrder(KdTree kd, void (*displayFn)(void *));

//Deleção da kd tree
KdTree minData(void *a, void *b, void *c, int dim);
KdTree find_min_rec(KdTree kd, int dim, int cd);
KdTree find_min(KdTree kd, int d);
KdTree delete_kd_node(KdTree kd, void *data, float point[], int depth);

//retorna se pontos sao iguais
int are_same(float a[], float b[]);

//free kd tree
void destroyTree(KdTree k);

//copia p2 para p
void copyPoint(float p[], float p2[]);

//vizinho mais proximo
void nn_aux(Ponto a, KdTree k, float *best, float *x, int i, Ponto *best_ponto);
float nn(KdTree k, Ponto a, Ponto *best_ponto);

//par mais proximo na árvore kd
float closest_aux(KdTree k, float *minor, Ponto *best_ponto);
float closest_kd(KdTree k, Ponto *best_ponto );

//remove figura e já escreve no arquivo fTxt
void kd_remove(KdTree k, int (*compr)(void *, void *), void *figura, void (*f_print)(void *, FILE *), FILE *fTxt);

//dado uma arvore, utiliza a funcao cmpr para comparar uma dada key com key da kd tree
void kd_search(KdTree k, Lista l, int(*cmpr)(void *, char *), char *key);
//Procura por umm ponto. depth inicial é 0
void *search_tree(KdTree k, float *p, int depth);
\

void delete_kd_nodes(KdTree k);
#endif
