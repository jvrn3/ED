#ifndef SEMAFORO_H
#define SEMAFORO_H
#include <stdlib.h>
#include <string.h>

typedef void *Semaforo;

typedef struct stSemaforo{
  char fill[100], strk[100];
  char id[100];
  double x, y;

}StSemaforo;

Semaforo createSemaforo(char *fill, char *strk, char *id, double x, double y);
#endif
