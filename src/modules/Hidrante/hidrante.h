#ifndef HIDRANTE_H
#define HIDRANTE_H
#include <stdlib.h>
#include <string.h>

typedef void *Hidrante;
typedef struct stHidrante{
  char fill[100], strk[100];
  char id[100];
  double x, y;

}StHidrante;

Hidrante createHidrante(char *fill, char *strk, char *id, double x, double y);
#endif
