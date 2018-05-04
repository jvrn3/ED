#include "svg.h"

void drawCircle(FILE *svgName, Circle c){
	StCircle *sc = (StCircle *) c;

	fprintf(svgName, "<circle r=\"%.2lf\" cx=\"%.2lf\" cy=\"%.2lf\"  stroke=\"%s\" fill=\"%s\" />\n", 
			sc->r, 
			sc->x,
			sc->y,
			sc->border,
			sc->inside);

}

void drawRect(FILE *svgName, Rect r){
	StRect *sr = (StRect *) r;
	fprintf(svgName, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2lf\" height=\"%.2f\" fill=\"%s\" stroke=\"%s\"/>\n", 
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
	fprintf(svgName, "<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" stroke=\"black\"/>\n", 
			sc->x,
			sc->y,
			sc2->x,
			sc2->y);
}
void drawLineCToR(FILE *svgName, Circle c, Rect r){
	StCircle *sc = (StCircle *) c;
	StRect *sr = (StRect *) r;

	fprintf(svgName, "<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" stroke=\"black\"/>\n",
			sc->x,
			sc->y,
			sr->x + sr->w/2,
			sr->y + sr->h/2);

}
void drawLineRToC(FILE *svgName, Rect r, Circle c){
	StCircle *sc = (StCircle *) c;
	StRect *sr = (StRect *) r;
	fprintf(svgName, "<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" stroke=\"%s\"/>\n",
			sr->x + sr->w/2,
			sr->y + sr->h/2,
			sc->x,
			sc->y, 
			sr->inside);
}
void drawLineRToR(FILE *svgName, Rect r, Rect r2){
	StRect *sr = (StRect *) r;
	StRect *sr2 = (StRect *) r2;
	fprintf(svgName, "<line x1=\"%.2lf\" y1=\"%.2lf\" x2=\"%.2lf\" y2=\"%.2lf\" stroke=\"%s\"/>\n",
			sr->x + sr->w/2,
			sr->y + sr->h/2,
			sr2->x + sr2->w/2,
			sr2->y + sr2->h/2, sr->inside);
}
