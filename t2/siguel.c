#include "../modules/Lista/static_ist.h"
#include "../modules/String/mystr.h"
#include "../modules/Circle/circle.h"
#include "../modules/Rect/rect.h"
#include "../modules/Svg/svg.h"

#define MAXSIZE 256

	int
	main(int argc, char *argv[]){
		int id, id2, i;

		char border[MAXSIZE];
		char inside[MAXSIZE];
		char suffix[MAXSIZE];
		char *token;

		//
		Lista listC = createList();
		Lista listR = createList();
		Lista linha = createList();
		Lista linha2 = createList();

		Circle c;
		Rect rect;

		char *path, *dir, *leitura;

		double r, x, y, w, h;

		FILE *fWrite, *fRead, *fTxt;

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
		token = strtok(leitura, ".");
		fTxt  = fopen(token, "w");

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
				case 'd':
					sscanf(line, "d %d %d", &id, &id2);
					if ((linha = search_id(listC, id, 1)) != NULL){
						if((linha2 = search_id(listC, id2, 1)) != NULL)
							fprintf(fTxt, "d %d %d\n%.2lf\n",id, id2,distanceCC(linha, linha2));
						else
							fprintf(fTxt, "d %d %d\n%.2lf\n",id, id2, distanceCR(search_id(listC, id, 1), search_id(listR, id2,1)));
					}
					if ((linha = search_id(listR, id,1 )) != NULL){
						if((linha2 = search_id(listC, id2, 1)) != NULL)
							fprintf(fTxt, "d %d %d\n%.2lf\n",id, id2,distanceCR(linha2, linha));
						else
							fprintf(fTxt, "d %d %d\n%.2lf\n",id, id2, distanceRR(linha, search_id(listR, id2, 1)));
					}
					break;

				case 'o':
					sscanf(line, "o %d %d", &id, &id2);
					if ((linha = search_id(listC, id, 1)) != NULL){
						if((linha2 = search_id(listC, id2, 1)) != NULL){
								fprintf(fTxt, "o %d %d\n",id, id2);
							if(overlayCC(linha, linha2))
								fprintf(fTxt, "SIM\n");
							else
								fprintf(fTxt, "NAO\n");
						}
						else{
							linha2 = search_id(listR, id2, 1);

							fprintf(fTxt, "o %d %d\n", id, id2);
							if(overlayCR(linha, linha2))
								fprintf(fTxt, "SIM\n");
							else
								fprintf(fTxt, "NAO\n");
					}
				}
				if ((linha = search_id(listR, id,1 )) != NULL){
					if((linha2 = search_id(listC, id2, 1)) != NULL)
						fprintf(fTxt, "d %d %d\n%.2lf\n",id, id2,distanceCR(linha2, linha));
					else
						fprintf(fTxt, "d %d %d\n%.2lf\n",id, id2, distanceRR(linha, search_id(listR, id2, 1)));
				}


				break;

			case 'a':
				sscanf(line, "a %d %s", &id, suffix);
				concatena(dir, token);
				concatena(dir, "-");
				concatena(dir, suffix);
				concatena(dir, ".svg");

				fWrite = fopen(dir, "w");
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
	fclose(fTxt);
	//free circle

}
