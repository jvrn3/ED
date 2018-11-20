#include "linked_list.h"

typedef struct stList{
	Node *head;
	int size;
}StList;

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
	Node * n = (Node *) l;
	n = n->next;
	if(n == NULL)
		return NULL;
	return n;
}
Node *getFirst(Lista l){
	StList *list = (StList* )l;
	if(list->head == NULL)
		return NULL;
	Node *n = list->head;
	return n;

}
Node *getLast(Lista l){
	StList *list = (StList *)l;
	Node *node = list->head;
	if(list->head == NULL)
		return NULL;

	while(getNext(node) != NULL){
		node = getNext(node);
	}
	return node;

}
int insertAtEnd(Lista l, void *data){

	StList *lista = (StList *) l;
	if(lista->head == NULL){
		insert(l, data, 0);
		return 1;
	}
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
//Deprecated
//used only for t2
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
//Deprecated
//used only for t2
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
void *removeLast(Lista l){
	if(l == NULL)
		return NULL;
	StList *st = (StList *) l;
	if(st->head == NULL)
		return NULL;
	Node *tmp = st->head;
	Node *t = tmp;
	//there's only one element
	if(tmp->next == NULL){
		void *d = tmp->data;
		free(st->head);
		st->head = NULL;
		st->size--;
		return d;
	}
	else{
		while(tmp->next != NULL){
			t = tmp;
			tmp = tmp->next;
		}
	}
	void *d =NULL;
	if(t->next)
		d = t->next->data;
	free(t->next);
	t->next = NULL;
	st->size--;
	return d;
}
void * del(Lista l, void *data){
	if(l == NULL)
		return NULL;

	StList *list = (StList *) l;
	Node *n = list->head;
	Node *prev = NULL;

	if(n == NULL)
		return NULL;
	if(n->data == data){
		void *d = removeFirst(l);
		return d;
	}
	if(n->next == NULL){
		void *d = removeLast(l);
		return d;
	}
	while(n->next != NULL && n->data != data){
		prev = n;
		n = n->next;
	}
	if(n == NULL)
		return NULL;
	else{
		void *d = n->data;
		prev->next = n->next;
		free(n);
		list->size--;
		return d;
	}
}
void *removeFirst(Lista l){
	if(l == NULL)
		return NULL;
	StList *st = (StList *) l;
	if(st->head == NULL)
		return NULL;
	Node *n = st->head;
	if(n->next == NULL){
		void *d = n->data;
		st->head = NULL;
		st->size--;
		free(n);
		return d;
	}
	void *d = n->data;
	st->head = n->next;
	st->size--;
	free(n);
	return d;
}


void *search_del(Lista l, int (*compare)(void *, void *), void *comp ){
	Node *n;
	for(n = getFirst(l); n != NULL; n = n->next){
		if(compare(n->data, comp))
			return del(l, n->data);
	}
	return NULL;
}

Lista searchList(Lista l, int (*compare)(void *, void *), void *comp){
	Node *n;
	for(n = getFirst(l); n != NULL; n = n->next){
		if(compare(n->data, comp))
			return n->data;
	}
	return NULL;
}
void destroy(Lista l){

	if(l == NULL)
		return;
	StList *list = (StList *) l;
	while(list->size > 0){
		void *data = removeFirst(list);
		if(data != NULL)
			free(data);
	}
	free(list);
}
void destroyList(Lista l){

	if(l == NULL)
		return;
	StList *list = (StList *) l;
	while(list->size > 0){
		removeFirst(list);
	}
	free(list);
}
Lista list_get_data(Lista l){
	Node *n = (Node *) l;
	return n->data;
}

Node *list_get_middle(Lista	l){
	Node *n = (Node *)l;
	if(n == NULL)
		return NULL;

	Node *fast = n->next;
	Node *slow = n;

	while(fast != NULL ){

		fast = fast->next;
		if(fast != NULL){
			slow = slow->next;
			fast = fast->next;
		}
	}
	return slow;
}
Node *reverse_list(Lista l){
	Node *root = (Node *) l;
	Node *new_root = NULL;
	while(root){
		Node *next = root->next;
		root->next = new_root;
		new_root = root;
		root = next;
	
	}
	return new_root;
}
