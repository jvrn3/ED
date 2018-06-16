#include "quadra.h"
#include <stdlib.h>
#include <string.h>

Quadra createQuadra(char *fill, char *strk, char *cep, 
		double x, double y, double larg, double alt){


	Quadra q = malloc(sizeof(StQuadra));

	StQuadra *sq = (StQuadra *)q;

	strcpy(sq->fill, fill);
	strcpy(sq->strk, strk);
	strcpy(sq->cep, cep);
	sq->x = x;
	sq->y = y;
	sq->larg = larg;
	sq->alt = alt;

	return q;
}

