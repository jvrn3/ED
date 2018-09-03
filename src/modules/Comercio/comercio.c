#include "comercio.h"


Comercio createComercio(char *cnpj, char *codt, char *cep, char face, int num, char *comp, char *nome){
	StComercio *sc = malloc(sizeof(StComercio));
	strcpy(sc->cnpj, cnpj);
	strcpy(sc->nome, nome);
	strcpy(sc->codt, codt);
	sc->address = createAddress(cep, face, num, comp);
	return sc;
}
