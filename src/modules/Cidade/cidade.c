#include "cidade.h"
#include <float.h>
#include <string.h>


//Inicializa tudo da cidade
Cidade createCity(){
	Cidade city;

	city.lista_quadra = createList();
	city.lista_hidrante = createList();
	city.lista_semaforo = createList();
	city.lista_torre = createList();


	city.arvore_quadra = NULL;
	city.arvore_semaforo = NULL;
	city.arvore_hidrante = NULL;
	city.arvore_torre = NULL;

	city.comercio = new_hash_table();
	city.pessoas = new_hash_table();
	city.moradores = new_hash_table();
	city.tipo_comercio = new_hash_table();
	city.cep_quadra = new_hash_table();

	city.mor = createList();
	city.est = createList();
	city.mortos = createList();
	city.mud = createList();
	city.mudec = createList();
	return city;
}
Ponto hmp(Hidrante h){
	StHidrante *sh = (StHidrante *) h;
	return createPonto(sh->x, sh->y);
}
Ponto tmp(Torre t){
	StTorre *st = (StTorre *) t;
	return createPonto(st->x, st->y);
}
Ponto city_get_ponto(Cidade c, Address a){
	Quadra q = search(c.cep_quadra, address_get_cep(a));
	if(q == NULL){
		printf("Quadra com o cep %s nao encontrada\n", address_get_cep(a));
		exit(-1);
	}
	char face = address_get_face(a);
	int num = address_get_num(a);
	double x, y;
	if(face == 'S' || face == 's'){
		x = quadra_get_x(q) + num;
		y = quadra_get_y(q);
	}
	else if(face == 'N' || face == 'n'){
		x = quadra_get_x(q) + num;
		y = quadra_get_y(q) + quadra_get_h(q);
	}
	else if (face == 'O' || face == 'o'){
		x = quadra_get_x(q) + quadra_get_w(q);
		y = quadra_get_y(q) + num;
	}
	else{
		x = quadra_get_x(q);
		y = quadra_get_y(q) + num;
	}
	Ponto p = createPonto(x,y);
	return p;
}
Comercio searchComercioTipo(Hash h, char *key){
	StComercioTipo *sct = (StComercioTipo *) search(h, key);
	if(sct == NULL){
		printf("Tipo nao encontrado\n");
		return NULL;
	}
	return sct;
}
Pessoa searchPessoa(Hash h, char *key){
	StPessoa *sp= (StPessoa *) search(h, key);
	if(sp == NULL){
		printf("Pessoa nao encontrada ");
		return NULL;
	}
	return sp;
}
Quadra searchQuadra(Hash h, char *key){
	StQuadra *sq = (StQuadra *) search(h, key);
	if(sq == NULL){
		printf("Cep nao encontrado\n");
		return NULL;
	}
	return sq;
}
Comercio searchComercio(Hash h, char *key){
	StComercio *sc = (StComercio *) search(h, key);
	if(sc == NULL){
		printf("Comercio nao encontrado\n");
		return NULL;
	}
	return sc;
}
Morador searchMorador(Hash h, char *key){
	StMorador *sm = (StMorador *) search(h, key);
	if(sm == NULL){
		return NULL;
	}
	return sm;
}
char *get_sexo(Pessoa p){
	StPessoa *sp = (StPessoa *) p;
	if(sp->sexo == 'm' || sp->sexo == 'M')
		return "Masculino";
	else
		return "Feminino";
}
int _compareCodtEstblc(void *h, void *k){
	HashData *hd= (HashData *) h;
	char *key = (char *) k;
	char *codt = estabelecimento_get_codt(hd->data);
	if(strcmp(codt, key) == 0)
		return 1;
	
	else
		return 0;
}
int _compareCepMorador(void *h, void *k){
	HashData *hd = (HashData *) h;
	char *key = (char *) k;
	char *morador_cep  = morador_get_cep(hd->data);

	if(strcmp(morador_cep, key) == 0)
		return 1;
	else
		return 0;
}
int _compareCepEstblcmto(void *h, void *k){
	HashData *hd = (HashData *) h;
	char *key = (char *) k;
	char *estabelecimento_cep = estabelecimento_get_cep(hd->data);
	if(strcmp(estabelecimento_cep, key) == 0)
		return 1;
	else
		return 0;
}
void _hashSearchEstblcInRect(Cidade c, Rect r, FILE *fTxt){
	HashTable *ht = (HashTable *) c.comercio;
	Node *n;
	fprintf(fTxt, "\n---- Estabelecimentos dentro do retangulo ----\n");
	for(int i = 0; i < get_hash_max(); i++){
		if(ht->table[i] != NULL){
			for(n = getFirst(ht->table[i]); n != NULL; n = n->next){
				HashData *hd = (HashData *) n->data;
				StComercio *sc  = (StComercio *) hd->data;
				Ponto p = city_get_ponto(c, sc->address);
				if(isInsideR(r, p.x, p.y)){
					fprintf(fTxt, "Nome => %s\nEndereco => %s/%c/%d\n",
								sc->nome,
								estabelecimento_get_cep(sc),
								estabelecimento_get_face(sc),
								estabelecimento_get_num(sc));
				}
			}
		}
	}
}
void _hashRemoveEstblcInRect(Cidade c, Rect r, FILE *fTxt){
	HashTable *ht = (HashTable *) c.comercio;
	Node *n;
	Lista list_cnpj = createList();
	fprintf(fTxt, "\n----Estabelecimentos desapropriados ----\n");
	for(int i = 0; i < get_hash_max(); i++){
		if(ht->table[i] != NULL){
			for(n = getFirst(ht->table[i]); n != NULL; n = n->next){
				HashData *hd = (HashData *) n->data;
				StComercio *sc = (StComercio *) hd->data;
				Ponto p = city_get_ponto(c, sc->address);
				if(isInsideR(r, p.x, p.y)){
					fprintf(fTxt, "Nome => %s\nEndereco => %s/%c/%d\n",
							sc->nome,
							estabelecimento_get_cep(sc),
							estabelecimento_get_face(sc),
							estabelecimento_get_num(sc));
					char cnpj[50];
					strcpy(cnpj, sc->cnpj);
					insert(list_cnpj, cnpj, 0);
				}
			}
		}
	}
	for(n = getFirst(list_cnpj); n != NULL; n = n->next){
		void *d = remove_hash(ht, n->data);
		free(d);
	}
	destroyList(list_cnpj);

}
void _hashRemoveMoradorInRect(Cidade c, Rect r, FILE *fTxt){
	HashTable *ht = (HashTable *) c.moradores;
	Node *n;
	fprintf(fTxt, "\n----Moradores Desapropriados ----\n");
	Lista list_cpf = createList();
	for(int i = 0; i < get_hash_max(); i++){
		if(ht->table[i] != NULL){
			for(n = getFirst(ht->table[i]); n != NULL; n = n->next){
				HashData *hd = (HashData *) n->data;
				StMorador *sm = (StMorador *) hd->data;
				Ponto p = city_get_ponto(c, sm->addr);
				if(isInsideR(r, p.x, p.y)){
					fprintf(fTxt, "Morador com o cpf %s removido",
							sm->cpf
						   );
					char cpf[50];
					strcpy(cpf, sm->cpf);
					insert(list_cpf, cpf, 0);
				}
			}
		}
	}
	for(n = getFirst(list_cpf); n != NULL; n = n->next){
		void *d = remove_hash(ht, n->data);
		free(d);
	}
	destroyList(list_cpf);

}
void _hashSearchTipoInRect(Cidade c, Rect r, char *key, FILE *fTxt){
	HashTable *ht = (HashTable *) c.comercio;
	Node *n;
	fprintf(fTxt, "\n---- Estabelecimentos do tipo %s dentro do retangulo ----\n", key);
	for(int i = 0; i < get_hash_max(); i++){
		if(ht->table[i] != NULL){
			for(n = getFirst(ht->table[i]); n != NULL; n = n->next){
				HashData *hd = (HashData *) n->data;
				StComercio *sc = (StComercio *) hd->data;
				//se codt == codt pesquisado, entao
				if(strcmp(key, sc->codt) == 0){
					Ponto p = city_get_ponto(c, sc->address);
					if(isInsideR(r, p.x, p.y)){
						fprintf(fTxt, "Nome => %s\nEndereco => %s/%c/%d\n",
								sc->nome,
								estabelecimento_get_cep(sc),
								estabelecimento_get_face(sc),
								estabelecimento_get_num(sc));
					}
				}

			}
		}
	
	}
}
void _hashSearchQuadraInRect(Cidade c, Rect r, FILE *fTxt){
	HashTable *ht = (HashTable *) c.moradores;
	StQuadra *sq;
	Node *n;
	char *quadra;
	fprintf(fTxt, "\n---- Moradores dentro do retangulo ---- \n");

	for(int i = 0; i < get_hash_max(); i++){
		if(ht->table[i] != NULL){
			for(n = getFirst(ht->table[i]); n != NULL; n = n->next){
				HashData *hd = (HashData *) n->data;
				quadra = morador_get_cep(hd->data);
				sq = searchQuadra(c.cep_quadra, quadra);
				if(sq != NULL){
					Rect r2 = createRect("", "", sq->larg, sq->alt, sq->x, sq->y);
					if(isRectInsideRect(r2, r)){
						StPessoa *sp = (StPessoa *)search(c.pessoas, hd->key);
						fprintf(fTxt, "Nome %s %s\n", sp->nome, sp->sobrenome);
						fprintf(fTxt, "Endereco %s/%c/%d\n", morador_get_cep(hd->data), 
								morador_get_face(hd->data), 
								morador_get_num(hd->data));
					}
					free(r2);

				}
			}
		}
	}
}
KdTree insert_quadra(Cidade c, Quadra q, float point[2]){
	return kd_insert(c.arvore_quadra, q, point);
}
KdTree insert_hidrante(Cidade c, Hidrante h, float point[]){
	return kd_insert(c.arvore_hidrante, h, point);
}
KdTree insert_torre(Cidade c, Torre t, float point[]){
	return kd_insert(c.arvore_torre, t, point);
}
KdTree insert_semaforo(Cidade c, Semaforo s, float point[]){
	return kd_insert(c.arvore_semaforo, s, point);
}

