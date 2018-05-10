#ifndef MAXSIZE
#define MAXSIZE 256
#endif
#ifndef RECT_H
#define RECT_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef void *Rect;
typedef struct stRect{
	char border[MAXSIZE];
	char inside[MAXSIZE];
	double w,
				 h,
				 x,
				 y;
}StRect;

Rect createRect(char *border, char *inside, double w, double h, double x, double y);
#endif
