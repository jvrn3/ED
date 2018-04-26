#include "static_ist.h"

typedef struct node{
	void *data;
	int id;
	struct node *next;
}Node;


Lista createList(){
	Lista l = malloc(sizeof(Node));
	Node *n = (Node *) l;

	n->next = NULL;

	return l;
}

int length(Lista l){
	int count = 0;

	Node *n = (Node *) l;
	Node *aux = n;

	while(aux->next != NULL){
		count++;
		aux = aux->next;
	}
	return count; 
}
Lista insert(Lista l, void *data, int id){
	Node *n = (Node *) l;
	Node *aux = createList();
	Node *tmp;
	aux->data = data;
	aux->id = id;
	/* if(n == NULL) */
	/* 	n = aux; */
	/* else{ */
	/* 	tmp = n; */
  /*  */
	/* 	while(tmp->next != NULL) */
	/* 		tmp = tmp->next; */
  /*  */
	/* 	tmp->next = aux; */
	/* } */
	aux->next = n;
	n = aux;
	return n;
}

void display(Lista l, FILE *fname, void (*f)(FILE *, void *)){
	Node *n = (Node *) l;
	Node *aux;
	aux = n;
	while(aux->next != NULL){
		f(fname, aux->data);

		aux = aux->next;
	}


}
Lista search_id(Lista l, int id){
	Node *n = (Node *) l;
	Node *aux = n;
	while(aux->id != id && aux->next != NULL){
		aux = aux->next;
	}
	if(aux->next != NULL)
		return aux;
	return NULL;
}
void destroy(Lista l){
	Node *n = (Node *) l;
	Node *next;
	while(n != NULL){
		next = n->next;
		free(n);
		n = next;
	}
}