Quadra search_cep(char *cep, KdTree kd_quadra){
	if(kd_quadra != NULL){
		KdNode *kd = (KdNode *) kd_quadra;
		StQuadra *sq = (StQuadra *) kd->data;
		if(strcmp(cep, sq->cep) == 0){
			return sq;
		}
		else{
			StQuadra *found = search_cep(cep, kd->left);
			if(found == NULL)
				found = search_cep(cep, kd->right);

			return found;
		}
	}
	else
		return NULL;
}
Semaforo search_id_sem(char *id, KdTree kd_sem){
	if(kd_sem != NULL){
		KdNode *kd = (KdNode *) kd_sem;
		StSemaforo *ss = (StSemaforo *) kd->data;
		if(strcmp(id, ss->id) == 0)
			return ss;
		else{
			StSemaforo *found = search_id_sem(id, kd->left);
			if(found == NULL)
				found = search_id_sem(id, kd->right);

			return found;
		}
	}
	else
		return NULL;
}
Hidrante search_id_hi(char *id, KdTree kd_hi){
	if(kd_hi != NULL){
		KdNode *kd = (KdNode *) kd_hi;
		StHidrante *sh = (StHidrante *) kd->data;

		if(strcmp(id, sh->id) == 0)
			return sh;
		else{
			StHidrante *found = search_id_hi(id, kd->left);

			if(found == NULL)
				found = search_id_hi(id, kd->right);

		return found;
		}
	}
	else
		return NULL;
}
Torre search_id_to(char *id, KdTree kd_to){
	if(kd_to != NULL){
		KdNode *kd = (KdNode *) kd_to;
		StTorre *st = (StTorre *) kd->data;

		if(strcmp(id, st->id) == 0)
			return st;
		else{
			StTorre *found = search_id_to(id, kd->left);

			if(found == NULL)
				found = search_id_to(id, kd->right);

			return found;
		}
	}
	else
		return NULL;
}
KdTree remove_quadra(KdTree t, Quadra q, float point[]){
	return delete_kd_node(t, q, point, 0);
}
KdTree remove_hidrante(KdTree t, Hidrante h, float point[]){
	return delete_kd_node(t, h, point, 0);
}
KdTree remove_semaforo(KdTree t, Semaforo s, float point[]){
	return delete_kd_node(t, s, point, 0);
}
KdTree remove_torre(KdTree t, Torre to, float point[]){
	return delete_kd_node(t, to, point, 0);
}
//this kind of search should be implemented using range search algorithm
void searchQuadraInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return;
	StQuadra *sq;
	Rect r2;
	KdNode *kd = (KdNode *) k;
	searchQuadraInRect(r, kd->left, fTxt);
	searchQuadraInRect(r, kd->right, fTxt);
	sq = (StQuadra *) kd->data;
	r2 = createRect("", "", sq->larg, sq->alt, sq->x, sq->y); 

	if(isRectInsideRect(r2, r)){
		fprintf(fTxt, "Quadra Cep=%s Fill=%s Stroke=%s X=%lf Y=%lf W=%lf H=%lf\n",
			sq->cep,
			sq->fill,
			sq->strk, 
			sq->x,
			sq->y,
			sq->larg,
			sq->alt);
	}
	free(r2);
	r2 = NULL;
}
void searchQuadraInCircle(Circle c, KdTree k, FILE *fTxt){
	if(k == NULL)
		return;
	StQuadra *sq;
	Rect r;
	KdNode *kd = (KdNode *) k;
	searchQuadraInCircle(c, kd->left, fTxt);
	searchQuadraInCircle(c, kd->right, fTxt);
	sq = (StQuadra *) kd->data;
	r = createRect("", "", sq->larg, sq->alt, sq->x, sq->y); 
	if(isRectInsideCircle(c, r)){
		fprintf(fTxt, "Quadra Cep=%s Fill=%s Stroke=%s X=%lf Y=%lf W=%lf H=%lf\n",
				sq->cep,
				sq->fill,
				sq->strk, 
				sq->x,
				sq->y,
				sq->larg,
				sq->alt);

	}
	free(r);
	r = NULL;
}
void file_quadra_d(Quadra q, FILE *fTxt){
	StQuadra *sq = (StQuadra *) q;
	fprintf(fTxt, "CEP REMOVIDO %s\n", sq->cep);
}
void file_semaforo_d(Semaforo s, FILE *fTxt){
	StSemaforo *ss = (StSemaforo *) s;
	fprintf(fTxt, "SEMAFORO %s REMOVIDO\n",ss->id);
}
void file_hidrante_d(Hidrante h, FILE *fTxt){
	StHidrante *sh = (StHidrante *)h;
	fprintf(fTxt, "HIDRANTE %s REMOVIDO\n", sh->id);
}
void file_torre_d(Torre t, FILE *fTxt){
	StTorre *st = (StTorre *) t;
	fprintf(fTxt, "TORRE %s REMOVIDA", st->id);
}
void deleteQuadraInRect(Rect r, KdTree k, FILE *fTxt){
	kd_remove(k, isQuadraInsideRect, r, file_quadra_d, fTxt);
}
void deleteQuadraInCircle(Circle c, KdTree k, FILE *fTxt ){
	kd_remove(k, isQuadraInsideCircle, c, file_quadra_d, fTxt);
}
void searchSemaforoInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return;
	StSemaforo *ss;
	Rect r2;
	KdNode *kd = (KdNode *) k;
	searchSemaforoInRect(r, kd->left, fTxt);
	searchSemaforoInRect(r, kd->right, fTxt);
	ss = (StSemaforo *) kd->data;
	r2 = createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
	if(isRectInsideRect(r2, r)){
		fprintf(fTxt, "Semaforo ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n",
				ss->id,
				ss->fill,
				ss->strk, 
				ss->x,
				ss->y);
	}
	free(r2);
	r2 = NULL;
}
void searchSemaforoInCircle(Circle c, KdTree k, FILE *fTxt){
	if(k == NULL)
		return;
	StSemaforo *ss;
	Rect r;
	KdNode *kd = (KdNode *) k;
	searchSemaforoInCircle(c, kd->left, fTxt);
	searchSemaforoInCircle(c, kd->right, fTxt);

	ss = (StSemaforo *) kd->data;
	r = createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
	if(isRectInsideCircle(c,r)){
		fprintf(fTxt, "Semaforo ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n",
				ss->id,
				ss->fill,
				ss->strk, 
				ss->x,
				ss->y);
	}
	free(r);
}

