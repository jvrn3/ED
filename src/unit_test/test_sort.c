#include <stdio.h>
#include "../modules/Sort/sort.h"
#include "../modules/Carro/carro.h"

int
main(){
	Lista l = createList();
	Carro c1 = newCarro("A", 10, 20, 15, 25);
	Carro c2 = newCarro("B", 40, 50, 15, 25);
	Carro c3 = newCarro("C", 20, 10, 15, 25);
	insert(l, c1, 0);
	insert(l, c2, 0);
	insert(l, c3, 0);

	sort_list(l, car_cmp);
	Node *n;
	for(n = getFirst(l); n != NULL; n = getNext(n)){
		printf("%lf\n", rect_get_y(carro_get_posic(list_get_data(n))));
	}
}

