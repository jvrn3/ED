#ifndef GRAPH_H
#define GRAPH_H
#include "../Lista/linked_list.h"
#include "../String/mystr.h"
#include "../Hash/hash_table.h"
#include <stdlib.h>
/* Um grafo é uma estrutura cuja representação é dada por um par de conjuntos V e E que se conectam,
 * sendo V as vértices e E as arestas(edge). 
 *
 * O grafo aqui usado é representado usando duas tabela hash, uma salvando as arestas e outra os vertices
 *
 *
 * 
 * */

typedef void * Grafo;
typedef void * Aresta;
typedef void * Vertice;

//inicializa grafo
Grafo createGrafo();

//cria arestas :: src -> dir -> data
Aresta createEdge(char *key_src, char *key_dest, void *data);

//cria vertce com id e dados
Vertice createVertex(char *id, void *data);

//insere vertice no grafo
void insertVertex(Grafo grafo, char *id, void *data);

//gera um src -> | usado para inserir aresta
char *concatena_src_dest(char *src, char *dest);

//insere aresta do grafo
void insertEdge(Grafo grafo, char *key_src, char * key_dest, void *data);

//pega informação da aresta src->dest
Aresta getInfo(Grafo grafo, char *key_src, char *key_dest);
void free_grafo(Grafo g);

/*Função booleana que retorna se src é adjacente a dest*/
int a_adjacente(Grafo grafo, char * src, char *dest);

/*
 *Lista os adjacentes de um dado vértice
 * */
Lista v_adjacentes(Grafo grafo, char* key);

//func auxiliar
int compare_aresta(Hash h, void *k);

/* Getters */
void *aresta_get_data(Aresta aresta);
void *vertice_get_data(Vertice vertice);
char *vertice_get_id(Vertice vertice);

#endif
