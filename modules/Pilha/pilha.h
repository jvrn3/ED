#include <stdio.h>
#include <stdlib.h>

typedef void *Pilha;

//criar pilha
Pilha crete_stack();
//adicionar elemento no final
Pilha push(Pilha p, void *data);
//tirar elemento do final
Pilha pop(Pilha p);
//verificar se está vazia
int empty(Pilha p);
