#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct sStack{
  int valor[MAX];
  int length;
  int top;
}Stack;

void push(Stack *s, int x);
int pop(Stack *s);
void show(Stack *s);
int is_empty(Stack *s);


