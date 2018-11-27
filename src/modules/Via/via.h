#ifndef VIA_H
#define VIA_H
#include "../Geometry/geometry.h"
#include "../Graph/graph.h"
#include "../Lista/linked_list.h"
#include "../Rua/rua.h"
#include "../Svg/svg.h"

typedef void *Via;

/* Sistema viário da Siguel 
 *
 * */
//retorna o comprimento da rua r
double weightDistancia(Rua r);

//retorna a distancia/tempo da rua r
double weightTempo(Rua r);
//cria um novo sistema viário

Via createVia();

//Recebe uma lista de vértices e acha o vértice mais proximo do ponto p
Vertice nearest_via(Lista l, Ponto p, FILE *fSvg);

void via_insertEsquina(Via via, char *nome, double x, double y);
void via_insertRua(Via via, char *src, char *dest, char *ldir, char *lesq, double comp, double vm, char *nome);

//calcula o menor caminho e salva os vértices em uma lista
Lista shortest_path(Via via, Ponto p_src, Ponto p_dest, double (*getWeight)(void *), Lista l);

//printa o menor caminho no arquivo svg
void viaShortestPaths(Via v,Lista l, FILE *fSvg, char *cor);
//escreve o a menor direcao no arquivo txt
void viaTxtShortestPaths(Via v, Lista l, FILE *fTxt);

//dado uma lista de carro, calcular se se sobrepõem.
void car_overlap(Via via, Lista l, int (*cmp)(void *, void *), FILE *fSvg, FILE *fTxt);

//retorna a direção(esquerda, direita etc)
char *viaGetDirecao(Vertice a, Vertice b);

void n_shortest_paths(Via via, Ponto *R, int *indices, int n, char *cor1, char *co2, double (*getWeight)(void *), FILE *fSvg);
void drawVias(Grafo g, FILE *fSvg);
void colisaoGetRua(Via via, Rect r, Lista l);
#endif
