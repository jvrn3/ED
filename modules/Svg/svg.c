#include "svg.h"

void drawCircle(FILE *svgName, Circle c){
	StCircle *sc = (StCircle *) c;

	fprintf(svgName, "<circle r=\"%lf\" cx=\"%lf\" cy=\"%lf\"  stroke=\"%s\" fill=\"%s\" />", 
			(double )sc->r, 
			(double ) sc->x,
			(double )sc->y,
			*(char *) sc->border,
			*(char *) sc->inside);
}


