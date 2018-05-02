#include "rect.h"
Rect createRect(char *border, char *inside, double w, double h, double x, double y){

	Rect r = malloc(sizeof(StRect));
	StRect *sr = (StRect *) r;
	
	printf("Gambiarra no rect.h\n");
	sr->border = malloc(sizeof(char) * MAXSIZE);
	strcpy(sr->inside, inside);
	strcpy(sr->border, border);

	sr->w = w;
	sr->h = h;
	sr->x = x;
	sr->y = y;

	return r;
	
}

