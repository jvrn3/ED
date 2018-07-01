#include "hidrante.h"


Hidrante createHidrante(char *fill, char *strk, char *id, double x, double y){
	Hidrante h = malloc(sizeof(StHidrante));
	StHidrante *sh = (StHidrante *) h;
	strcpy(sh->fill, fill);
	strcpy(sh->strk, strk);
	strcpy(sh->id, id);
	sh->x = x;
	sh->y = y;
	return h;
}
void deletaHidrante(Hidrante h){
	StHidrante *sh = (StHidrante *)h;
	free(sh);
}
