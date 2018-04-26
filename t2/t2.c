#include "../modules/Lista/static_ist.h"
#include "../modules/String/mystr.h"
#include "../modules/Circle/circle.h"
#include "../modules/Rect/rect.h"
#include "../modules/Svg/svg.h"

#define MAXSIZE 1000

int
main(int argc, char *argv[]){
	int id, i;

	char border[MAXSIZE];
	char inside[MAXSIZE];
	char buffer[MAXSIZE];

	//
	Lista list = createList();
	Circle c;
	Rect rect;

	char *path, *dir, *escrita, *leitura;

	double r, x, y, w, h;

	FILE *fWrite, *fRead;

	//read line
	size_t len = 0;
	ssize_t read;
	char *line = NULL;
	leitura = path = dir = NULL;

	i = 1;
	while(i < argc){
		if(strcmp("-e", argv[i]) == 0){
			i++;
			path = aloca_tamanho(path, strlen(argv[i]));
			strcpy(path, arruma_path(argv[i]));
		}
		if(strcmp("-f", argv[i]) == 0){
			i++;
			leitura = aloca_tamanho(leitura, strlen(argv[i]));
			strcpy(leitura, argv[i]);
		}
		if(strcmp("-o", argv[i]) == 0){
			i++;
			dir = aloca_tamanho(dir, strlen(argv[i]));
			strcpy(dir, arruma_path(argv[i]));
		}
		i++;
	}

	if(path==NULL){
		path = aloca_tamanho(path, 1);
		path[0] = '\0';
	}
	if(leitura == NULL || dir == NULL){
		fprintf(stderr, "siguel usage: siguel [-e path] -f arq.geo -o dir");
		exit(-1);
	}
	concatena(path, leitura);

	fRead = fopen(path, "r");

	fWrite = fopen(dir, "w");
	if(fRead == NULL){
		fprintf(stderr, "Can't find file to read\nCheck if it exists\n");
		exit(-1);
	}
	if(fWrite == NULL){
		fprintf(stderr, "Error dir");
		exit(-1);
	}
	/* //line variable is where file line is stored */
	while((read = getline(&line, &len, fRead)) != -1){
		switch(line[0]){
			case 'c':
				sscanf(line, "c %d %s %s %lf %lf %lf", &id, border, inside, &r, &x, &y);
				c = createCircle(id, border, inside, r, x, y);
				list = insert(list, c, id);
				drawCircle(fWrite, c);
				
				break;
			case 'r':
				sscanf(line, "r %d %s %s %lf %lf %lf %lf", &id, border, inside, &w, &h, &x, &y);

				break;

		}
	}
	printf("%d", id);
	free(path);
	free(dir);
	free(line);
	free(leitura);
	fclose(fRead);
	fclose(fWrite);
	//free circle

}
