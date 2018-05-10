#include "svg.h"
/* need to create a geometry library */

void drawCircle(FILE *svgName, Circle c){
	StCircle *sc = (StCircle *) c;

	fprintf(svgName, "<circle r=\"%.2f\" cx=\"%.2f\" cy=\"%.2f\"  stroke=\"%s\" fill=\"%s\" />\n", 
			sc->r, 
			sc->x,
			sc->y,
			sc->border,
			sc->inside);

}

void drawRect(FILE *svgName, Rect r){
	StRect *sr = (StRect *) r;
	fprintf(svgName, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" fill=\"%s\" stroke=\"%s\"/>\n", 
			sr->x,
			sr->y,
			sr->w,
			sr->h,
			sr->inside,
			sr->border);
}

void drawLineCToC(FILE *svgName, Circle c, Circle c2){
	StCircle *sc = (StCircle *) c;
	StCircle *sc2 = (StCircle *) c2;
	double x1,x2, y1,y2, d;
	x1 = sc->x;
	y1 = sc->y;
	x2 = sc2->x;
	y2 = sc2->y;
	d = sqrt(pow(sc->x -sc2->x, 2) + pow(sc->y - sc2->y, 2));
	fprintf(svgName, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\"/>\n<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\">%.2f</text>\n", 
			x1,
			y1,
			x2,
			y2,
			sc->border,
			(x1+x2)/2,
			(y1+y2)/2,
			sc->border,
			d);


}
void drawLineCToR(FILE *svgName, Circle c, Rect r){
	StCircle *sc = (StCircle *) c;
	StRect *sr = (StRect *) r;

	double x1, x2, y1, y2, d;
	x1 = sc->x;
	y1 = sc->y;
	x2 = sr->x + sr->w/2;
	y2 = sr->y + sr->h/2;

	d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

	fprintf(svgName, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\"/>\n<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\">%.2f</text>\n", 
			x1,
			y1,
			x2,
			y2,
			sc->border,
			(x1 + x2)/2,
			(y1+y2)/2,
			sc->border,
			d);


}
void drawLineRToC(FILE *svgName, Rect r, Circle c){
	StCircle *sc = (StCircle *) c;
	StRect *sr = (StRect *) r;
	double x1, x2, y1, y2, d;
	x1 = sr->x + sr->w/2;
	y1 = sr->y + sr->h/2;
	x2 = sc->x;
	y2 = sc->y;

	d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	fprintf(svgName, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\"/>\n<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\">%.2f</text>\n", 
			x1,
			y1,
			x2,
			y2,
			sr->border,
			(x1 + x2)/2,
			(y1+ y2)/2,
			sr->border,
			d);
}
void drawLineRToR(FILE *svgName, Rect r, Rect r2){
	StRect *sr = (StRect *) r;
	StRect *sr2 = (StRect *) r2;

	double x1, x2, y1, y2, d;
	x1 = sr->x + sr->w/2;
	y1 = sr->y + sr->h/2;
	x2 = sr2->x + sr2->w/2;
	y2 = sr2->y + sr2->h/2;
	d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));


	fprintf(svgName, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\"/>\n<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\">%.2f</text>\n", 
			x1,
			y1,
			x2,
			y2,
			sr->border,
			(x1+x2)/2,
			(y1+y2)/2,
			sr->border,
			d);
}