void deleteSemaforoInRect(Rect r, KdTree k, FILE *fTxt){
	kd_remove(k, isSemaforoInsideRect, r, file_semaforo_d, fTxt);
}

void deleteSemaforoInCircle(Circle c, KdTree k, FILE *fTxt){
	kd_remove(k, isSemaforoInsideCircle, c, file_semaforo_d, fTxt);
}
void searchHidranteInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return;
	StHidrante *sh;
	Circle c;
	KdNode *kd = (KdNode *) k;
	searchHidranteInRect(r, kd->left, fTxt);
	searchHidranteInRect(r, kd->right, fTxt);
	sh = (StHidrante *) kd->data;
	c = createCircle(sh->strk, sh->fill, 10,sh->x, sh->y );
	if(isCircleInsideRect(c, r)){
		fprintf(fTxt, "Hidrante ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
				sh->id,
				sh->fill,
				sh->strk,
				sh->x,
				sh->y
			   );

	}
	free(c);
}
void searchHidranteInCircle(Circle c, KdTree k, FILE *fTxt){
	if(k == NULL)
		return;
	StHidrante *sh;
	Circle c2;
	KdNode *kd = (KdNode *) k;
	searchHidranteInCircle(c, kd->left, fTxt);
	searchHidranteInCircle(c, kd->right, fTxt);
	sh = (StHidrante *) kd->data;
	c2 = createCircle(sh->strk, sh->fill, 10,sh->x, sh->y );
	if(isCircleInsideCircle(c2, c)){
		fprintf(fTxt, "Hidrante ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
				sh->id,
				sh->fill,
				sh->strk,
				sh->x,
				sh->y
				);
	}
	free(c2);

}
void deleteHidranteInRect(Rect r, KdTree k, FILE *fTxt){
	kd_remove(k, isHidranteInsideRect, r, file_hidrante_d, fTxt);
}

