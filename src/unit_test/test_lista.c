#include "../modules/Lista/static_ist.h"
#include "../modules/Rect/rect.h"


int
main(){
	Lista l = createList();
	StRect *r;
	Rect r2= createRect("blue,", "green",1, 2, 3, 4);

	l = insert(l, createRect("blue,", "yellow",10, 20, 30, 40),
 2);
	l = insert(l, r2, 3);
	l = insert(l, createRect("pink", "pink", 5,6, 7, 8), 3);
	l = insert(l, createRect("grey", "gasdg", 11,12, 13, 14), 6);
	l = insertAfter(l, 1, createRect("yello", "yello", 7,8,9,10), 5);
	del(l, r2);
	for(int i = 0; i < length(l)-1; i++){
		r = (StRect *)get(l, i);
		printf("%s\n", r->inside);
	
	}
	/* for(int i = 0; i < length(l); i++){ */
	/* 	printf("") */
	/*  */
	/* } */
	
	

}
