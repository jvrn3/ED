#ifndef COMERCIO_H
#define COMERCIO_H
#include <stdlib.h>
#include <string.h>
#include "../Address/address.h"
typedef void *Comercio;

typedef struct stComercio{
	char cnpj[50];
	char codt[50];
	char nome[100];
	Address address;
}StComercio;


Comercio createComercio(char *cnpj, char *codt, char *cep, char face, int num, char *comp, char *nome);
#endif