void deleteHidranteInCircle(Circle c, KdTree k, FILE *fTxt){
	kd_remove(k, isHidranteInsideCircle, c, file_hidrante_d, fTxt);
}
void searchTorreInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return;
	StTorre *st;
	Circle c;
	KdNode *kd = (KdNode *) k;

	searchTorreInRect(r, kd->left, fTxt);
	searchTorreInRect(r, kd->right, fTxt);

	st = (StTorre *) kd->data;
	c = createCircle(st->strk, st->fill, 10, st->x, st->y);
	if(isCircleInsideRect(c, r)){
		fprintf(fTxt, "Torre ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
				st->id,
				st->fill,
				st->strk,
				st->x,
				st->y
			   );
	}
	free(c);
}
void searchTorreInCircle(Circle c, KdTree k, FILE *fTxt){
	if(k == NULL)
		return;
	StTorre *st;
	Circle c2;
	KdNode *kd = (KdNode *) k;
	searchTorreInCircle(c, kd->left, fTxt);
	searchTorreInCircle(c, kd->right, fTxt);
	st = (StTorre *) kd->data;
	c2 = createCircle(st->strk, st->fill, 10, st->x, st->y);
	if(isCircleInsideCircle(c2, c)){
		fprintf(fTxt, "Torre ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
				st->id,
				st->fill,
				st->strk,
				st->x,
				st->y
			   );
	}
	free(c2);
}
void deleteTorreInRect(Rect r, KdTree k, FILE *fTxt){
	kd_remove(k, isTorreInsideRect, r, file_torre_d, fTxt);
}
void deleteTorreInCircle(Circle c, KdTree k, FILE *fTxt){
	kd_remove(k, isTorreInsideCircle, c, file_torre_d, fTxt);
}
void free_cidade(Cidade c){
	destroy(c.lista_hidrante);
	destroy(c.lista_quadra);
	destroy(c.lista_semaforo);
	destroy(c.lista_torre);
	destroyTree(c.arvore_quadra);
	destroyTree(c.arvore_hidrante);
	destroyTree(c.arvore_torre);
	destroyTree(c.arvore_semaforo);
	delete_hash_table(c.tipo_comercio, free);
	delete_hash_table(c.moradores, free_morador);
	delete_hash_table(c.pessoas, free);
	delete_hash_table(c.cep_quadra, free);
	delete_hash_table(c.comercio, free_comercio);
	destroy(c.mor);
	destroy(c.est);
	destroy(c.mudec);
	destroy(c.mud);
	destroy(c.mortos);
}
void traverseTreeQuadra(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	if(kd == NULL)
		return;
	KdNode *knode = (KdNode *)kd;
	StQuadra *sq = (StQuadra *) knode->data;
	if(knode->used != 0)
		func(f, sq);
	if(knode->left != NULL)
		traverseTreeQuadra(knode->left, func, f);
	if(knode->right != NULL )
		traverseTreeQuadra(knode->right, func, f);

}
void traverseTreeSemaforo(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	if(kd == NULL)
		return;
	KdNode *knode = (KdNode *)kd;
	StSemaforo *sq = (StSemaforo *) knode->data;
	if(knode->used != 0)
		func(f, sq);
	if(knode->left != NULL)
		traverseTreeSemaforo(knode->left, func, f);
	if(knode->right != NULL )
		traverseTreeSemaforo(knode->right, func, f);

}
void traverseTreeTorre(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	if(kd == NULL)
		return;
	KdNode *knode = (KdNode *)kd;
	StTorre *sq = (StTorre *) knode->data;
	if(knode->used != 0)
		func(f, sq);
	if(knode->left != NULL)
		traverseTreeTorre(knode->left, func, f);
	if(knode->right != NULL )
		traverseTreeTorre(knode->right, func, f);

}
void traverseTreeHidrante(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	if(kd == NULL)
		return;
	KdNode *knode = (KdNode *)kd;
	StHidrante *sq = (StHidrante *) knode->data;
	if(knode->used != 0)
		func(f, sq);
	if(knode->left != NULL)
		traverseTreeHidrante(knode->left, func, f);
	if(knode->right != NULL )
		traverseTreeHidrante(knode->right, func, f);
}

