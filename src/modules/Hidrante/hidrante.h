#ifndef HIDRANTE_H
#define HIDRANTE_H
#include <stdlib.h>
#include <string.h>

typedef void *Hidrante;
Hidrante createHidrante(char *fill, char *strk, char *id, double x, double y);
void deletaHidrante(Hidrante h);
int compareHidranteX(Hidrante a, Hidrante b);
int compareHidranteY(Hidrante a, Hidrante b);
float hidrantePointInX(Hidrante a);
float hidrantePointInY(Hidrante a);
char *hidrante_get_id(Hidrante h);
char *hidrante_get_fill(Hidrante h);
char *hidrante_get_strk(Hidrante h);
void hidrante_set_fill(Hidrante h, char *color);
void hidrante_set_strk(Hidrante h, char *color);
float hidrante_get_x(Hidrante h);
float hidrante_get_y(Hidrante h);

#endif
