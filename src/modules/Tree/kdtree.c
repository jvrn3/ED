#include "kdtree.h"

typedef struct node{
    void *data;
     
    struct node *left;
    struct node *right;
    int height;
}Node;

KdTree newKdTree(void *data){
    KdTree kd = malloc(sizeof(Node));
    Node *n = (Node *) kd;
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;

    return kd;
}


KdTree kd_insert_aux(KdTree t, void *data, int(*comparePointX)(void *, void*), int (*comparePointY)(void *, void *), int depth){
    Node *n = (Node *) t;


    if(n == NULL)
	return newKdTree(data);

    if(depth % 2 == 0){
	if(comparePointX(data, n->data) == -1){
	    n->left = kd_insert_aux(n->left, data, comparePointX,comparePointY, depth + 1);
	}
	else{
	    n->right = kd_insert_aux(n->right, data, comparePointX, comparePointY, depth + 1);
	}
    }
    else if(depth % 2 == 1){
	if(comparePointY(data, n->data) == -1){
	    n->left = kd_insert_aux(n->left, data, comparePointX, comparePointY, depth + 1);
	}
	else{
	    n->right = kd_insert_aux(n->right, data, comparePointX, comparePointY, depth + 1);
	}
    
    }

    return n;
}
KdTree kd_insert(KdTree kd, void *data, int (comparePointX)(void *, void *), int (*comparePointY)(void *, void *)){
   return kd_insert_aux(kd, data, comparePointX, comparePointY, 0);
}
float min(float a, float b){
    if(a < b)
	return a;
    else
	return b;

}
KdTree minNode(KdTree a, KdTree b, KdTree  c, float (*point_in_d)(void *)){

    Node *na = (Node *) a;
    Node *nb = (Node *) b;
    Node *nc = (Node *) c;

    float fb, fc;
    Node *x = na;
    if(nb == NULL){
	printf("null");
	return NULL;
    }

    if(nb != NULL)
	fb = point_in_d(nb->data);
    if(nc != NULL)
	fc = point_in_d(nc->data);
    if(nb != NULL && fb < point_in_d(x->data))
	x = nb;
    if(nc != NULL && fc < point_in_d(x->data))
	x = nc;

    return x;
}
void *get_min_data(KdTree kd){
    Node *n = (Node *) kd;
    return n->data;

}
    
KdTree  find_min_x(KdTree kd, int depth, float (*point_in_d)(void *)){
    Node *n = (Node *) kd; 

    if(n == NULL){
	printf("Error min\n");
	exit(-1);
    }
	if(n->left == NULL){
	    return n;
	}
	else{
	    return minNode(n,
		    find_min_x(n->left, depth+1, point_in_d),
		    find_min_x(n->right, depth+1, point_in_d), point_in_d);
	}

}
int are_same(void *a, void *b, float (*point_in_x)(void *), float (*point_in_y)(void *)){
    if(point_in_x(a) != point_in_x(b))
	return -1;
    if(point_in_y(a) != point_in_y(b))
	return -1;

    return 1;
}


KdTree delete_kd_node(KdTree kd, void *data, float (*point_in_x)(void *), float (*point_in_y)(void *), int depth){
    Node *n = (Node *) kd;
    Node *n_min;
    if(n == NULL)
	return NULL;
    if(are_same(n->data, data, point_in_x, point_in_y) == 1){
	if(n->right != NULL){
	    if(depth %2 == 0){
	    n_min = (Node *)find_min_x(n->right, depth, point_in_x);
	    }
	    else{
	    n_min = (Node *) find_min_y(n->right, depth, point_in_y);
	    }

	    n->data = n_min->data;

	    n->right = (Node *)delete_kd_node(n->right, n_min->data, point_in_x, point_in_y, depth +1);
	}
	else if(n->left != NULL){
	    if(depth % 2 == 0)
		n_min = (Node *)find_min_x(n->left, depth, point_in_x);
	    else
		n_min = (Node *) find_min_y(n->left, depth, point_in_y);

	    n->data = n_min->data;
	    n->right = (Node *)delete_kd_node(n->left, n_min->data, point_in_x, point_in_y, depth+1);
	    n->left = NULL;
	}
	else{
	    printf("foi");
	    printf("Apagando %lf", point_in_x(n->data));
	    free(n);
	    n = NULL;
	    return NULL;
	}
	return n;
    }
    if(depth % 2 == 0){
	if(point_in_x(data) < point_in_x(n->data))
	    n->left = (Node *)delete_kd_node(n->left, data, point_in_x, point_in_y, depth+1);
	else
	    n->right = (Node *)delete_kd_node(n->right, data, point_in_x, point_in_y, depth+1);

    }
    else{
	printf("a");
	if(point_in_y(data) < point_in_y(n->data))
	    n->left = (Node *)delete_kd_node(n->left, data, point_in_x, point_in_y, depth+1);
	else
	    n->right = (Node *)delete_kd_node(n->right, data, point_in_x, point_in_y, depth+1);
    }
    return n;
}
KdTree find_min_y(KdTree kd, int depth, float (*point_in_d)(void *)){
    Node *n = (Node *) kd;

    if(n == NULL){
	printf("Error min\n");
	exit(-1);
    }
	if(n->left == NULL){
	    return  n;

	}
	else{
	    return minNode(n,
		    find_min_y(n->left, depth+1, point_in_d),
		    find_min_y(n->right, depth+1, point_in_d), point_in_d);
	}
}

void printInOrder(KdTree t, void (*displayFn)(void *)){
    Node *n = (Node *) t;
    if(n == NULL){
	printf("Error\n");
	return;
    }

    if(n->left)
	printInOrder(n->left, displayFn);
    displayFn(n->data);
    if(n->right)
	printInOrder(n->right, displayFn);
}

