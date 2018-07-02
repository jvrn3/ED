#include "mystr.h"

char *criaString(char *dir, char *nome, char *ext){
	char *aux = malloc(sizeof(char) * strlen(dir) + 1);
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
int has_slash(char *str){
	for(int i =0; i < strlen(str) -1; i++){
		if(str[i] == '/')
			return 1;
	}
	return 0;

}
char *get_last_slash(char *str){
	char *tmp = strchr(str, '/');
	if(tmp != NULL){
		tmp++;
		return tmp;
	}
	return NULL;
}
char *concatena(char *str, char *str2){
	str = (char *)realloc(str, sizeof(char) * (strlen(str) + strlen(str2) )+2);
	strcat(str, str2);
	return str;
}

