#include "svg.h"
/* need to create a geometry library */
void startSvg(FILE *fSvg){
	fprintf(fSvg,"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100000\" height=\"100000\">\n");
}
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
	Quadra sr = r;
	fprintf(svgName, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" fill=\"%s\" stroke=\"%s\"/>\n", 
			quadra_get_x(sr),
			quadra_get_y(sr),
			quadra_get_w(sr),
			quadra_get_h(sr),
			quadra_get_fill(sr),
			quadra_get_strk(sr)
		   );
	fprintf(svgName, "<text x=\"%.2f\" y=\"%.2f\" fill=\"black\" font-size=\"12\">%s</text>\n",
			quadra_get_x(sr) + quadra_get_w(sr)/2,
			quadra_get_y(sr) + quadra_get_h(sr)/2,
			quadra_get_cep(sr));
}

void drawHidrante(FILE *svgName, Hidrante h){
	Hidrante sh = h;
fprintf(svgName, "<circle r=\"5.00\" cx=\"%.2f\" cy=\"%.2f\"  stroke=\"%s\" fill=\"%s\" />\n<text x=\"%.2f\" y=\"%.2f\" fill=\"white\" font-size=\"7\">H</text>\n", 
		hidrante_get_x(sh),
		hidrante_get_y(sh),
		hidrante_get_strk(sh),
		hidrante_get_fill(sh),
		hidrante_get_x(sh) - 3,
		hidrante_get_y(sh) + 2
			);
}
void drawSemaforo(FILE *svgName, Semaforo s){
	Semaforo sh =  s;
	fprintf(svgName, "<rect x=\"%.2f\" y=\"%.2f\" width=\"5\" height=\"15\" fill=\"%s\" stroke=\"%s\"/>\n<text x=\"%.2f\" y=\"%.2f\" fill=\"white\" font-size=\"8\">S</text>\n", 
			semaforo_get_x(sh),
			semaforo_get_y(sh),
			semaforo_get_fill(sh),
			semaforo_get_strk(sh),
			semaforo_get_x(sh) - 0.5,
			semaforo_get_y(sh) + 10);
}
void drawTorre(FILE *svgName, Torre t){
	Torre st = t;
	fprintf(svgName, "<circle r=\"7.00\" cx=\"%.2f\" cy=\"%.2f\"  stroke=\"%s\" fill=\"%s\" />\n", 
			torre_get_x(st),
			torre_get_y(st),
			torre_get_strk(st),
			torre_get_fill(st));
	fprintf(svgName, "<text x=\"%.2f\" y=\"%.2f\" fill=\"white\" font-size=\"11\">T</text>\n",
			torre_get_x(st) - 4,
			torre_get_y(st) + 4);

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
void drawMorador(FILE *svgName, Ponto p, char *cpf){
	//face é nort
		fprintf(svgName, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"10\" fill=\"violet\"/>",

				p.x,
				p.y);
	fprintf(svgName, "<text x=\"%.2f\" y=\"%.2f\" fill=\"black\" font-size=\"12\">%s</text>\n",
			p.x + 5, p.y, cpf);
}
void drawEstabelecimento(FILE *svgName, Ponto p){
	fprintf(svgName, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"10\" fill=\"darkgoldenrod\"/>",
			p.x,
			p.y
			);
}
void drawLineMudanca(FILE *svgName, Ponto a, Ponto b){
	fprintf(svgName, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke-width=\"3\" stroke=\"%s\"/>\n",
			a.x + 10,
			a.y,
			b.x,
			b.y,
			"yellow");
}
void drawLineMudancaEst(FILE *svgName, Ponto a, Ponto b){
	fprintf(svgName, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke-width=\"3\" stroke=\"%s\"/>\n",
			a.x + 10,
			a.y,
			b.x,
			b.y,
			"thistle");
}
void drawLinePontilhado(FILE *svgName, Ponto p, Ponto q){
	fprintf(svgName, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke-width=\"1\" stroke-dasharray=\"5,5\" stroke=\"red\"/>\n", p.x, p.y, q.x, q.y);
}
void drawCruz(FILE *svgName, Ponto p){
	fprintf(svgName, "<rect x=\"%.2f\" y=\"%.2f\" width=\"15\" height=\"15\" fill=\"%s\" stroke=\"%s\"/>\n transform=\"rotate(-45)\"",
			p.x -8,
			p.y -8,
			"black",
			"black");
	fprintf(svgName, "<text x=\"%.2f\" y=\"%.2f\" fill=\"white\" font-size=\"18\">✞</text>\n",
			p.x-8,
			p.y +5);

}
void drawCarro(FILE *svgName, Carro c){
	Rect r = carro_get_posic(c);
	drawRect(svgName, r);
	if(rect_vertical(r)){
	    fprintf(svgName, "<text x=\"%.2f\" y=\"%.2f\" fill=\"grey\" font-size=\"3\">%s</text>\n",
		    rect_get_x(r) + rect_get_w(r)/2,
		    rect_get_y(r) + rect_get_h(r)/2,
		    carro_get_placa(c)
		   );
	}
	else{
	    fprintf(svgName, "<text x=\"%.2f\" y=\"%.2f\" fill=\"grey\" font-size=\"3\">%s</text>\n",
		    rect_get_x(r),
		    rect_get_y(r),
		    carro_get_placa(c)
		   );

	
	}
}
void drawArrow(FILE *file, char *cor){
    fprintf(file, "%s\n", "<defs>");
    fprintf(file, "%s\n", "<marker id=\"arrowhead\" markerWidth=\"10\" markerHeight=\"7\" refX=\"8\" refY=\"3.5\" orient=\"auto\">");
    fprintf(file, "<polygon points=\"0 0, 10 3.5, 0 7\" fill=\"%s\"/>\n", cor);
    fprintf(file, "%s\n", "</marker>");
    fprintf(file, "%s\n", "</defs>");
}

void drawArrow2(FILE *file, float x1, float y1, float x2, float y2, char *cor){
    fprintf(file, "%s\n", "<line");
    fprintf(file, " %s", "x1=");
    fprintf(file, "\"%.5f\"\n", x1);
    fprintf(file, " %s", "y1=");
    fprintf(file, "\"%f\"\n", y1);
    fprintf(file, " %s", "x2=");
    fprintf(file, "\"%.5f\"\n", x2);
    fprintf(file, " %s", "y2=");
    fprintf(file, "\"%f\"\n", y2);
    fprintf(file, " %s", "style=");
    fprintf(file, "\"%s", "stroke: ");
    fprintf(file, " %s;", cor);
    fprintf(file, " %s\"\n", "stroke-width: 1");
    fprintf(file, " marker-end=\"%s\"\n", "url(#arrowhead)");
    fprintf(file, "%s\n", "/>");
}
void drawOverlapCar(FILE *fSvg, Rect r1, Rect r2){
    StRect *sr = (StRect *) r1;
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


	fprintf(fSvg,"<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\"  fill-opacity=\"0\" stroke=\"red\" stroke-width=\"2\"/>\n", x,y,w,h );

}
