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
/* int *counting_sort(int *A,  int k, int n){ */
/* 	int c[k]; */
/* 	for(int i = 0; i < k; i++) */
/* 		c[i] = 0; */
/*  */
/* 	for(int j = 0; j < n ; j++) */
/* 		c[A[j]] = c[A[j]]++; */
/*  */
/* 	for(int i = 1; i < k; i++) */
/* 		c[i] = c[i] + c[i-1]; */
/*  */
/*  */
/* 	int *B = malloc(sizeof(A) * n); */
/* 	for(int i =0 ; i < n; i++) */
/* 		B[i] = 0; */
/* 	for(int j = n-1; j >= 0; j--){ */
/* 		B[c[A[j]]] = A[j]; */
/* 		c[A[j]] = c[A[j]] - 1; */
/* 	} */
/* 	return B; */
/* } */
/*
 * function should be called first with array -> 0 -> size of array.
 */

void **list_to_array(Lista l){
	int len = length(l);
	void **v = malloc(sizeof(void *) * len);
	Node *n;
	int i = 0;
	for(n = getFirst(l); n != NULL; n = getNext(n)){
		v[i] = n->data;
		i++;
	}
	return v;
}
void array_to_list(void **v, int len, Lista l){
	//removendo o antigo dado
	
	while(length(l) > 0){
		removeFirst(l);
	}
	for(int i = 0; i < len; i++){
		insertAtEnd(l, v[i]);
	}
}
void sort_list(Lista l, int (*cmp)(void *, void *)){
	void **v = list_to_array(l);
	quick_sort(v, 0, length(l), cmp);

	array_to_list(v, length(l), l);
	free(v);
}
void quick_sort(void **a, int p, int r, int (*cmp)(void *, void *)){
	if(p < r){
		int q = partition(a, p, r, cmp);
		quick_sort(a, p, q, cmp);
		quick_sort(a, q+1, r, cmp);
	}
}
int partition(void **a, int p, int r, int (*cmp)(void *, void *)){
	/*
	 * The idea behind this is that it sorts based on x, also known as pivot
	 */
	void *x = a[r-1];
	void *aux;
	int i = p-1;
	// j from p to r 
	for(int j = p; j < r-1; j++){
		if (cmp(x, a[j])){
			i++;
			aux = a[i];
			a[i] = a[j];
			a[j] = aux;
		}
	}
	aux = a[i+1];
	a[i+1] = a[r-1];
	a[r-1] = aux;
	return i+1;
}

/*  */
/* Node *merge_sort(Node * head){ */
/* 	if(head == NULL || getNext(head)) */
/* 		return head; */
/* 	Node *middle = list_get_middle(head); */
/*  */
/* 	Node *sHalf = getNext(middle); */
/* 	middle->next = NULL; */
/* 	return merge(merge_sort(head), merge_sort(sHalf)); */
/* } */


