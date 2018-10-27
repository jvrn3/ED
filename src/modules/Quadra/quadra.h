#ifndef QUADRA_H
#define QUADRA_H


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
char *quadra_get_fill(Quadra q);
char *quadra_get_strk(Quadra q);
char *quadra_get_cep(Quadra q);
void quadra_set_fill(Quadra q, char *color);
void quadra_set_strk(Quadra q, char *color);






#endif
