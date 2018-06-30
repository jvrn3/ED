#include <stdio.h>
#include "sort.h"

/* goals: heap sort, quick sort, merge sort */


//parent is in position k/2
//childrens = 
//l = 2k
//r = 2k+1
//

int parent(int i){ return i/2;}
int left(int i ){return 2*i + 1;}
int right(int i){return 2*i + 2;}
void exch(double *i, double *j){
	double tmp = *i;
	*i = *j;
	*j = tmp;
}
	

void max_heapify(double a[], int i, int heap_size){
	int l = left(i);
	int r = right(i);
	int largest = i;

	if(l < heap_size && a[l] > a[largest])
		largest = l;
	
	if(r < heap_size && a[r] > a[largest])
		largest = r;

	if(largest != i){
		exch(&a[i], &a[largest]);

		max_heapify(a, largest, heap_size);
	}
}

void build_max_heap(double a[], int n){
	for(int i = n /2 -1; i >= 0; i--){
		max_heapify(a, i, n);
	}
}
void heap_sort(double A[], int length){
	build_max_heap(A, length);
	for(int i = length -1; i >= 0; i--){
		exch(&A[i], &A[0]);
		max_heapify(A, 0, i);
	}
}

