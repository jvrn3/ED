#ifndef COMERCIO_H
#define COMERCIO_H
#include <stdlib.h>
#include <string.h>
#include "../Address/address.h"
typedef void *Comercio;



Comercio createComercio(char *cnpj, char *codt, char *cep, char face, int num, char *nome);
Comercio createTipoComercio(char *codt, char *descricao);
char *estabelecimento_get_cep(Comercio c);
int estabelecimento_get_num(Comercio c);
char estabelecimento_get_face(Comercio c);
char *estabelecimento_get_codt(Comercio c);
char *estabelecimento_get_nome(Comercio c);
char *estabelecimento_get_cnpj(Comercio c);
char *estabelecimento_get_address(Comercio c);
void estabelecimento_set_address(Comercio c, Address addr);
char * estabelecimento_get_descricao(Comercio c);
void free_comercio(Comercio c);
#endif

