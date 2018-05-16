#include "fila.h"

Queue *criar_fila(){
	Queue *q = malloc(sizeof(Queue) * MAXQUEUE);
	q->tamanho = 0;
	return q;
}

int empty(Queue *q){
	if(q->tamanho == 0)
		return 1;
	else return 0;
}

Queue *queue(Queue *q, int data){
	if(q->tamanho == 100){
		printf("Full a a ");
		printf("oi")
	}
	else{
		for(int i = q->tamanho; i >= 0; i--)
			q->data[i+1] = q->data[i];
		q->data[0] = data;
	}
	q->tamanho++;
	return q;
}
void display(Queue *q){
	for(int i = 0; i < q->tamanho; i++){
		printf("%d\n", q->data[i]);
	
	}
}
Queue *dequeue(Queue *q){
	q->data[q->tamanho--];
	return q;
}

int
main(){
	Queue *q= criar_fila();
	/* queue(q, 1); */
	/* queue(q, 2); */
	/* queue(q, 3); */
	/* dequeue(q); */
	/* display(q); */

}
