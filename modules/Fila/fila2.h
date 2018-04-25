#include <stdio.h>
#include <stdlib.h>

typedef void *Fila;

/* 
 * Queue is a FIFO data structure 
 *
 *
 * */
Fila createFila();

Fila enQueue(Fila f, void *data);

void display(Fila f);

Fila deQueue(Fila f);

int empty(Fila f);
