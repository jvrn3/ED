#ifndef VIA_H
#define VIA_H
#include "../Geometry/geometry.h"
#include "../Graph/graph.h"
#include "../Lista/linked_list.h"
#include "../Rua/rua.h"
#include "../Svg/svg.h"

typedef void *Via;
double weightDistancia(void *);
double weightTempo(void *);
Via createVia();
Vertice nearest_via(Lista l, Ponto p, FILE *fSvg);
void via_insertEsquina(Via via, char *nome, double x, double y);
void via_insertRua(Via via, char *src, char *dest, char *ldir, char *lesq, double comp, double vm, char *nome);

//calcula o menor caminho e salva os vértices em uma lista
Lista shortest_path(Via via, Ponto p_src, Ponto p_dest, double (*getWeight)(void *), Lista l);
void viaShortestPaths(Via v,Lista l, FILE *fSvg, char *cor);
void viaTxtShortestPaths(Via v, Lista l, FILE *fTxt);

void car_overlap(Lista l, int (*cmp)(void *, void *), FILE *fSvg);

char *viaGetDirecao(Vertice a, Vertice b);

void n_shortest_paths(Via via, Ponto *R, int *indices, int n, char *cor1, char *co2, double (*getWeight)(void *), Lista vertices, FILE *fSvg);
void drawVias(Grafo g, FILE *fSvg);
void colisaoGetRua(Via via, Rect r, Lista l);
#endif
