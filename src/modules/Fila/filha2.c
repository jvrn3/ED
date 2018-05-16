#include "fila2.h"

typedef struct node{
	void *data;
	struct node *next;
}Node;

typedef struct queue{
	Node *front;
	Node *rear;
}Queue;


Fila createFila(){
	Fila f = malloc(sizeof(Queue));
	Queue *q = (Queue *) f;
	q->front = NULL;
	q->rear = NULL;

	return f;
}
Fila enQueue(Fila f, void *data){
	Node *node = malloc(sizeof(Node));
	node->data = data;
	Queue *q = (Queue *) f;
	if(q->front == NULL){
		q->front = node;
	}
	else{
		q->rear->next = node;
	}
		q->rnextear = node;
		q->rear->next = q->front;
	return f;
}

Fila deQueue(Fila f){
	Node *n = malloc(sizeof(Node));
	Queue *q = (Queue *) f;
	if(q->front == NULL){
		printf("Queue is empty");
		return NULL;
	}
	else{
		n = q->front;
		q->front = q->front->next;
		q->rear->next = q->front;
		}
}

void display(Fila f){
	Queue *q = (Queue *) f;
	Node *x = q->front;
	while(x->next  != q->front){
		printf("%d", *(int *) x->data);
		x = x->next;
	}
		printf("%d", *(int *) x->data);
}


int
main(){
	Fila f = createFila();
	int i, j, k;
	i = 1;
	j = 2;
	k = 3;
	enQueue(f, &i);
	enQueue(f, &j);
	enQueue(f, &k);
	deQueue(f);
	display(f);

}
