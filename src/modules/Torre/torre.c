#include "torre.h"

Torre createTorre(char *fill, char *strk, char *id, double x, double y){
	Torre t = malloc(sizeof(StTorre));

	StTorre *st = (StTorre *) t;

	strcpy(st->fill, fill);
	strcpy(st->strk, strk);
	strcpy(st->id, id);

	st->x = x;
	st-> y = y;

	return t;

}
int compareTorreX(Torre a, Torre b){
  StTorre *sa = (StTorre *) a;
  StTorre *sb = (StTorre *) b;


  if(sa->x < sb->x)
    return 1;
  else
    return -1;
}
int compareTorreY(Torre a, Torre b){
  StTorre *sa = (StTorre *) a;
  StTorre *sb = (StTorre *) b;


  if(sa->y < sb->y)
    return 1;
  else
    return -1;
}
