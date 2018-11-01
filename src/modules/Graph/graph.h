#ifndef GRAPH_H
#define GRAPH_H
#include "../Lista/linked_list.h"
#include <stdlib.h>
#include "../Hash/hash_table.h"
/* Um grafo é uma estrutura cuja representação é dada por um par de conjuntos V e E que se conectam,
 * sendo V as vértices e E as arestas(edge). 
 *
 * O grafo aqui usado é representado usando o conceito de listas adjacentes
 *
 * Listas adjacentes são listas ligadas que representam cada vértice
 * Cada lista armazena os vizinhos do vértice
 *
 * 
 * */

typedef void * Grafo;

/*
 * cria um grafo com n vertices
 * */
Grafo createGrafo(int n);

/*insere uma aresta de src para dest
  src -----> dest
 */
void insertEdge(Grafo grafo, int src, int dest);

/*
 * Adiciona informação na aresta src ----> dest
 *
 * */
void addInfo(Grafo grafo, int src, int dest, void *data);

/*Retorna a informação numa dada aresta*/
void *getInfo(Grafo grafo, int src, int dest);

void removeAresta(Grafo grafo, int src, int dest);

/*Função booleana que retorna se src é adjacente a dest*/
int a_adjacente(Grafo grafo, int src, int dest);

/*
 *Lista os adjacentes de um dado vértice
 * */
Lista v_adjacente(Grafo grafo, int v);


int cmpr_src_dest(void *a, void *b);

#endif
