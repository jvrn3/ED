#ifndef CIRCLE_H
#define CIRCLE_H

typedef void *Circle;
#include <stdlib.h>
#include <string.h>

typedef struct stCircle{
	char *border;
	char *inside;
	double r,
				 x,
				 y;
}StCircle;

Circle createCircle(char *border, char *inside, double r, double x, double y);
#endif


