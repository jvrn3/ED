#ifndef KDTREE_H

#define KDTREE_H
#include <stdio.h>
#include <stdlib.h>
typedef void *KdTree;
typedef struct kdnode{
    void *data;
     
    struct kdnode *left;
    struct kdnode *right;
    int height;
}KdNode;

KdTree newKdTree(void *);
KdTree kd_insert_aux(KdTree t, void *, int(*comparePoint)(void*, void *), int (*comparePointY) (void *, void *), int depth);
KdTree kd_insert(KdTree t, void *, int(*comparePoint)(void*, void *), int (*comparePointY) (void *, void *));
void printInOrder(KdTree kd, void (*displayFn)(void *));
KdTree  find_min_x(KdTree kd, int depth, float (*point_in_d) (void *));
KdTree find_min_y(KdTree kd, int depth, float (*point_in_d) (void *));
float min(float a, float b);
KdTree  minNode(KdTree  a, KdTree  b, KdTree  c, float (*point_in_d)(void *));

void *get_min_data(KdTree kd);
KdTree delete_kd_node(KdTree kd, void *data, float (*point_in_x)(void *), float (*point_in_y)(void *), int depth);

void copy_node(void *a, void *b);
int are_same(void *a, void *b, float (*point_in_x)(void *), float (*point_in_y)(void *));
#endif
