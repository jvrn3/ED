#include "../modules/Graph/graph.h"


int
main(){
	Grafo *grafo;
	grafo = createGrafo(10);

	insertEdge(grafo, 1, 2);
	insertEdge(grafo, 1, 3);
	insertEdge(grafo, 3, 5);
	insertEdge(grafo, 3, 9);


	int i = 5;
	void *a = &i;
	addInfo(grafo, 1, 3, a);

	void *b = getInfo(grafo, 1, 3);
	printf("%d\n", *(int *) b);
	return 0;

}
