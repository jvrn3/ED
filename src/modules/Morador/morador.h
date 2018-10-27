#ifndef MORADOR_H

#define MORADOR_H
#include "../Address/address.h"

typedef void *Morador;


Morador createMorador(char *cpf, char *cep, char face, int num, char *comp);

char *morador_get_cep(Morador m);

char morador_get_face(Morador m);

int morador_get_num(Morador m);

char *morador_get_comp(Morador m);

void free_morador(Morador m);

char *morador_get_cpf(Morador m);

Address morador_get_addr(Morador m);

void morador_set_cpf(Morador m, char *cpf);

#endif
