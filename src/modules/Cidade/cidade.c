#include "cidade.h"

Cidade createCity(){
	Cidade city;
	Quadra q = (Quadra *)createList();
	Hidrante h = (Hidrante *) createList();
	Semaforo s = (Semaforo *) createSemaforo();


	city.lista_quadra = q;
	city.lista_hidrante = h;
	city.lista_semaforo = s
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

