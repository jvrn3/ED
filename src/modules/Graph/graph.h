#ifndef GRAPH_H
#define GRAPH_H
#include "../Lista/linked_list.h"
#include "../String/mystr.h"
#include <stdlib.h>
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
typedef void * Aresta;
typedef void * Vertice;

/*
 * cria um grafo com n vertices
 * */
Grafo createGrafo();

/*insere uma aresta de src para dest
  src -----> dest
 */
Aresta createEdge(char *key_src, char *key_dest, void *data);


Vertice createVertex(char *id, void *data);

void insertVertex(Grafo grafo, char *id, void *data);

char *concatena_src_dest(char *src, char *dest);

void insertEdge(Grafo grafo, char *key_src, char * key_dest, void *data);

Aresta getInfo(Grafo grafo, char *key_src, char *key_dest);
/*
 * 
 * Adiciona informação na aresta src ----> dest
 *
 * */

void free_grafo(Grafo g);
/*Retorna a informação numa dada aresta*/
// void *getInfo(Grafo grafo, int src, int dest);



/*Função booleana que retorna se src é adjacente a dest*/
int a_adjacente(Grafo grafo, char * src, char *dest);

/*
 *Lista os adjacentes de um dado vértice
 * */
Lista v_adjacente(Grafo grafo, int v);


int cmpr_src_dest(void *a, void *b);

void *aresta_get_data(Aresta aresta);

void *vertice_get_data(Vertice vertice);

char *vertice_get_id(Vertice vertice);
#endif
