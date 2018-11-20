#ifndef CARRO_H
#define CARRO_H
#include "../Rect/rect.h"
typedef void *Carro;


Carro newCarro(char *placa, double x, double y, double larg, double alt);
char *carro_get_placa(Carro c);
Rect carro_get_posic(Carro c);
int car_cmp(Carro a, Carro b);
int cmp_placa(Carro a, Carro b);
#endif
