#include "torre.h"

Torre createTorre(char *fill, char *strk, int id, double x, double y){
	Torre t = malloc(sizeof(StTorre));

	StTorre *st = (StTorre *) t;

	strcpy(st->fill, fill);
	strcpy(st->strk, strk);

	st->id = id;
	st->x = x;
	st-> y = y;

	return t;

}
