#ifndef QUADRA_H
#define QUADRA_H


typedef struct stQuadra{
  char fill[100], strk[100];
  char cep[100];

  double x, y, larg, alt;
}StQuadra;

typedef void *Quadra;



Quadra createQuadra(char *fill, char *strk, char *cep, double x, double y, double larg, double alt);


#endif
