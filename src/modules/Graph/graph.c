#include "graph.h"

/*
 *cria um grafo com tamanho v
 *grafo é uma hash table representando os vetores adjacentes
 *

 */
typedef struct stAresta{
	/*
	 * */
	char edge_nome[100];
	int src, dest;
	void *data;
}Aresta;
/*
 * 
 * */
typedef struct stVertice{
	/*
	 * Vertice guarda as arestas e também uma informação nela, assim como o nome
	 * */
	char vertice_nome[100];
	Lista arestas;
	void *data;
}Vertice;


typedef struct stGrafo{

	int v;
	Vertice **vertices;

}StGrafo;

//cria grafo com o numero de vértices
Grafo createGrafo(int n){
	//alocação dinâmica do grafo
	//TODO desalocação
	StGrafo *g = malloc(sizeof(StGrafo) * n);
	g->vertices = malloc(sizeof(Vertice *) * n);
	for(int i = 0; i < n; i++){
		g->vertices[i] = malloc(sizeof(Vertice));
		g->vertices[i]->arestas = createList();
	}
	return g;
}
void insertEdge(Grafo grafo, int src, int dest){
	//cria uma aresta e insere na lista dos vertices.
	StGrafo *sg = (StGrafo *) grafo;

	Aresta *aresta = malloc(sizeof(Aresta));
	aresta->src = src;
	aresta->dest = dest;
	aresta->data = NULL;

	//in oo style:
	//vertice[i].add(aresta)
	insert(sg->vertices[src]->arestas, aresta, src);
}

int cmpr_src_dest(void *a, void *b){
	Aresta *aresta = (Aresta *) a;
	int *n_b = (int *) b;
	if(aresta->dest == *n_b)
		return 1;
	return 0;
}
void addInfo(Grafo grafo, int src, int dest, void *data){
	StGrafo *sg = (StGrafo *) grafo;
	Aresta *aresta = searchList(sg->vertices[src]->arestas, cmpr_src_dest, &dest);

	if(aresta == NULL)
		return;
	aresta->data = data;
}

void *getInfo(Grafo grafo, int src, int dest){
	StGrafo *sg = (StGrafo *) grafo;
	Aresta *aresta = searchList(sg->vertices[src]->arestas, cmpr_src_dest, &dest);
	if(aresta != NULL)
		return aresta->data;
}

int a_adjacente(Grafo grafo, int src, int dest){
	StGrafo *sg = (StGrafo *) grafo;
	Node *n = sg->vertices[src]->arestas;
	/* for(n = getFirst(n); n != NULL; n = getNext(n)) */


}

