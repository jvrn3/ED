#ifndef QUADRA_H
#define QUADRA_H


typedef struct stQuadra{
  char fill[50], strk[50];
  char cep[50];

  double x, y, larg, alt;
}StQuadra;

typedef void *Quadra;



Quadra createQuadra(char *fill, char *strk, char *cep, double x, double y, double larg, double alt);
/* int compareQuadraX(Quadra a, Quadra b); */
/* int compareQuadraY(Quadra a, Quadra b); */
/* float quadraPointInX(Quadra a); */
/* float quadraPointInY(Quadra a); */
float quadra_get_x(Quadra q);
float quadra_get_y(Quadra q);
float quadra_get_h(Quadra q);
float quadra_get_w(Quadra q);



#endif
