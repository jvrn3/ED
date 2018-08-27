#include "modules/String/mystr.h"


#include "modules/Circle/circle.h"
#include "modules/Rect/rect.h"
#include "modules/Svg/svg.h"
#include "modules/Geometry/geometry.h"
#include "modules/Cidade/cidade.h"
#include "modules/Sort/sort.h"
#include "palmeiras.h"
#include "modules/Tree/kdtree.h"

int
main(int argc, char *argv[]){
	int id, id2, i;

	float point[2];
	char border[MAXSIZE];
	char inside[MAXSIZE];
	char suffix[MAXSIZE];
	char line[1000];
	char cep[MAXSIZE];
	/*
	 * variables used to "cc" comand 
	 *
	 * */
	char fill_q[MAXSIZE], strk_q[MAXSIZE];
	char fill_h[MAXSIZE], strk_h[MAXSIZE];
	char fill_t[MAXSIZE], strk_t[MAXSIZE];
	char fill_s[MAXSIZE], strk_s[MAXSIZE];
	char tmp_strk[MAXSIZE], tmp_fill[MAXSIZE];
	//
	char id_equipamentos[50];
	int crb = 0;
	Lista listC = createList();
	Lista listR = createList();
	Lista linha = createList();
	Lista linha2 = createList();
	Lista l;

	Cidade city = createCity();

	Circle c;
	Rect rect;


	char *path, *dir, *leitura, *nomeTxt, *nomeSvg, *nomePath, *qry, *ec;
	char *qry_name;

	double r, x, y, w, h;
	int n;

	FILE *fWrite, *fRead, *fTxt, *fDraw, *fQry, *fSvgQry, *fEc;


	leitura = path = dir = qry = ec = NULL;
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
		if(strcmp("-q", argv[i]) == 0){
			i++;
			qry = aloca_tamanho(qry, strlen(argv[i]));
			strcpy(qry, argv[i]);

		}
		if(strcmp ("-ec", argv[i]) == 0){
			i++;
			ec = aloca_tamanho(ec, strlen(argv[i]));
			strcpy(ec, argv[i]);
		
		}
		i++;
	}
	if(path==NULL){
		path = aloca_tamanho(path, 3);
		strcpy(path, "./");
	}
	if(leitura == NULL || dir == NULL){
		fprintf(stderr, "siguel usage: siguel [-e path -q file.qry -ec file.ec] -f arq.geo -o dir");
		exit(-1);
	}

	
	// -f 
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
		fprintf(stderr, "cant create file");
		exit(-1);
	}
	fprintf(fDraw,"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100000\" height=\"100000\">\n");

	if(fRead == NULL){
		fprintf(stderr, "Can't find file to read\nCheck if it exists\n");
		exit(-1);
	}
	//read .geo file
	while(!feof(fRead)){
		fgets(line , 1000, fRead);

		switch(line[0]){
			case 'c': 
				if(line[1] == 'q')
					sscanf(line, "cq %s %s", strk_q, fill_q);
				else if(line[1] == 'h')
					sscanf(line, "ch %s %s", strk_h, fill_h);
				else if(line[1] == 't')
					sscanf(line, "ct %s %s", strk_t, fill_t);

				else if(line[1] == 's')
					sscanf(line, "cs %s %s", strk_s, fill_s);
				else{
					sscanf(line, "c %d %s %s %lf %lf %lf", &id, border, inside, &r, &x, &y);
					c = createCircle(border, inside, r, x, y);
					insert(listC, c, id);


				}

				break;

			case 'r':
				sscanf(line, "r %d %s %s %lf %lf %lf %lf", &id, border, inside, &w, &h, &x, &y);
				rect = createRect(border, inside, w, h, x, y);

				insert(listR, rect, id);


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
						else{
							fprintf(fTxt, "NAO\n");
						}
					}
					else{
						linha2 = search_id(listR, id2, 1);

						if(overlayCR(linha, linha2)){
							fprintf(fTxt, "SIM\n");
							drawOverlapCR(fDraw, linha, linha2);
						}
						else{
							fprintf(fTxt, "NAO\n");
						}
					}
				}
				//actually i have no idea what it is 28/06/2018
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
						else{
							fprintf(fTxt, "NAO\n");
						}
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
				sscanf(line, "h %s %lf %lf",id_equipamentos, &x, &y);
				Hidrante hid= createHidrante(fill_h, strk_h, id_equipamentos, x, y);
				point[0] = x;
				point[1] = y;
				city.arvore_hidrante = insert_hidrante(city, hid, point);
				drawHidrante(fDraw, hid);

				break;

				//ler quadra
			case 'q':
				sscanf(line, "q %s %lf %lf %lf %lf", cep,&x, &y, &w,&h);
				Quadra q = createQuadra(fill_q, strk_q, cep, x, y, w, h);
				point[0] = x;
				point[1] = y;
				city.arvore_quadra = insert_quadra(city, q, point);
				drawQuadra(fDraw, q);


				break;

			case 's':
				sscanf(line, "s %s %lf %lf", id_equipamentos, &x, &y);
				Semaforo sem = createSemaforo(fill_s, strk_s, id_equipamentos, x, y);

				point[0] = x;
				point[1] = y;
				city.arvore_semaforo = insert_semaforo(city, sem, point);

				drawSemaforo(fDraw, sem);
				break;
			case 't':
				sscanf(line, "t %s %lf %lf", id_equipamentos, &x, &y);
				Torre t = createTorre(fill_t, strk_t, id_equipamentos, x, y);
				point[0] = x;
				point[1] = y;
				city.arvore_torre = insert_torre(city, t, point);
				drawTorre(fDraw, t);
				break;

			case 'a':
				sscanf(line, "a %d %s", &id, suffix);
				leitura = criaString(leitura, "-", suffix);
				leitura = criaString(dir, leitura, ".svg");
				printf("end: %s", path);
				fWrite = fopen(criaString(dir, criaString(leitura, "-", suffix), ".svg"), "w");

				if(fWrite == NULL)
					fprintf(stderr, "cant open file");
				fprintf(fWrite, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100000\" height=\"100000\">\n");


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
			default:
				break;
		}

	}
	//parsing and handling .qry files
	if(qry != NULL){
		qry[strlen(qry) -4] = 0;

		fQry = fopen(criaString(path, qry, ".qry"), "r");
		if(!fQry){
			fprintf(stdout, "Cant open file");
			exit(-1);
		}
		if(has_slash(qry))
			qry_name = get_last_slash(qry);
		else
			qry_name = qry;
		qry_name = criaString(dir, criaString(leitura, "-", qry_name), ".svg");
		printf("%s\n", qry_name);
		fSvgQry = fopen(qry_name, "w");

		if(!fSvgQry){
			fprintf(stderr, "bugou ao criar file");
			exit(-1);
		}
		fprintf(fSvgQry, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100000\" height=\"100000\">\n");
		/* while(!feof(fQry)){ */
		while(fgets(line,1000,fQry) != NULL){

			if(strncmp(line, "dq", 2) == 0){

				sscanf(line, "dq %lf %lf %lf %lf", &x, &y, &w, &h);

				rect = createRect("", "", w, h, x, y);
				city.arvore_quadra = deleteQuadraInRect(rect, city.arvore_quadra, fTxt);
				drawRectPontilhado(fSvgQry, rect);
				free(rect);
			}
			else if(strncmp(line, "q?", 2) == 0){
				sscanf(line, "q? %lf %lf %lf %lf", &x, &y, &w, &h);
				rect = createRect("", "", w, h, x, y);

				searchQuadraInRect(rect, city.arvore_quadra, fTxt);
				searchSemaforoInRect(rect, city.arvore_semaforo, fTxt);
				searchHidranteInRect(rect, city.arvore_hidrante, fTxt);
				searchTorreInRect(rect, city.arvore_torre, fTxt);
				drawRectPontilhado(fSvgQry, rect);
				free(rect);
			}
			else if(strncmp(line, "Q?", 2) == 0){
				sscanf(line, "Q? %lf  %lf %lf", &r, &x, &y);
				c = createCircle("", "", r, x, y);

				searchQuadraInCircle(c, city.arvore_quadra, fTxt);
				searchSemaforoInCircle(c, city.arvore_semaforo, fTxt);
				searchHidranteInCircle(c, city.arvore_hidrante, fTxt);
				searchTorreInCircle(c, city.arvore_torre, fTxt);


				drawCirclePontilhado(fSvgQry, c);
				free(c);
			}
			else if(strncmp(line, "Dq", 2) == 0){
				sscanf(line, "Dq %lf %lf %lf", &r, &x, &y);
				c = createCircle("", "", r, x, y);
				
				city.arvore_quadra = deleteQuadraInCircle(c, city.arvore_quadra, fTxt);
				drawCirclePontilhado(fSvgQry, c);
				free(c);
			}
			else if(strncmp(line, "dle", 3)==0){
				sscanf(line, "dle %*[srh] %lf %lf %lf %lf ",&x, &y, &w, &h);

				rect = createRect("", "", w, h, x, y);
				if(line[4] == 'r' || line[5] == 'r' || line[6] == 'r'){
					city.arvore_torre = deleteTorreInRect(rect, city.arvore_torre, fTxt);
				}

				if(line[4] == 'h' || line[5] == 'h' || line[6] == 'h'){
					//remove h
					city.arvore_hidrante = deleteHidranteInRect(rect, city.arvore_hidrante, fTxt);
				}
				if(line[4] == 's' || line[5] == 's' || line[6] == 's'){
					//remove r
					city.arvore_semaforo = deleteSemaforoInRect(rect, city.arvore_semaforo, fTxt);
				}
				drawRectPontilhado(fSvgQry, rect);
				free(rect);
			}
			else if(strncmp(line, "Dle", 3) == 0){
				sscanf(line, "Dle %*[rsh] %lf %lf %lf", &x, &y, &r );
				c = createCircle("", "", r, x, y);

				if(line[4] == 'h' || line[5] == 'h' || line[6] == 'h'){
					city.arvore_hidrante = deleteHidranteInCircle(c, city.arvore_hidrante, fTxt);
				}
				if(line[4] == 'r' || line[5] == 'r' || line[6] == 'r'){
					city.arvore_torre = deleteTorreInCircle(c, city.arvore_torre, fTxt);
				}
				if(line[4] == 's' || line[5] == 's' || line[6] == 's'){
					city.arvore_semaforo = deleteSemaforoInCircle(c, city.arvore_semaforo, fTxt);
				}
				drawCirclePontilhado(fSvgQry, c);
				free(c);
			}
			else if(strncmp(line, "cc", 2) == 0){
				sscanf(line, "cc %s %s %s", cep, tmp_strk, tmp_fill);
				StQuadra *sq;
				StTorre *st;
				StHidrante *sh;
				StSemaforo *ss;

				sq = (StQuadra *) search_cep(cep, city.arvore_quadra);
				if(sq != NULL){
					strcpy(sq->fill, tmp_fill);
					strcpy(sq->strk, tmp_strk);
				}

				else if((ss = (StSemaforo *) search_id_sem(cep, city.arvore_semaforo)) != NULL){
					strcpy(ss->fill, tmp_fill);
					strcpy(ss->strk, tmp_strk);
				}
				else if((st = (StTorre *) search_id_to(cep, city.arvore_torre) )!= NULL){
					strcpy(st->fill, tmp_fill);
					strcpy(st->strk, tmp_strk);

				}
				else if((sh = (StHidrante *) search_id_hi(cep, city.arvore_hidrante)) != NULL){
					strcpy(sh->fill, tmp_fill);
					strcpy(sh->strk, tmp_strk);
				}
			}
			else if(strncmp(line, "crd?", 4) == 0){

				sscanf(line, "crd? %s", cep);
				printf("%s\n", cep);
				StQuadra *sq;
				StTorre *st;
				StHidrante *sh;
				StSemaforo *ss;
				sq = (StQuadra *) search_cep(cep, city.arvore_quadra);
				if(sq != NULL)
					fprintf(fTxt, "%lf %lf %lf %lf QUADRA\n", sq->x, sq->y, sq->larg, sq->alt);
				else if((ss = (StSemaforo *) search_id_sem(cep, city.arvore_semaforo)) != NULL)
					fprintf(fTxt, "%lf %lf SEMAFORO\n", ss->x, ss->y);
				else if((st = (StTorre *) search_id_to(cep, city.arvore_torre) )!= NULL)
					fprintf(fTxt, "%lf %lf TORRE\n", st->x, st->y);
				else if((sh = (StHidrante *) search_id_hi(cep, city.arvore_hidrante)) != NULL)
					fprintf(fTxt, "%lf %lf HIDRANTE\n", sh->x, sh->y);
			}
			/* closest pair */
			else if(strncmp(line, "crb?", 4) == 0){
				crb = 1;
			}
		}


		//Estabelecimento comercial

		if(ec != NULL){
			ec[strlen(ec) -4] = 0;
			fEc =  fopen(criaString(path, ec, ".ec"), "r");
		}


		/*
		 * create new svg file after manipulating [deleting etc] the old list
		 *
		 */

		//it's time to print


		
		traverseTreeQuadra(city.arvore_quadra, drawQuadra, fSvgQry);
		traverseTreeSemaforo(city.arvore_semaforo, drawSemaforo, fSvgQry);
		traverseTreeHidrante(city.arvore_hidrante, drawHidrante, fSvgQry);
		traverseTreeTorre(city.arvore_torre, drawTorre, fSvgQry);

		
		//had to do this because the circle on svg would be printed before other elements and then be hidden
		if(crb){
				pointt(city.arvore_torre, closest_kd(city.arvore_torre), fSvgQry, fTxt );
		}

		free(qry_name);
		fprintf(fSvgQry, "\n</svg>\n");
		fclose(fSvgQry);
	}
	//t2 stuff
	l = listR;
	n = length(listR);
	for(int i =0; i < n; i++){
		StRect *sr = (StRect *) get(l, 0);
		drawRect(fDraw, sr);
		l = pop(l);
	}

	l = listC;
	n = length(listC);
	for(int i =0; i < n; i++){
	  StCircle *sc = (StCircle *) get(l, 0);
	  drawCircle(fDraw, sc);
	  l = pop(l);
	}
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
	free_cidade(city);
	destroy(listC);
	destroy(listR);
	/*destroy(linha2); */
	/* destroy(linha); */
	return 0;
}
