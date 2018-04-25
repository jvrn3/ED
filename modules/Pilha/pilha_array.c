#include "pilha.h"

Stack *create_stack(){
  Stack *s;
  s = malloc(sizeof(s) * MAX);
  s->length = 0;
  s->top = -1;
  return s;
}
void push(Stack *s, int x){
  if(s->length > MAX)
    printf("Stack full");
  else{
    s->top = x;
    s->valor[s->length++] = x;
    printf("Valor adicionado\n");
  }
}
int pop(Stack *s){
  if(s->top != -1){
    return s->valor[s->length--];
  }

}
void show(Stack *s){
  for(int i =0; i < s->length; i++){
    printf("%d\n", s->valor[i]);
  }
}
int is_empty(Stack *s){
  if(s->length == 0)
    return 1;
  else
    return 0;

}
int
main(){
  Stack *s = create_stack();
  push(s, 2);
  push(s, 3);
  push(s, 4);
  pop(s);
  show(s);

}
