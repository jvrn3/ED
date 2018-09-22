#include "pessoa.h"
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
