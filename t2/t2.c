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
	char suffix[MAXSIZE];

	//
	Lista listC = createList();
	Lista listR = createList();
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
			/* strcpy(dir, argv[i]); */
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

	if(fRead == NULL){
		fprintf(stderr, "Can't find file to read\nCheck if it exists\n");
		exit(-1);
	}
	/* //line variable is where file line is stored */
	while((read = getline(&line, &len, fRead)) != -1){
		switch(line[0]){
			case 'c':
				sscanf(line, "c %d %s %s %lf %lf %lf", &id, border, inside, &r, &x, &y);
				c = createCircle(border, inside, r, x, y);
				listC = insert(listC, c, id);
				/* drawCircle(fWrite, c); */
				
				break;
			case 'r':
				sscanf(line, "r %d %s %s %lf %lf %lf %lf", &id, border, inside, &w, &h, &x, &y);
				rect = createRect(border, inside, w, h, x, y);
				listR = insert(listR, rect, id);
				/* drawRect(fWrite, rect); */
				break;
			case 'a':
				sscanf(line, "a %d %s", &id, suffix);
				concatena(dir, suffix);
				concatena(dir, ".svg");

				fWrite = fopen(dir, "w");
				fprintf(fWrite, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");

				display(listC, fWrite, drawCircle);
				display(listR, fWrite, drawRect);
				fprintf(fWrite, "</xml>");
				fclose(fWrite);
				destroy(listR);
				destroy(listC);
								
				break;

		}
	}
	free(path);
	free(dir);
	free(line);
	free(leitura);
	fclose(fRead);
	//free circle

}
