#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <stdlib.h>
#include <string.h>

typedef void *Semaforo;
Semaforo createSemaforo(char *fill, char *strk, char *id, double x, double y);
#endif
int compareSemaforoX(Semaforo a, Semaforo b);
int compareSemaforoY(Semaforo a, Semaforo b);
float semaforoPointInX(Semaforo s);
float semaforoPointInY(Semaforo s);
char *semaforo_get_fill(Semaforo s);
char *semaforo_get_strk(Semaforo s);
char *semaforo_get_id(Semaforo s);
float semaforo_get_x(Semaforo s);
float semaforo_get_y(Semaforo s);
void semaforo_set_fill(Semaforo s, char *color);
void semaforo_set_strk(Semaforo s, char *color);

