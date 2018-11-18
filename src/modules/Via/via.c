#include "via.h"
double weightDistancia(void *a){
	return rua_get_cmp(a);
}
Via createVia(){
	Via via = createGrafo();
	return via;
}
Vertice nearest_via(Lista l, Ponto p){
	Node *n; 
	Vertice v;
	double menor = FLT_MAX;
	for(n = getFirst(l); n != NULL; n = getNext(n)){
		void *p2 = vertice_get_data(hash_get_data(list_get_data(n)));
		Ponto ponto2 = *(Ponto *) p2;
		double d = distancePoints(p, ponto2);
		if(d < menor){
			menor = d;
			v = hash_get_data(list_get_data(n));
		}
	}
	return v;
}
void via_insertEsquina(Via via, char *nome, double x, double y){
	Ponto p = createPonto(x, y);
	insertVertex(via, nome, &p);
}
void via_insertRua(Via via, char *src, char *dest, char *ldir, char *lesq, double comp, double vm, char *nome){

	Rua r = createRua(nome, ldir, lesq, comp, vm);
	insertEdge(via, src, dest, r, weightDistancia);
}

void shortest_path(Via via, Ponto p_src, Ponto p_dest){
	
	Vertice src = nearest_via(get_all_vertices(via), p_src);
	Vertice dest = nearest_via(get_all_vertices(via), p_dest);
	dijkstra(via, src, dest);
}
