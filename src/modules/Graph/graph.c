#include "graph.h"
/*
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
	char id[100];
	void *data;
}StVertice;


typedef struct stGrafo{
	Hash vertices;
	Hash arestas;

}StGrafo;

Grafo createGrafo(){
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
char *concatena_src_dest(char *src, char *dest){
	char *new_key = malloc(sizeof(char) * 100);
	strcpy(new_key, src);
	strcat(new_key, " ");
	strcat(new_key, dest);
	return new_key;
}
Aresta createEdge(char *key_src, char *key_dest, void *data){
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
Aresta getInfo(Grafo grafo, char *key_src, char *key_dest){
	StGrafo *sg = (StGrafo *) grafo;
	char *key = concatena_src_dest(key_src, key_dest);

	Aresta aresta = search(sg->arestas, key);

	free(key);

	return aresta;
}
int a_adjacente(Grafo grafo, char *key_src, char *key_dest){
	StGrafo *sg = (StGrafo *) grafo;
	Aresta a = search(sg->arestas, concatena_src_dest(key_src, key_dest));
	if(a == NULL)
		return -1;
	return 1;
}
Lista v_adjacentes(Grafo grafo, char *key){
	StGrafo *sg = (StGrafo *) grafo;
	Lista l = hash_filter_to_list(sg->arestas, compare_aresta, key);

	Lista retorno = createList();
	while(length(l) > 0){
		void *hash_data = removeLast(l);

		StAresta *sa = (StAresta *) hash_get_data(hash_data);
		Vertice v = search(sg->vertices, sa->key_dest);
		insert(l, v, 0);
	}
	return retorno;
}
int compare_aresta(Hash h, void *k){
	char *key = (char *) k;
	StAresta *sa = hash_get_data(h);
	if(strcmp(sa->key_src, key) == 0){
		return 1;
	}
	return 0;
}
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

