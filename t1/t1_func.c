#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1000
char *concatenar(char *var, char *argumento ){
	if(argumento[0] == '+' && argumento[3] != '@'){
	argumento = argumento + 4;
	argumento[strlen(argumento) - 2] = '\0';
	}
	var = (char *)realloc(var, sizeof(char) * (strlen(var) + strlen(argumento) + 1));
	strcat(var, argumento);
	return var;
}
char * limpar(char *var){
	free(var);
	var = (char * )malloc(sizeof(char));
	*var = 0;
	return var;
}
char *multiplicar_str(char *Z, int argumento){
	char *inicial;
	inicial = (char *)malloc(sizeof(char) * strlen(Z) + 1);
	strcpy(inicial, Z);
	for(int i = 0; i < argumento; i++){
		/* printf("%s\n", Z); */
		Z = concatenar(Z, inicial);
	}
	/* printf("Conteudo de Z: %s\n", Z); */
	free(inicial);
	return Z;
}
char *alocar(char *ptr, char *str){
	ptr = (char *) malloc(sizeof(char) * strlen(str) + 2);
	return ptr;
}
void get_pars(char **par1, char **par2, char **par3, int argc, char **argv){

	if(argc >= 4){
		if(strcmp("-o", argv[3]) == 0){
			if(argc == 6){
				*par1 = alocar(*par1, argv[5]);
				strcpy(*par1, argv[5]);
			}
			else if(argc == 7){
				*par1 = alocar(*par1, argv[5]);
				strcpy(*par1, argv[5]);

				*par2 = alocar(*par2, argv[6]);
				strcpy(*par2, argv[6]);
			}
			else if(argc == 8){
				*par1 = alocar(*par1, argv[5]);
				strcpy(*par1, argv[5]);

				*par2 = alocar(*par2, argv[6]);
				strcpy(*par2, argv[6]);

				*par3 = alocar(*par3, argv[7]);
				strcpy(*par3, argv[7]);
			}
		}
		else{
			if(argc ==4){
				*par1 = alocar(*par1, argv[3]);
				strcpy(*par1, argv[3]);
			}
			if(argc == 5){
				*par1 = alocar(*par1, argv[3]);
				strcpy(*par1, argv[3]);

				*par2 = alocar(*par2, argv[4]);
				strcpy(*par2, argv[4]);
			}
			if(argc == 6){
				*par1 = alocar(*par1, argv[3]);
				strcpy(*par1, argv[3]);

				*par2= alocar(*par3, argv[4]);
				strcpy(*par2, argv[4]);

				*par3 = alocar(*par3, argv[5]);
				strcpy(*par3, argv[5]);
			}
		}
	}
}
FILE *criar_arquivo(char *f_name, char *f_ext, char *f_dir, FILE *files[10], int id, char arg){
	char *completo = (char *)malloc(strlen(f_name) + strlen(f_dir) + strlen(f_ext) + 3);
	strcpy(completo, f_dir);
	strcat(completo, f_name);
	strcat(completo, f_ext);

	if(id < 10){
		if(arg == 'c')
		files[id] = fopen(completo, "w");
		if(arg == 'o')
			files[id] = fopen(completo, "a");
		if(arg == 'l')
			files[id] = fopen(completo, "r");
	}	

	if(files[id] == NULL){
		/* printf("Erro criar_arquivo\n"); */
		return NULL;
	}
	else{
		/* printf("Arquivo aberto com nome %s\n", completo); */
		return files[id];
	}
	free(completo);
}
char * fix_dir(char *dir){
	if(dir[strlen(dir) -1] != '/'){
		dir = (char *)realloc(dir, sizeof(char) * (strlen(dir) + strlen("/") + 1));
		strcat(dir, "/");
	}
	return dir;
}
void condicoes_arq(char *X, char *Y, char *Z, char *inteira, char *f_dir, char *f_name, char *f_ext, FILE *files[10]){
	int id, i;
	if(inteira[0] == 'd'){
		if(inteira[2] == '#'){
			if(inteira[3] == 'x'){
				free(f_dir);
				f_dir = (char *)malloc(strlen(X) * sizeof(char));
				strcpy(f_dir, X);
				f_dir = fix_dir(f_dir);
			}
			if(inteira[3] == 'y'){
				free(f_dir);
				f_dir = (char *)malloc(strlen(Y) * sizeof(char) + 1);
				strcpy(f_dir, Y);
			}
			if(inteira[3] == 'z'){
				free(f_dir);
				f_dir = (char *)malloc( strlen(Z) * sizeof(char) + 1);
				strcpy(f_dir, Z);
			}
		}
		else{
			inteira = inteira + 2;
			inteira[strlen(inteira) -1] = '\0';
			free(f_dir);
			f_dir = (char *)malloc(strlen(inteira) * sizeof(char) + 2);
			strcpy(f_dir, inteira);
		}
		f_dir = fix_dir(f_dir);
		/* printf("Dir: %s\n", f_dir); */
	}
	//######################################################
	
	else if(inteira[0] == 'a'){
		if(inteira[2] == '#'){
			if(inteira[3] == 'x')
				strcpy(f_name, X);
			if(inteira[3] == 'y')
				strcpy(f_name, Y);
			if(inteira[3] == 'z'){
				strcpy(f_name, Z);
			}
		}
		else{
			inteira = inteira + 3;
			inteira[strlen(inteira) -2] = '\0';
			strcpy(f_name, inteira);
		}
		/* printf("Nome do arquivo: %s\n", f_name); */
	}

	//######################################################
	else if(inteira[0] == 'e'){
		strcpy(f_ext, ".");
		if(inteira[2] == '#'){
			if(inteira[3] == 'x')
				strcat(f_ext, X);
			if(inteira[3] == 'y')
				strcat(f_ext, Y);
			if(inteira[3] == 'z')
				strcat(f_ext, Z);
		}
		else{
			inteira = inteira + 3;
			inteira[strlen(inteira) -2] = '\0';
			/* strtok(inteira, "\""); */
			strcat(f_ext, inteira);
		}
		/* printf("Nome Extencao: %s\n", f_ext); */
	}
	else if(inteira[0] == 'c' || inteira[0] == 'o' || inteira[0] == 'l'){
		if(strcmp(inteira +2, "#x") == 0)
			id = atoi(X);
		if(strcmp(inteira +2, "#y") == 0)
			id = atoi(Y);
		if(strcmp(inteira +2, "#z") == 0)
			id = atoi(Z);
		else
			id = atoi(inteira + 2);
		id--;
		if(inteira[0] == 'c'){
			criar_arquivo(f_name, f_ext, f_dir, files, id, 'c');
		}
		if(inteira[0] == 'l')
			criar_arquivo(f_name, f_ext, f_dir, files, id, 'l');
		if(inteira[0] == 'o')
			criar_arquivo(f_name, f_ext, f_dir, files, id, 'o');
	}
	//########################################################################
	
	else if(inteira[0] == 'w'){
		id = inteira[2] - '0';
		id--;
		if(files[id] != NULL){
			inteira = inteira + 4;
			if(inteira[0] != '#'){
				i = 0;
				while(i < strlen(inteira)){
					if(inteira[i] != '$')
						fputc(inteira[i], files[id]);
					else
						fputc('\n', files[id]);
					i++;
				}
				/* printf("Conteudo salvo\n"); */
			}
			else if (inteira[0] == '#'){
				if(inteira[1] == 'x'){
					fprintf(files[id], "%s\n", X);
					/* printf("Conteudo salvo de X"); */
				}
				if(inteira[1] == 'y'){
					fprintf(files[id], "%s\n", Y);
					/* printf("Conteudo salvo de Y\n"); */
				}
				if(inteira[1] == 'z'){
					fprintf(files[id], "%s\n", Z);
					/* printf("Conteudo salvo de Z\n"); */
				}
			}
		}
		else
			printf("erro ao escrever no arquivo");
	}
	else if(inteira[0] == 'f'){
		if(strcmp(inteira + 2, "#x") == 0)
			id = atoi(X);
		if(strcmp(inteira + 2, "#y") == 0)
			id = atoi(Y);
		if(strcmp(inteira + 2, "#z") == 0)
			id = atoi(Z);
		else
			id = atoi(inteira + 2);
		id--;
		if(files[id] == NULL){
			/* printf("Erro ao fecar arquivo"); */
		}
		else{
			fclose(files[id]);
			/* printf("Arquivo fechado com id %d\n", id); */
		}
	}
	else if(inteira[0] == 'r'){
		id = inteira[2] - '0';
		id--;
		if(inteira[5] == 'x'){
			fgets(X, MAX_SIZE, files[id]);
			strtok(X, "\n");
			/* printf("String lida %s\n", X); */
		}
		if(inteira[5] == 'y'){
			fgets(Y, MAX_SIZE, files[id]);
			strtok(Y, "\n");
			/* printf("String lida %s\n", Y); */
		}
		if(inteira[5] == 'z'){
			fgets(Z, MAX_SIZE, files[id]);
			strtok(Z, "\n");
			/* printf("String lida %s\n", Z); */
		}
	}
}

