#ifndef HASH_H
#define HASH_H
#include "../Lista/linked_list.h"
#include <stdlib.h>
#include <string.h>
#include "../Lista/linked_list.h"
typedef void *Hash;
typedef struct hashTable{
	int size;
	// StList *table;
	Lista *table;
}HashTable;

typedef struct hashData{
	void *data;
	char key[50];
}HashData;
//djb2 hash function for strings
int hash(char *str);
Hash new_hash_entry();
Hash new_hash_table();
void __remove(char *key);
void delete_hash_table(HashTable *ht, void (*func)(void *));
void insertHash(char *key, void *data);
void put(HashTable *ht, char *key, void *data);
void *search(HashTable *ht, char *key);
int compare(void *, void *);
Lista hash_filter_to_list(HashTable *ht, int (*_cmpr)(void *, void *), void *key);
int get_hash_max();
void *remove_hash(HashTable *ht, char *key);
#endif
