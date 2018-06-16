#include "geometry.h"
double distanceCC(Circle c, Circle c2){
	StCircle *sc = (StCircle *) c;
	StCircle *sc2 = (StCircle *) c2;

	double x1, y1, x2, y2, d;

	x1 = sc->x;
	x2 = sc2->x;
	y1 = sc->y;
	y2 = sc2->y;
	 d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return d;
}
double distanceCR(Circle c, Rect r){
	StCircle *sc = (StCircle *) c;
	StRect *sr = (StRect *) r;

	double x1, y1, x2, y2, d;

	x1 = sc->x;

	x2 = sr->x + sr->w/2;
	y1 = sc->y;
	y2 = sr->y + sr->h/2;
	d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return d;
}

double distanceRR(Rect r, Rect r2){
	StRect *sr = (StRect *) r;
	StRect *sr2 = (StRect *) r2;

	double x1, y1, x2, y2, d;
	x1 = sr->x + sr->w/2;
	y1 = sr->y + sr->h/2;

	x2 = sr2->x + sr2->w/2;
	y2 = sr2->y + sr2->h/2;

	d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return d;
}

int overlayCC(Circle c, Circle c2){
	StCircle *sc = (StCircle *) c;
	StCircle *sc2 = (StCircle *) c2;

	printf("\nDistancia : %f\n", distanceCC(c,c2));
	printf("\nDistancia : %f\n", (sc->r + sc2->r));
	if (distanceCC(c, c2) < (sc->r + sc2->r ))
		return 1;
	else return 0;
}
int overlayCR(Circle c, Rect r){
	StCircle *sc = (StCircle *) c;
	StRect *sr = (StRect *) r;
	double d, d2, d3;
	d = abs(sc->x - sr->x);
	d2 = abs(sc->y-sr->y);

	if(d > (sr->w/2 + sc->r)) return 0;
	if(d2 > (sr->h/2 + sc->r)) return 0;

	if(d <=(sr->w/2)) return 1;
	if(d2 <= (sr->h/2)) return 1;

	d3 = pow((d - sr->w/2),2) + pow((d2 - sr->h/2),2);

	return (d3 <= pow(sc->r,2));
}
int overlayRR(Rect r, Rect r2){
	StRect *sr = (StRect *)r;
	StRect *sr2 = (StRect *)r2;

	double leftX = MAX(sr->x, sr2->x);
	double rightX = MIN(sr->x + sr->w, sr2->x + sr2->w);
	double leftY = MAX(sr->y, sr2->y);
	double rightY = MIN(sr->y+sr->h, sr2->y + sr2->h);
	if(leftX < rightX && leftY < rightY)
		return 1;
	else
		return 0;
}
int isInsideC(Circle c, double x, double y){
	StCircle *sc = (StCircle *) c;

	double x1, y1, d;
	x1 = sc->x;
	y1 = sc->y;

	d = sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
	if(d < sc->r ) return 1;
	else
		return 0;
}
int isInsideR(Rect r, double x, double y){
	StRect *sr = (StRect *) r;
	if((x < (sr->x + (.5 *sr->w))) && (x > (sr->x - (.5 * sr->w)))
				&& (y < (sr->y  +(sr->h))) && (y  > (sr->y -(.5 * sr->h))))
		return 1;
	else
		return 0;
}


