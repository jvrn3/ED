#include "mystr.h"

char *criaString(char *dir, char *nome, char *ext){
	char *completo = (char *)malloc(strlen(dir));
	strcpy(completo, dir);
	concatena(completo, nome);
	concatena(completo, ext);

	return completo;

}
char *aloca_tamanho(char *str, size_t len){
	str = (char *)malloc(sizeof(char) * len +2);
	return str;
}
char *arruma_path(char *str){
	char ultimo = str[strlen(str) -1];
	char *aux;
	if(ultimo != '/'){
		aux = (char *)malloc(sizeof(sizeof(char) * strlen(str) +2));
		strcpy(aux, str);
		strcat(aux, "/");
		return aux;
	}
	return str;
}
char *concatena(char *str, char *str2){
	str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(str2) + 1));
	strcat(str, str2);
	return str;
}

