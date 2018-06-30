#ifndef HIDRANTE_H
#define HIDRANTE_H
#include <stdlib.h>
#include <string.h>

typedef void *Hidrante;
typedef struct stHidrante{
  char fill[50], strk[50];
  char id[50];
  double x, y;

}StHidrante;

Hidrante createHidrante(char *fill, char *strk, char *id, double x, double y);
#endif
