#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct stPQ{
	int N;
	void **keys;
	int *pq;
	int *qp;

}StPQ;

int pq_less(PQ p, int i, int j, int (*cmp)(void *, void *)){
	StPQ *spq = (StPQ *) p;
	int *pq = spq->pq;
	void **keys = spq->keys;
	if(cmp(keys[pq[i]], keys[pq[j]]) > 0){
		return 1;
	}
	return 0;
}

void pq_exch(PQ p, int i, int j){
	StPQ *spq = (StPQ *) p;
	int *pq = spq->pq;
	void **keys = spq->keys;
	void *data = keys[pq[i]];
	keys[pq[i]] = keys[pq[j]];
	keys[pq[j]] = data;
}
PQ createPQ(int max){
	PQ pq = malloc(sizeof(StPQ));
	StPQ *spq = (StPQ *) pq;

	spq->N = 0;
	spq->pq = malloc(sizeof(int) * (max + 1));

	spq->qp = malloc(sizeof(int) * (max + 1));

	for(int i = 0; i <= max; i++)
		spq->qp[i] = -1;

	spq->keys = malloc(sizeof(void *) * (max + 1));

}

void pq_swim(PQ p, int k, int (*cmp)(void *, void *)){
	StPQ *spq = (StPQ *) p;
	void **keys = spq->keys;
	int *pq = spq->pq;

	while(k > 1 && pq_less(p, k/2, k, cmp)){
		pq_exch(p, k/2, k);
		k = k/2;
	}
}
void pq_sink(PQ p, int k, int (*cmp)(void *, void *)){
	StPQ *spq = (StPQ *) p;
	while(2*k <= spq->N){
		int j = 2 *k;
		if(j < spq->N && pq_less(p, j, j +1, cmp))
				j++;
		if(pq_less(p, k, j, cmp) == 0)
			break;
		pq_exch(p, k, j);

		k = j;
	}
}
void pq_insert(PQ p, int k, void *key, int(*cmp)(void *, void *)){
	StPQ  *spq = (StPQ *) p;
	spq->N++;
	spq->qp[k] = spq->N;
	spq->pq[spq->N] = k;
	spq->keys[k] = key;

	pq_swim(p, k, cmp);
}
int pq_delMin(PQ p, int (*cmp)(void *, void *)){
	StPQ *spq = (StPQ *) p;
	int indexOf  = spq->pq[1];
	pq_exch(p, 1, spq->N--);
	pq_sink(p, 1,cmp);
	spq->keys[spq->pq[spq->N+1]] = NULL;
	spq->qp[spq->pq[spq->N+1]] = -1;
	return indexOf;
}
void *pq_min(PQ p){
	StPQ *spq = (StPQ *) p;
	return spq->keys[spq->pq[1]];
}
int pq_isEmpty(PQ p){
	StPQ *spq = (StPQ *) p;
	if(spq->N == 0)
		return 1;
	return 0;

}
//free
