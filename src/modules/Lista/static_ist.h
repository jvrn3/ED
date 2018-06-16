#include <stdio.h>
#include <stdlib.h>

typedef void *Lista;


Lista createList();

int length(Lista l);

Lista insert(Lista l, void *data, int id);
Lista insertAfter(Lista l, int pos, void *data, int id);

Lista search_id(Lista l, int id, int data);
void *get(Lista l, int pos);

void display(Lista l, FILE *fname,  void (*f)(FILE *, void *));

void manipulate(Lista l, Lista l2, FILE *fname, void (*f) (FILE *, void *, void *));

void destroy(Lista l);
