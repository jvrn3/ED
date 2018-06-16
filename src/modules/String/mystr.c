#include "mystr.h"

char *criaString(char *dir, char *nome, char *ext){
	char *aux = malloc(sizeof(char) * strlen(dir) + 2);
	strcpy(aux, dir);
	aux = concatena(aux, nome);
	aux = concatena(aux, ext);
	return aux;

}
char *aloca_tamanho(char *str, int len){
	str = (char *)malloc(sizeof(char) * len +1);
	return str;
}
char *arruma_path(char *str){
	char ultimo = str[strlen(str) -1];
	char *aux;
	if(ultimo != '/'){
		aux = (char *)malloc(sizeof(char) * strlen(str) +2);
		strcpy(aux, str);
		strcat(aux, "/");
		return aux;
	}
	return str;
}
char *concatena(char *str, char *str2){
	str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(str2) + 2));
	strcat(str, str2);
	return str;
}

