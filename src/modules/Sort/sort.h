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

#endif
