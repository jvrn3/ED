#ifndef VIA_H
#define VIA_H
#include "../Geometry/geometry.h"
#include "../Graph/graph.h"
#include "../Lista/linked_list.h"

typedef void *Via;
double weightDistancia(void *);
Via createVia();
Vertice nearest_via(Lista l, Ponto p);
void via_insertEsquina(Via via, char *nome, double x, double y);
void via_insertRua(Via via, char *src, char *dest, char *ldir, char *lesq, double comp, double vm, char *nome);

void shortest_path(Via via, Ponto p_src, Ponto p_dest);
#endif
