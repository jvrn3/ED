#ifndef COMERCIO_H
#define COMERCIO_H
#include <stdlib.h>
#include <string.h>
#include "../Address/address.h"
typedef void *Comercio;

typedef struct stComercio{
	char cnpj[100];
	char codt[50];
	char nome[100];
	Address address;
}StComercio;

typedef struct stComercioTipo{
	char codt[50];
	char descricao[100];
}StComercioTipo;

Comercio createComercio(char *cnpj, char *codt, char *cep, char face, int num, char *nome);
Comercio createTipoComercio(char *codt, char *descricao);
char *estabelecimento_get_cep(Comercio c);
int estabelecimento_get_num(Comercio c);
char estabelecimento_get_face(Comercio c);
char *estabelecimento_get_codt(Comercio c);
void free_comercio(Comercio c);
#endif

