#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef void *Lista;
/* Uma lista ligada é uma coleção linear de dados. Cada elemento aponta para o próximo, até chegar ao final da lista(tail).
 *
 *Neste trabalho, é usado a Single Linked List, que só possuio o nó apontando para o head*/
typedef struct node{
	void *data;
	int id;
	int len;
	struct node *next;
}Node;

Lista createList();

int length(Lista l);
Lista del_posicao(Lista l, int i);

Node *createNode(void *data, int id);
int insertAtEnd(Lista l, void *data);

int insert(Lista l, void *data, int id);
int insertAfter(Lista l, int pos, void *data, int id);

Lista search_id(Lista l, int id, int data);
void *get(Lista l, int pos);

void display(Lista l, FILE *fname,  void (*f)(FILE *, void *));

void manipulate(Lista l, Lista l2, FILE *fname, void (*f) (FILE *, void *, void *));

Lista del(Lista l, void *data);

void *pop(Lista l);
Node *getNext(Lista l);

Lista searchList(Lista l, int (*compare)(void *, void *), void *comp);
void destroy(Lista l);
Node *getFirst(Lista l);
void *removeFirst(Lista l);
void *removeLast(Lista l);
void *search_del(Lista l, int (*compare)(void *, void *), void *comp);
void destroyList(Lista l);
Lista list_get_data(Lista l);
#endif
int _structListSize();
