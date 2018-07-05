#include "../modules/Lista/static_ist.h"
#include "../modules/Rect/rect.h"


int
main(){
	Lista l = createList();
	StRect *r;
	Rect r2= createRect("blue,", "green",1, 2, 3, 4);

	insert(l, createRect("blue,", "yellow",10, 20, 30, 40),
 2);
	 insert(l, r2, 3); 
	 insert(l, createRect("pink", "pink", 5,6, 7, 8), 3); 
	 insert(l, createRect("grey", "gasdg", 11,12, 13, 14), 6); 

	 Node *n;
	for(n = getFirst(l); n != NULL; n = n->next){
		r = (StRect *) n->data;
		printf("%s", r->border);
	}
	/* for(int i = 0; i < length(l); i++){ */
	/* 	printf("") */
	/*  */
	/* } */
	
	

}
