#include "rect.h"
Rect createRect(char *border, char *inside, double w, double h, double x, double y){

	Rect r = malloc(sizeof(StRect));
	StRect *sr = (StRect *) r;
	strcpy(sr->inside, inside);
	strcpy(sr->border, border);
	sr->w = w;
	sr->h = h;
	sr->x = x;
	sr->y = y;

	return r;
	
}

float rect_get_y(Rect r){
	StRect *sr =(StRect *) r;
	return sr->y;
}
