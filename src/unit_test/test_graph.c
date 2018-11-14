#include "../modules/Graph/graph.h"
#include "../modules/Rua/rua.h"
typedef struct ponto{
	float x, y;
}Ponto;
int
main(){
	Grafo grafo = createGrafo();

	Rua r1 = createRua("Nossa Senhora do Rocio", "l", "r", 1, 2);
	Ponto *p, *p2;
	p = malloc(sizeof(Ponto));
	p2 = malloc(sizeof(Ponto));
	p->x = 5;
	p->y = 10;
	p2->x = 15;
	p2->y = 25;
	insertVertex(grafo, "josue", p);
	insertVertex(grafo, "Hobsbawn", p2);
	insertEdge(grafo, "josue", "Hobsbawn", r1);

	Aresta a = getInfo(grafo, "josue", "Hobsbawn");
	Rua get = (Ponto *)aresta_get_data(a);
	printf("Nome da rua -> %s", rua_get_nome(get));



	Lista l= v_adjacentes(grafo, "josue");
	/* Node *n; */
	/* for(n = getFirst(l); n != NULL; n = getNext(n)){ */
	/* 	printf("%s\n", vertice_get_id(list_get_data(n))); */
	/* 	 */
	/* } */
	free_grafo(grafo);
	return 0;

}
