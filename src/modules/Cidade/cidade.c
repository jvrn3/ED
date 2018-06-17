#include "cidade.h"

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
	c.lista_quadra = del(c.lista_quadra, q);
}
