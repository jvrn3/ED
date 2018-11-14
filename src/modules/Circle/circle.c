#include "circle.h"

Circle createCircle(char *border, char *inside, double r, double x, double y){
	Circle c = malloc(sizeof(StCircle));
	StCircle *sc = (StCircle *) c;
	strcpy(sc->inside, inside);
	strcpy(sc->border, border);

	sc->r = r;
	sc->x = x;
	sc->y = y;

	return c;
}

