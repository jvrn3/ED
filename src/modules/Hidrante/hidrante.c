#include "hidrante.h"
typedef struct stHidrante{
  char fill[50], strk[50];
  char id[50];
  double x, y;

}StHidrante;



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
char *hidrante_get_id(Hidrante h){
	StHidrante *sh = (StHidrante *) h;
	return sh->id;
}

void hidrante_set_fill(Hidrante h, char *color){
	StHidrante *sh = (StHidrante *) h;
	strcpy(sh->fill, color);
}
void hidrante_set_strk(Hidrante h, char *color){
	StHidrante *sh = (StHidrante *) h;
	strcpy(sh->strk, color);
}
float hidrante_get_x(Hidrante h){
	StHidrante *sh = (StHidrante *) h;
	return sh->x;
}
float hidrante_get_y(Hidrante h){
	StHidrante *sh = (StHidrante *) h;
	return sh->y;
}
char *hidrante_get_fill(Hidrante h){
	StHidrante *sh = (StHidrante *) h;
	return sh->fill;
}
char *hidrante_get_strk(Hidrante h){
	StHidrante *sh = (StHidrante *)h;
	return sh->strk;
}
