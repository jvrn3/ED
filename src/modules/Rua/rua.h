#ifndef RUA_H
#define RUA_H

typedef void *Rua;


Rua createRua(char *nome, char *ldir, char *lesq, float cmp, float vm);
char *rua_get_nome(Rua r);
char *rua_get_ldir(Rua r);
char *rua_get_lesq(Rua r);
float rua_get_cmp(Rua r);
float rua_get_vm(Rua r);
#endif
