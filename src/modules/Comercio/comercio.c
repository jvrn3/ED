#include "comercio.h"

Comercio createComercio(char *cnpj, char *codt, char *cep, char face, int num, char *comp, char *nome){
	StComercio *sc = malloc(sizeof(StComercio));
	strcpy(sc->cnpj, cnpj);
	strcpy(sc->nome, nome);
	strcpy(sc->codt, codt);
	sc->address = createAddress(cep, face, num, comp);
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
