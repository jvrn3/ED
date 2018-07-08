#ifndef SVG_H
#define SVG_H
#include "../Circle/circle.h"
#include "../Rect/rect.h"
#include "math.h"
#include "../Geometry/geometry.h"
#include "../Lista/linked_list.h"
#include "../Quadra/quadra.h"
#include "../Hidrante/hidrante.h"
#include "../Semaforo/semaforo.h"
#include "../Torre/torre.h"


/* procedures to draw in svg format */ 

void drawCircle(FILE *fname, Circle c);
void drawRect(FILE *fname, Rect r);
void drawQuadra(FILE *svgName, Quadra r);
void drawLineCToC(FILE *fname, Circle c, Circle c2);
void drawLineCToR(FILE *svgName, Circle c, Rect r);
void drawLineRToC(FILE *svgName, Rect r, Circle c);
void drawLineRToR(FILE *svgName, Rect r, Rect r2);
void drawOverlapCC(FILE *fDraw, Circle c, Circle c2);
void drawOverlapRR(FILE *svgName, Rect r, Rect r2);
void drawOverlapCR(FILE *svgName, Circle c, Rect r);
void displayRectToSvg(FILE *f, Lista l);
void displayCircleToSvg(FILE *f, Lista l);
void drawHidrante(FILE *svgName, Hidrante h);
void drawSemaforo(FILE *svgName, Semaforo s);
void drawTorre(FILE *svgName, Torre t);
void drawRectPontilhado(FILE *svgName, Rect r);
void drawCirclePontilhado(FILE *svgName, Circle c);
#endif



