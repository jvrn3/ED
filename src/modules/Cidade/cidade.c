#include "cidade.h"
#include <float.h>
#include <string.h>

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

	return city;
}

KdTree insert_quadra(Cidade c, Quadra q, float point[2]){
	/* insert(c.lista_quadra, q, 0); */
	return kd_insert(c.arvore_quadra, q, point);
}
KdTree insert_hidrante(Cidade c, Hidrante h, float point[]){
	/* insert(c.lista_hidrante, h, 0); */
	return kd_insert(c.arvore_hidrante, h, point);
}
KdTree insert_torre(Cidade c, Torre t, float point[]){
	/* insert(c.lista_torre, t, 0); */
	return kd_insert(c.arvore_torre, t, point);
}
KdTree insert_semaforo(Cidade c, Semaforo s, float point[]){
	/* insert(c.lista_semaforo, s, 0); */
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

Torre search_id_toxy(float x, float y, Torre t){
	Node *n;
	StTorre *st;
	for(n = getFirst(t); n != NULL; n = n->next){
		st = (StTorre *) n->data;
		if((x - st->x) < 0.1 && (y - st->y) < 0.1){
			return st;
		}

	}
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




KdTree deleteQuadraInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StQuadra *sq;
	Rect r2;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteQuadraInRect(r, kd->left, fTxt);
	kd->right = deleteQuadraInRect(r, kd->right, fTxt);
	sq = (StQuadra *) kd->data;
	r2 = createRect("", "", sq->larg, sq->alt, sq->x, sq->y); 
	if(isRectInsideRect(r2, r)){
		fprintf(fTxt, "CEP REMOVIDO %s\n", sq->cep);
		kd = remove_quadra(kd, kd->data, kd->point);
	}
	else
		return kd;
	free(r2);

	r2 = NULL;
	
	return kd;
}
KdTree deleteQuadraInCircle(Circle c, KdTree k, FILE *fTxt ){
	if(k == NULL)
		return NULL;
	StQuadra *sq;
	Rect r;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteQuadraInCircle(c, kd->right, fTxt);
	kd->right = deleteQuadraInCircle(c, kd->left, fTxt);
	sq = (StQuadra *) kd->data;
	r = createRect("", "", sq->larg, sq->alt, sq->x, sq->y); 
	if(isRectInsideCircle(c, r)){
		fprintf(fTxt, "CEP REMOVIDO %s\n", sq->cep);

		kd = remove_quadra(kd, kd->data, kd->point);
	}
	free(r);
	r = NULL;
	return kd;
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

KdTree deleteSemaforoInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StSemaforo *ss;
	Rect r2;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteSemaforoInRect(r, kd->left, fTxt);
	kd->right= deleteSemaforoInRect(r, kd->right, fTxt);
	ss = (StSemaforo *) kd->data;
	r2 = createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
	if(isRectInsideRect(r2, r)){
		fprintf(fTxt, "dle s %s\n", ss->id);
		kd = remove_semaforo(kd, kd->data, kd->point);
	}
	free(r2);
	r2 = NULL;
	return kd;
}

KdTree deleteSemaforoInCircle(Circle c, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StSemaforo *ss;
	Rect r;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteSemaforoInCircle(c, kd->left, fTxt);
	kd->right = deleteSemaforoInCircle(c, kd->right, fTxt);
	ss = (StSemaforo *) kd->data;
	r = createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
	if(isRectInsideCircle(c,r)){
		kd = remove_semaforo(kd, kd->data, kd->point);
		fprintf(fTxt, "Dle s %s\n", ss->id);
		
	}
	free(r);
	r = NULL;
	return kd;
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
KdTree deleteHidranteInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StHidrante *sh;
	Circle c;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteHidranteInRect(r, kd->left, fTxt);
	kd->right = deleteHidranteInRect(r, kd->right, fTxt);
	sh = (StHidrante *) kd->data;
	c = createCircle(sh->strk, sh->fill, 10,sh->x, sh->y );
	if(isCircleInsideRect(c, r)){
		fprintf(fTxt, "dle h %s\n", sh->id);
		kd = remove_hidrante(kd, kd->data, kd->point);
	}
	free(c);
	c = NULL;
	return kd;
}

KdTree deleteHidranteInCircle(Circle c, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StHidrante *sh;
	Circle c2;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteHidranteInCircle(c, kd->left, fTxt);
	kd->right = deleteHidranteInCircle(c, kd->right, fTxt);
	sh = (StHidrante *) kd->data;
	c2 = createCircle(sh->strk, sh->fill, 10,sh->x, sh->y );
	if(isCircleInsideCircle(c2, c)){
		fprintf(fTxt, "Dle h %s\n", sh->id);
		kd =remove_hidrante(kd, kd->data, kd->point);
	}
	free(c2);
	c2 = NULL;
	return kd;
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
KdTree deleteTorreInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StTorre *st;
	Circle c;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteTorreInRect(r, kd->left, fTxt);
	kd->right = deleteTorreInRect(r, kd->right, fTxt);
	st = (StTorre *) kd->data;
	c = createCircle(st->strk, st->fill, 10, st->x, st->y);
	if(isCircleInsideRect(c, r)){
		fprintf(fTxt, "dle t %s\n", st->id);
		kd = remove_torre(kd, kd->data, kd->point);
	}
	free(c);
	c = NULL;
	return kd;
}
KdTree deleteTorreInCircle(Circle c, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StTorre *st;
	Circle c2;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteTorreInCircle(c, kd->left, fTxt);
	kd->right = deleteTorreInCircle(c, kd->right, fTxt);
	st = (StTorre *) kd->data;
	c2 = createCircle(st->strk, st->fill, 10, st->x, st->y);
	if(isCircleInsideCircle(c2, c)){
		fprintf(fTxt, "Dle t %s\n", st->id);
		kd = remove_torre(kd, kd->data, kd->point);
	}

	free(c2);
	c2 = NULL;
	return kd;
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
	
}

void traverseTreeQuadra(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	if(kd == NULL)
		return;

	KdNode *knode = (KdNode *)kd;
	StQuadra *sq = (StQuadra *) knode->data;
	func(f, sq);
	if(knode->left != NULL)
		traverseTreeQuadra(knode->left, func, f);
	if(knode->right != NULL )
		traverseTreeQuadra(knode->right, func, f);

}
void traverseTreeSemaforo(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	KdNode *knode = (KdNode *)kd;
	if(knode != NULL){
		StSemaforo *sq = (StSemaforo *) knode->data;
		if(sq != NULL)
			func(f, sq);

		if(knode->left != NULL)
			traverseTreeSemaforo(knode->left, func, f);
		if(knode->right != NULL )
			traverseTreeSemaforo(knode->right, func, f);
	}

}
void traverseTreeTorre(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	KdNode *knode = (KdNode *)kd;
	if(knode != NULL){
		StTorre *sq = (StTorre *) knode->data;
		if(sq != NULL)
			func(f, sq);

		if(knode->left != NULL)
			traverseTreeTorre(knode->left, func, f);
		if(knode->right != NULL )
			traverseTreeTorre(knode->right, func, f);
	}

}
void traverseTreeHidrante(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	KdNode *knode = (KdNode *)kd;
	if(knode != NULL){
		StHidrante *sq = (StHidrante *) knode->data;
		if(sq != NULL)
			func(f, sq);

		if(knode->left != NULL)
			traverseTreeHidrante(knode->left, func, f);
		if(knode->right != NULL )
			traverseTreeHidrante(knode->right, func, f);
	}

}

void nn_aux(float a[], KdTree k, float *best){
	if(k == NULL)
		return;
	KdNode *kd = (KdNode *) k;
	StTorre *st = (StTorre *) kd->data;
	float b[] = {st->x, st->y};
	float dist = distancePoints(a, b);
	if(dist < *best){
		*best = dist;
	}

	if(kd->left != NULL && kd->right != NULL){
		StTorre *st2 = (StTorre* ) kd->left->data;
		float c[] = {st2->x, st2->y};
		StTorre *st3 = (StTorre* ) kd->right->data;
		float d[] = {st3->x, st3->y};
		if(distancePoints(a, c) < distancePoints(a, d)){
			nn_aux(a, kd->left, best);
		}
		else
			nn_aux(a, kd->right, best);
	}
	if(kd->left == NULL && kd->right != NULL)
		nn_aux(a, kd->right, best);
	if(kd->left != NULL && kd->right == NULL)
		nn_aux(a, kd->left, best);

	if(kd->right == NULL && kd->left == NULL){
		printf("%lf\n", dist);
	
	}

}
void nn(KdTree k){
	KdNode *kd = (KdNode *)k;
	StTorre *st = (StTorre *) kd->data;
	float a[] = {st->x, st->y};
	float best_dist = FLT_MAX;
	nn_aux(a, k, &best_dist);
}
