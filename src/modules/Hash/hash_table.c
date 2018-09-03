#include "hash_table.h"

int HASH_SIZE=128;

Hash new_hash_entry(){
	HashEntry *hs = malloc(sizeof(HashEntry));
	hs->hash_list = createList();
	return hs;
}
int compare(void *data, void *key){
	HashData *hd = (HashData *) data;
	if(strcmp(hd->key, (char *)key) == 0)
		return 1;
	else
		return 0;
}

Hash new_hash_table(){
	HashTable *ht = malloc(sizeof(HashTable));
	ht->table = malloc(sizeof(StList) * HASH_SIZE);
	ht->size = 0;
	for(int i = 0; i < HASH_SIZE; i++){
		ht->table[i] = NULL;
	}
	return ht;
}
void put(HashTable *ht, char *key, void *data){
	int index = hash(key);
	printf("Hash %s INDEX %d\n", key, index);
	if(ht->table[index] == NULL){
		ht->table[index] = createList();
	}
	HashData *hd = malloc(sizeof(HashData));
	hd->data = data;
	strcpy(hd->key, key);
	insert(ht->table[index], hd, 0);
	/* insertAtEnd(ht->table[index]->hash_list, hd); */
	ht->size++;

	/** ** ** ** ** **  */
	/* if(ht->size >= 0.7 * HASH_SIZE){ */
	/* 	HASH_SIZE = HASH_SIZE *2; */
	/* 	ht->table = realloc(ht->table, HASH_SIZE); */
	/* } */
}
void *search(HashTable *ht, char *key){
	int index = hash(key);
	printf("Search Hash %s INDEX %d\n", key, index);
	if(ht->table[index] != NULL){
		//compare function compare key and the element of the hash
		HashData *hd= (HashData *) searchList(ht->table[index], compare, key);
		return hd->data;
	}
	else
		return NULL;
}
Lista hash_filter_to_list(HashTable *ht, int (*_cmpr)(void *, void *),char *_comp_key ){
	Lista new_list = createList();
	for(int i = 0; i < HASH_SIZE; i++){
		if(ht->table[i] != NULL){
			Node *n;
			for(n = getFirst(ht->table[i]); n != NULL; n = n->next){
				if(_cmpr(n->data, _comp_key)){
					HashData *hd = (HashData *)n->data;
					insert(new_list, hd->data, 0);
				}
			}
		}
	}
	return new_list;
}
void delete_hash_table(HashTable *ht){
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


