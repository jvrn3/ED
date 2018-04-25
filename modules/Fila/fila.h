#include <stdio.h>
#include <stdlib.h>
#define MAXQUEUE 100
//basic queue

typedef struct queue{
	int tamanho;
	int in, fim;
	int data[MAXQUEUE];
}Queue;

Queue *criar_fila();
int empty(Queue *q);
Queue *queue(Queue *q, int data);
void display(Queue *q);
Queue *dequeue(Queue *q);



