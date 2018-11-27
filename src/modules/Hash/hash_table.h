#ifndef HASH_H
#define HASH_H
#include "../Lista/linked_list.h"
typedef void *Hash;
/* A hash table implementada aqui utiliza um vetor de listas e uma chave que transforma uma dada string em 
 * um dado int, e salva os dados nessa posição. O objetivo é que para cada chave, há um número int representando sua posição.
 * No entanto, existe colisão, e por esse motivo que devemos criar uma lista para as posições
 * */


int hash(char *str);

//create a hash table with size 256
Hash new_hash_table();

//create a hash table with size n
Hash new_hash_table_n(int n);


//Deletes a hash table using a free function 
void delete_hash_table(Hash h, void (*free_func)(void *));

//add to hash table, given key and data
void put(Hash h, char *key, void *data);

//search in the table given key
void *search(Hash h, char *key);

int compare(void *, void *);

//given a hash h, filter using cmpr function with key.
//similar to filter in fp
Lista hash_filter_to_list(Hash h, int (*_cmpr)(void *, void *), void *key);

//get length of a table. 
int get_hash_max();

//delete a hash given its key
void *remove_hash(Hash h, char *key);

/* Getters */
Hash hash_get_data(Hash h);
char *hash_get_key(Hash h);
Hash ht_get_(Hash h,int i);
#endif
