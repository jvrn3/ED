#ifndef MAXSIZE
#define MAXSIZE 100
#endif
#ifndef MYSTR_H
#define MYSTR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *criaString(char *dir, char *nome, char *ext);
char *aloca_tamanho(char *str, int len);
char *arruma_path(char *str);
char *concatena(char *str, char *str2);

#endif
