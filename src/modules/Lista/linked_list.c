#include "linked_list.h"


Lista createList(){
	Lista l = malloc(sizeof(StList));
	StList *n = (StList*) l;

	n->head= NULL;
	n->size = 0;
	return l;
}
Node* createNode(void *data, int id){
	Node *n=  (Node*)malloc(sizeof(Node));
	n->data = data;
	n->id = id;
	n->next = NULL;
	return n;
}

int length(Lista l){
	StList *list = (StList *) l;
	return list->size;
}
void * get(Lista l, int pos){
	StList *n = (StList *) l;
	Node *tmp = n->head;
	int count = 0;
	while(count < pos ){
		if(tmp->next == NULL)
			return NULL;
		tmp = tmp->next;
		count++;
	}
	return tmp->data;
}
Node * getNext(Lista l){
	StList *list = (StList *) l;
	Node * n = list->head;
	n = n->next;
	if(n == NULL)
		return NULL;
	return n;
}
Node *getFirst(Lista l){
	StList *list = (StList* )l;
	Node *n = list->head;
	return n;

}
int insertAtEnd(Lista l, void *data){

	StList *lista = (StList *) l;
	if(lista->head == NULL)
		insert(l, data, 0);
	Node *tmp = lista->head;
	Node *new_node = createNode(data, 0);
	if(!new_node)
		return 0;

	while(tmp->next != NULL){
		tmp = tmp->next;
	}
	tmp->next = new_node;

	/* lista->head = tmp; */
	lista->size++;
	return 1;
	
return 0;
}
int insert(Lista l, void *data, int id){
	StList *lista = (StList *) l;
	Node *aux = (Node* )createNode(data, id);
	
	aux->next = lista->head;
	lista->head = aux;
	lista->size++;
	return 1;

}
Lista pop(Lista l){
	StList *list = (StList *) l;
	Node *head= list->head;
	Node *next = head->next;

	if(list->size ==1){
		list->head = NULL;
	}
	else{
		list->head = next;
		list->size--;

			free(head->data);  
		 free(head); 
	}
	return list;
}

int insertAfter(Lista l, int pos, void *data, int id){
	int count = 0;
	StList *list = (StList *) l;
	Node *n = list->head;
	Node *aux = createNode(data,id);
	Node *aux2 = createNode(data,id);

	if(n == NULL)
		return -1;
	if(pos == 0){
		insert(l, data, id);
		return 1;
	}

	while(count < pos && n->next != NULL){
		n = n->next;
		count++;
	}
	aux2 = n->next;
	n->next = aux;
	n = n->next;
	n->next = aux2;

	list->size++;
	list->head = n;
	return 1;
}

void display(Lista l, FILE *fname, void (*f)(FILE *, void *)){
	StList *n = (StList *) l;
	Node *nod = n->head;
	while(nod->next != NULL){
		f(fname, nod->data);
		nod = nod->next;

	}

}
void manipulate(Lista l, Lista l2, FILE *fname, void (*f)(FILE *, void *, void *)){
	StList *n = (StList *) l;
	StList *n2 = (StList *) l2;
	Node *aux = n2->head;
	Node *aux2 = n->head;
	while(aux->next != NULL){
		if(aux2->id != aux->id)
			f(fname, aux2->data, aux->data);
		aux = aux->next;
	}
}
Lista search_id(Lista l, int id, int data){
	StList *list = (StList *) l;
	Node *n = list->head;
	for(int i = 0; i< list->size;i++){
		if(n->id == id){
			if(data)
				return n->data;
			else
				return n;
		}

	n = n->next;
	}
	return NULL;
	
}
/* Lista del_posicao(Lista l, int i){ */
/* 	Node *n = (Node *) l; */
/* 	Node *tmp = n; */
/* 	Node *prev = NULL; */
/* 	int j = 0; */
/* 	while(i != j && tmp->next != NULL){ */
/* 		prev = tmp; */
/* 		tmp = tmp->next; */
/* 	} */
/* 	if(i == j){ */
/* 		if(prev) */
/* 			prev->next = tmp->next; */
/* 		else */
/* 			n = n->next; */
/* 	} */
/* 	free(tmp); */
/* 	return n; */
/*  */
/*  */
/* } */
Lista del(Lista l, void *data){
	StList *list = (StList *) l;
	Node *tmp = list->head;
	Node *prev = NULL;

	while(tmp->data != data && tmp->next != NULL){
		prev = tmp;
		tmp = tmp->next;
	}
	if(tmp->data == data){
		if(prev)
				prev->next = tmp->next;
		else
			list->head = tmp->next;
	}
	/* free(tmp->data); */
	/* free(tmp); */
	list->size--;
	return l;
}

void destroy(Lista l){
	StList *list = (StList *) l;
	Node *n = list->head;
	Node *next;
	while(n != NULL){
		next = n->next;
		free(n->data);
		free(n);
		n = next;
	}
	/* free(list->head); */
	list->size = 0;
	list->head = NULL;
}

Lista searchList(Lista l, int (*compare)(void *, void *), void *comp){
	StList *sl = (StList *) l;
	Node *n = sl->head;
	while(n->next != NULL || compare(n->data, comp) == 0){
		n = n->next;
	}
	if(n != NULL)
		return n->data;
	else
		return NULL;
}
