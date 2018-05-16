#include "t1_func.c"
char *concatenar(char *var, char *argumento);
char *multiplicar_str(char *Z, int argumento);
char *alocar(char *ptr, char *str);
void get_pars(char **par1, char **par2, char **par3, int argc, char **argv);
FILE *criar_arquivo(char *f_name, char *f_ext, char *f_dir, FILE *files[10], int id, char arg);
void condicoes_arq(char *X, char *Y, char *Z, char *inteira, char *f_dir, char *f_name, char *f_ext, FILE *files[10]);
int ler_arquivo(char *nome,   FILE *files[10], int argc, char **argv) ;

