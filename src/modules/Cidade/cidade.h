#ifndef CIDADE_H
#define CIDADE_H
#include "../Quadra/quadra.h"
#include "../Hidrante/hidrante.h"
#include "../Semaforo/semaforo.h"
#include "../Torre/torre.h"
#include "../Lista/linked_list.h"
#include "../Rect/rect.h"
#include "../Circle/circle.h"
#include "../Geometry/geometry.h"


typedef struct cidade{
  Lista lista_quadra;
  Lista lista_semaforo;
  Lista lista_hidrante;
  Lista lista_torre;

}Cidade;

Cidade createCity();
void insert_quadra(Cidade c, Quadra q);
void insert_hidrante(Cidade c, Hidrante h);
void insert_semaforo(Cidade c, Semaforo s);
void insert_torre(Cidade c, Torre t);
void remove_quadra(Cidade c, Quadra q);
Hidrante remove_hidrante(Cidade c, Hidrante h);
Torre remove_torre(Cidade c, Torre t);
Semaforo remove_semaforo(Cidade c, Semaforo s);
Quadra search_cep(char *cep, Cidade c);
Semaforo search_id_sem(char *id, Cidade c);
Hidrante search_id_hi(char *id, Cidade c);
Torre search_id_to(char *id, Cidade c);
Torre search_id_toxy(float x, float y, Torre c);
void searchOrDeleteQuadraInRect(Rect r, Lista lista_quadra, FILE *fp, int del);
void searchOrDeleteSemaforoInRect(Rect r, Lista lista_semaforo, FILE *fp, int del);
void searchOrDeleteHidranteInRect(Rect r, Lista lista_hidrante, FILE *fp, int del);
void searchOrDeleteTorreInRect(Rect r, Lista lista_torre, FILE *fp, int del);
void searchOrDeleteQuadraInCircle(Circle c, Lista lista_quadra, FILE *fTxt, int del);
void searchOrDeleteSemaforoInCircle(Circle c, Lista lista_semaforo, FILE *fp, int del);
void searchOrDeleteHidranteInCircle(Circle c, Lista lista_hidrante, FILE *fp, int del);
void searchOrDeleteTorreInCircle(Circle c, Lista lista_torre, FILE *fp, int del);
void rem_quadra(Lista lista_quadra, StQuadra *sq);
void rem_torre(Lista lista_torre, StTorre *st);
void rem_semaforo(Lista lista_semaforo, StSemaforo *ss);
void rem_hidrante(Lista lista_hidrante, StHidrante *sh);
void free_cidade(Cidade c);
#endif

