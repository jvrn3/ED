#include "torre.h"

Torre createTorre(char *fill, char *strk, char *id, double x, double y){
	Torre t = malloc(sizeof(StTorre));

	StTorre *st = (StTorre *) t;

	strcpy(st->fill, fill);
	strcpy(st->strk, strk);
	strcpy(st->id, id);

	st->x = x;
	st-> y = y;

	return t;

}
