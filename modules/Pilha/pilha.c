#include "pilha.h"

typedef struct node{
	void *data;
	struct node *next;

}Node;

typedef struct stack{
	int length;
	Node *top;
}Stack;

Pilha create_stack(){
	Pilha p = malloc(sizeof(Stack));
	Stack *s = (Stack *) p;
	s->top = NULL;
	s->length = 0;
	return p;
}

Pilha push(Pilha p, void *data){
	Stack *s = (Stack *) p;
	//n is temporary
	Node *n = malloc(sizeof(Node));
	n->data = data;
	n->next = s->top;
	s->top = n;
	return p;

}

Pilha pop(Pilha p){
	Stack *s = (Stack *) p;
	void *d;
	d = s->top->data;
	s->top = s->top->next;
	return d;


}

int empty(Pilha p){
	Stack *s = (Stack *) p;
	return s->top ==NULL;
}
/* void display(Pilha p){ */
/* 	Stack *s = (Stack *) p; */
/* 	while(s->top != NULL){ */
/* 		printf("%d\n", *(int *)s->top->data); */
/* 		s->top = s->top->next; */
/* 	} */
/* } */

