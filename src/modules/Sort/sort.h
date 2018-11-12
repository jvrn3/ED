#ifndef SORT_H
#define SORT_H

#include "../Geometry/geometry.h"
int parent(int i);
int left(int i);
int right(int i);
void exch( Ponto *i, Ponto *j);
void max_heapify_y(Ponto *p, int i, int n);
void max_heapify_x(Ponto *p, int i, int n);
void build_max_heap_x(Ponto *p, int n);
void build_max_heap_y(Ponto *p, int n);
void heap_sort_y(Ponto *p, int length);
void heap_sort_x(Ponto *p, int length);
int  *counting_sort(int *A,  int k, int n);
void quick_sort(void **a, int p, int q, int (*cmp)(void *, void *));
int partition(void **a, int p, int q, int (*cmp)(void *, void *));
void swap(void *a, void *b);
void **list_to_array(Lista l);
void array_to_list(void **v, int len, Lista l);
void sort_list(Lista l, int (*cmp)(void *, void *));
#endif

