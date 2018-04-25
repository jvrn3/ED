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
	}
	return count; 
}
Lista insert(Lista l, void *data, int id){
	Node *n = (Node *) l;
	Node *aux = createList();
	Node *tmp;
	aux->data = data;
	aux->id = id;
	if(n == NULL)
		n = aux;
	else{
		tmp = n;

		while(tmp->next != NULL)
			tmp = tmp->next;

		tmp->next = aux;
	}
}
Lista search_id(Lista l, int id){
	Node *n = (Node *n) l;
	Node *aux = n;
	while(aux->id != id && aux->next != NULL){
		aux = aux->next;
	}
	if(aux->next != NUL)
		return aux;
	return NULL;
}

