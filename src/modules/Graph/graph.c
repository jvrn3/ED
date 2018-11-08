#include "graph.h"
#include "../Hash/hash_table.h"
/*
 *cria um grafo com tamanho v
 *grafo é uma hash table representando os vetores adjacentes
 *

 */
typedef struct stAresta{
	/*
	 * */
	char key_src[50], key_dest[50];
	void *data;

}StAresta;
/*
 * 
 * */
typedef struct stVertice{
	/*
	 * Vertice guarda as arestas e também uma informação nela, assim como o nome
	 * */
	char id[100];
	void *data;
}StVertice;


typedef struct stGrafo{
	Hash vertices;
	Hash arestas;

}StGrafo;

//cria grafo com o numero de vértices
Grafo createGrafo(){
	//alocação dinâmica do grafo
	StGrafo *sg = malloc(sizeof(StGrafo));
	sg->arestas = new_hash_table();
	sg->vertices = new_hash_table();
	return sg;
}

Vertice createVertex(char *id, void *data){
	Vertice vertice = malloc(sizeof(StVertice));
	StVertice *sv = (StVertice *) vertice;
	strcpy(sv->id, id);
	sv->data = data;
	return vertice;
}
void insertVertex(Grafo grafo, char *id, void *data){
	StGrafo *sg = (StGrafo *) grafo;
	Vertice vertice = createVertex(id, data);
	put(sg->vertices, id, vertice);
}
/* int cmpr_src_dest(void *a, void *b){ */
/* 	Aresta *aresta = (Aresta *) a; */
/* 	int *n_b = (int *) b; */
/* 	if(aresta->dest == *n_b) */
/* 		return 1; */
/* 	return 0; */
/* } */
char *concatena_src_dest(char *src, char *dest){
	char *new_key = malloc(sizeof(char) * 100);
	strcpy(new_key, src);
	strcat(new_key, " ");
	strcat(new_key, dest);
	return new_key;
}
Aresta createEdge(char *key_src, char *key_dest, void *data){
	//cria uma aresta e insere na lista dos vertices.
	Aresta aresta = malloc(sizeof(StAresta));
	StAresta *ar = (StAresta *) aresta;
	strcpy(ar->key_src, key_src);
	strcpy(ar->key_dest, key_dest);
	ar->data = data;

	return aresta;
}
void insertEdge(Grafo grafo, char *key_src, char *key_dest, void *data){
	StGrafo *sg = (StGrafo *) grafo;
	Aresta aresta = createEdge(key_src, key_dest, data);

	char *key = concatena_src_dest(key_src, key_dest);
	put(sg->arestas, key, aresta);
	free(key);
}
//Procura por uma aresta a partir de src -> dest 
Aresta getInfo(Grafo grafo, char *key_src, char *key_dest){
	StGrafo *sg = (StGrafo *) grafo;
	char *key = concatena_src_dest(key_src, key_dest);

	Aresta aresta = search(sg->arestas, key);

	free(key);

	return aresta;
}
/* int a_adjacente(Grafo grafo, int src, int dest){ */
/* 	StGrafo *sg = (StGrafo *) grafo; */
/* 	Node *n; */
/* 	for(n = getFirst(sg->vertices[src]->arestas); n != NULL; n = getNext(n)){ */
/* 		Aresta *aresta = list_get_data(n); */
/* 		if(dest == aresta->dest) */
/* 			return 1; */
/* 	} */
/* 	return 0; */
/* } */
/* Lista v_adjacentes(Grafo grafo, int v){ */
/* 	StGrafo *sg = (StGrafo *) grafo; */
/* 	if(sg == NULL) */
/* 		return NULL; */
/* 	return sg->vertices[v]->arestas; */
/* } */

/* int a_adjacente(Grafo grafo, char *key_src, char *key_dest){ */
/* 	//Should imlement */
/*  */
/* } */

void free_grafo(Grafo g){
	StGrafo *sg = (StGrafo *) g;
	delete_hash_table(sg->arestas, free);
	delete_hash_table(sg->vertices, free);
}
void *aresta_get_data(Aresta aresta){
	StAresta *sa = (StAresta *) aresta;
	return sa->data;
}
void *vertice_get_data(Vertice vertice){
	StVertice *sv = (StVertice *) vertice;
	return sv->data;
}
char *vertice_get_id(Vertice vertice){
	StVertice *sa = (StVertice *) vertice;
	return sa->id;
}

