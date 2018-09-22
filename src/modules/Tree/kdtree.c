#include "kdtree.h"
KdTree newKdTree(void *data, float point[]){
    KdTree kd = malloc(sizeof(KdNode));
    KdNode *n = (KdNode *) kd;
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    n->used = 1;
    copyPoint(n->point, point);
    return kd;
}
void copyPoint(float p[], float p2[]){
   for(int i = 0; i < 2;i++){
      p[i] = p2[i];
   }
}
KdTree kd_insert_aux(KdTree t, void *data, float point[2], int cd){
    KdNode *n = (KdNode *) t;
    if(n == NULL){
       return newKdTree(data, point);
    }
    if(point[cd] < n->point[cd]){
       n->left = kd_insert_aux(n->left, data, point, (cd + 1) % 2);
    }
    else{
       n->right = kd_insert_aux(n->right, data, point, (cd + 1) % 2);
    }
    return n;
}
KdTree kd_insert(KdTree kd, void *data, float point[2]){
   return kd_insert_aux(kd, data, point, 0);
}

KdTree minData(void *a,  void *b, void *c, int dim){
   KdNode *kMin = (KdNode *) a;
   KdNode *kb = (KdNode *) b;
   KdNode *kc = (KdNode *) c;

   if(kb->point[dim] < kMin->point[dim]){
      kMin = kb;
   }
   if(kc->point[dim] < kMin->point[dim]){
      kMin = kc;
   }
   return kMin;
}

//acha o menor valor a partir de um nó  
KdTree find_min_rec(KdTree kd, int d, int depth){
   KdNode *n = (KdNode *)  kd; 
   if(n == NULL)
      return NULL;
      
   int cd = d % 2;
   if(cd == d){
      if(n->left == NULL )
	 return n;
      else return find_min_rec(n->left, d, depth+1);
   }
   else{
      return minData(n,
	    find_min_rec(n->left, d, depth+1),
	    find_min_rec(n->right, d, depth+1), d);
   }
}
KdTree find_min(KdTree kd, int d){
   return find_min_rec(kd, d, 0);

}
int are_same(float pointA[], float pointB[]){
  for(int i = 0; i < 2; i++){
     if(pointA[i] != pointB[i])
	return 0;
  }
  return 1;
}

