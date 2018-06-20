#include "cidade.h"
#include <string.h>


Cidade createCity(){
	Cidade city;
	Quadra q = (Quadra *)createList();
	Hidrante h = (Hidrante *) createList();

	Semaforo s = (Semaforo *) createList();

	city.lista_quadra = q;
	city.lista_hidrante = h;
	city.lista_semaforo = s;
	return city;
}


Cidade  insert_quadra(Cidade c,Quadra q){
	c.lista_quadra = insert(c.lista_quadra, q, 0);
	return c;
}
Cidade insert_hidrante(Cidade c, Hidrante h){
	c.lista_hidrante = insert(c.lista_hidrante, h, 0);
	return c;

}
Cidade insert_semaforo(Cidade c, Semaforo s){
	c.lista_semaforo = insert(c.lista_semaforo, s, 0);
	return c;
}
Cidade insert_torre(Cidade c, Torre t){
	c.lista_torre = insert(c.lista_torre, t, 0);
	return c;
}

void remove_quadra(Cidade c, Quadra q){
	del(c.lista_quadra, q);
}
Hidrante remove_hidrante(Cidade c, Hidrante h){
	return del(c.lista_hidrante, h);
}
Torre remove_torre(Cidade c, Torre t){
	return del(c.lista_torre, t);
}
Semaforo remove_semaforo(Cidade c, Semaforo s){
	return del(c.lista_semaforo, s);
}
Quadra search_cep(char *cep, Cidade c){
	Node *s = (Node *)c.lista_quadra;
	int i = 0;
	while(s->next != NULL){
		StQuadra *sq = (StQuadra *) get(c.lista_quadra, i);
		if(strcmp(sq->cep, cep) == 0){
			return sq;
		}
		else
			s = s->next;
	i++;
	}
	return NULL;
}
void *search_id(char *id, Cidade c){

}
