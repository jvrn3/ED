#include "via.h"
double weightDistancia(void *a){
	return rua_get_cmp(a);
}
double weightTempo(void *a){
	if(rua_get_cmp(a) == 0)
		return 0;
	if(rua_get_cmp(a) < 0 || rua_get_vm(a) <= 0)
		return FLT_MAX;
	else{
		return rua_get_cmp(a)/rua_get_vm(a);
	}
}
Via createVia(){
	Via via = createGrafo();
	return via;
}
Vertice nearest_via(Lista l, Ponto p){
	Node *n; 
	Vertice v = NULL;
	double menor = FLT_MAX;
	double d;
	for(n = getFirst(l); n != NULL; n = getNext(n)){
		Ponto *p2 = vertice_get_data(hash_get_data(list_get_data(n)));
		Ponto ponto2 = *(Ponto *) p2;
		d = distancePoints(p, ponto2);
		if(d < menor){
			menor = d;
			v = hash_get_data(list_get_data(n));
		}
	}
	return v;
}
void via_insertEsquina(Via via, char *nome, double x, double y){
	Ponto *p = malloc(sizeof(Ponto));
	p->x = x;
	p->y = y;
	insertVertex(via, nome, p);
}
void via_insertRua(Via via, char *src, char *dest, char *ldir, char *lesq, double comp, double vm, char *nome){

	Rua r = createRua(nome, ldir, lesq, comp, vm);
	insertEdge(via, src, dest, r);
}

Lista shortest_path(Via via, Ponto p_src, Ponto p_dest, double (*getWeight)(void *), Lista vertices){
	Vertice all = get_all_vertices(via);

	Vertice src = nearest_via(all, p_src);
	Vertice dest = nearest_via(all, p_dest);
	if(src == NULL || dest == NULL || all == NULL){
		printf("Erro shortest path");
		return NULL;
	}
	dijkstra(via, src, dest, getWeight);

	printf("Shortest %lf\n", get_minDist(dest));
	for(Vertice vertex = dest; vertex != NULL; vertex = vertice_get_previous(vertex)){
		insert(vertices, vertex, 0);
	}
	return vertices;
}
void viaShortestPaths(Via v, Lista l, FILE *fSvg, char *cor){
	Node *node = getFirst(l);
	for(Node *n = node; n != NULL; n = getNext(n)){
		char *src = vertice_get_id(list_get_data(n));
		if(getNext(n) != NULL){
			char *dest = vertice_get_id(list_get_data(getNext(n)));
			if(a_adjacente(v, src, dest)){
				Vertice a = list_get_data(n);
				Vertice b = list_get_data(getNext(n));
				Ponto *p1 = vertice_get_data(a);
				Ponto *p2 = vertice_get_data(b);


				drawArrow2(fSvg, p1->x, p1->y, p2->x, p2->y, cor );
				drawArrow(fSvg, cor);
			}
		}
	}
}

char * viaGetDirecao(Vertice a, Vertice b){

	Ponto *pontoA = vertice_get_data(a);
	Ponto *pontoB = vertice_get_data(b);
	if(pontoB->x - pontoA->x > 0)
		return "Direita";
	if(pontoB->x - pontoA->x < 0){
		return "Esquerda";
	}
	if(pontoB->y - pontoA->y > 0){
		return "Sul";
	}
	else{
		return "Norte";
	}
}
void viaTxtShortestPaths(Via v, Lista l, FILE *fTxt){

	Node *node = getFirst(l);
	for(Node *n = node; n != NULL; n = getNext(n)){
		Vertice a = list_get_data(n);
		char *src = vertice_get_id(a);
		if(getNext(n) != NULL){
			Vertice b = list_get_data(getNext(n));
			char *dest = vertice_get_id(b);
			if(a_adjacente(v, src, dest)){
				fprintf(fTxt, "Siga na direcao %s na Rua %s\n", viaGetDirecao(a,b), rua_get_nome(aresta_get_data(edge_getInfo(v, src, dest))));
			}
		}
	}
}

void car_overlap(Lista l, int (*cmp)(void *, void *), FILE *fSvg){
	//should sorta according to x
	sort_list(l, cmp);
	Node *n, *node_low;
	Rect r, r_low;
	StRect *sr, *sr_low;
	for(n = getFirst(l); n != NULL; n = getNext(n)){
		r = carro_get_posic(list_get_data(n));
		sr = (StRect *) r;

		if(getNext(n) != NULL){
			//proximo carro;
			Lista overlap = createList();

			insert(overlap, r, 0);
			node_low = getNext(n);
			r_low = carro_get_posic(list_get_data(node_low));
			sr_low = (StRect *) r_low;


			while(node_low != NULL && sr->x + sr->w > sr_low->x ){
				/* printf("overlap %s\n", carro_get_placa(list_get_data(node_low))); */
				if(overlayRR(r, r_low)){
					insertAtEnd(overlap, r_low);
				}
				node_low = getNext(node_low);
				if(node_low == NULL)
					break;
				r_low = carro_get_posic(list_get_data(node_low));
				sr_low = (StRect *) r_low;
			}
			if(length(overlap ) > 1){
				Rect first = list_get_data(getFirst(overlap));
				Rect last = list_get_data(getLast(overlap));
				drawOverlapCar(fSvg, first, last);
			}
			destroyList(overlap);

		}
	}
}
