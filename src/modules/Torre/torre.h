#ifndef TORRE_H
#define TORRE_H
#include <string.h>
#include <stdlib.h>
typedef void *Torre;

typedef struct stTorre{
  char fill[50];
  char strk[50];
  char id[50];
  double x, y;

}StTorre;

Torre createTorre(char *fill, char *strk, char *id, double x, double y);

#endif
