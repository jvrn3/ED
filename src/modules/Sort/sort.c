#include <stdio.h>
#include "sort.h"
#include "../Geometry/geometry.h"
/* goals: heap sort, quick sort, merge sort */


//parent is in position k/2
//childrens = 
//l = 2k
//r = 2k+1
//

int parent(int i){ return i/2;}
int left(int i ){return 2*i + 1;}
int right(int i){return 2*i + 2;}

void exch(Ponto *i, Ponto *j){
	Ponto tmp = *i;
	*i = *j;
	*j = tmp;
}
void max_heapify_x(Ponto *p, int i, int heap_size){
	int l = left(i);
	int r = right(i);
	int largest = i;

	if(l < heap_size && p[l].x > p[largest].x)
		largest = l;
	
	if(r < heap_size && p[r].x > p[largest].x)
		largest = r;

	if(largest != i){
		exch(&p[i], &p[largest]);
		max_heapify_x(p, largest, heap_size);
	}
}
	void max_heapify_y(Ponto *p, int i, int heap_size){
	int l = left(i);
	int r = right(i);
	int largest = i;

	if(l < heap_size && p[l].y > p[largest].y)
		largest = l;
	
	if(r < heap_size && p[r].y > p[largest].y)
		largest = r;

	if(largest != i){
		exch(&p[i], &p[largest]);

		max_heapify_y(p, largest, heap_size);
	}
}

void build_max_heap_y(Ponto *p, int n){
	for(int i = n /2; i >= 0; i--){
		max_heapify_y(p, i, n);
	}
}
void build_max_heap_x(Ponto *p, int n){
	for(int i = n /2; i >= 0; i--){
		max_heapify_x(p, i, n);
	}
}



void heap_sort_x(Ponto *p, int length){
	build_max_heap_x(p, length);
	for(int i = length-1; i >= 0; i--){
		exch(&p[i], &p[0]);
		max_heapify_x(p, 0, i);
	}
}
void heap_sort_y(Ponto *p, int length){
	build_max_heap_y(p, length);
	for(int i = length-1; i >= 0; i--){
		exch(&p[i], &p[0]);
		max_heapify_y(p, 0, i);
	}
}
//sorting in linear order for Integers
int *counting_sort(int *A,  int k, int n){
	int c[k];
	for(int i = 0; i < k; i++)
		c[i] = 0;

	for(int j = 0; j < n ; j++)
		c[A[j]] = c[A[j]]++;

	for(int i = 1; i < k; i++)
		c[i] = c[i] + c[i-1];


	int *B = malloc(sizeof(A) * n);
	for(int i =0 ; i < n; i++)
		B[i] = 0;
	for(int j = n-1; j >= 0; j--){
		B[c[A[j]]] = A[j];
		c[A[j]] = c[A[j]] - 1;
	}
	return B;
}
/*
 * function should be called first with array -> 0 -> size of array.
 */
void quick_sort(float *a, int p, int r){
	
	if(p < r){
		float q = partition(a, p, r);
		quick_sort(a, p, q);
		quick_sort(a, q+1, r);
	}
}
int partition(float *a, int p, int r){
	/*
	 * The idea behind this is that it sorts based on x, also known as pivot
	 */

	float x = a[r-1];
	int i = p-1;
	// j from p to r 
	for(int j = p; j < r-1; j++){
		if (x >= a[j]){
			i++;
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[i+1], &a[r-1]);
	return i+1;
}
void swap(float *a, float*b){
	float tmp = *a;
	*a = *b;
	*b = tmp;
}
