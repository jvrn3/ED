#include "semaforo.h"
typedef struct stSemaforo{
  char fill[50], strk[50];
  char id[50];
  double x, y;

}StSemaforo;

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
/* int compareSemaforoX(Semaforo a, Semaforo b){ */
/* 	StSemaforo *sa = (StSemaforo *) a; */
/* 	StSemaforo *sb = (StSemaforo *) b; */
/*  */
/* 	if(sa->x < sb->x) */
/* 		return 1; */
/* 	else */
/* 		return -1; */
/* } */
/*  */
/* int compareSemaforoY(Semaforo a, Semaforo b){ */
/* 	StSemaforo *sa = (StSemaforo *) a; */
/* 	StSemaforo *sb = (StSemaforo *) b; */
/*  */
/* 	if(sa->y < sb->y) */
/* 		return 1; */
/* 	else */
/* 		return -1; */
/* } */
/*  */
/* float semaforoPointInX(Semaforo s){ */
/* 	StSemaforo *ss = (StSemaforo *) s; */
/* 	return ss->x; */
/* } */
/* float semaforoPointInY(Semaforo s){ */
/* 	StSemaforo *ss = (StSemaforo *) s; */
/* 	return ss->y; */
/* } */
char *semaforo_get_fill(Semaforo s){
	StSemaforo *ss = (StSemaforo *) s;
	return ss->fill;
}
char *semaforo_get_strk(Semaforo s){
	StSemaforo *ss = (StSemaforo *) s;
	return ss->strk;
}
char *semaforo_get_id(Semaforo s){
	StSemaforo *ss = (StSemaforo *) s;
	return ss->id;
}

float semaforo_get_x(Semaforo s){
	StSemaforo *ss = (StSemaforo *) s;
	return ss->x;
}
float semaforo_get_y(Semaforo s){
	StSemaforo *ss = (StSemaforo *) s;
	return ss->y;
}
void semaforo_set_fill(Semaforo s, char *color){
	StSemaforo *ss = (StSemaforo *) s;
	strcpy(ss->fill, color);
}
void semaforo_set_strk(Semaforo s, char *color){
	StSemaforo *ss = (StSemaforo *) s;
	strcpy(ss->strk, color);
}

