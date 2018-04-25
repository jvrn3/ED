#ifndef SVG_H
#define SVG_H
#include <stdio.h>
#include <stdlib.h>
#include "../Lista/static_ist.h"
#include "../Circle/circle.h"
#include "../Rect/rect.h"

Circle createCircle(FILE fname, Circle c);
Rect createRect(FILE fname, Rect *r);

#endif


