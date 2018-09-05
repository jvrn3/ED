#include "svg.h"
/* need to create a geometry library */
void displayRectToSvg(FILE *f, Lista l){
	Node *n = (Node *)l;
	while(n->next != NULL){
		drawRect(f, (Rect) n->data);
		n = n->next;
	}
}
void displayCircleToSvg(FILE *f, Lista l){
	Node *n = (Node *)l;
	while(n->next != NULL){
		drawCircle(f, (Circle) n->data);
		n = n->next;
	}
}

void drawCircle(FILE *svgName, Circle c){
	StCircle *sc = (StCircle *) c;

	fprintf(svgName, "<circle r=\"%.2f\" cx=\"%.2f\" cy=\"%.2f\"  stroke=\"%s\" fill=\"%s\" />\n", 
			sc->r, 
			sc->x,
			sc->y,
			sc->border,
			sc->inside);

}
void drawQuadra(FILE *svgName, Quadra r){
	StQuadra *sr = (StQuadra *) r;
	fprintf(svgName, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" fill=\"%s\" stroke=\"%s\"/>\n", 
			sr->x,
			sr->y,
			sr->larg,
			sr->alt,
			sr->fill,
			sr->strk);
	fprintf(svgName, "<text x=\"%.2f\" y=\"%.2f\" fill=\"black\" font-size=\"12\">%s</text>\n",
			sr->x + sr->larg/2,
			sr->y + sr->alt/2,
			sr->cep);
}

