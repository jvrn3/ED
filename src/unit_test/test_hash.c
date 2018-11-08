#include "../modules/Hash/hash_table.h"
#include "../modules/Morador/morador.h"


int
main(){
	Hash ht = new_hash_table();
	put (ht, "123",createMorador("123", "abc", 'S', 123, "apto" ));
	/* Morador m = createMorador("123", "abc", 'S', 123, "apto" ); */
	/* printf("%s\n", morador_get_cep(m)); */
	/* #<{(| put (ht, "223",createMorador("223", "bbc", 'N', 223, "apto" )); |)}># */
	put (ht, "323",createMorador("323", "cbc", 'L', 323, "apto" ));
	search(ht, "323");
	/* put (ht, "423",createMorador("423", "dbc", 'O', 423, "apto" )); */
    /*  */
	/* Morador sm = search(ht, "123"); */
    /*  */
	/* delete_hash_table(ht, free_morador); */
	return 0;
}
