#ifndef HASH_H
#define HASH_H
#include "../Lista/linked_list.h"
#include <stdlib.h>
#include <string.h>
#include "../Lista/linked_list.h"
typedef void *Hash;
//djb2 hash function for strings
int hash(char *str);
Hash new_hash_entry();
Hash new_hash_table();
void __remove(char *key);
void delete_hash_table(Hash h, void (*func)(void *));
void insertHash(char *key, void *data);
void put(Hash h, char *key, void *data);
void *search(Hash h, char *key);
int compare(void *, void *);
Lista hash_filter_to_list(Hash h, int (*_cmpr)(void *, void *), void *key);
int get_hash_max();
void *remove_hash(Hash h, char *key);
Hash new_hash_table_n(int n);
Hash hash_get_data(Hash h);
char *hash_get_key(Hash h);
Hash ht_get_(Hash h,int i);
#endif
