#define MAX(A,B) ((A) >(B) ? (A) : (B))
#define MIN(A,B) ((A) < (B) ? (A) : (B))
#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct ponto{
 double x;
  double y;
}Ponto;
/**/

#include "../Circle/circle.h"
#include "../Rect/rect.h"
#include "../Torre/torre.h"
#include "../Lista/linked_list.h"
#include "../Sort/sort.h"
#include "../Cidade/cidade.h"
#include "../Quadra/quadra.h"
#include "../Hidrante/hidrante.h"
#include "../Semaforo/semaforo.h"
#include "../Torre/torre.h"
#include "math.h"
#include <float.h>
Ponto createPonto(float x, float y);
double distancePoints(Ponto a, Ponto b);
double distanceCC(Circle c, Circle c2);
double distanceCR(Circle c, Rect r);
double distanceRR(Rect r, Rect r2);
int overlayCC(Circle c, Circle c2);
int overlayCR(Circle c, Rect r);
int overlayRR(Rect r, Rect r2);
int isInsideC(Circle c, double x, double y);
int isInsideR(Rect r, double x, double y);
int isRectInsideRect(Rect a, Rect b);
int isRectInsideCircle(Circle c, Rect r);
int isCircleInsideRect(Circle c, Rect r);
int isCircleInsideCircle(Circle a, Circle b);
float area(int x1, int y1, int x2, int y2, int x3, int y3);
Ponto *getPontos(Torre t);
float stripClosest(Ponto *strip, int size, float d);
float closestPairs(Ponto *px, int n);
float closest(Ponto *p, int n);
float bruteForce(Ponto *pontos, int n);
float distPoints(Ponto a, Ponto b);
int find_ponto(Ponto *p, int n, float d, FILE *fp, FILE *fTxt, Torre t);
int isQuadraInsideRect(Quadra q, Rect r);
int isQuadraInsideCircle(Quadra q, Circle b);
int isSemaforoInsideRect(Semaforo s, Rect r);
int isSemaforoInsideCircle(Semaforo s, Circle c);
int isHidranteInsideRect(Hidrante h, Rect r);
int isHidranteInsideCircle(Hidrante h, Circle c);
int isTorreInsideRect(Torre t, Rect r);
int isTorreInsideCircle(Torre t, Circle c);
#endif
