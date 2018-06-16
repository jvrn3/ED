#ifndef HIDRANTE_H
#define HIDRANTE_H
#include <stdlib.h>
#include <string.h>

typedef void *Hidrante;
typedef struct stHidrante{
  char fill[100], strk[100];
  int id;
  double x, y;

}StHidrante;

Hidrante createHidrante(char *fill, char *strk, int id, double x, double y);
#endif
