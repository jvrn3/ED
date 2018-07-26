#include "geometry.h"
#include <float.h>

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

	if (distanceCC(c, c2) < (sc->r + sc2->r ))
		return 1;
	else return 0;
}
int overlayCR(Circle c, Rect r){
	StCircle *sc = (StCircle *) c;
	StRect *sr = (StRect *) r;
	double d, d2, d3;
	//x
	d = abs(sc->x - sr->x);
	//y
	d2 = abs(sc->y- sr->y);

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

	d = pow(x-x1, 2) + pow(y-y1, 2);
	if(d <= pow(sc->r,2) ) return 1;
	else
		return 0;
}
float area(int x1, int y1, int x2, int y2, int x3, int y3){
	return abs((x1 * (y2-y3) + x2 *(y3-y1) + x3 *(y1-y2))/2.0);
	}
int isInsideR(Rect r, double x, double y){
	StRect *sr = (StRect *) r;
	if(x <= sr->x + sr->w && x>= sr->x && y >= sr->y && y <= sr->y + sr->h)
		return 1;
	else
		return 0;
}

// is the rect a inside b?
int isRectInsideRect(Rect in, Rect out){
	StRect *sa = (StRect *)in;
	if(isInsideR(out, sa->x, sa->y) && 
			isInsideR(out, sa->x + sa->w, sa->y) &&
			isInsideR(out, sa->x, sa->y + sa->h) &&
			isInsideR(out, sa->x + sa->w, sa->y + sa->h))
		return 1;
	else return 0;
}

int isRectInsideCircle(Circle c, Rect r){
	StRect *sr = (StRect *) r;
	if(isInsideC(c, sr->x, sr->y) && isInsideC(c, sr->x + sr->w, sr->y) && isInsideC(c, sr->x, sr->y + sr->h) && isInsideC(c, sr->x + sr->w, sr->y + sr->h))
		return 1;
	else return 0;
}
int isCircleInsideRect(Circle c, Rect r){
	StCircle *sc = (StCircle *) c;
	if(isInsideR(r, sc->x + sc->r, sc->y) && isInsideR(r, sc->x -sc->r, sc->y) && isInsideR(r, sc->x, sc->y + sc->r) && isInsideR(r, sc->x, sc->y - sc->r))
		return 1;
	else
		return 0;

}
// is a inside b?
int isCircleInsideCircle(Circle a, Circle b){
	StCircle *sc = (StCircle *) a;
	if(isInsideC(b, sc->x + sc->r, sc->y) && isInsideC(b, sc->x - sc-> r, sc-> y) && isInsideC(b, sc->x, sc->y + sc->y) && isInsideC(b, sc->x, sc->y - sc-> r))
		return 1;
	else 
		return 0;
}

Ponto  *getPontos(Torre t){
	Node *n;
	int i;
	Ponto *p = (Ponto *)malloc(sizeof(Ponto) * length(t));
	for(i = 0, n = getFirst(t); n != NULL; n = n->next, i++){
		StTorre *st = (StTorre *) n->data;
		p[i].x = st->x;
		p[i].y = st->y; 
	}
	return p;
}

/* Ponto *sortPontos(Ponto *pontos, int length){ */
/* 	heap_sort(pontos, length); */
/* 	return pontos; */
/* } */

//get the smallest distance between two points

float distPoints(Ponto p1, Ponto p2){
	return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
			(p1.y - p2.y)*(p1.y - p2.y)
			);
}

float bruteForce(Ponto P[], int n)
{
    float min = FLT_MAX;
				for (int i = 0; i < n; ++i)
						for (int j = i+1; j < n; ++j)
            if (distPoints(P[i], P[j]) < min){
                min = distPoints(P[i], P[j]);
												}
    return min;
}
int find_ponto(Ponto p[], int n, float d, FILE *fp, FILE *fTxt, Torre t ){
    for(int i = 0 ; i < n; i++){
	for(int j = i+1 ; j < n; j++){
	    if(distPoints(p[i], p[j]) == d){
		fprintf(fp, "<circle r=\"%.2lf\" cx=\"%.2f\" cy=\"%.2f\"  stroke=\"black\" fill-opacity=\"0\" stroke-dasharray=\"5,5\" stroke-width=\"3\"/>\n",
			15.0,
			p[i].x,
			p[i].y);
		fprintf(fp, "<circle r=\"%.2lf\" cx=\"%.2f\" cy=\"%.2f\"  stroke=\"black\" fill-opacity=\"0\" stroke-dasharray=\"5,5\" stroke-width=\"3\"/>\n",
			15.0,
			p[j].x,
			p[j].y);
		StTorre *sa = (StTorre *)search_id_toxy(p[i].x, p[i].y, t);
		StTorre *sb = (StTorre *)search_id_toxy(p[j].x, p[j].y, t);


		fprintf(fTxt, "ID %s  %s Distancia %lf\n",
			sa->id,
			sb->id,
			d);
		return 0;
	    }
	}
    }
    return -1;
}
float closestPairs(Ponto px[],  int n){
	if(n <= 3)
		return bruteForce(px,n);

	int mid = n/2;
	Ponto midPoint = px[mid];

/* 	Ponto pyl[mid+1]; */
/* 	Ponto pyr [n-mid-1]; */
/* 	int li=0, ri=0; */
/* 	for(int i =0 ; i< n; i++){ */
/* 		if(py[i].x <= midPoint.x) */
/* 			pyl[li++] = py[i]; */
/* 		 */
/* 		else */
/* 			pyr[ri++] = py[i]; */
/* 	} */
	float dl = closestPairs(px, mid);
	float dr = closestPairs(px + mid, n - mid);


/* 	float dr = closestPairs(px + mid, pyr, n-mid); */
/*  */
	float d = MIN(dl, dr);
/*  */
	Ponto strip[n];
	int j = 0;
	for(int i = 0; i < n; i++){
		if(abs(px[i].x - midPoint.x) < d)
			strip[j] = px[i], j++;
	}
	return stripClosest(strip, j, d);
}
float stripClosest(Ponto *strip, int size, float d){
	float min = d;
	heap_sort_y(strip, size );

	for(int i =0 ; i < size; i++){
		for(int j = i +1; j < size && (strip[j].y - strip[i].y) < min; ++j){
			if(distPoints(strip[i], strip[j]) < min)
				min = distPoints(strip[i], strip[j]);
		}
	}
	return min;
}
float closest(Ponto *ponto, int n){
/* 	Ponto px[n]; */
/* 	Ponto py[n]; */
/* 	for(int i = 0; i < n; i++){ */
/* 		px[i] = p[i]; */
/* 		py[i] = p[i]; */
/* 	} */
/* 	heap_sort_x(p, n); */

	heap_sort_x(ponto, n);
	float min = closestPairs(ponto, n);
	return min;
}
