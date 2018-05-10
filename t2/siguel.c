#include "../modules/Lista/static_ist.h"
#include "../modules/String/mystr.h"
#include "../modules/Circle/circle.h"
#include "../modules/Rect/rect.h"
#include "../modules/Svg/svg.h"
#include "../modules/Geometry/geometry.h"
#include "palmeiras.h"


int
main(int argc, char *argv[]){
	int id, id2, i;

	char border[MAXSIZE];
	char inside[MAXSIZE];
	char suffix[MAXSIZE];
	/* char *token; */
	char line[MAXSIZE];

	Lista listC = createList();
	Lista listR = createList();
	Lista linha = createList();
	Lista linha2 = createList();

	Circle c;
	Rect rect;

	char *path, *dir, *leitura;

	double r, x, y, w, h;

	FILE *fWrite, *fRead, *fTxt, *fDraw;

	leitura = path = dir = NULL;
	printaPalmeiras1();

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
			strcpy(dir, argv[i]);
			dir = arruma_path(dir);

			printf("%s\n", dir);
		}
		i++;
	}
	if(path==NULL){
		path = aloca_tamanho(path, 0);
		path[0] = '\0';
	}
	if(leitura == NULL || dir == NULL){
		fprintf(stderr, "siguel usage: siguel [-e path] -f arq.geo -o dir");
		exit(-1);
	}

	concatena(path, leitura);
	printf("Dir:%s\n", dir);
	printf("path:%s", path);
	path[strlen(path) -4] = 0;

	fRead = fopen(criaString(dir, path, ".geo"), "r");

	fTxt  = fopen(criaString(dir, path, ".txt"), "w");
	if(fTxt == NULL)
		fprintf(stderr, "cant open");

	fDraw = fopen(criaString(dir, path, ".svg"), "w");
	if(fDraw == NULL)
		fprintf(stderr, "cant open");
	fprintf(fDraw,"<svg>\n");

	if(fRead == NULL){
		fprintf(stderr, "Can't find file to read\nCheck if it exists\n");
		exit(-1);
	}
	/* //line variable is where file line is stored */
	/* while((read = getline(&line, &len, fRead)) != -1){ */
	while(!feof(fRead)){
		fgets(line, MAXSIZE, fRead);
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

			case 'd':
				sscanf(line, "d %d %d", &id, &id2);
				fputs(line, fTxt);
				if ((linha = search_id(listC, id, 1)) != NULL){
					if((linha2 = search_id(listC, id2, 1)) != NULL)
						fprintf(fTxt, "%.2f\n",distanceCC(linha, linha2));
					else
						fprintf(fTxt, "%.2f\n",distanceCR(search_id(listC, id, 1), search_id(listR, id2,1)));
				}
				if ((linha = search_id(listR, id,1 )) != NULL){
					printf("a");
					if((linha2 = search_id(listC, id2, 1)) != NULL)
						fprintf(fTxt, "%.2f\n",distanceCR(linha2, linha));
					else
						fprintf(fTxt, "%.2f\n",distanceRR(linha, search_id(listR, id2, 1)));
				}
				break;

			case 'o':
				sscanf(line, "o %d %d", &id, &id2);
				fputs(line, fTxt);
				if ((linha = search_id(listC, id, 1)) != NULL){
					if((linha2 = search_id(listC, id2, 1)) != NULL){

						if(overlayCC(linha, linha2))
							fprintf(fTxt, "SIM\n");
						else
							fprintf(fTxt, "NAO\n");
					}
					else{
						linha2 = search_id(listR, id2, 1);

						if(overlayCR(linha, linha2))
							fprintf(fTxt, "SIM\n");
						else
							fprintf(fTxt, "NAO\n");
					}
				}
				if((linha = search_id(listR, id, 1)) != NULL){
					if((linha2 = search_id(listC, id2, 1)) != NULL){
						if(overlayCR(linha2, linha))
							fprintf(fTxt, "SIM\n");
						else
							fprintf(fTxt, "NAO\n");
					}
					else{
						linha2= search_id(listR, id2,1 );
						if(overlayRR(linha, linha2))
							fprintf(fTxt, "SIM\n");
						else
							fprintf(fTxt, "NAO\n");
					}
				}
				break;
			case 'i':
				sscanf(line, "i %d %lf %lf ",&id, &x, &y);
				fprintf(fTxt, "i %d %.2f %.2f\n", id, x, y); 
				if ((linha = search_id(listC, id, 1))){
					if(isInsideC(linha, x, y))
						fprintf(fTxt, "SIM\n");
					else
						fprintf(fTxt, "NAO\n");

				}
				break;

			case 'a':
				sscanf(line, "a %d %s", &id, suffix);
				concatena(path, "-");
				concatena(path, suffix);
				printf("end: %s", path);
				fWrite = fopen(criaString(dir, path, ".svg"), "w");
				if(fWrite == NULL)
					fprintf(stderr, "cant open file");
				fprintf(fWrite, "<svg>\n");


				display(listC, fWrite, drawCircle);
				display(listR, fWrite, drawRect);

				if((linha = search_id(listC, id, 0)) != NULL){

					manipulate(linha, listC, fWrite, drawLineCToC);
					manipulate(linha, listR, fWrite, drawLineCToR);
				}
				if((linha = search_id(listR, id, 0)) != NULL){
					manipulate(linha, listC, fWrite, drawLineRToC);
					manipulate(linha, listR, fWrite, drawLineRToR);

				}
				fprintf(fWrite, "</svg>");

				fclose(fWrite);
				break;
		}

	}
	display(listC, fDraw, drawCircle);
	display(listR, fDraw, drawRect);
	fprintf(fDraw, "</svg>");

	free(path);
	free(dir);
	free(leitura);


	fclose(fRead);
	fclose(fTxt);
	fclose(fDraw);

	destroy(listC);
	destroy(listR);
	return 0;

}
