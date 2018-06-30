#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef void *Lista;

typedef struct node{
	void *data;
	int id;
	struct node *next;
}Node;




Lista createList();

int length(Lista l);
Lista del_posicao(Lista l, int i);

Lista insert(Lista l, void *data, int id);
Lista insertAfter(Lista l, int pos, void *data, int id);

Lista search_id(Lista l, int id, int data);
void *get(Lista l, int pos);

void display(Lista l, FILE *fname,  void (*f)(FILE *, void *));

void manipulate(Lista l, Lista l2, FILE *fname, void (*f) (FILE *, void *, void *));

Lista del(Lista l, void *data);

void *pop(Lista l);

void destroy(Lista l);
#endif

