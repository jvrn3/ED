#include "semaforo.h"

Semaforo createSemaforo(char *fill, char *strk, char *id, double x, double y){
	Semaforo s = malloc(sizeof(StSemaforo));

	StSemaforo *ss = (StSemaforo *) s;

	strcpy(ss->fill, fill);
	strcpy(ss->strk, strk);
	strcpy(ss->id, id);
	ss->x = x;
	ss->y = y;

	return s;
}

