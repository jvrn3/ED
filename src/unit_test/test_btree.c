#include <stdio.h>
#include <stdlib.h>
#include "../modules/Tree/btree.h"

int
main(){
	Elemento n1 = {.chave = 10};
	Elemento n2 = {.chave = 20};
	Elemento n3 = {.chave = 30};
	Elemento n4 = {.chave = 40};
	Elemento n5 = {.chave = 50};
	Elemento n6 = {.chave = 60};
	Elemento n7 = {.chave = 70};
	Elemento n8 = {.chave = 80};
	printf("Test Btree...");
	FILE *fp = fopen("arquivo.bin", "wb+");
	bTree tree = bTree_create(4);
	bTree_insert(tree, n1, fp);
	bTree_insert(tree, n2, fp);
	bTree_insert(tree, n3, fp);
	bTree_insert(tree, n4, fp);
	bTree_insert(tree, n5, fp);
	bTree_insert(tree, n6, fp);
	bTree_insert(tree, n7, fp);
	bTree_insert(tree, n8, fp);



}
