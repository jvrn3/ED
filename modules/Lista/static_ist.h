#include <stdio.h>
#include <stdlib.h>

typedef void *Lista;


Lista createList();

int length(Lista l);

Lista insert(Lista l, void *data, int id);

Lista search_id(Lista l, int id);
