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
int compareSemaforoX(Semaforo a, Semaforo b){
	StSemaforo *sa = (StSemaforo *) a;
	StSemaforo *sb = (StSemaforo *) b;

	if(sa->x < sb->x)
		return 1;
	else
		return -1;
}

int compareSemaforoY(Semaforo a, Semaforo b){
	StSemaforo *sa = (StSemaforo *) a;
	StSemaforo *sb = (StSemaforo *) b;

	if(sa->y < sb->y)
		return 1;
	else
		return -1;
}