void drawHidrante(FILE *svgName, Hidrante h){
	StHidrante *sh = (StHidrante *) h;
fprintf(svgName, "<circle r=\"10.00\" cx=\"%.2f\" cy=\"%.2f\"  stroke=\"%s\" fill=\"%s\" />\n<text x=\"%.2f\" y=\"%.2f\" fill=\"white\" font-size=\"16\">H</text>\n", 
			sh->x,
			sh->y,
			sh->strk,
			sh->fill, 
			sh->x - 5,
			sh->y + 5
			);

}
void drawSemaforo(FILE *svgName, Semaforo s){
	StSemaforo *sh = (StSemaforo *) s;
	fprintf(svgName, "<rect x=\"%.2f\" y=\"%.2f\" width=\"5\" height=\"15\" fill=\"%s\" stroke=\"%s\"/>\n", 
			sh->x,
			sh->y,
			sh->fill,
			sh->strk);
}
void drawTorre(FILE *svgName, Torre t){
	StTorre *st = (StTorre *) t;
	fprintf(svgName, "<circle r=\"10.00\" cx=\"%.2f\" cy=\"%.2f\"  stroke=\"%s\" fill=\"%s\" />\n", 
			st->x,
			st->y,
			st->strk,
			st->fill);
	fprintf(svgName, "<text x=\"%.2f\" y=\"%.2f\" fill=\"white\" font-size=\"16\">T</text>\n",
			st->x - 5, 
			st->y + 5
			);

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
	fprintf(svgName, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\"/>\n<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\" font-size=\"16\">%.2f</text>\n", 
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

void drawOverlapCC(FILE *svgName, Circle c, Circle c2){
	StCircle *sc = (StCircle *) c;
	StCircle *sc2 = (StCircle *) c2;

	double x, y, w, h;

	x = MIN(sc->x - sc->r, sc2->x - sc2->r);
	y = MIN(sc->y - sc->r, sc2->y - sc2->r);

	if(x > 0)
		w = MAX(sc->x + sc->r , sc2->x + sc2->r) -abs(x) ;
	else
		w = MAX(sc->x + sc->r , sc2->x + sc2->r) +abs(x) ;

	printf("\n\n%.2f", y);
	if(y > 0)
		h = MAX(sc->y + sc->r, sc2->y + sc2->r) - y;
	else
		h = MAX(sc->y + sc->r, sc2->y + sc2->r) + y;
		
	fprintf(svgName, "<text x=\"%.2f\" y=\"%.2f\" fill=\"red\" font-size=\"20\" >Sobrepoe</text>", x,y-2);
	fprintf(svgName,"<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" stroke-dasharray=\"5,5\" fill-opacity=\"0\" stroke=\"pink\" stroke-width=\"5\"/>\n", x,y,w,h );
}
void drawOverlapRR(FILE *svgName, Rect r, Rect r2){
	StRect *sr = (StRect *) r;
	StRect *sr2 =(StRect *) r2;
	double x, y, w, h;

	x = MIN(sr->x, sr2->x);
	y = MIN(sr->y, sr2->y);
	if(sr->x > sr2->x){
		w = MAX(sr->w + sr->x, sr2->x + sr->w);
		w = w - sr2->x;
	}
	else{
		w = MAX(sr->w + sr->x, sr2->x + sr->w);
		w = w - sr2->x;
	}
	if(sr->y > sr2->y){
		h = MAX(sr->h + sr-> y, sr2->y + sr2->h);
		h = h - sr2->y;
	}
	else{
		h = MAX(sr->h + sr-> y, sr2->y + sr2->h);
		h = h - sr->y;
	}

	

	fprintf(svgName, "<text x=\"%.2f\" y=\"%.2f\" fill=\"red\" font-size=\"20\" >Sobrepoe</text>", x,y-2);
	fprintf(svgName,"<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" stroke-dasharray=\"5,5\" fill-opacity=\"0\" stroke=\"pink\" stroke-width=\"5\"/>\n", x,y,w,h );
}

void drawOverlapCR(FILE *svgName, Circle c, Rect r){
	StCircle *sc = (StCircle *) c;
	StRect *sr = (StRect *) r;

	double x, y, w, h;

	x = MIN(sr->x, sc->x - sc->r);
	y = MIN(sr->y, sc->y - sc->r);
	h = MAX(sr->h + sr->y, sc->y + sc->r);
	w = MAX(sr->w + sr->x, sc->x + sc->r);
	if(sr->w + sr->x> sc->x + sc->r){
		/* x = sc->x - sc->r; */
		w = w+sc->r -sc->x;
	}
	else{
		/* x = sr->x + sr->w - sc->x ; */
		if(x < 0)
		w = MAX(sc->x + sc->r , sr->x + sr->w) +abs(x) ;
		else
		w = MAX(sc->x + sc->r , sr->x + sr->w) -abs(x) ;
	}
	if(sr->y + sr->h > sc->r + sc->y){
		h = sr->h + sr->y + sc->r - sc->y;
	
	}
	else{
			h = sc->y + sc->r - y;
	}


	fprintf(svgName, "<text x=\"%.2f\" y=\"%.2f\" fill=\"red\" font-size=\"20\" >Sobrepoe</text>", x,y-2);
	fprintf(svgName,"<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" stroke-dasharray=\"5,5\" fill-opacity=\"0\" stroke=\"pink\" stroke-width=\"5\"/>\n", x,y,w,h );
}
void drawRectPontilhado(FILE *svgName, Rect r){
	StRect *sr = (StRect *) r;

	fprintf(svgName,"<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" stroke-dasharray=\"5,5\" fill-opacity=\"0\" stroke=\"pink\" stroke-width=\"5\"/>\n", sr->x,sr->y,sr->x + sr->w,sr->y + sr->h );

}
void drawCirclePontilhado(FILE *svgName, Circle c){
	StCircle *sc = (StCircle *) c;
fprintf(svgName, "<circle r=\"%.2lf\" cx=\"%.2f\" cy=\"%.2f\"  stroke=\"pink\" fill-opacity=\"0\" stroke-dasharray=\"5,5\" stroke-width=\"3\"/>\n ",
		sc->r,
		sc->x,
		sc->y);
}
void drawCruz(FILE *svgName, float *pontos){

}
