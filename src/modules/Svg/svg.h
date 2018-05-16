#ifndef SVG_H
#define SVG_H
#include "../Circle/circle.h"
#include "../Rect/rect.h"
#include "math.h"
#include "../Geometry/geometry.h"


/* functions to draw in svg format */ 

void drawCircle(FILE *fname, Circle c);
void drawRect(FILE *fname, Rect r);
void drawLineCToC(FILE *fname, Circle c, Circle c2);
void drawLineCToR(FILE *svgName, Circle c, Rect r);
void drawLineRToC(FILE *svgName, Rect r, Circle c);
void drawLineRToR(FILE *svgName, Rect r, Rect r2);
void drawOverlapCC(FILE *fDraw, Circle c, Circle c2);
void drawOverlapRR(FILE *svgName, Rect r, Rect r2);
void drawOverlapCR(FILE *svgName, Circle c, Rect r);

#endif



