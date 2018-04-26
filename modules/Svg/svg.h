#ifndef SVG_H
#define SVG_H
#include "../Lista/static_ist.h"
#include "../Circle/circle.h"
#include "../Rect/rect.h"


/* functions to draw in svg format */ 

void drawCircle(FILE *fname, Lista c);
void drawRect(FILE *fname, Rect r);
#endif



