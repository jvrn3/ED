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

Torre remove_torre(Cidade c, Torre t){
	return del(c.lista_torre, t);
}
Semaforo remove_semaforo(Cidade c, Semaforo s){
	return del(c.lista_semaforo, s);
}
//could return the cep position and then use get function to access it
Quadra search_cep(char *cep, Cidade c){
	Lista ss = c.lista_quadra;
	int n = length(ss)-1;
	for(int i = 0; i < n; i++){
		StQuadra *sq = (StQuadra *) get(ss, 0);
		if(strcmp(sq->cep, cep) == 0){
			return sq;
		}

		ss = pop(ss);
	}
	return NULL;
}
Semaforo search_id_sem(char *id, Cidade c){
	Lista s = c.lista_semaforo;
	int n = length(s) -1;
	for(int i = 0; i < n; i++){
		StSemaforo *ss = (StSemaforo *) get(s, 0);
		if(strcmp(ss->id, id) == 0){
			return ss;
	}
		s = pop(s);

	}

	return NULL;
}
Hidrante search_id_hi(char *id, Cidade c){
	Lista s = c.lista_hidrante;
	int n = length(s) -1;
	for(int i = 0; i < n; i ++){
		StHidrante *sh = (StHidrante *) get(s, 0);
		if(strcmp(sh->id, id) == 0)
			return sh;
		s = pop(s);
	}
	return NULL;
}
Torre search_id_to(char *id, Cidade c){
	Lista s = c.lista_torre;
	int n = length(s) -1;
	for(int i =0; i < n; i++){
		StTorre *st = (StTorre *) get(s, 0);
		if(strcmp(st->id, id) == 0)
			return st;
		s = pop(s);
	}
	return NULL;
}
