#ifndef RECT_H
#define RECT_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 256
typedef void *Rect;
typedef struct stRect{
	char *border;
	char inside[MAXSIZE];
	double w,
				 h,
				 x,
				 y;
}StRect;

Rect createRect(char *border, char *inside, double w, double h, double x, double y);
#endif