KdTree delete_kd_node(KdTree kd, void *data, float point[], int depth){
   if(kd == NULL){
      return NULL;
   }
   KdNode *n = (KdNode *) kd;
   int cd = depth % 2;
   if(are_same(n->point, point)){
      if(n->right != NULL){
	 KdNode *min = (KdNode *) find_min(n->right, cd);

	 n->data = min->data;
	 copyPoint(n->point, min->point);
	 n->right = (KdNode *) delete_kd_node(n->right, min->data, min->point, depth+1);
      }
      else if(n->left != NULL){
	 KdNode *min = (KdNode *) find_min(n->left, cd);
	 n->data = min->data;
	 copyPoint(n->point, min->point);
	 n->right = (KdNode *) delete_kd_node(n->left, min->data, min->point, depth+1);
	 n->left = NULL;
      }
      else{
	n = NULL;
	 return NULL;
      }
      return n;
   }
   else{
      if(point[cd] < n->point[cd]){
	 n->left = (KdNode *) delete_kd_node(n->left, data, point, depth+1);
      }
      else{
	 n->right = (KdNode *) delete_kd_node(n->right, data, point, depth+1);
      }
   }
   return n;
}
void kd_remove(KdTree k, int (*compr)(void *, void *), void *figura, void (*f_print)(void *, FILE *), FILE *fTxt){
  if(k == NULL)
    return;
  KdNode *kd = (KdNode *) k;
  //set used to 0 aka delete
  if(compr(kd->data, figura)){
    kd->used = 0;
    f_print(kd->data, fTxt);
  }
  kd_remove(kd->left, compr, figura, f_print, fTxt);
  kd_remove(kd->right, compr, figura, f_print, fTxt);
}
void *search_tree(KdTree k, float *p, int depth){
  if(k == NULL)
    return NULL;
  KdNode *kd = (KdNode *) k;
  if(are_same(p, kd->point)){
    return kd->data;
  }
  int cd = depth % 2;
  if(p[cd] < kd->point[cd])
    return search_tree(kd->left, p, depth+1);

  return search_tree(kd->right, p, depth+1);
}
void kd_search(KdTree k,Lista l, int(*cmpr)(void *, char*), char *key){
  if(k == NULL)
    return;
  KdNode *kd = (KdNode *) k;
  if(cmpr(kd->data, key)){
    insert(l, kd->data, 0);
  }
  //Quadra, key
  kd_search(kd->left, l, cmpr, key);
  kd_search(kd->right, l, cmpr, key);
}
void printInOrder(KdTree t, void (*displayFn)(void *)){
    KdNode *n = (KdNode *) t;
    if(n == NULL){
	printf("NULL\n");
	return;
    }
    if(n->left != NULL)
	printInOrder(n->left, displayFn);
    displayFn(n->data);
    if(n->right != NULL)
	printInOrder(n->right, displayFn);
}
void delete_kd_nodes(KdTree k){
  KdNode *kd = (KdNode *) k;
  if(k == NULL)
    return;
  free(kd->data);
  free(kd);
}
void destroyTree(KdTree k){
  KdNode *kd = (KdNode *) k;
  if(k == NULL)
    return ;
  destroyTree(kd->left);
  destroyTree(kd->right);
  free(kd->data);
  free(kd);
}
//nearest neighbor of a given point
void nn_aux(Ponto a, KdTree k, float *best, float a_float[], int i, Ponto (*getPontos)(void *), Ponto *best_ponto){
  if(k == NULL)
    return;
  KdNode *kd = (KdNode *) k;
  Ponto p_root = getPontos(kd->data);

  double d = distancePoints(p_root, a);
  double dx = kd->point[i] - a_float[i];
  double dx2 = dx * dx;

  if(d < *best){
    *best = d;
    *best_ponto = p_root;
  }
  if(!*best)
    return;
  i = i+1;
  if(i >= 2)
    i = 0;
  nn_aux(a, dx > 0? kd->left : kd->right, best, a_float, i, getPontos, best_ponto);
  if(dx2 >= *best)
    return;
  nn_aux(a, dx > 0? kd->right : kd->right, best, a_float, i,getPontos, best_ponto);
  /* if(k != NULL){ */
  /*  */
  /*   Ponto b = getPontos(kd->data); */
  /*   float dist = distancePoints(a, b); */
  /*   if(dist < *best && dist != 0){ */
  /* #<{(|     *best = dist; |)}># */
  /*   } */
    //determina qual nó está mais perto da raiz

    /* if(kd->left != NULL && kd->right != NULL){ */
    /*   Ponto c = getPontos(kd->left->data); */
    /*   Ponto d = getPontos(kd->right->data); */
    /*   if(distancePoints(a, c) < distancePoints(a, d)){ */
	/* if(distancePoints(a, c) < dist) */
	/*   *best = distancePoints(a,c); */
	/* nn_aux(a, kd->left, best, getPontos); */
    /*   } */
    /*   else{ */
	/* if(distancePoints(a,d) < dist) */
	/*   *best = distancePoints(a,d); */
	/* nn_aux(a, kd->right, best, getPontos); */
    /*   } */
    /* } */
    /* if(kd->left == NULL && kd->right != NULL) */
    /*   nn_aux(a, kd->right, best, getPontos); */
    /* else if(kd->left != NULL && kd->right == NULL) */
    /*   nn_aux(a, kd->left, best, getPontos); */
  /* } */
  /* return *best; */
}
float nn(KdTree k, Ponto a, Ponto (*getPontos)(void *), Ponto *best_ponto){
  /* KdNode *kd = (KdNode *)k; */
  float best_dist = FLT_MAX;
  float x[] = {a.x, a.y};
  nn_aux(a, k,&best_dist, x, 0, getPontos, best_ponto); 
  return best_dist;
}
float closest_aux(KdTree k, float *minor, Ponto (*getPoints)(void *), Ponto *best_ponto){
  if(k != NULL){
    KdNode *kd = (KdNode *) k;
    Ponto a = getPoints(kd->data);
    float d = nn(k, a, getPoints, best_ponto);
    if(d < *minor){
      *minor = d;
      *best_ponto = a;
    }
    if(kd->left != NULL){
      closest_aux(kd->left, minor, getPoints, best_ponto);
    }

    if(kd->right != NULL){
      closest_aux(kd->right, minor, getPoints, best_ponto);
    }
  }
  return *minor;
}
//closest points in a kd tree
float closest_kd(KdTree k, Ponto (*getPontos)(void *), Ponto *best_ponto){
	float m = FLT_MAX;
	return closest_aux(k, &m, getPontos, best_ponto);

}
