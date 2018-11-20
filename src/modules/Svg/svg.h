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
#include "../Morador/morador.h"
#include "../Address/address.h"
#include "../Carro/carro.h"
/* procedures to draw in svg format */ 

void startSvg(FILE *fSvg);
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
void drawMorador(FILE *svg, Ponto p, char *cpf);
void drawEstabelecimento(FILE *svgName, Ponto p);
void drawLineMudanca(FILE *svgName, Ponto a, Ponto b);
void drawLineMudancaEst(FILE *svgName, Ponto a, Ponto b);
void drawLinePontilhado(FILE *svgName, Ponto p, Ponto q);
void drawCruz(FILE *fsvgName, Ponto p);
void drawCarro(FILE *svgName, Carro c);
void drawArrow(FILE *file, char *cor);
void drawArrow2(FILE *file, float x1, float y1, float x2, float y2, char *cor);
void drawOverlapCar(FILE *fSvg, Rect r1, Rect r2);
#endif



