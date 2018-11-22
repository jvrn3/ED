#include "geometry.h"

Ponto createPonto(float x, float y){
    Ponto p;
    p.x = x;
    p.y = y;
    return p;
}
double distancePoints(Ponto a, Ponto b){
    return pow((a.x - b.x), 2) +
	pow((a.y - b.y), 2)
	    ;

}
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

int isQuadraInsideRect(Quadra q, Rect b){
    Rect r;
    Quadra sq = q;
    r = createRect("", "", quadra_get_w(sq), quadra_get_h(sq), quadra_get_x(sq), quadra_get_y(sq)); 
    if(isRectInsideRect(r, b)){
	free(r);
	return 1;
    }
    free(r);
    return 0;
}
int isQuadraInsideCircle(Quadra q, Circle b){
    Rect r;
    Quadra sq = q;
    r = createRect("", "", quadra_get_w(sq), quadra_get_h(sq), quadra_get_x(sq), quadra_get_y(sq)); 
    if(isRectInsideCircle(b, r)){
	free(r);
	return 1;
    }
    free(r);
    return 0;

}
int isTorreInsideRect(Torre t, Rect r){
    Torre st = t;
    if(isInsideR(r, torre_get_x(st), torre_get_y(st)))
	return 1;
    return 0;
}
int isTorreInsideCircle(Torre t, Circle c){
    Torre st = t;
    if(isInsideC(c, torre_get_x(st), torre_get_y(st)))
	return 1;
    return 0;
}
int isHidranteInsideRect(Hidrante h, Rect r){
    Hidrante sh =  h;
    if(isInsideR(r, hidrante_get_x(sh), hidrante_get_y(sh)))
	return 1;
    return 0;
}
int isHidranteInsideCircle(Hidrante h, Circle c){
    Hidrante sh =  h;
    if(isInsideC(c, hidrante_get_x(sh), hidrante_get_y(sh)))
	return 1;
    return 0;
}
int isSemaforoInsideRect(Semaforo s, Rect r){
    Semaforo ss = s;
    if(isInsideR(r, semaforo_get_x(ss), semaforo_get_y(ss)))
	return 1;
    return 0;
}
int isSemaforoInsideCircle(Semaforo s, Circle c){
    Semaforo ss = s;
    if(isInsideC(c, semaforo_get_x(ss), semaforo_get_y(ss)))
	return 1;
    return 0;
}
//check if rect in is inside out
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
float closestPairs(Ponto px[],  int n){
	if(n <= 3)
		return bruteForce(px,n);

	int mid = n/2;
	Ponto midPoint = px[mid];
	float dl = closestPairs(px, mid);
	float dr = closestPairs(px + mid, n - mid);


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

	heap_sort_x(ponto, n);
	float min = closestPairs(ponto, n);
	return min;
}
int rect_vertical(Rect r){
    Ponto a = createPonto(rect_get_x(r), rect_get_y(r) + rect_get_w(r));
    Ponto b = createPonto(rect_get_x(r), rect_get_y(r));

    double larg = distancePoints(a, b);

    Ponto c = createPonto(rect_get_x(r), rect_get_y(r));
    Ponto d = createPonto(rect_get_x(r), rect_get_y(r) + rect_get_h(r));

    double alt = distancePoints(c, d);

    if(alt > larg)
	return 1;
    return 0;
}
