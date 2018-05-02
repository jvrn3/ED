#include "../modules/Lista/static_ist.h"
#include "../modules/String/mystr.h"
#include "../modules/Circle/circle.h"
#include "../modules/Rect/rect.h"
#include "../modules/Svg/svg.h"

#define MAXSIZE 256

int
main(int argc, char *argv[]){
	int id, i;

	char border[MAXSIZE];
	char inside[MAXSIZE];
	char suffix[MAXSIZE];
	char *token;

	//
	Lista listC = createList();
	Lista listR = createList();
	Lista linha = createList();

	Circle c;
	Rect rect;

	char *path, *dir, *leitura;

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
///
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
				
				break;
			case 'r':
				sscanf(line, "r %d %s %s %lf %lf %lf %lf", &id, border, inside, &w, &h, &x, &y);
				rect = createRect(border, inside, w, h, x, y);

				listR = insert(listR, rect, id);
				break;
			case 'a':
				token = strtok(leitura, ".");
				sscanf(line, "a %d %s", &id, suffix);
				concatena(dir, token);
				concatena(dir, "-");
				concatena(dir, suffix);
				concatena(dir, ".svg");

				fWrite = fopen(dir, "w");
				fprintf(fWrite, "<svg>\n");

				

				display(listR, fWrite, drawRect);
				display(listC, fWrite, drawCircle);
				if((linha = search_id(listC, id)) != NULL){
					/* manipulate(listC, getX(linha), getY(linha), drawLine); */
					manipulate(listC, linha, fWrite, drawLineCToC);
					manipulate(listC, linha, fWrite, drawLineCToR);
					
				
				}
				else{
				}
					fprintf(fWrite, "</svg>");

				fclose(fWrite);
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
