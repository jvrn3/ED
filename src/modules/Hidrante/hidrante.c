#include "hidrante.h"


Hidrante createHidrante(char *fill, char *strk, int id, double x, double y){
	Hidrante h = malloc(sizeof(StHidrante));
	StHidrante *sh = (StHidrante *) h;
	strcpy(sh->fill, fill);
	strcpy(sh->strk, strk);
	sh->id = id;
	sh->x = x;
	sh->y = y;

	return h;
}
