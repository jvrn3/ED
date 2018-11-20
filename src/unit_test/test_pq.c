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
	PQ pq = createPQ(40);

	int a = 5;
	int b = 3;
	int h = 10;
	void *va = &a;
	void *vb = &b;
	void *vh = &h;
	pq_insert(pq, va, cmp);
	pq_insert(pq, vh, cmp);
	pq_insert(pq, vb, cmp);
	pq_remove(pq, va, cmp, cmp);
	printf("%d", *(int *)pq_min(pq));
	
}


