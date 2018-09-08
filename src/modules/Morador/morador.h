#ifndef MORADOR_H

#define MORADOR_H
#include "../Address/address.h"
#include <stdlib.h>
#include <string.h>

typedef void *Morador;

typedef struct stMorador{
	char cpf[50];
	Address addr;

}StMorador;
Morador createMorador(char *cpf, char *cep, char face, int num, char *comp);

char *morador_get_cep(Morador m);

char morador_get_face(Morador m);

int morador_get_num(Morador m);

char *morador_get_comp(Morador m);

void free_morador(Morador m);

#endif
