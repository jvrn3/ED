#include "../modules/Hash/hash_table.h"
#include "../modules/Morador/morador.h"

int
main(){
	HashTable *ht = new_hash_table();
	put (ht, "123",createMorador("123", "abc", 'S', 123, "apto" ));
	put (ht, "223",createMorador("223", "bbc", 'N', 223, "apto" ));
	put (ht, "323",createMorador("323", "cbc", 'L', 323, "apto" ));
	put (ht, "423",createMorador("423", "dbc", 'O', 423, "apto" ));

	StMorador *sm = (StMorador *) search(ht, "123");
	printf("%s\n", sm->cpf);


	delete_hash_table(ht, free_morador);
	return 0;
}
