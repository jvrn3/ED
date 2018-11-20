#include "../modules/Graph/graph.h"
#include "../modules/Rua/rua.h"
typedef struct ponto{
	float x, y;
}Ponto;

double getWeight(void *a){
	return rua_get_cmp(a) / rua_get_vm(a);
}
int
main(){
	Grafo grafo = createGrafo();

	Rua r1 = createRua("Nossa Senhora do Rocio", "l", "r", 100, 4);
	Rua r2 = createRua("Nossa Senhora do Satanas", "l", "r", 200, 2);
	Rua r3 = createRua("Nossa Senhora do Jesus", "l", "r", 300, 10);
	Rua r4 = createRua("Nossa Senhora do Capeta", "l", "r", 10, 2);
	Rua r5 = createRua("Nossa Senhora do Virgem maria", "l", "r", 50, 10);
	Rua r6 = createRua("Nossa Senhora do Cristo jesus", "l", "r", 1, 1);
	Rua r7 = createRua("Nossa Senhora do Lula", "l", "r", 55, 55);
	Rua r8 = createRua("Nossa Senhora da Pablo Vitar", "l", "r", 23, 23);
	Rua r9 = createRua("Nossa Senhora do Bolsonaro", "l", "r", 44, 44);
	Ponto *p, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9;
	p = malloc(sizeof(Ponto));
	p2 = malloc(sizeof(Ponto));
	p3 = malloc(sizeof(Ponto));
	p4= malloc(sizeof(Ponto));
	p5= malloc(sizeof(Ponto));
	p6= malloc(sizeof(Ponto));
	p7= malloc(sizeof(Ponto));
	p8= malloc(sizeof(Ponto));
	p9= malloc(sizeof(Ponto));
	p->x = 5; p->y = 10;
	p2->x = 5; p2->y = 10;
	p3->x = 25; p3->y = 25;
	p4->x = 55; p4->y = 60;
	p5->x = 90; p5->y = 95;
	p6->x = 80; p6->y = 95;
	p7->x = 70; p7->y = 85;
	p8->x = 50; p8->y = 75;
	p9->x = 40; p9->y = 65;
	insertVertex(grafo, "josue", p);
	insertVertex(grafo, "Hobsbawn", p2);
	insertVertex(grafo, "Cleidiane", p3);
	insertVertex(grafo, "Joarez", p4);
	insertVertex(grafo, "Hacker", p5);
	insertVertex(grafo, "Malaquias", p6);
	insertVertex(grafo, "Jesus", p7);
	insertVertex(grafo, "Reginaldo", p8);
	insertVertex(grafo, "Satanas", p9);
	insertEdge(grafo, "josue", "Hobsbawn", r1);
	insertEdge(grafo, "josue", "Cleidiane", r2 );
	insertEdge(grafo, "Joarez", "Cleidiane", r3 );
	insertEdge(grafo, "Hacker", "Malaquias", r4);
	insertEdge(grafo, "Malaquias", "Jesus", r5);
	insertEdge(grafo, "Jesus", "Hacker", r6);
	insertEdge(grafo, "Reginaldo", "Satanas", r7);
	insertEdge(grafo, "Cleidiane", "Hacker", r8);
	insertEdge(grafo, "josue", "Jesus", r1);
	Aresta a = edge_getInfo(grafo, "josue", "Cleidiane");
	Rua get = (Ponto *)aresta_get_data(a);
	printf("Nome da rua -> %s", rua_get_nome(get));
	dijkstra(grafo, vertex_getInfo(grafo, "josue"),vertex_getInfo(grafo, "Hacker"), getWeight);


	printf("\nMin dist %lf\n", get_minDist(vertex_getInfo(grafo, "Hacker")));
	Lista vertices = createList();
	for(Vertice vertex = vertex_getInfo(grafo, "Hacker"); vertex != NULL; vertex = vertice_get_previous(vertex)){
		/* char *src = vertice_get_id(vertex); */
		/* printf("%s\n", src); */
		if(vertice_get_previous(vertex) != NULL){
			char *dest = vertice_get_id(vertice_get_previous(vertex));
			/* printf("%d ", a_adjacente(via, src, dest)); */
		}
		insert(vertices, vertex, 0);
	}
	for(Node *n = getFirst(vertices); n != NULL; n = getNext(n)){
		char *src = vertice_get_id(list_get_data(n));
		printf("%s\n", src);
		if(getNext(n) != NULL){
			char *dest = vertice_get_id(list_get_data(getNext(n)));

			/* printf("%d ", a_adjacente(via, src, dest)); */

		}
	}
	free_grafo(grafo);
	return 0;

}
