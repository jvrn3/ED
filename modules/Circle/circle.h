#ifndef CIRCLE_H
#define CIRCLE_H

typedef void *Circle;
#include <stdlib.h>

typedef struct stCircle{
	char *border, *inside;
	double r, x, y;
}StCircle;

Circle createCircle(char *border, char *inside, double r, double x, double y);
#endif


