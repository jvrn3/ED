#ifndef TORRE_H
#define TORRE_H
#include <string.h>
#include <stdlib.h>
typedef void *Torre;


Torre createTorre(char *fill, char *strk, char *id, double x, double y);
int compareTorreX(Torre a, Torre b);
int compareTorreY(Torre a, Torre b);
float torrePointInX(Torre a);
float torrePointInY(Torre a);
char *torre_get_fill(Torre t);
char *torre_get_strk(Torre t);
char *torre_get_id(Torre t);
float torre_get_x(Torre t);
float torre_get_y(Torre t);
void torre_set_fill(Torre t, char *color);
void torre_set_strk(Torre t, char *color);
#endif
