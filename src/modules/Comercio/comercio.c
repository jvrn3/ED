#include "comercio.h"

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
void free_comercio(Comercio c){
	StComercio *sc = (StComercio *) c;
	free(sc->address);
	free(sc);
}
