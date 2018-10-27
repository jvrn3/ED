#include "morador.h"
#include <stdlib.h>
#include <string.h>

/*Morador é um morador da cidade, com cpf e o endereço de sua residência*/

typedef struct stMorador{
	char cpf[50];
	Address addr;

}StMorador;

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
char *morador_get_cpf(Morador m){
	StMorador *sm = (StMorador *) m;
	return sm->cpf;
}
Address morador_get_addr(Morador m){
	StMorador *sm = (StMorador *) m;
	return sm->addr;
}
void morador_set_cpf(Morador m, char *cpf){
	StMorador *sm = (StMorador *) m;
	strcpy(sm->cpf, cpf);

}
void free_morador(Morador m){
	StMorador *sm = (StMorador *) m;
	free(sm->addr);
	free(sm);
}
void morador_set_addr(Morador m, Address novo){
	StMorador *sm = (StMorador *) m;
	sm->addr = changeAddress(
			sm->addr,
			address_get_cep(novo),
			address_get_face(novo),
			address_get_num(novo),
			address_get_comp(novo));
}
