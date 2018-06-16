#include "modules/String/mystr.h"
#include "modules/Circle/circle.h"
#include "modules/Rect/rect.h"
#include "modules/Svg/svg.h"
#include "modules/Geometry/geometry.h"
#include "modules/Cidade/cidade.h"
#include "palmeiras.h"
/* fix arruma_path */

int
main(int argc, char *argv[]){
	int id, id2, i;

	char border[MAXSIZE];
	char inside[MAXSIZE];
	char suffix[MAXSIZE];
	char line[1000];
	char cep[MAXSIZE];
	char fill_q[MAXSIZE], strk_q[MAXSIZE];
	char fill_h[MAXSIZE], strk_h[MAXSIZE];
	char fill_t[MAXSIZE], strk_t[MAXSIZE];
	char fill_s[MAXSIZE], strk_s[MAXSIZE];
	Lista listC = createList();
	Lista listR = createList();
	Lista linha = createList();
	Lista linha2 = createList();

	Cidade city = createCity();

	Circle c;
	Rect rect;
	Quadra q;

	char *path, *dir, *leitura, *nomeTxt, *nomeSvg, *nomePath;

	double r, x, y, w, h;

	FILE *fWrite, *fRead, *fTxt, *fDraw;

	leitura = path = dir = NULL;
	printaPalmeiras1();

	i = 1;
	while(i < argc){
		if(strcmp("-e", argv[i]) == 0){
			i++;
			path = aloca_tamanho(path, strlen(argv[i]));
			strcpy(path,arruma_path(argv[i]));
			printf("PATH=%s\n", path);
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
		path = aloca_tamanho(path, 3);
		strcpy(path, "./");
	}
	if(leitura == NULL || dir == NULL){
		fprintf(stderr, "siguel usage: siguel [-e path] -f arq.geo -o dir");
		exit(-1);
	}

	leitura[strlen(leitura) -4] = 0;

	nomeTxt = criaString(dir, leitura, ".txt");
	nomeSvg = criaString(dir, leitura, ".svg");

	nomePath = criaString(path, leitura, ".geo");
	printf("NOME LEITURA=%s\n", nomePath);

	fRead = fopen(nomePath, "r");
	printf("NOME ESCRITA=%s\n", nomeTxt);

	fTxt  = fopen(nomeTxt, "w");
	if(fTxt == NULL){
		fprintf(stderr, "cant open file ");
		exit(-1);
	}

	fDraw = fopen(nomeSvg, "w");
	if(fDraw == NULL){
		fprintf(stderr, "cant open file");
		exit(-1);
	}
	fprintf(fDraw,"<svg>\n");

	if(fRead == NULL){
		fprintf(stderr, "Can't find file to read\nCheck if it exists\n");
		exit(-1);
	}
	//read .geo file
	while(!feof(fRead)){
		fgets(line, MAXSIZE, fRead);

		switch(line[0]){
			case 'c':
				if(line[1] != 'q'){
					sscanf(line, "c %d %s %s %lf %lf %lf", &id, border, inside, &r, &x, &y);
					c = createCircle(border, inside, r, x, y);
					listC = insert(listC, c, id);
				}
				if(line[1] == 'q'){
					sscanf(line, "cq %s %s", fill_q, strk_q);

				}
				if(line[1] == 'h')
					sscanf(line, "ch %s %s", fill_h, strk_h);
				if(line[1] == 't')
					sscanf(line, "ct %s %s", fill_t, strk_t);

				if(line[1] == 's')
					sscanf(line, "cs %s %s", fill_s, strk_s);

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

						if(overlayCC(linha, linha2)){
							fprintf(fTxt, "SIM\n");
							drawOverlapCC(fDraw, linha, linha2);
						}
						else
							fprintf(fTxt, "NAO\n");
					}
					else{
						linha2 = search_id(listR, id2, 1);

						if(overlayCR(linha, linha2)){
							fprintf(fTxt, "SIM\n");
							drawOverlapCR(fDraw, linha, linha2);
						}
						else
							fprintf(fTxt, "NAO\n");
					}
				}
				else if((linha = search_id(listR, id, 1)) != NULL){
					if((linha2 = search_id(listC, id2, 1)) != NULL){
						if(overlayCR(linha2, linha)){
							fprintf(fTxt, "SIM\n");
							drawOverlapCR(fDraw, linha2, linha);
						}
						else
							fprintf(fTxt, "NAO\n");
					}
					else{
						linha2= search_id(listR, id2,1 );
						if(overlayRR(linha, linha2)){
							fprintf(fTxt, "SIM\n");
							drawOverlapRR(fDraw, linha, linha2);
						}
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
				if ((linha = search_id(listR, id, 1))){
					if(isInsideR(linha, x, y))
						fprintf(fTxt, "SIM\n");
					else
						fprintf(fTxt, "NAO\n");
				}
				break;

				case 'h':
				sscanf(line, "h %d %lf %lf", &id, &x, &y);
				city = insert_hidrante(city, createHidrante(fill_h, strk_h, id, x, y));

				break;


				case 'q':
				sscanf(line, "q %s %lf %lf %lf %lf", cep,&x, &y, &w,&h);
				
				
				city = insert_quadra(city, createQuadra(fill_q, strk_q, cep, x, y, w, h));

				q = get(city.lista_quadra, 0);

				StQuadra *sss = (StQuadra* )q;
				printf("\n\n\n %s",sss->fill);

				break;

				case 's':
				sscanf(line, "s %d %lf %lf", &id, &x, &y);
				city = insert_semaforo(city, createSemaforo(fill_s, strk_s, id, x, y));

				break;
				case 't':
				sscanf(line, "t %d %lf %lf", &id, &x, &y);
				city = insert_torre(city, createTorre(fill_t, strk_t, id, x, y));
				break;

			case 'a':
				sscanf(line, "a %d %s", &id, suffix);
				leitura = criaString(leitura, "-", suffix);
				leitura = criaString(dir, leitura, ".svg");
				printf("end: %s", path);
				fWrite = fopen(leitura, "w");
				if(fWrite == NULL)
					fprintf(stderr, "cant open file");
				fprintf(fWrite, "<svg>\n");


				display(listC, fWrite, drawCircle);
				display(listR, fWrite, drawRect);

				if((linha = search_id(listC, id, 0)) != NULL){

					manipulate(linha, listC, fWrite, drawLineCToC);
					manipulate(linha, listR, fWrite, drawLineCToR);
				}
				else if((linha = search_id(listR, id, 0)) != NULL){
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

	//is there more allocated variables? 
	free(path);
	free(dir);
	free(leitura);
	free(nomeSvg);
	free(nomeTxt);
	free(nomePath);



	fclose(fRead);
	fclose(fTxt);
	fclose(fDraw);

	//destroying lists
	destroy(city.lista_semaforo);
	destroy(city.lista_quadra);
	destroy(city.lista_hidrante);
	destroy(listC);
	destroy(listR);
	return 0;
}