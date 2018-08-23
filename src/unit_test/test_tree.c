#include "../modules/Tree/kdtree.h"
#include "../modules/Rect/rect.h"


int compare(Rect a, Rect b){
	StRect *ra = (StRect *) a;
	StRect *rb = (StRect *) b;

	if(ra->x > rb->x){
		return 1;
	}
	else
		return -1;

}

int compareY(Rect a, Rect b){
	StRect *ra = (StRect *) a;
	StRect *rb = (StRect *) b;

	if(ra->y > rb->y){
		return 1;
	}
	else
		return -1;

}

float point_in_x(Rect r){
	StRect *sr = (StRect *) r;
	return sr->x;
}
float point_in_y(Rect r){
	StRect *sr = (StRect *) r;
	return sr->y;
}

void display_fn(void  *a){
	StRect *sr = (StRect *) a;
	printf("Printando %s %s %lf %lf %lf %lf\n", sr->inside, sr->border, sr->x, sr->y, sr->w, sr->h);

}
int compareZ(Rect a, Rect b, int cd){
	StRect *sa = (StRect *) a;
	StRect *sb = (StRect *) b;
	if(cd % 2 == 0){
		if(sa->x < sb->x )
			return 1;
		else
			return 0;
	}
	else{
		if(sa->y < sb->y)
			return 1;
		else
			return 0;
	}
}
int
main(){
	KdTree kd = NULL;
	Rect r3 = createRect("pink", "pink", 5,6, 40, 45);
	Rect r5 = createRect("pink", "pink", 10, 11, 70, 10); 
	Rect r2= createRect("blue,", "green",1, 2, 15, 70);

	float point[] = {40,45};
	kd = kd_insert(kd, r3, point);
	float point2[] = {70, 10};
	kd = kd_insert(kd, r5, point2);
	kd = delete_kd_node(kd, r3, point, 0);
    /*  */
	/* kd=  kd_insert(kd, r2, );   */
	/* kd  = kd_insert(kd, r5, compare, compareY);  */
	/* kd = kd_insert(kd, createRect("grey", "gasdg", 11,12, 69, 50),compare, compareY); */
	/* kd = kd_insert(kd, createRect("grey", "gasdg", 11,12, 66, 85),compare, compareY); */
	/* kd = kd_insert(kd, createRect("grey", "gasdg", 11,12, 85, 90),compare, compareY); */
    /*  */
	printInOrder(kd, display_fn);
	/* delete_kd_node(kd, createRect("grey", "gasdg", 11,12, 66, 85), compareZ, 0); */
	/* printf("%\n\n"); */
	/* printInOrder(kd, display_fn); */

	

}
