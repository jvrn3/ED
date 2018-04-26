#ifndef CIRCLE_H
#define CIRCLE_H

typedef void *Circle;
#include <stdlib.h>

typedef struct stCircle{
	int id;
	char *border, *inside;
	double r, x, y;
}StCircle;

Circle createCircle(int id, char *border, char *inside, double r, double x, double y);
#endif


