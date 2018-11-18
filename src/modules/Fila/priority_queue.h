#ifndef PQ_H
#define PQ_H

typedef void *PQ;

PQ createPQ(int max);
int pq_less(PQ p, int i, int j, int (*cmp)(void *, void *));
void pq_exch(PQ p, int i, int j);
void pq_swim(PQ p,int k, int (*cmp)(void *, void *));
void pq_sink(PQ p, int k, int (*cmp)(void *, void *));
void pq_insert(PQ p,void *key, int(*cmp)(void *, void *));
void *pq_delMin(PQ p, int (*cmp)(void *, void *));
void *pq_min(PQ p);
int pq_isEmpty(PQ p);
// void change(PQ p, int k, void *item, int (*cmp)(void *, void *));
#endif
