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
#include "../Comercio/comercio.h"
#include "../Hash/hash_table.h"
#include "../Pessoa/pessoa.h"
#include "../Morador/morador.h"
#include "../Svg/svg.h"
#include "../Graph/graph.h"
#include "../Rua/rua.h"
#include "../Via/via.h"

/* Representação de Siguel, cidade com diversos equipamentos, pessoas etc 
 * Este arquivo contém funções que manipulam a cidade
 *
 * */


typedef struct cidade{
  Lista lista_quadra;
  Lista lista_semaforo;
  Lista lista_hidrante;
  Lista lista_torre;
  Lista lista_carros;

  KdTree arvore_quadra;
  KdTree arvore_semaforo;
  KdTree arvore_hidrante;
  KdTree arvore_torre;
  KdTree arvore_comercio;

  Hash comercio;
  Hash pessoas;
  Hash moradores;
  Hash tipo_comercio;
  Hash cep_quadra;

  Lista mor;
  Lista est;
  Lista mortos;
  Lista mud;
  Lista mudec;

  Via via;


}Cidade;

Cidade createCity();
// Address changeAddress(Address a, char *cep, char face, int num, char *comp);
Ponto hmp(Hidrante h);
Ponto tmp(Torre t);
Ponto city_get_ponto(Cidade c, Address a);
Pessoa searchPessoa(Hash h, char *key);
Comercio searchComercioTipo(Hash h, char *key);
Morador searchMorador(Hash h, char *key);
Comercio searchComercio(Hash h, char *key);
Quadra searchQuadra(Hash h, char *key);
int _compareCepMorador(void *hd, void *k);
int _compareCepEstblcmto(void *h, void *k);
int _compareCodtEstblc(void *h, void *k);
int compareTorreId(Torre t, char *key);

void _hashSearchEstblcInRect(Cidade c, Rect r, FILE *fTxt);
void _hashSearchQuadraInRect(Cidade c, Rect r, FILE *fp);
void _hashSearchTipoInRect(Cidade c, Rect r, char *key, FILE *fTxt);
void _hashRemoveMoradorInRect(Cidade c, Rect r, FILE *fTxt);
void _hashRemoveEstblcInRect(Cidade c, Rect r, FILE *fTxt);

KdTree insert_quadra(Cidade c, Quadra q, float point[2]);
KdTree insert_hidrante(Cidade c, Hidrante h, float point[]);
KdTree insert_semaforo(Cidade c, Semaforo s, float point[]);
KdTree insert_torre(Cidade c, Torre t, float point[]);
KdTree remove_quadra(KdTree t,  Quadra q, float point[]);
Hidrante remove_hidrante(KdTree t, Hidrante h, float point[]);
Torre remove_torre(KdTree t, Torre to, float point[]);
Semaforo remove_semaforo(KdTree t, Semaforo s, float point[]);

Quadra search_cep(char *cep, KdTree kd);
Semaforo search_id_sem(char *id, KdTree kd);
Hidrante search_id_hi(char *id, KdTree kd);
Torre search_id_to(char *id, KdTree kd);
Torre search_id_toxy(float x, float y, Torre c);

void deleteQuadraInRect(Rect r,KdTree k, FILE *fp);
void deleteSemaforoInRect(Rect r, KdTree k, FILE *fTxt);
void deleteHidranteInRect(Rect r, KdTree k, FILE *fTxt);
void deleteTorreInRect(Rect r, KdTree k, FILE *fTx);
void deleteQuadraInCircle(Circle c, KdTree k, FILE *fTxt) ;
void deleteSemaforoInCircle(Circle c, KdTree k, FILE *fTxt);
void searchQuadraInRect(Rect r, KdTree k, FILE *fTxt);
void searchQuadraInCircle(Circle c, KdTree k, FILE *fTxt);
void searchHidranteInRect(Rect r, KdTree k, FILE *fTxt);
void searchHidranteInCircle(Circle c, KdTree k, FILE *fTxt);
void searchSemaforoInRect(Rect r, KdTree k, FILE *fTxt);
void searchSemaforoInCircle(Circle c, KdTree k, FILE *fTxt);
void searchTorreInRect(Rect r, KdTree k, FILE *fTxt);
void searchTorreInCircle(Circle c, KdTree k, FILE *fTxt);
void deleteHidranteInCircle(Circle c, KdTree k, FILE *fTxt);
void deleteTorreInCircle(Circle c, KdTree k, FILE *fTxt);


void traverseTreeQuadra(KdTree kd, void (*func)(FILE *, void *), FILE *f);
void traverseTreeHidrante(KdTree kd, void (*func)(FILE *, void *), FILE *f);
void traverseTreeTorre(KdTree kd, void (*func)(FILE *, void *), FILE *f);
void traverseTreeSemaforo(KdTree kd, void (*func)(FILE *, void *), FILE *f);

int printa_closest(KdTree k, float dist, FILE *fSvg, FILE *fTxt, Ponto (*getPontos)(void *), void (*print_func)(FILE *, FILE *, void *, void *, float ));
void printa_closest_torre(FILE *fSvg, FILE *fTxt, void *a, void *b, float dist);
void printa_closest_given_p(KdTree k, Ponto p, Ponto q, float dist, FILE *fSvg, FILE *fTxt);
void printa_closest_given_radio(KdTree k, Ponto p, Ponto q, float dist, FILE *fSvg, FILE *fTxt);

void file_quadra_d(Quadra q, FILE *fTxt);
void file_semaforo_d(Semaforo s, FILE *fTxt);
void file_hidrante_d(Hidrante h, FILE *fTxt);
void file_torre_d(Torre t, FILE *fTxt);

void desapropriar(Cidade c, Rect r, FILE *fTxt);
void kill_pessoa(Cidade c, char *cpf, FILE *fTxt);
void mudar_pessoa(Cidade c, char *cpf, Address novo, FILE *fTxt);
void mudar_estbl(Cidade c, char *cnpj, Address novo, FILE *fTxt);
void drawCidade(Cidade c, FILE *nome);

void free_cidade(Cidade c);

Vertice nearest_via(Lista l, Ponto p);

void printShortest(FILE *fTxt, Grafo g, Vertice v);
#endif
