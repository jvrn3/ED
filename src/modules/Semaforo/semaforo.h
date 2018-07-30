#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <stdlib.h>
#include <string.h>

typedef void *Semaforo;

typedef struct stSemaforo{
  char fill[50], strk[50];
  char id[50];
  double x, y;

}StSemaforo;

Semaforo createSemaforo(char *fill, char *strk, char *id, double x, double y);
#endif
int compareSemaforoX(Semaforo a, Semaforo b);
int compareSemaforoY(Semaforo a, Semaforo b);

