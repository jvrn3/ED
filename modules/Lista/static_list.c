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
	n->data = NULL;

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
	aux->data = data;
	aux->id = id;
	
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
void manipulate(Lista l, Lista l2, FILE *fname, void (*f)(FILE *, void *, void *)){
	Node *n = (Node *) l;
	Node *n2 = (Node *) l2;
	Node *aux = n2;
	while(aux->next != NULL){
		if(n->id != aux->id)
			f(fname, n->data, aux->data);
		aux = aux->next;
	}

}
Lista search_id(Lista l, int id, int data){
	Node *n = (Node *) l;
	if(n == NULL)
		return NULL;
	if(n->id == id){
		if(data)
			return n->data;
		else
			return n;
	}
	else
		return search_id(n->next, id, data);
	/* while(aux->id != id && aux->next != NULL){ */
	/* 	aux = aux->next; */
	/* } */
	/* if(aux->next != NULL){ */
	/* 	if(data) */
	/* 		return aux->data; */
	/* 	else */
	/* 		return aux; */
	/* } */
  /*  */
	/* return NULL; */
}
void destroy(Lista l){
	Node *n = (Node *) l;
	Node *next;
	while(n != NULL){
		next = n->next;
		free(n->data);
		free(n);
		n = next;
	}
}

