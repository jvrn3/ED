#include "../modules/String/mystr.h"
#include "minunit.h"
#include <string.h>
int tests_run =0;
static char *testCriaString(){
	mu_assert("Cria String errado\n", strcmp(criaString("a", "b", "c"), "abc") == 0);
	mu_assert("Cria String2 errado\n", strcmp(criaString("a", "b", "c"), "abc\n") == 0);
	return 0;
}

static char *all_tests(){
	mu_run_test(testCriaString);
	return 0;
}

int
main(){
	char *resultado = all_tests();
	if(resultado != 0){
		printf("%s", resultado);
	}
	else{
		printf("Yeah boy");
	
	}
	printf("Tests run %d\n", tests_run);
}
