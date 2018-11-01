#include "quadra.h"
#include <stdlib.h>
#include <string.h>
typedef struct stQuadra{
  char fill[50], strk[50];
  char cep[50];

  double x, y, larg, alt;
}StQuadra;

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

char *quadra_get_cep(Quadra q){
	StQuadra *sq = (StQuadra *) q;
	return sq->cep;
}
char *quadra_get_fill(Quadra q){
	StQuadra *sq = (StQuadra *) q;
	return sq->fill;
}
char *quadra_get_strk(Quadra q){
	StQuadra *sq = (StQuadra *)q;
	return sq->strk;
}
void quadra_set_fill(Quadra q, char *color){
	StQuadra *sq = (StQuadra *) q;
	strcpy(sq->fill, color);
}
void quadra_set_strk(Quadra q, char *color){
	StQuadra *sq = (StQuadra *) q;
	strcpy(sq->strk, color);

}
