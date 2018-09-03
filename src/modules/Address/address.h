#ifndef ADDRESS_H
#define ADDRESS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Address é um endereço pertencente à cidade */
typedef void *Address;

typedef struct stAddress{
	char cep[50];
	char face;
	int num;
	char comp[50];

}StAddress;


Address createAddress(char *cep, char face, int num, char *comp);

char *address_get_cep(Address a);

char address_get_face(Address a);

int address_get_num(Address a);

char *address_get_comp(Address a);
#endif
