#ifndef TORRE_H
#define TORRE_H
#include <string.h>
#include <stdlib.h>
typedef void *Torre;

typedef struct stTorre{
  char fill[100];
  char strk[100];
  char id[100];
  double x, y;

}StTorre;

Torre createTorre(char *fill, char *strk, char *id, double x, double y);

#endif
