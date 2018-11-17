#ifndef PQ_H
#define PQ_H

typedef void *PQ;

PQ createPQ(int max);
int pq_less(PQ p, int i, int j, int (*cmp)(void *, void *));
void pq_exch(PQ p, int i, int j);
void pq_swim(PQ p, int k, int (*cmp)(void *, void *));
void pq_sink(PQ p, int k, int (*cmp)(void *, void *));
void pq_insert(PQ p, int ind, void *key, int(*cmp)(void *, void *));
int pq_delMin(PQ p, int (*cmp)(void *, void *));
void *pq_min(PQ p);
int pq_isEmpty(PQ p);
#endif
