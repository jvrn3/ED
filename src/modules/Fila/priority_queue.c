#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct stPQ{
	int N;
	void **pq;
}StPQ;

int pq_less(PQ p, int i, int j, int (*cmp)(void *, void *)){
	StPQ *spq = (StPQ *) p;
	void **pq = spq->pq;
	if(cmp(pq[i], pq[j]) > 0){
		return 1;
	}
	return 0;
}

void pq_exch(PQ p, int i, int j){
	StPQ *spq = (StPQ *) p;

	void **pq = spq->pq;
	void *data = pq[i];
	pq[i] = pq[j];
	pq[j] = data;
}
PQ createPQ(int max){
	PQ pq = malloc(sizeof(StPQ));
	StPQ *spq = (StPQ *) pq;
	spq->N = 0;

	spq->pq = malloc(sizeof(void *) * (max + 1));
	for(int i = 0; i < spq->N; i++){
		spq->pq[i] = NULL;
	}

	return pq;
}

void pq_swim(PQ p, int k, int (*cmp)(void *, void *)){

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
void pq_insert(PQ p, void *key, int(*cmp)(void *, void *)){

	StPQ  *spq = (StPQ *) p;
	spq->N++;
	spq->pq[spq->N] = key;
	pq_swim(p,spq->N, cmp);
}
void * pq_delMin(PQ p, int (*cmp)(void *, void *)){
	StPQ *spq = (StPQ *) p;

	void *data  = spq->pq[1];
	pq_exch(p, 1, spq->N--);
	spq->pq[spq->N + 1] = NULL;
	pq_sink(p, 1,cmp);
	return data;
}

void *pq_min(PQ p){
	StPQ *spq = (StPQ *) p;
	return spq->pq[1];
}
int pq_isEmpty(PQ p){
	StPQ *spq = (StPQ *) p;
	if(spq->N == 0)
		return 1;
	return 0;
}
void pq_remove(PQ p, void *data, int(*cmp)(void *, void *), int(*cmpr_data)(void *, void *)){

	StPQ *spq = (StPQ *) p;
	int i;
	for(i = 0; i < spq->N; i++){
		if(spq->pq[i] != NULL){
			if(spq->pq[i] == data)
				break;
		}
	}
	pq_exch(p, i, spq->N--);
	spq->pq[spq->N+1] = NULL;
	pq_sink(p, i, cmp);
}
void free_pq(PQ p){
	StPQ *spq = (StPQ *) p;
	free(spq->pq);
	free(spq);
}
//free
