#include "torre.h"

typedef struct stTorre{
  char fill[50];
  char strk[50];
  char id[50];
  double x, y;

}StTorre;


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

float torrePointInX(Torre a){
  StTorre *st = (StTorre *) a;
  return st->x;
}
float torrePointInY(Torre a){
  StTorre *st = (StTorre *) a;
  return st->y;
}

char *torre_get_fill(Torre t){
  StTorre *st = (StTorre *) t;
  return st->fill;
}
char *torre_get_strk(Torre t){
  StTorre *st = (StTorre *) t;
  return st->strk;
}
char *torre_get_id(Torre t){
  StTorre *st = (StTorre *) t;
  return st->id;
}
float torre_get_x(Torre t){
  StTorre *st = (StTorre *) t;
  return st->x;
}
float torre_get_y(Torre t){
  StTorre *st =(StTorre *) t;
  return st->y;
}
void torre_set_fill(Torre t, char *color){
  StTorre *st = (StTorre *) t;
  strcpy(st->fill, color);
}
void torre_set_strk(Torre t, char *color){
  StTorre *st = (StTorre *) t;
  strcpy(st->strk, color);
}




