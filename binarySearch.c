#include <stdio.h>
/* void swap(int *a, int *b){ */
/* 	int tmp; */
/* 	tmp = *a; */
/* 	*a = *b; */
/* 	*b = tmp; */
/* } */
/*  */
/* int quick_sort(int v[], int lo, int hi){ */
/* 	int p; */
/* 	if(lo < hi){ */
/* 		p = partition(v, p, p-1); */
/* 	} */
/* } */
/* int partition(int v[], int lo, int hi){ */
/* 	int pivot = v[hi]; */
/* 	int i = lo-1; */
/* 	for(int j = lo; j < hi-1){ */
/* 		if(v[j] < pivot){ */
/* 		} */
/* 	 */
/* 	} */
/*  */
/*  */
/* } */

void insertion_sort(int v[], int len){
	for(int j = 1; j < len;j ++ ){
		int key = v[j];
		int i = j-1;
		while(i >= 0 && v[i] > key){
			v[i+1] = v[i];
			i = i-1;
		}
		v[i+1] = key;
		
	}
}
int binary_search(int v[], int procura, int len, int in){
	if(in > len){
		printf("Error");
		exit(1);
	}
	int meio = v[len+i/2];


}
int
main(){
	insertion_sort(a, 4);

	


}
