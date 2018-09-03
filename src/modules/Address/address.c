#include "address.h"

Address createAddress(char *cep, char face, int num, char *comp){
	StAddress *sa = malloc(sizeof(StAddress));

	strcpy(sa->cep, cep);
	strcpy(sa->comp, comp);
	sa->num = num;
	sa->face = face;

	return sa;
}

char *address_get_cep(Address a){
	StAddress *sa = (StAddress *) a;
	return sa->cep;
}
char address_get_face(Address a){
	StAddress *sa = (StAddress *) a;
	return sa->face;
}
int address_get_num(Address a){
	StAddress *sa = (StAddress *) a;
	return sa->num;
}
char *address_get_comp(Address a){
	StAddress *sa = (StAddress *) a;
	return sa->comp;
}
