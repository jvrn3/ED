#include "mystr.h"

char *aloca_tamanho(char *str, size_t len){
	str = malloc(sizeof(char) * len);
	return str;
}

char *arruma_path(char *str){
	char ultimo = str[strlen(str) -1];
	char *aux;
	aux = aloca_tamanho(aux, strlen(str) + 2);
	strcpy(aux, str);

	if(ultimo != '/'){
		aux[strlen(str)] = '/';
		aux[strlen(str)+1] = '\0';
	}
	return aux;
}

char *concatena(char *str, char *str2){
	str = realloc(str, sizeof(char) * (strlen(str) + strlen(str2) + 1));
	strcat(str, str2);
	return str;
}

