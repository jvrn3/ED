#define MAX(A,B) ((A) >(B) ? (A) : (B))
#define MIN(A,B) ((A) < (B) ? (A) : (B))
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../Circle/circle.h"
#include "../Rect/rect.h"
#include "math.h"
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

#endif
