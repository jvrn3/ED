#ifndef PESSOA_H
#define PESSOA_H
typedef void *Pessoa;

Pessoa createPessoa(char *cpf, char *nome, char *sobrenome, char sexo, char *nascimento);
char *pessoa_get_cpf(Pessoa p);
char *pessoa_get_nome(Pessoa p);
char *pessoa_get_sobrenome(Pessoa p);
char pessoa_get_sexo(Pessoa p);
char *pessoa_get_nasc(Pessoa p);
#endif


