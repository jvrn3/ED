#include "address.h"

typedef struct stAddress{
	char cep[50];
	char face;
	int num;
	char comp[50];

}StAddress;

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

Address changeAddress(Address a, char *cep, char face, int num, char *comp){
	StAddress *sa = (StAddress *) a;
	strcpy(sa->cep, cep);
	strcpy(sa->comp, comp);
	sa->face= face;
	sa->num = num;
	return sa;
}
