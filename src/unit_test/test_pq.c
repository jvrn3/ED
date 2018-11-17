#include "../modules/Fila/priority_queue.h"
#include <stdio.h>

int cmp(void *va, void *vb){
	int *a = (int *)va;
	int *b = (int *) vb;
	if(*a > *b )
		return 1;
	return 0;
}
int
main(){
	PQ pq = createPQ(10);

	int a = 5;
	int b = 3;
	int h = 10;
	void *va = &a;
	void *vb = &b;
	void *vh = &h;
	pq_insert(pq, 1, va, cmp);
	pq_insert(pq, 2, vh, cmp);
	pq_insert(pq, 3, vb, cmp);
	while(!pq_isEmpty(pq)){
		void *r = pq_min(pq);
		printf("%d\n", *(int *)r);
		pq_delMin(pq, cmp);
	}
}


