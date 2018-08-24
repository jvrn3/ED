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
#include "../Tree/kdtree.h"


typedef struct cidade{
  Lista lista_quadra;
  Lista lista_semaforo;
  Lista lista_hidrante;
  Lista lista_torre;

  KdTree arvore_quadra;
  KdTree arvore_semaforo;
  KdTree arvore_hidrante;
  KdTree arvore_torre;


}Cidade;

Cidade createCity();
KdTree insert_quadra(Cidade c, Quadra q, float point[2]);
KdTree insert_hidrante(Cidade c, Hidrante h, float point[]);
KdTree insert_semaforo(Cidade c, Semaforo s, float point[]);
KdTree insert_torre(Cidade c, Torre t, float point[]);
KdTree remove_quadra(KdTree t,  Quadra q, float point[]);
Hidrante remove_hidrante(KdTree t, Hidrante h, float point[]);
Torre remove_torre(KdTree t, Torre to, float point[]);
Semaforo remove_semaforo(KdTree t, Semaforo s, float point[]);
Quadra search_cep(char *cep, Cidade c);
Semaforo search_id_sem(char *id, Cidade c);
Hidrante search_id_hi(char *id, Cidade c);
Torre search_id_to(char *id, Cidade c);
Torre search_id_toxy(float x, float y, Torre c);
KdTree  deleteQuadraInRect(Rect r,KdTree k, FILE *fp);
KdTree deleteSemaforoInRect(Rect r, KdTree k, FILE *fTxt);
KdTree deleteHidranteInRect(Rect r, KdTree k, FILE *fTxt);
KdTree deleteTorreInRect(Rect r, KdTree k, FILE *fTx);
KdTree deleteQuadraInCircle(Circle c, KdTree k, FILE *fTxt) ;
KdTree deleteSemaforoInCircle(Circle c, KdTree k, FILE *fTxt);
void searchQuadraInRect(Rect r, KdTree k, FILE *fTxt);
void searchQuadraInCircle(Circle c, KdTree k, FILE *fTxt);
void searchHidranteInRect(Rect r, KdTree k, FILE *fTxt);
void searchHidranteInCircle(Circle c, KdTree k, FILE *fTxt);
void searchSemaforoInRect(Rect r, KdTree k, FILE *fTxt);
void searchSemaforoInCircle(Circle c, KdTree k, FILE *fTxt);
void searchTorreInRect(Rect r, KdTree k, FILE *fTxt);
void searchTorreInCircle(Circle c, KdTree k, FILE *fTxt);
KdTree deleteHidranteInCircle(Circle c, KdTree k, FILE *fTxt);
KdTree deleteTorreInCircle(Circle c, KdTree k, FILE *fTxt);
void free_cidade(Cidade c);
void traverseTreeQuadra(KdTree kd, void (*func)(FILE *, void *), FILE *f);
void traverseTreeHidrante(KdTree kd, void (*func)(FILE *, void *), FILE *f);
void traverseTreeTorre(KdTree kd, void (*func)(FILE *, void *), FILE *f);
void traverseTreeSemaforo(KdTree kd, void (*func)(FILE *, void *), FILE *f);

#endif

