#ifndef RECT_H
#define RECT_H
#include <stdio.h>
#include <stdlib.h>

typedef void *Rect;
typedef struct stRect{
	char *border, *inside;
	double w, h, x, y;
}StRect;

Rect createRect(char *border, char *inside, double w, double h, double x, double y);
#endif
