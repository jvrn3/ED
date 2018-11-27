#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
typedef struct hashTable{

	int size;
	Lista *table;

}HashTable;

typedef struct hashData{

	void *data;
	char key[100];

}HashData;

int HASH_SIZE=256;

Hash new_hash_table(){

	HashTable *ht = malloc(sizeof(HashTable));
	ht->table = malloc(sizeof(Lista) * HASH_SIZE);
	ht->size = 0;
	for(int i = 0; i < HASH_SIZE; i++){
		ht->table[i] = createList();
	}
	return ht;
}
Hash new_hash_table_n(int n){
	
	HASH_SIZE = n;
	return new_hash_table();
}
int compare(void *data, void *key){

	HashData *hd = (HashData *) data;
	if(strcmp(hd->key, (char *)key) == 0)
		return 1;
	else
		return 0;
}


void put(Hash h, char *key, void *data){

	HashTable *ht = (HashTable *)  h;
	int index = hash(key);
	if(index > HASH_SIZE)
		return;
	HashData *hd = malloc(sizeof(HashData));
	hd->data = data;
	strcpy(hd->key, key);
	insert(ht->table[index], hd, 0);
	ht->size++;
}
void *search(Hash h, char *key){

	HashTable *ht = (HashTable *) h;
	int index = hash(key);
	if(ht->table[index] != NULL){
		HashData *hd= (HashData *) searchList(ht->table[index], compare, key);
		if(hd != NULL)
			return hd->data;
	}
	return NULL;
}
Lista hash_filter_to_list(Hash h, int (*_cmpr)(void *, void *),void *_comp_key ){

	HashTable *ht = (HashTable *) h;
	Lista new_list = createList();
	for(int i = 0; i < HASH_SIZE; i++){
		if(ht->table[i] != NULL){
			Node *n;
			for(n = getFirst(ht->table[i]); n != NULL; n = getNext(n)){
				if(_cmpr(list_get_data(n), _comp_key)){
					insert(new_list, list_get_data(n), 0);
				}
			}
		}
	}
	return new_list;
}
void *remove_hash(Hash h, char *key){

	HashTable *ht = (HashTable *) h;
	int index = hash(key);

	HashData *hd = search_del(ht->table[index], compare, key);
	if(hd != NULL){
		void *d = hd->data;
		free(hd);
		return d;
	}
	//does this key exist? 
	return NULL;
}
void delete_hash_table(Hash h, void (*func)(void *)){

	HashTable *ht = (HashTable *) h;
	for(int i = 0; i < get_hash_max(); i++){
		if(ht->table[i] != NULL){
			while(length(ht->table[i]) > 0){
				HashData *data= removeFirst(ht->table[i]);
				if(data != NULL){
					func(data->data);
					free(data);
				}
			}
			destroy(ht->table[i]);
		}
	}
	free(ht->table);
	free(ht);
}
int get_hash_max(){
	return HASH_SIZE;
}
//djb2 hash function
int hash(char *str){

	unsigned long hash = 5381;
	int c;
	while ((c = *str++)){
		hash = (((hash << 5) + hash) + c ); /* hash * 33 + c */
	}
	return hash % HASH_SIZE;
}
Hash hash_get_data(Hash h){
	HashData *hd = (HashData *) h;
	return hd->data;
}
char *hash_get_key(Hash h){
	HashData *hd = (HashData *) h;
	return hd->key;
}
Hash ht_get_(Hash h,int i){
	HashTable *ht = (HashTable *) h;
	return ht->table[i];
}
