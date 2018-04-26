#include "rect.h"
Rect createRect(char *border, char *inside, double w, double h, double x, double y){
	Rect r = malloc(sizeof(StRect));
	StRect *sr = (StRect *) r;
	sr->border = border;
	sr->inside = inside;
	sr->w = w;
	sr->h = h;
	sr->x = x;
	sr->y = y;

	return r;
}
