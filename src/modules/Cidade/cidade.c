#include "cidade.h"

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


KdTree insert_quadra(Cidade c,Quadra q){
	/* insert(c.lista_quadra, q, 0); */
	return kd_insert(c.arvore_quadra, q, compareQuadraX, compareQuadraY);
}
KdTree insert_hidrante(Cidade c, Hidrante h){
	/* insert(c.lista_hidrante, h, 0); */
	return kd_insert(c.arvore_hidrante, h, compareHidranteX, compareHidranteY);
}
KdTree insert_torre(Cidade c, Torre t){
	/* insert(c.lista_torre, t, 0); */
	return kd_insert(c.arvore_torre, t, compareTorreX, compareTorreY);
}
KdTree insert_semaforo(Cidade c, Semaforo s){
	/* insert(c.lista_semaforo, s, 0); */
	return kd_insert(c.arvore_semaforo, s, compareSemaforoX, compareSemaforoY);
}
//could return the cep position and then use get function to access it
Quadra search_cep(char *cep, Cidade c){
	Node *n;
	StQuadra *sq;
	for(n = getFirst(c.lista_quadra); n != NULL; n = n->next){
		sq = (StQuadra *) n->data;
		if(strcmp(sq->cep, cep) == 0){
			return sq;
		}
	}
	return NULL;
	/* Lista ss = c.lista_quadra; */
	/* int n = length(ss)-1; */
	/* for(int i = 0; i < n; i++){ */
	/* 	StQuadra *sq = (StQuadra *) get(ss, 0); */
	/* 	if(strcmp(sq->cep, cep) == 0){ */
	/* 		return sq; */
	/* 	} */
  /*  */
	/* 	ss = pop(ss); */
	/* } */
	/* return NULL; */
}
Semaforo search_id_sem(char *id, Cidade c){
	Node *n; 
	StSemaforo *ss;
	for(n = getFirst(c.lista_semaforo); n != NULL; n = n->next){
		ss = (StSemaforo *) n->data;
		if(strcmp(ss->id, id) == 0){
			return ss;
		}
	}
	return NULL;
	/* Lista s = c.lista_semaforo; */
	/* int n = length(s) -1; */
	/* for(int i = 0; i < n; i++){ */
	/* 	StSemaforo *ss = (StSemaforo *) get(s, 0); */
	/* 	if(strcmp(ss->id, id) == 0){ */
	/* 		return ss; */
	/* } */
	/* 	s = pop(s); */
  /*  */
	/* } */
  /*  */
	/* return NULL; */
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
Hidrante search_id_hi(char *id, Cidade c){
	Node *n;
	StHidrante *sh;
	for(n = getFirst(c.lista_hidrante); n != NULL; n = n->next){
		sh = (StHidrante *) n->data;
		if(strcmp(sh->id, id) == 0){
			return sh;
		}
	}
	return NULL;
	/* Lista s = c.lista_hidrante; */
	/* int n = length(s) -1; */
	/* for(int i = 0; i < n; i ++){ */
	/* 	StHidrante *sh = (StHidrante *) get(s, 0); */
	/* 	if(strcmp(sh->id, id) == 0) */
	/* 		return sh; */
	/* 	s = pop(s); */
	/* } */
	/* return NULL; */
}
Torre search_id_to(char *id, Cidade c){
	Node *n;
	StTorre *st;
	for(n = getFirst(c.lista_torre); n != NULL; n = n->next){
		st = (StTorre *) n->data;
		if(strcmp(st->id, id) == 0){
			return st;
		}
	}
	return NULL;
	/* Lista s = c.lista_torre; */
	/* int n = length(s) -1; */
	/* for(int i =0; i < n; i++){ */
	/* 	StTorre *st = (StTorre *) get(s, 0); */
	/* 	if(strcmp(st->id, id) == 0) */
	/* 		return st; */
	/* 	s = pop(s); */
	/* } */
	/* return NULL; */
}
void rem_quadra( KdTree t, StQuadra *sq){
	/* lista_quadra = del(lista_quadra,sq);  */
	delete_kd_node(t, sq, quadraPointInX, quadraPointInY, 0);
}
void rem_hidrante(Lista lista_hidrante, StHidrante *sh){
	lista_hidrante = del(lista_hidrante, sh);
}
void rem_semaforo(Lista lista_semaforo, StSemaforo *ss){
	lista_semaforo = del(lista_semaforo, ss);
}
void rem_torre(Lista lista_torre, StTorre *st){
	lista_torre = del(lista_torre, st);

}
void searchOrDeleteQuadraInRect(Rect r, KdTree k, Lista lista_quadra, FILE *fTxt, int del){
	/* Node *n; */
	if(k != NULL){
		KdNode *kd = (KdNode *) k;
		if(kd->right)
			searchOrDeleteQuadraInRect(r, kd->right, lista_quadra, fTxt, del);
		if(kd->left)
			searchOrDeleteQuadraInRect(r, kd->left, lista_quadra, fTxt, del);

		StQuadra *sq;
		Rect r2;
		if(kd->data != NULL){
			sq = (StQuadra *) kd->data;
			r2 = createRect("", "", sq->larg, sq->alt, sq->x, sq->y); 
			if(isRectInsideRect(r2, r)){
				if(del == 1){
					fprintf(fTxt, "CEP REMOVIDO %s\n", sq->cep);
					printf("%s\n", sq->cep);
					/* rem_quadra(lista_quadra, sq); */
					/* rem_quadra(kd, sq); */
					k= delete_kd_node(k, kd->data, quadraPointInX, quadraPointInY, 0);

				}
				else{
					fprintf(fTxt, "Quadra Cep=%s Fill=%s Stroke=%s X=%lf Y=%lf W=%lf H=%lf\n",
							sq->cep,
							sq->fill,
							sq->strk, 
							sq->x,
							sq->y,
							sq->larg,
							sq->alt);
				}

			}

			free(r2);
			r2 = NULL;
		}


	}
	/* for(n = getFirst(lista_quadra); n != NULL; n = n->next){ */

	/* 	sq = (StQuadra *)n->data; */
	/* 	r2 = createRect("", "", sq->larg, sq->alt, sq->x, sq->y);  */
	/* 	if(isRectInsideRect(r2, r)){ */
	/* 		if(del == 1){ */
	/* 			fprintf(fTxt, "CEP REMOVIDO %s\n", sq->cep); */
	/* 			rem_quadra(lista_quadra, sq); */
	/* 		} */
	/* 		else{ */
	/* 			fprintf(fTxt, "Quadra Cep=%s Fill=%s Stroke=%s X=%lf Y=%lf W=%lf H=%lf\n", */
	/* 							sq->cep, */
	/* 							sq->fill, */
	/* 							sq->strk,  */
	/* 							sq->x, */
	/* 							sq->y, */
	/* 							sq->larg, */
	/* 							sq->alt); */
	/* 		} */
	/* 	} */
	/* 	free(r2); */
	/* 	r1 = NULL; */
	/* } */
}
void searchOrDeleteQuadraInCircle(Circle c, Lista lista_quadra, FILE *fTxt, int del){
	Node *n;
	StQuadra *sq;
	Rect r;
	for(n = getFirst(lista_quadra); n != NULL; n = n->next){
		sq = (StQuadra *)n->data;
		r = createRect("", "", sq->larg, sq->alt, sq->x, sq->y); 
		if(isRectInsideCircle(c, r)){
			if(del == 1){
				fprintf(fTxt, "CEP REMOVIDO %s\n", sq->cep);
				rem_quadra(lista_quadra, sq);
			}
			else{
				fprintf(fTxt, "Quadra Cep=%s Fill=%s Stroke=%s X=%lf Y=%lf W=%lf H=%lf\n",
						sq->cep,
						sq->fill,
						sq->strk, 
						sq->x,
						sq->y,
						sq->larg,
						sq->alt);
			}
		}
		free(r);
		r = NULL;
	}
}
void searchOrDeleteSemaforoInRect(Rect r, Lista lista_semaforo, FILE *fTxt, int del){
	Node *n;
	StSemaforo *ss;
	Rect r2;
	for(n = getFirst(lista_semaforo); n != NULL; n = n->next){
		ss = (StSemaforo *) n->data;
		r2 = createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
		if(isRectInsideRect(r2, r)){
			if(del == 1){
				rem_semaforo(lista_semaforo, ss);
				fprintf(fTxt, "dle s %s\n", ss->id);

			}
			else{
				fprintf(fTxt, "Semaforo ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n",
						ss->id,
						ss->fill,
						ss->strk, 
						ss->x,
						ss->y);
			}
		}
		free(r2);
		r2 = NULL;
	}
}
void searchOrDeleteSemaforoInCircle(Circle c, Lista lista_semaforo, FILE *fTxt, int del){
	Node *n;
	StSemaforo *ss;
	Rect r;
	for(n = getFirst(lista_semaforo); n != NULL; n = n->next){
		ss = (StSemaforo *) n->data;
		r = createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
		if(isRectInsideCircle(c,r)){
			if(del == 1){
				rem_semaforo(lista_semaforo, ss);
				fprintf(fTxt, "Dle s %s\n", ss->id);
			}
			else{
				fprintf(fTxt, "Semaforo ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n",
						ss->id,
						ss->fill,
						ss->strk, 
						ss->x,
						ss->y);
			}
		}
		free(r);
		r = NULL;
	}
}
void searchOrDeleteHidranteInRect(Rect r, Lista lista_hidrante, FILE *fTxt, int del){
	Node *n;
	StHidrante *sh;
	Circle c;
	for(n = getFirst(lista_hidrante); n != NULL; n = n->next){
		sh = (StHidrante *) n->data;
		c = createCircle(sh->strk, sh->fill, 10,sh->x, sh->y );
		if(isCircleInsideRect(c, r)){
			if(del == 1){
				rem_hidrante(lista_hidrante, sh);
				fprintf(fTxt, "dle h %s\n", sh->id);
			}
			else{
				fprintf(fTxt, "Hidrante ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
						sh->id,
						sh->fill,
						sh->strk,
						sh->x,
						sh->y
						);
			}
		}
		free(c);
		c = NULL;
	}
}
void searchOrDeleteHidranteInCircle(Circle c, Lista lista_hidrante, FILE *fTxt, int del){
	Node *n;
	StHidrante *sh;
	Circle c2;
	for(n = getFirst(lista_hidrante); n != NULL; n = n->next){
		sh = (StHidrante *) n->data;
		c2 = createCircle(sh->strk, sh->fill, 10,sh->x, sh->y );
		if(isCircleInsideCircle(c2, c)){
			if(del == 1){
				rem_hidrante(lista_hidrante, sh);
				fprintf(fTxt, "Dle h %s\n", sh->id);
			}
			else{
				fprintf(fTxt, "Hidrante ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
						sh->id,
						sh->fill,
						sh->strk,
						sh->x,
						sh->y
						);
			}
		}
		free(c2);
		c2 = NULL;
	}
}
void searchOrDeleteTorreInRect(Rect r, Lista lista_torre, FILE *fTxt, int del){
	Node *n;
	StTorre *st;
	Circle c;
	for(n = getFirst(lista_torre);  n != NULL; n = n->next){
        st = (StTorre *) n->data;
	c = createCircle(st->strk, st->fill, 10, st->x, st->y);
	  if(isCircleInsideRect(c, r)){
	    if(del == 1){
	        rem_torre(lista_torre, st);
	        fprintf(fTxt, "dle t %s\n", st->id);
	    }
			else{
				fprintf(fTxt, "Torre ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
						st->id,
						st->fill,
						st->strk,
						st->x,
						st->y
						);
			}
		}
		free(c);
		c = NULL;
	}
}

void searchOrDeleteTorreInCircle(Circle c, Lista lista_torre, FILE *fTxt, int del){
	Node *n;
	StTorre *st;
	Circle c2;
	for(n = getFirst(lista_torre);  n != NULL; n = n->next){
		st = (StTorre *) n->data;
		c2 = createCircle(st->strk, st->fill, 10, st->x, st->y);
		if(isCircleInsideCircle(c2, c)){
			if(del == 1){
				rem_torre(lista_torre, st);
				fprintf(fTxt, "Dle t %s\n", st->id);
			}
			else{
				fprintf(fTxt, "Torre ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
						st->id,
						st->fill,
						st->strk,
						st->x,
						st->y
						);
			}
		}
		free(c2);
		c2 = NULL;
	}
}

void free_cidade(Cidade c){
	destroy(c.lista_hidrante);
	destroy(c.lista_quadra);
	destroy(c.lista_semaforo);
	destroy(c.lista_torre);
}

void traverseTreeQuadra(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	KdNode *knode = (KdNode *)kd;
	if(knode != NULL){
		StQuadra *sq = (StQuadra *) knode->data;
		if(sq != NULL)
			func(f, sq);

		if(knode->left != NULL)
			traverseTreeQuadra(knode->left, func, f);
		if(knode->right != NULL )
			traverseTreeQuadra(knode->right, func, f);
	}


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
