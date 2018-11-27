#ifndef LIST_H
#define LIST_H
typedef void *Lista;
#include <stdio.h>
/* Uma lista ligada é uma coleção linear de dados. Cada elemento aponta para o próximo, até chegar ao final da lista(tail).
 *
 *Neste trabalho, é usado a Single Linked List, que só possuio o nó apontando para o head


 A estrutura lista ligada utilizada nesse trabalho possui alguns problemas que não afetam a funcionalidade nem a velocidade de processamentod ela. 

O primeiro é que não há encapsulamento da estrutura nó, que está localizada no arquivo .h


O segundo é que a função insert possui 3 argumentos, mas na maioria dos casos(95%), precisaria de apenas dois, pois o id nunca é usado. Foi usado apenas no trabalho 3;
 
 */
typedef struct node{
	void *data;
	int id;
	int len;
	struct node *next;
}Node;

Lista createList();

//retorna o tamanho da lista l;
int length(Lista l);

// Lista del_posicao(Lista l, int i);

//cria um nó 
Node *createNode(void *data, int id);

//Inserção. 
int insertAtEnd(Lista l, void *data);
int insert(Lista l, void *data, int id);
int insertAfter(Lista l, int pos, void *data, int id);

//int data é um boolean
Lista search_id(Lista l, int id, int data);
//dado uma lista L, retornar o elemento da posiçaõ pos

void *get(Lista l, int pos);

//deprecated
void display(Lista l, FILE *fname,  void (*f)(FILE *, void *));
void manipulate(Lista l, Lista l2, FILE *fname, void (*f) (FILE *, void *, void *));
void *pop(Lista l);

//deleta elemento de L a partir de data
Lista del(Lista l, void *data);

//n->next
Node *getNext(Lista l);

//busca a partir da função compare e retorna todos que satisfazem a condição
Lista searchList(Lista l, int (*compare)(void *, void *), void *comp);

//similar a searchList, porém deleta
void *search_del(Lista l, int (*compare)(void *, void *), void *comp);
//free list
void destroy(Lista l);

Node *getFirst(Lista l);

void *removeFirst(Lista l);
void *removeLast(Lista l);

int _structListSize();
//free list but do not remove data
void destroyList(Lista l);

//get node data;
Lista list_get_data(Lista l);
//get middle of a node
Node *list_get_middle(Lista l);

Node *reverse_list(Lista l);

Node *getLast(Lista l);
#endif
