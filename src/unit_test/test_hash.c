#include "../modules/Hash/hash_table.h"

int
main(){
	int a = 2;
	int b = 4;
	void *d = &a;
	void *e = &b;
	HashTable *ht = new_hash_table();
	put(ht, "joao", d);
	put(ht, "Joao", e);

	printf("%d\n",  *(int *)search(ht, "Joao"));
	printf("%d",  *(int *)search(ht, "joao"));


}
