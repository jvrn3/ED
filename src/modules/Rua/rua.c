#include "rua.h"
#include <string.h>
#include <stdlib.h>

typedef struct stRua{
	char nome[100],
		 ldir[100],
		 lesq[100];

	float cmp,
		  vm;

}StRua;

Rua createRua(char *nome, char *ldir, char *lesq, float cmp, float vm){

	StRua *sr = malloc(sizeof(StRua));
	strcpy(sr->nome, nome);
	strcpy(sr->ldir, ldir);
	strcpy(sr->lesq, lesq);
	
	sr->cmp = cmp;
	sr->vm = vm;
	return sr;
}

char *rua_get_nome(Rua r){
	StRua *sr = (StRua *) r;
	return sr->nome;
}
char *rua_get_ldir(Rua r){
	StRua *sr = (StRua *) r;
	return sr->ldir;
}
char *rua_get_lesq(Rua r){
	StRua *sr = (StRua *) r;
	return sr->lesq;
}

float rua_get_cmp(Rua r){
	StRua *sr = (StRua *) r;
	return sr->cmp;
}
float rua_get_vm(Rua r){
	StRua *sr = (StRua *) r;
	return sr->vm;
}
void rua_set_vm(Rua r, float vm){
	StRua *sr = (StRua *) r;
	sr->vm  = vm;
}