void printa_closest_torre(FILE *fSvg, FILE *fTxt, void *sa, void *sb, float dist){
	StTorre *a = (StTorre *) sa;
	StTorre *b = (StTorre *) sb;
	fprintf(fTxt, "\n----Torres mais proximas----\n");
	fprintf(fSvg, "<circle r=\"%.2lf\" cx=\"%.2f\" cy=\"%.2f\"  stroke=\"black\" fill-opacity=\"0\" stroke-dasharray=\"5,5\" stroke-width=\"3\"/>\n",
			15.0,
			a->x,
			a->y);
	fprintf(fSvg, "<circle r=\"%.2lf\" cx=\"%.2f\" cy=\"%.2f\"  stroke=\"black\" fill-opacity=\"0\" stroke-dasharray=\"5,5\" stroke-width=\"3\"/>\n",
			15.0,
			b->x,
			b->y);
	fprintf(fTxt, "IDs => %s | %s | Distancia %lf\n", 
			a->id,
			b->id,
			dist);
}
void printa_closest_given_radio(KdTree k, Ponto p, Ponto q, float dist, FILE *fSvg, FILE *fTxt){
	if(k == NULL)
		return;
	KdNode *kd = (KdNode *) k;
	float ponto[] = {q.x, q.y};
	StHidrante *sh = (StHidrante *) search_tree(k, ponto, 0);
	if(sh != NULL){
		StHidrante *sh = (StHidrante *) kd->data;
		fprintf(fTxt, "\n----HIDRANTE MAIS PROXIMO DA RADIO----\nID => %s | COR => %s | Distancia radio x hidrante %lf",sh->id, sh->fill, dist);
		drawLinePontilhado(fSvg, p, q);
	}
}
void printa_closest_given_p(KdTree k, Ponto p, Ponto q, float dist, FILE *fSvg, FILE *fTxt){
	if(k == NULL)
		return;
	float ponto[] = {q.x, q.y};
	StHidrante *sh = (StHidrante *) search_tree(k, ponto, 0);
	if(sh != NULL){
		fprintf(fTxt, "\n----HIDRANTE MAIS PROXIMO----\nID HIDRANTE => %s | COR =>%s | Distancia ponto x hidrante => %lf",sh->id, sh->fill, dist);
		drawLinePontilhado(fSvg, p, q);
		fprintf(fSvg, "<text x=\"%.2f\" y=\"%.2f\" fill=\"black\" font-size=\"12\">%s</text>\n", p.x, p.y, "X");
		
	}
}
int printa_closest(KdTree k, float dist, FILE *fSvg, FILE *fTxt, Ponto (*getPontos)(void *), void (*print_func)(FILE *, FILE *, void *, void *, float )){
	if(k == NULL)
		return -1;
	KdNode *kd = (KdNode *) k;
	Ponto a = getPontos(kd->data);
	if(kd->left != NULL){
		Ponto b = getPontos(kd->left->data);
		if(distancePoints(a, b) == dist){
				print_func(fSvg, fTxt, kd->data, kd->right->data, dist);
		}
		if(kd->right != NULL){
			Ponto c = getPontos(kd->right->data);
			if(distancePoints(a, c) == dist){
				print_func(fSvg, fTxt, kd->data, kd->right->data, dist);
				return 1;
			}
		}
		printa_closest(kd->left, dist, fSvg, fTxt, getPontos, print_func);
	}
	else if(kd->right != NULL){
		Ponto c = getPontos(kd->right->data);
		if(distancePoints(a, c) == dist){
			print_func(fSvg, fTxt, kd->data, kd->right->data, dist);
			return 1;
		}
		printa_closest(kd->right, dist, fSvg, fTxt, getPontos, print_func);
	}
	return 0;
}
int compareTorreId(Torre t, char *key){
	StTorre *st = (StTorre *) t;
	if(strcmp(st->id, key) == 0)
		return 1;
	return 0;
}
void desapropriar(Cidade city, Rect r, FILE *fTxt){
	deleteQuadraInRect(r, city.arvore_quadra, fTxt);
	deleteHidranteInRect(r, city.arvore_hidrante, fTxt);
	deleteSemaforoInRect(r, city.arvore_semaforo, fTxt);
	deleteTorreInRect(r, city.arvore_torre, fTxt);
	_hashRemoveEstblcInRect(city, r, fTxt);
	_hashRemoveMoradorInRect(city, r, fTxt);

}
void kill_pessoa(Cidade c, char *cpf, FILE *fTxt){
	StPessoa *sp = searchPessoa(c.pessoas, cpf);
	StMorador *sm = searchMorador(c.moradores, cpf);
	if(sp != NULL){
		if(sp->sexo == 'm' || sp->sexo == 'M')
			fprintf(fTxt, "RIP %s %s, portador %s, do sexo Masculino, nascido a %s\n",
					sp->nome, sp->sobrenome, sp->cpf, sp->nasc);
		else
			fprintf(fTxt, "RIP %s %s, portador %s, do sexo Feminino, nascida a %s\n",
					sp->nome, sp->sobrenome, sp->cpf, sp->nasc);

		remove_hash(c.pessoas, cpf);
	}
	if(sm != NULL){
		fprintf(fTxt, "Residia no endereco %s/%c/%d\n",
				morador_get_cep(sm),
				morador_get_face(sm),
				morador_get_num(sm));

		Ponto q = city_get_ponto(c, sm->addr);
		Ponto *p = malloc(sizeof(Ponto));
		p->x = q.x;
		p->y = q.y;
		insert(c.mortos, p, 0);
		remove_hash(c.moradores, cpf);
	}
}
void mudar_pessoa(Cidade c, char *cpf, Address novo, FILE *fTxt){
	StPessoa *sp = searchPessoa(c.pessoas, cpf);
	StMorador *sm = searchMorador(c.moradores, cpf);
	if(sp == NULL || sm == NULL)
		return;
	fprintf(fTxt, "\n----%s %s mudou ----\n",
			sp->nome, sp->sobrenome);
	fprintf(fTxt, "Antigo endereco => %s/%c/%d\n",
			morador_get_cep(sm),
			morador_get_face(sm),
			morador_get_num(sm));

	Ponto old = city_get_ponto(c, sm->addr);
	sm->addr = changeAddress(
			sm->addr,
			address_get_cep(novo),
			address_get_face(novo),
			address_get_num(novo),
			address_get_comp(novo));
	Ponto new = city_get_ponto(c, sm->addr);

	fprintf(fTxt, "Novo endereco => %s/%c/%d\n",
			morador_get_cep(sm),
			morador_get_face(sm),
			morador_get_num(sm));
	Ponto *old_new = malloc(sizeof(Ponto) * 2);
	old_new[0] = old;
	old_new[1] = new;
	insert(c.mud, old_new, 0);
}
void mudar_estbl(Cidade c, char *cnpj, Address novo, FILE *fTxt){
	StComercio *sc = searchComercio(c.comercio, cnpj);
	if(sc == NULL)
		return;
	fprintf(fTxt, "\n---- %s mudou---\n", sc->nome);
	fprintf(fTxt, "Antigo endereco => %s/%c/%d\n",
			estabelecimento_get_cep(sc),
			estabelecimento_get_face(sc),
			estabelecimento_get_num(sc));
	Ponto old = city_get_ponto(c, sc->address);
	sc->address = changeAddress(sc->address,
			address_get_cep(novo),
			address_get_face(novo), 
			address_get_num(novo), "");
	Ponto new = city_get_ponto(c, sc->address);
	fprintf(fTxt, "Novo endereco => %s/%c/%d\n",
			estabelecimento_get_cep(sc),
			estabelecimento_get_face(sc),
			estabelecimento_get_num(sc));

	Ponto *old_new = malloc(sizeof(Ponto) * 2);
	old_new[0] = old;
	old_new[1] = new;
	insert(c.mudec, old_new, 0);
}
void drawCidade(Cidade c, FILE *fSvgQry){
	traverseTreeQuadra(c.arvore_quadra, drawQuadra, fSvgQry);
	traverseTreeSemaforo(c.arvore_semaforo, drawSemaforo, fSvgQry);
	traverseTreeHidrante(c.arvore_hidrante, drawHidrante, fSvgQry);
	traverseTreeTorre(c.arvore_torre, drawTorre, fSvgQry);
	
	Node *n;
	for(n = getFirst(c.mor); n != NULL; n = n->next){
		StMorador *sm = (StMorador *)n->data;
		drawMorador(fSvgQry, city_get_ponto(c, sm->addr), sm->cpf);
	}
	for(n = getFirst(c.est); n != NULL; n = n->next){
		StComercio *sc = (StComercio *) n->data;
		drawEstabelecimento(fSvgQry, city_get_ponto(c, sc->address));
	}
	for(n = getFirst(c.mud); n != NULL; n = n->next){
		Ponto *p = n->data;
		drawLineMudanca(fSvgQry, p[0], p[1]);
	}
	for(n = getFirst(c.mudec); n != NULL; n = n->next){
		Ponto *p = n->data;
		drawLineMudancaEst(fSvgQry, p[0], p[1]);
	}
	for(n = getFirst(c.mortos); n != NULL; n = n->next){
		Ponto *p = n->data;
		drawCruz(fSvgQry, p[0]);
	}
}
