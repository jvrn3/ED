#ifndef SORT_H
#define SORT_H

int parent(int i);
int left(int i);
int right(int i);
void exch( double *i, double *j);
void max_heapify(double a[], int i, int n);
void build_max_heap(double a[], int n);
void heap_sort(double a[], int length);
#endif
