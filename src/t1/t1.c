#include "t1_func.c"
#define SIZE 256

int
main(int argc, char *argv[]){
	FILE *files[10];
	for(int i = 0; i < 10; i++){
		files[i] = NULL;
	}
	if(argc > 2){
		if(strcmp(argv[1], "-f") != 0){
		printf("Usage: t1 -f file [-o dir] [par1] [par2] [par3]\n");
		}
		else{
			

			ler_arquivo(argv[2], files, argc, argv);
		}
	}
	else{
		printf("Usage: t1 -f file [-o dir] [par1] [par2] [par3]\n");
	}
	return 0;
}
