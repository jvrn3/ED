#include "carro.h"
#include <stdlib.h>
#include <string.h>
typedef struct stCarro{
	char placa[50];
	Rect dim_posic;
}StCarro;

Carro newCarro(char *placa, double x, double y, double larg, double alt){
	StCarro *sc = malloc(sizeof(StCarro));
	strcpy(sc->placa, placa);
	Rect rect = createRect("grey", "black", larg, alt, x, y);
	sc->dim_posic = rect;
	return sc;
}
char *carro_get_placa(Carro c){
	StCarro *sc = (StCarro *) c;
	return sc->placa;
}
Rect carro_get_posic(Carro c){
	StCarro *sc = (StCarro *) c;
	return sc->dim_posic;

}
int cmp_placa(Carro a, Carro b){

	StCarro *sa = (StCarro *) a;
	StCarro *sb = (StCarro *) b;

	if(strcmp(sa->placa, sb->placa) == 0)
		return 1;
	return 0;
}
//cmpr y's
int car_cmp(Carro a, Carro b){
	StCarro *carro1 = (StCarro *) a;
	StCarro *carro2 = (StCarro *) b;

	if(rect_get_x(carro1->dim_posic) >= rect_get_x(carro2->dim_posic))
		return 1;
	return 0;

}
