#ifndef SVG_H
#define SVG_H
#include "../Lista/static_ist.h"
#include "../Circle/circle.h"
#include "../Rect/rect.h"


/* functions to draw in svg format */ 

void drawCircle(FILE *fname, Lista c);
void drawRect(FILE *fname, Rect r);
void drawLineCToC(FILE *fname, Circle c, Circle c2);
void drawLineCToR(FILE *svgName, Circle c, Rect r);
void drawLineRToC(FILE *svgName, Rect r, Circle c);
void drawLineRToR(FILE *svgName, Rect r, Rect r2);
#endif



