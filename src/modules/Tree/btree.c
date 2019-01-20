#include "btree.h"
#include <stdlib.h>

/*
 * 
 * */
typedef struct stBtNode{
  Elemento *elementos; //elementos
  int n; // numero de elementos do nó 
  int is_leaf; //verifica se é um nó interno
  int posicao_disco;
  int *filhos;
  /*
   * Cada nó que não seja a raiz deve ter pelo menos N -1 keys. Cada nó interno que nao seja a raiz deve ter N filhos
   * */

}StBtNode;
//
typedef struct stBtree{
  StBtNode *root;
  int ordem;
  int node_count;

}StBtree;
btNode disk_read(int disk, int ordem, FILE *fp){
  StBtNode *node = malloc(sizeof(StBtNode));

  // tamanho das variáveis
  int size_btnode = sizeof(node->n) + sizeof(node->is_leaf) + sizeof(node->posicao_disco) + sizeof(Elemento) * (ordem -1) + (sizeof(int) * ordem);

  int offset = disk * size_btnode;

  fseek(fp, offset, SEEK_SET);

  fread(&node->n, sizeof(node->n), 1, fp);
  fread(&node->is_leaf, sizeof(node->is_leaf), 1, fp);
  fread(&node->posicao_disco, sizeof(node->posicao_disco), 1, fp);

  node->elementos = malloc(sizeof(Elemento) * ordem -1);
  fread(node->elementos, sizeof(Elemento), ordem -1, fp);

  node->filhos = malloc(sizeof(int) * ordem);
  fread(node->filhos, sizeof(int), ordem, fp);

  return node;
}
void disk_write(btNode n, int ordem, FILE *fp){
  StBtNode *node = (StBtNode *) n;

  int size_btnode = sizeof(node->n) + sizeof(node->is_leaf) + sizeof(node->posicao_disco) + (sizeof(Elemento) * (ordem -1) )+ (sizeof(int) * ordem);

  int offset = node->posicao_disco * size_btnode;
  printf("OFFSET %d\n", offset);
  fseek(fp, offset, SEEK_SET);

  fwrite(&node->n, sizeof(node->n), 1, fp);
  fwrite(&node->is_leaf, sizeof(node->is_leaf), 1, fp);
  fwrite(&node->posicao_disco, sizeof(node->posicao_disco), 1, fp);

  fwrite(node->elementos, sizeof(Elemento), ordem -1, fp);
  fwrite(node->filhos, sizeof(int), ordem, fp);

}
btNode btnew_node(int ordem, int is_leaf){
  StBtNode *node = malloc(sizeof(StBtNode));
  node->n = 0;
  node->is_leaf = is_leaf;
  node->posicao_disco = 0;
  node->elementos = malloc((ordem - 1) * sizeof(Elemento));
  for(int i = 0; i < ordem -1; i++){
    node->elementos[i].chave = -1;
    node->elementos[i].data = NULL;
  }

  node->filhos = malloc(ordem * sizeof(int));

  for(int i = 0; i < ordem; i++){
    node->filhos[i] = -1;
  }

  return node;
}

bTree bTree_create(int ordem){
  printf("Criando arvore b"); 
  bTree t = malloc(sizeof(StBtree));
  if(t == NULL)
    return NULL;
  StBtree *tree = (StBtree *) t;

  StBtNode *node = btnew_node(ordem, 1);
  node->posicao_disco = 0;

  tree->ordem = ordem;
  tree->root = node;
  tree->node_count = 0;
  return tree;
}
//retorna a posição do disco do nó. Se não encontrar, retorna -1.
int bTree_search(bTree root, Elemento elemento, int ordem, FILE *fp){
  StBtree *tree = (StBtree *) root;
  StBtNode *node = tree->root;
  int i = 0;
  while(i < node->n && elemento.chave > node->elementos[i].chave){
    i++;
  }
  if(i < node->n && elemento.chave == node->elementos[i].chave){
    return node->posicao_disco;
  }
  else if(node->is_leaf == 1){
    return -1;
  }
  else{
    //lê um novo nó
    StBtNode *filho = disk_read(node->filhos[i], ordem, fp);
    return bTree_search(filho, elemento, ordem, fp);
  }
}
  
