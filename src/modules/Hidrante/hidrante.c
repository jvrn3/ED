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

int compareHidranteX(Hidrante a, Hidrante b){
	StHidrante *sa = (StHidrante *) a;
	StHidrante *sb = (StHidrante *) b;
	if(sa->x < sb->x)
		return 1;
	else
		return -1;
}
int compareHidranteY(Hidrante a, Hidrante b){
	StHidrante *sa = (StHidrante *) a;
	StHidrante *sb = (StHidrante *) b;
	if(sa->y < sb->y)
		return 1;
	else
		return -1;
}
float hidrantePointInX(Hidrante a){
	StHidrante *sh = (StHidrante *) a;
	return sh->x;
}
float hidrantePointInY(Hidrante a){
	StHidrante *sh = (StHidrante *) a;
	return sh->y;
}
