#ifndef CIRCLE_H
#define CIRCLE_H

typedef void *Circle;
#define MAXSIZE 256
#include <stdlib.h>
#include <string.h>

typedef struct stCircle{
	char border[MAXSIZE];
	char inside[MAXSIZE];
	double r,
				 x,
				 y;
}StCircle;

Circle createCircle(char *border, char *inside, double r, double x, double y);
#endif


