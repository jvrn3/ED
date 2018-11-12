#ifndef RECT_H
#define RECT_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef void *Rect;
typedef struct stRect{
	char border[50];
	char inside[50];
	double w,
		   h,
		   x,
		   y;
}StRect;

Rect createRect(char *border, char *inside, double w, double h, double x, double y);
float rect_get_y(Rect r);
#endif
