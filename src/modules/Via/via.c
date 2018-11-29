#include "via.h"
double weightDistancia(void *a){
	return rua_get_cmp(a);
}
double weightTempo(void *a){
	if(rua_get_cmp(a) == 0 )
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
//lista de vértices
Vertice nearest_via(Lista l, Ponto p, FILE *fSvg){
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
	/* Ponto *ponto = vertice_get_data(v); */
	/* if(fSvg != NULL){ */
	/* 	Circle c = createCircle("black", "orange", 5, ponto->x, ponto->y); */
	/* 	drawCircle(fSvg, c); */
	/* 	free(c); */
	/* } */
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

	Vertice src = nearest_via(all, p_src, NULL);
	Vertice dest = nearest_via(all, p_dest, NULL);
	if(src == NULL || dest == NULL || all == NULL){
		printf("Erro shortest path");
		return NULL;
	}
	dijkstra(via, src, dest, getWeight);

	if(get_minDist(dest) == FLT_MAX){
		printf("Impossivel calcular menor caminho\n");
		destroyList(all);
		return NULL;
	}
		printf("Shortest %lf\n", get_minDist(dest));
	for(Vertice vertex = dest; vertex != NULL; vertex = vertice_get_previous(vertex)){
		insert(vertices, vertex, 0);
	}


	destroyList(all);
	return vertices;
}
void n_shortest_paths(Via via, Ponto *R, int *indices, int n, char *cor1, char *cor2, double (*getWeight)(void *), FILE *fSvg){
	for(int i = 0; i < n-1; i++){
		Lista v = createList();
		shortest_path(via, R[indices[i]], R[indices[i+1]], getWeight, v);
		if(i % 2 ==0){
			viaShortestPaths(via, v, fSvg, cor1);
		}
		else{
			viaShortestPaths(via, v, fSvg, cor2);

        /*  */
		}
		cleanMinDist(via);
		destroyList(v);
	}

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

	char anterior[50];
	strcpy(anterior, " ");
	for(Node *n = node; n != NULL; n = getNext(n)){
		Vertice a = list_get_data(n);
		char *src = vertice_get_id(a);
		if(getNext(n) != NULL){

			Vertice b = list_get_data(getNext(n));
			char *dest = vertice_get_id(b);

			if(a_adjacente(v, src, dest)){
				Rua r = aresta_get_data(edge_getInfo(v, src, dest));
				if(strcmp(rua_get_nome(r), anterior) != 0 && strcmp(anterior, " ") != 0){
					fprintf(fTxt, "Vire na direcao %s no cruzamento com a rua %s\n", viaGetDirecao(a,b), rua_get_nome(r));
					strcpy(anterior, rua_get_nome(r));
				}
				else{
					fprintf(fTxt, "Siga na direcao %s na Rua %s\n", viaGetDirecao(a,b), rua_get_nome(r));
					strcpy(anterior, rua_get_nome(r));
				}
			}
		}
	}
}

void car_overlap(Via via, Lista l, int (*cmp)(void *, void *), FILE *fSvg, FILE *fTxt){
	//should sort according to x
	printf("Numero de carros %d\n", length(l));
	sort_list(l, cmp);
	Node *n, *node_low;
	Rect r, r_low;
	StRect *sr, *sr_low;
	Lista all = get_all_vertices(via);
	for(n = getFirst(l); n != NULL; n = getNext(n)){
		r = carro_get_posic(list_get_data(n));
		sr = (StRect *) r;

		if(getNext(n) != NULL){
			//proximo carro;
			Lista overlap = createList();
			Lista carros = createList();

			insert(overlap, r, 0);
			insert(carros, list_get_data(n), 0);
			node_low = getNext(n);
			r_low = carro_get_posic(list_get_data(node_low));
			sr_low = (StRect *) r_low;


			while(node_low != NULL && sr->x + sr->w > sr_low->x ){
				if(overlayRR(r, r_low)){
					insertAtEnd(overlap, r_low);
					insertAtEnd(carros, list_get_data(node_low));
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
				Rect colisao  = getOverlapRect(first, last);
				colisaoGetRua(via, colisao, all); 
				free(colisao);
				fprintf(fTxt, "Acidente envolvendo : [");
				for(Node *n = getFirst(carros) ; n != NULL ; n = getNext(n)){
					fprintf(fTxt," %s", carro_get_placa(list_get_data(n)));
				}
				fprintf(fTxt, " ]\n");
			}
			destroyList(overlap);
			destroyList(carros);

		}
	}
	destroyList(all);
}

void drawVias(Grafo g, FILE *fSvg){
	
	Lista arestas = get_all_arestas(g);
	for(Node *n = getFirst(arestas); n != NULL; n = getNext(n)){
		if(getNext(n) != NULL){
			Aresta a = hash_get_data(list_get_data(n));
			Vertice va = vertex_getInfo(g, aresta_get_source(a));
			Vertice vb = vertex_getInfo(g, aresta_get_dest(a));

			Ponto *ponto_a = vertice_get_data(va);
			Ponto *ponto_b = vertice_get_data(vb);

			/* fprintf(fSvg, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\"/>\n", */
					/* ponto_a->x, ponto_a->y, ponto_b->x, ponto_b->y, "blue"); */
			drawArrow2(fSvg, ponto_a->x, ponto_a->y, ponto_b->x, ponto_b->y, "blue");
			drawArrow(fSvg, "blue");

		}
	}
	destroyList(arestas);
}
//fazer uma lista de retangulos de sobreposição, chamar essa função
void colisaoGetRua(Via via, Rect r, Lista l){
	printf("Setando...\n");
	if(rect_vertical(r)){
		Ponto sup = createPonto( rect_get_x(r) + rect_get_w(r)/2, rect_get_y(r) );
		Ponto inf = createPonto(rect_get_x(r) + rect_get_w(r)/2, rect_get_y(r) + rect_get_h(r));
	
		Vertice a = nearest_via(l, sup, NULL);
		Vertice b = nearest_via(l, inf, NULL);
		if(a != NULL && b != NULL){
			Aresta aresta;
			aresta = edge_getInfo(via, vertice_get_id(a), vertice_get_id(b));
			if(aresta != NULL){
				Rua r = aresta_get_data(aresta);
				rua_set_vm(r, 0);
				printf("DIFFFF");
			
			}
			else{
				aresta = edge_getInfo(via, vertice_get_id(b), vertice_get_id(a));
				if(aresta != NULL){
					Rua r = aresta_get_data(aresta);
					rua_set_vm(r, 0);
					printf("@@DIFFFF");

				
				}
			}

		}
	}
	else{
		Ponto dir = createPonto(rect_get_x(r) + rect_get_w(r), rect_get_y(r) + rect_get_h(r)/2);
		Ponto esq = createPonto(rect_get_x(r), rect_get_y(r) + rect_get_h(r)/2);

		Vertice a = nearest_via(l, dir, NULL);
		Vertice b = nearest_via(l, esq, NULL);

		if(a != NULL && b != NULL){
			Aresta aresta;
			aresta = edge_getInfo(via, vertice_get_id(a), vertice_get_id(b));
			if(aresta != NULL){
				Rua r = aresta_get_data(aresta);
				rua_set_vm(r, 0);
			
			}
			else{
				aresta = edge_getInfo(via, vertice_get_id(b), vertice_get_id(a));
				if(aresta != NULL){
					Rua r = aresta_get_data(aresta);
					rua_set_vm(r, 0);
					printf("@@DIFFFF");

				
				}
			}
		}
	}
}
