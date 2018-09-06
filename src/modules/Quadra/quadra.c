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
float quadra_get_x(Quadra q){
	StQuadra *sq = (StQuadra *) q;
	return sq->x;
}
float quadra_get_y(Quadra q){
	StQuadra *sq = (StQuadra *) q;
	return sq->y;
}
float quadra_get_h(Quadra q){
	StQuadra *sq = (StQuadra *) q;
	return sq->alt;
}
float quadra_get_w(Quadra q){
	StQuadra *sq = (StQuadra *) q;
	return sq->larg;
}


/* int compareQuadraX(Quadra a, Quadra b){ */
/* 	StQuadra *sq = (StQuadra *) a; */
/* 	StQuadra *sqb = (StQuadra *) b; */
/*  */
/* 	if(sq->x < sqb->x) */
/* 		return 1; */
/* 	else */
/* 		return -1; */
/* } */
/* int compareQuadraY(Quadra a, Quadra b){ */
/* 	StQuadra *sq = (StQuadra *) a; */
/* 	StQuadra *sqb = (StQuadra *) b; */
/*  */
/*  */
/* 	if(sq->y < sqb->y) */
/* 		return 1; */
/* 	else */
/* 		return -1; */
/* } */
/*  */
/* float quadraPointInX(Quadra a){ */
/* 	StQuadra *sq = (StQuadra *) a; */
/* 	return sq->x; */
/* } */
/* float quadraPointInY(Quadra a){ */
/* 	StQuadra *sq = (StQuadra *) a; */
/* 	return sq->y; */
/* } */
