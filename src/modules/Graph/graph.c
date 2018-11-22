#include "graph.h"
#include <float.h>
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
	double minDist;
	struct stVertice *previous;
}StVertice;

typedef struct stGrafo{
	int V, E;
	Hash vertices;
	Hash arestas;

}StGrafo;

Grafo createGrafo(){
	StGrafo *sg = malloc(sizeof(StGrafo));
	sg->arestas = new_hash_table();
	sg->vertices = new_hash_table();
	sg->V = 0;
	sg->E = 0;
	return sg;
}

Vertice createVertex(char *id, void *data){
	Vertice vertice = malloc(sizeof(StVertice));
	StVertice *sv = (StVertice *) vertice;
	strcpy(sv->id, id);
	sv->data = data;
	sv->minDist = FLT_MAX;
	sv->previous = NULL;
	return vertice;
}
void insertVertex(Grafo grafo, char *id, void *data){
	StGrafo *sg = (StGrafo *) grafo;
	Vertice vertice = createVertex(id, data);
	put(sg->vertices, id, vertice);
	sg->V++;
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
void free_edge(Aresta a){
	if(a == NULL)
		return;
	StAresta *se = (StAresta *) a;
	void *data = se->data;
	free(a);
	free(data);
}
void free_vertice(Vertice v){
	if(v == NULL)
		return;
	StVertice *sv = (StVertice *) v;
	void *data = sv->data;
	free(v);
	free(data);

}
void insertEdge(Grafo grafo, char *key_src, char *key_dest, void *data){
	StGrafo *sg = (StGrafo *) grafo;
	Aresta aresta = createEdge(key_src, key_dest, data);

	char *key = concatena_src_dest(key_src, key_dest);
	put(sg->arestas, key, aresta);
	sg->E++;
	free(key);
}
Aresta edge_getInfo(Grafo grafo, char *key_src, char *key_dest){
	StGrafo *sg = (StGrafo *) grafo;
	char *key = concatena_src_dest(key_src, key_dest);

	Aresta aresta = search(sg->arestas, key);

	free(key);

	return aresta;
}
Vertice vertex_getInfo(Grafo grafo, char *key){
	StGrafo *sg = (StGrafo *) grafo;

	Vertice vertice = search(sg->vertices, key);
	return vertice;
}
int a_adjacente(Grafo grafo, char *key_src, char *key_dest){
	StGrafo *sg = (StGrafo *) grafo;
	char *key = concatena_src_dest(key_src, key_dest);
	Aresta a = search(sg->arestas, key);
	free(key);
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
int cmpr_vertice(Vertice a, Vertice b){

	StVertice *sv = (StVertice *) a;
	StVertice *svb = (StVertice *) b;
	if(sv->minDist > svb->minDist)
		return 1;
	return 0;
}
void dijkstra(Grafo grafo, Vertice source, Vertice dest, double (*getWeight)(void *)){

	StGrafo *sg = (StGrafo *) grafo;
	int V = sg->V;
	PQ pq = createPQ(V);
	int found = 0;

	StVertice *sSource = (StVertice *) source;
	sSource->minDist = 0;
	pq_insert(pq, source, cmpr_vertice);
	while(!pq_isEmpty(pq) && found == 0){
		StVertice *v = pq_delMin(pq, cmpr_vertice);
		//a famosa relaxada
		Lista adjacentes = get_V_adj(grafo, v);
		Node *n;
		for(n = getFirst(adjacentes); n != NULL; n = getNext(n)){

			StAresta *aresta = hash_get_data(list_get_data(n));
			StVertice *vert = search(sg->vertices, aresta->key_dest);
			double weight = getWeight(aresta->data);
			if(weight != FLT_MAX){
				double distanceThroughVert = v->minDist + weight;
				if(distanceThroughVert < vert->minDist){
					vert->minDist = distanceThroughVert;
					vert->previous = v;

					if(strcmp(vertice_get_id(vert), vertice_get_id(dest))== 0){
						found = 1;
						break;
					}
					pq_insert(pq, vert, cmpr_vertice);
				}
			}

		}
		destroyList(adjacentes);
	}
	free_pq(pq);
}

int cmpr_v_adj(void *a, void *b){
	char *vertice_key = (char *) b;
	StAresta * aresta = hash_get_data(a);
	if(strcmp(aresta->key_src, vertice_key) == 0)
		return 1;
	return 0;
}
//get edges adjacent to a vertice V
Lista get_V_adj(Grafo g, Vertice v){
	StGrafo *sg = (StGrafo *) g;
	StVertice *sv = (StVertice *) v;
	Lista adjacentes = hash_filter_to_list(sg->arestas, cmpr_v_adj, sv->id);
	return adjacentes;
}
int compare_true(void *a, void *b){
	return 1;
}
Lista get_all_vertices(Grafo g){
	StGrafo *sg = (StGrafo *) g;
	Lista l = hash_filter_to_list(sg->vertices, compare_true, NULL);
	return l;
}
Lista get_all_arestas(Grafo g){
	StGrafo *sg = (StGrafo *) g;
	Lista l = hash_filter_to_list(sg->arestas, compare_true, NULL);
	return l;
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
	delete_hash_table(sg->arestas, free_edge);
	delete_hash_table(sg->vertices, free_vertice);
	free(sg);
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
int graph_edges(Grafo g){

	StGrafo *sg = (StGrafo *) g;
	return sg->E;
}
int graph_vercies(Grafo g){

	StGrafo *sg = (StGrafo *) g;
	return sg->V;
}
double get_minDist(Vertice v){
	StVertice *sv = (StVertice *)v;
	return sv->minDist;
}

Vertice vertice_get_previous(Vertice v){
	StVertice *sv = (StVertice *) v;
	return sv->previous;
}
char *aresta_get_source(Aresta a){
	StAresta *sa = (StAresta *) a;
	return sa->key_src;
}
char *aresta_get_dest(Aresta a){
	StAresta *sa = (StAresta *) a;
	return sa->key_dest;
}