void bTree_splitChild(btNode x, int i, bTree t, FILE *fp, int split_root){
  /*
   * Divide o filho a partir da mediana. Se for root, o antigo root será filho do novo nó criado 
   * */
  StBtNode *node = (StBtNode *) x;
  if(node == NULL){
    printf("Error");
    exit(-1);
  }
  StBtree *tree = (StBtree *) t;
  StBtNode *y = disk_read(node->filhos[i], tree->ordem, fp);
  if(y == NULL){
    printf("Ta bugado");
  }
  
  if(split_root == 1){
    tree->node_count++;
    y->posicao_disco = tree->node_count; 
  }

  StBtNode *z = btnew_node(tree->ordem, y->is_leaf);
  tree->node_count++;
  z->posicao_disco = tree->node_count; // nova posição

  //mediana
  int m = (tree->ordem)/2;

  if(tree->ordem %2 == 0)
    m--;

  z->n = m; // numero de elementos no novo nó

  if(tree->ordem % 2 != 0){
    m--;
  }
  //inserindo elementos no nó Z
  for(int j = 0; j <= m && (j + m + 1) <= y->n -1; j++){
    z->elementos[j] = y->elementos[j + m + 1];
    y->elementos[j+m +1].chave = -1;
    y->elementos[j+m +1].data = NULL;
  }
  if(y->is_leaf == 0){
    for(int j = 0; j <= m; j++){
      z->filhos[j] = y->filhos[j + m + 1];
      y->filhos[j + m + 1] = -1;
    }
  }
  y->n = m;

  if(split_root == 1){
    node->filhos[i] = y->posicao_disco;
    node->filhos[i + 1] = z->posicao_disco;
  }
  else{
    int j, k, l;
    l = 0;
    for(j = 0; j < tree->ordem; j++){
      if(node->filhos[j] == y->posicao_disco){
	for(k = j + 1; k < tree->ordem; k+=2){
	  if(k +1 < tree->ordem){
	    node->filhos[k+1] = node->filhos[k];
	  }
	}
	l = j;
      }
    }
    node->filhos[l+1] = z->posicao_disco;
  }
  //
  for(int j = i;  j < tree->ordem - 2;  j+=2){
    node->elementos[j+1] = node->elementos[j];
  }
  node->elementos[i] = y->elementos[m];
  y->elementos[m].chave = -1;
  y->elementos[m].data = NULL;
  node->n++;
  disk_write(node, tree->ordem, fp);
  disk_write(y, tree->ordem, fp);
  disk_write(z, tree->ordem, fp);

}
void bTree_insertNonFull(btNode n, Elemento elemento, bTree t, FILE *fp){
  printf("\nInserindo -- NON FULL\n");
  printf("Elemento %d\n", elemento.chave);
  StBtNode *node = (StBtNode *) n;
  StBtree *tree = (StBtree *) t;
  int i = node->n-1;
  if(node->is_leaf == 1){
    while(i >= 0 && elemento.chave < node->elementos[i].chave){
      node->elementos[i+1] = node->elementos[i];
      node->elementos[i].chave = -1;
      node->elementos[i].data = NULL;
      i--;
    }
    node->elementos[i+1] = elemento;
    node->n++;

    disk_write(node, tree->ordem, fp);
  }
  else{
    i = node->n -1;
    while(i >= 0 && elemento.chave < node->elementos[i].chave){
      i--;
    }
    StBtNode *node_x = disk_read(node->filhos[i], tree->ordem, fp);

    if(node_x->n == tree->ordem -1){
      //split filho
      bTree_splitChild(node_x, i, tree, fp, 0);
      StBtNode *x1 = disk_read(node->posicao_disco, tree->ordem, fp);
      if(elemento.chave > x1->elementos[i].chave){
	i++;
      }
    }
    StBtNode *x1 = disk_read(node->posicao_disco, tree->ordem, fp);
  
    StBtNode *x2 = disk_read(x1->filhos[i], tree->ordem, fp);
    bTree_insertNonFull(x2, elemento, tree, fp);
  }
}
void bTree_insert(bTree t, Elemento elemento, FILE *fp){
  StBtree *tree = (StBtree *) t;
  //verifica se existem elementos
  if(tree->node_count > 0){
    tree->root = disk_read(0, tree->ordem, fp);
  }
  StBtNode *root = tree->root;

  if(root->n == tree->ordem -1){
    //splitar node
    StBtNode *s = btnew_node(tree->ordem, 0);
    s->filhos[0] = root->posicao_disco;
    bTree_splitChild(s, 0, tree, fp, 1);
    s = disk_read(0, tree->ordem, fp);
    tree->root = s;
    bTree_insertNonFull(s, elemento, tree, fp);

  }
  else{
    //insert non_full
    bTree_insertNonFull(root, elemento, tree, fp);
  }
}

void traverse_bTree(bTree t, btNode x, FILE *fp){
  StBtree *tree = (StBtree *) t;
  StBtNode *node = (StBtNode *) x;
  int i = 0;
  for(i = 0; i < node->n; i++){
    printf("%d ", node->elementos[i].chave);
    if(node->filhos[i] != -1){
      StBtNode *x1 = disk_read(node->filhos[i], tree->ordem, fp);
      traverse_bTree(tree, x1, fp);
    }
  }

  /* if(node->is_leaf == 0){ */
  /*   StBtNode *x1 = disk_read(node->filhos[i], tree->ordem, fp); */
  /*   traverse_bTree(tree, x1, fp); */
  /*  */
  /* } */
}
void print_bTree(bTree t, FILE *fp){
  StBtree *tree = (StBtree *) t;
  StBtNode *root = tree->root;
  traverse_bTree(tree, root, fp);
}
