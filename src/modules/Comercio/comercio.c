#include "comercio.h"

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

Comercio createComercio(char *cnpj, char *codt, char *cep, char face, int num, char *nome){
	StComercio *sc = malloc(sizeof(StComercio));
	strcpy(sc->cnpj, cnpj);
	strcpy(sc->nome, nome);
	strcpy(sc->codt, codt);
	sc->address = createAddress(cep, face, num, "com");
	return sc;
}

Comercio createTipoComercio(char *codt, char *descricao){
	StComercioTipo *sct = malloc(sizeof(StComercioTipo));
	strcpy(sct->codt, codt);
	strcpy(sct->descricao, descricao);

	return sct;
}
char *estabelecimento_get_nome(Comercio c){
	StComercio *sc = (StComercio *) c;
	return sc->nome;
}
char *estabelecimento_get_cep(Comercio c){
	StComercio *sc = (StComercio *) c;
	return address_get_cep(sc->address);
}
int estabelecimento_get_num(Comercio c){
	StComercio *sc = (StComercio *) c;
	return address_get_num(sc->address);
}
char estabelecimento_get_face(Comercio c){
	StComercio *sc = (StComercio *) c;
	return address_get_face(sc->address);
}
char *estabelecimento_get_codt(Comercio c){
	StComercio *sc = (StComercio *) c;
	return sc->codt;
}
char *estabelecimento_get_cnpj(Comercio c){
	StComercio *sc = (StComercio *) c;
	return sc->cnpj;
}
char *estabelecimento_get_address(Comercio c){
	StComercio *sc = (StComercio *) c;
	return sc->address;
}
void estabelecimento_set_address(Comercio c, Address novo){
	StComercio *sc = (StComercio *) c;
	sc->address = changeAddress(estabelecimento_get_address(sc),
			address_get_cep(novo),
			address_get_face(novo), 
			address_get_num(novo), "");

}
char *estabelecimento_get_descricao(Comercio c){
	StComercioTipo *sct = (StComercioTipo *) c;
	return sct->descricao;
}
void free_comercio(Comercio c){
	StComercio *sc = (StComercio *) c;
	free(sc->address);
	free(sc);
}
