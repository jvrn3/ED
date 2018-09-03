#ifndef PESSOA_H
#define PESSOA_H
#include <stdlib.h>
#include <string.h>
/* */
typedef void *Pessoa;
typedef struct stPessoa{
	char cpf[50];
	char nome[50];
	char sobrenome[50];
	char sexo;
	char nasc[100];

}StPessoa;
#endif

Pessoa createPessoa(char *cpf, char *nome, char *sobrenome, char sexo, char *nascimento);
