#ifndef KDTREE_H
#define KDTREE_H
#include <stdio.h>
#include <stdlib.h>
typedef void *KdTree;
typedef struct kdnode{
    int used;
    void *data;
    float point[2];
    struct kdnode *left;
    struct kdnode *right;
}KdNode;
#include "../Geometry/geometry.h"
#include "../Lista/linked_list.h"
/* 2d Tree */
/* uma árvore kd é uma árvore binária que armazena pontos*/
KdTree newKdTree(void *, float point[]);
KdTree kd_insert_aux(KdTree t, void *data, float point[2], int cd);
KdTree kd_insert(KdTree kd, void *data, float point[2]);
void printInOrder(KdTree kd, void (*displayFn)(void *));
KdTree minData(void *a, void *b, void *c, int dim);
KdTree find_min_rec(KdTree kd, int dim, int cd);
KdTree find_min(KdTree kd, int d);
void *get_min_data(KdTree kd);
KdTree delete_kd_node(KdTree kd, void *data, float point[], int depth);
void copy_node(void *a, void *b);
int are_same(float a[], float b[]);
void destroyTree(KdTree k);
void copyPoint(float p[], float p2[]);
void nn_aux(Ponto a, KdTree k, float *best, float *x, int i,  Ponto (*getPontos)(void *), Ponto *best_ponto);
float nn(KdTree k, Ponto a, Ponto (*getPontos)(void *), Ponto *best_ponto);
float closest_aux(KdTree k, float *minor, Ponto (*getPontos)(void *), Ponto *best_ponto);
float closest_kd(KdTree k, Ponto (*getPontos)(void *), Ponto *best_ponto );
void kd_remove(KdTree k, int (*compr)(void *, void *), void *figura, void (*f_print)(void *, FILE *), FILE *fTxt);
void kd_search(KdTree k, Lista l, int(*cmpr)(void *, char *), char *key);
void *search_tree(KdTree k, float *p, int depth);
#endif
