#include "morador.h"

/*Morador é um morador da cidade, com cpf e o endereço de sua residência*/


Morador createMorador(char *cpf, char *cep, char face, int num, char *comp){
	StMorador *sm = malloc(sizeof(StMorador));
	sm->addr = createAddress(cep, face, num, comp);
	strcpy(sm->cpf, cpf);
	return sm;
}

char *morador_get_cep(Morador m){
	StMorador *sm = (StMorador *) m;
	return address_get_cep(sm->addr);
}
char morador_get_face(Morador m){
	StMorador *sm = (StMorador *) m;
	return address_get_face(sm->addr);
}
int morador_get_num(Morador m){
	StMorador *sm = (StMorador *) m;
	return address_get_num(sm->addr);
}
char *morador_get_comp(Morador m){
	StMorador *sm = (StMorador *) m;
	return address_get_comp(sm->addr);

}
