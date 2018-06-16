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
void * get(Lista l, int pos){
	Node *n = (Node *) l;
	int count = 0;
	while(count < pos){
		n = n->next;
		count++;
	}
	return n->data;
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
Lista insertAfter(Lista l, int pos, void *data, int id){
	int count = 0;
	Node *n = (Node *) l;
	Node *tracker = n;
	Node *aux = createList();
	Node *aux2 = createList();

	aux->data = data;
	aux->id = id;

	if(n == NULL)
		return n;
	if(pos == 0)
		return insert(l, data, id);

	while(count < pos && n->next != NULL){
		n = n->next;
		count++;
	}
	aux2 = n->next;
	n->next = aux;
	n = n->next;
	n->next = aux2;

	return tracker;

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