char *mallocar(char *str){
	str = (char * ) malloc(sizeof(char));
	str[0] = '\0';
	return str;
}
int ler_arquivo(char *nome, FILE *files[10], int argc, char **argv) {
	char *X, *Y, *Z;
	char *f_dir;
	char f_name[MAX_SIZE];
	char f_ext[MAX_SIZE];
	X = mallocar(X);
	Y = mallocar(Y);
	Z = mallocar(Z);
	f_dir = mallocar(f_dir);
	FILE *fp = fopen(nome, "r");
	if(fp == NULL){
		/* printf("Erro ao abrir o arquivo inicial\n"); */
		return -1;
	}
	char *inteira;
	inteira = mallocar(inteira);
	size_t len = 0;
	ssize_t read;
	char *line = NULL;
	char *par1, *par2, *par3; 
	par1 = par2 = par3 = NULL;
	get_pars(&par1, &par2, &par3, argc, argv);

	if(argc >= 4){
		if(strcmp("-o", argv[3]) == 0){
			f_dir = (char *)realloc(f_dir, strlen(argv[4]) * sizeof(char) + 2);

			strcpy(f_dir, argv[4]);
			if(argv[4][strlen(argv[4]) -1] != '/'){
				strcat(f_dir, "/");
			}
			/* printf("Dir: %s\n", f_dir); */
		}
	}
	//memory leak
	while((read = getline(&line, &len, fp)) != -1){
		free(inteira);
		inteira = (char *)malloc( sizeof(char) * len + 1);
		strcpy(inteira,line);
		char *comandos = strtok(line, " ");
		if(strcmp(comandos, "+x") == 0){
			if(inteira[3] =='@'){
				if(inteira[4] == '1')
					X = concatenar(X, par1);
				if(inteira[4] == '2')
					X = concatenar(X, par2);
				if(inteira[4] == '3')
					X = concatenar(X, par3);
			}
			else{
				X = concatenar(X, inteira);
			}
		}
		if(strcmp(comandos, "+y") == 0){
			if(inteira[3] =='@'){
				/* printf("\n%s", par3); */
				if(inteira[4] == '1')
					Y = concatenar(Y, par1);
				if(inteira[4] == '2')
					Y = concatenar(Y, par2);
				if(inteira[4] == '3')
					Y = concatenar(Y, par3);
			}
			else
				concatenar(X, inteira);
		}
		if(strcmp(comandos, "+z") == 0){
			if(inteira[3] == '*' && inteira[4] == '*'){
				Z = multiplicar_str(Z, atoi(par1));
			}
			else if(inteira[3] == '*' && inteira[4] != '*'){
				Z = multiplicar_str(Z, inteira[4] - '0');
			}
			else
				Z = concatenar(Z, inteira);
		}
		if(strcmp(comandos, "x") == 0)
			X = limpar(X);
		if(strcmp(comandos, "y") == 0)
			Y = limpar(Y);
		if(strcmp(comandos, "x") == 0)
			Z = limpar(Z);

		condicoes_arq(X, Y, Z, inteira, f_dir, f_name, f_ext, files);
	}

	free(X); 
	free(Y);
	free(Z);
	fclose(fp);
	free(f_dir);
	if (par1 != NULL)  free(par1);
	if(par2 != NULL)   free(par2);
	if(par3 != NULL)   free(par3);
	return 0;
}

//todo limap
