#include "pessoa.h"
#include <stdlib.h>
#include <string.h>
typedef struct stPessoa{
	char cpf[50];
	char nome[50];
	char sobrenome[50];
	char sexo;
	char nasc[100];
	int vivo;

}StPessoa;

Pessoa createPessoa(char *cpf, char *nome, char *sobrenome,char sexo, char *nasc){
	StPessoa *sp = malloc(sizeof(StPessoa));

	strcpy(sp->cpf, cpf);
	strcpy(sp->nome, nome);
	strcpy(sp->sobrenome, sobrenome);
	sp->sexo = sexo;
	strcpy(sp->nasc, nasc);
	sp->vivo = 1;
	return sp;
}
char *pessoa_get_cpf(Pessoa p){
	StPessoa *sp = (StPessoa *) p;
	return sp->cpf;
}
char *pessoa_get_nome(Pessoa p){
	StPessoa *sp = (StPessoa *) p;
	return sp->nome;
}
char *pessoa_get_sobrenome(Pessoa p){
	StPessoa *sp = (StPessoa *) p;
	return sp->sobrenome;
}
char pessoa_get_sexo(Pessoa p){
	StPessoa *sp = (StPessoa *) p;
	return sp->sexo;
}
char *pessoa_get_nasc(Pessoa p){
	StPessoa *sp = (StPessoa *) p;
	return sp->nasc;
}


