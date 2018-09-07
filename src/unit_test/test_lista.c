#include "../modules/Lista/linked_list.h"
#include "../modules/Rect/rect.h"


int
main(){
	Lista l = createList();
	StRect *r;
	Rect r2= createRect("blue,", "green",1, 2, 3, 4);
	Rect r3= createRect("green,", "yellow",1, 2, 3, 4);

	insert(l, createRect("blue,", "yellow",10, 20, 30, 40), 5);
	insert(l, r3, 5);
	 insert(l, createRect("blue,", "green",1, 2, 3, 4),3); 
	 insert(l, createRect("pink", "pink", 5,6, 7, 8), 3); 
	 insert(l, createRect("grey", "gasdg", 11,12, 13, 14), 6); 
	 /* void *d = del(l, r2); */
	 void *d = del(l, r3);
	 free(r2);
	 free(d);

	 Node *n;
	for(n = getFirst(l); n != NULL; n = n->next){
		r = (StRect *) n->data;
		printf("%s\n", r->border);
	}
	/* for(int i = 0; i < length(l); i++){ */
	/* 	printf("") */
	/*  */
	/* } */
	
	destroy(l);
	

}
