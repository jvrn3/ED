#include "modules/String/mystr.h"
#include "modules/Circle/circle.h"
#include "modules/Rect/rect.h"
#include "modules/Svg/svg.h"
#include "modules/Geometry/geometry.h"
#include "modules/Cidade/cidade.h"
#include "palmeiras.h"

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
	char tmp_strk[MAXSIZE], tmp_fill[MAXSIZE];
	Lista listC = createList();
	Lista listR = createList();
	Lista linha = createList();
	Lista linha2 = createList();

	Cidade city = createCity();

	Circle c;
	Rect rect;
	Quadra q;

	char *path, *dir, *leitura, *nomeTxt, *nomeSvg, *nomePath, *qry ;

	double r, x, y, w, h;

	FILE *fWrite, *fRead, *fTxt, *fDraw, *fQry, *fSvgQry;

	leitura = path = dir = qry = NULL;
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
		if(strcmp("-q", argv[i]) == 0){
			i++;
			qry = aloca_tamanho(qry, strlen(argv[i]));
			strcpy(qry, argv[i]);

		
		}
		i++;
	}
	if(path==NULL){
		path = aloca_tamanho(path, 3);
		strcpy(path, "./");
	}
	if(leitura == NULL || dir == NULL){
		fprintf(stderr, "siguel usage: siguel [-e path -q file.qry] -f arq.geo -o dir");
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
		fgets(line, 1000, fRead);

		switch(line[0]){
			case 'c':
				if(line[1] == 'q')
					sscanf(line, "cq %s %s", fill_q, strk_q);
				else if(line[1] == 'h')
					sscanf(line, "ch %s %s", fill_h, strk_h);
				else if(line[1] == 't')
					sscanf(line, "ct %s %s", fill_t, strk_t);

				else if(line[1] == 's')
					sscanf(line, "cs %s %s", fill_s, strk_s);
				else{
					sscanf(line, "c %d %s %s %lf %lf %lf", &id, border, inside, &r, &x, &y);
					c = createCircle(border, inside, r, x, y);
					listC = insert(listC, c, id);
				}

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
				c = createCircle(strk_h, fill_h, 10.0, x, y);

				listC = insert(listC, c, -1);
				

				break;


				case 'q':
				sscanf(line, "q %s %lf %lf %lf %lf", cep,&x, &y, &w,&h);
				
				
				city = insert_quadra(city, createQuadra(fill_q, strk_q, cep, x, y, w, h));

				rect = createRect(strk_q, fill_q, w, h, x, y);
				listR = insert(listR, rect, -1);

				q = get(city.lista_quadra, 0);

				StQuadra *sss = (StQuadra* )q;
				printf("Adafasdfa %d", length(city.lista_semaforo));
				printf("\n\n\n %s",sss->fill);

				break;

				case 's':
				sscanf(line, "s %d %lf %lf", &id, &x, &y);
				city = insert_semaforo(city, createSemaforo(fill_s, strk_s, id, x, y));

				rect = createRect(strk_s, fill_s, 10, 10, x, y);
				listR = insert(listR, rect, -1);

				break;
				case 't':
				sscanf(line, "t %d %lf %lf", &id, &x, &y);
				city = insert_torre(city, createTorre(fill_t, strk_t, id, x, y));
				printf("Adafasdfa %d", length(city.lista_torre));

				c = createCircle(strk_t, fill_t, 15, x, y);
				listC = insert(listC, c, -1);
				
				break;

			case 'a':
				sscanf(line, "a %d %s", &id, suffix);
				leitura = criaString(leitura, "-", suffix);
				leitura = criaString(dir, leitura, ".svg");
				printf("end: %s", path);
				fWrite = fopen(criaString(dir, criaString(leitura, "-", suffix), ".svg"), "w");

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
			default:
				break;
		}

	}
	//parsing and handling .qry files
	if(qry != NULL){
		qry[strlen(qry) -4] = 0;
		/* qry = criaString(dir, qry, ".qry"); */

		fQry = fopen(criaString(dir, qry, ".qry"), "r");
		if(!fQry){
			fprintf(stdout, "Cant open file");
			exit(-1);
		
		}
	
		while(!feof(fQry)){
			fgets(line, 1000, fQry);

			//dq command
			if(strncmp(line, "dq", 2) == 0){
				printf("%s", line);


				sscanf(line, "dq %lf %lf %lf %lf", &x, &y, &w, &h);

				rect = createRect("", "", w, h, x, y);
				for(int i = 0; i < length(city.lista_quadra)-1; i++){
					printf("%d\n", i);
					StQuadra * sq =   (StQuadra *)get(city.lista_quadra, i);
					printf("%s\n", sq->cep);


					if(isRectInsideRect(createRect("", "", sq->larg, sq->alt, sq->x, sq->y), rect)){

						fprintf(fTxt, "CEP REMOVIDO: %s\n", ((StQuadra * )get(city.lista_quadra, i))->cep);

						city.lista_quadra = del(city.lista_quadra, get(city.lista_quadra, i));
						printf("New list size %d \n", length(city.lista_quadra));
					}
				}


			}
			//Dq 
			else if(strncmp(line, "Dq", 2) == 0){

				printf("%s", line);
				sscanf(line, "Dq %lf %lf %lf", &r, &x, &y);

				c = createCircle("", "", r, x, y);
				// go through the entire list and remove the ones that overlap
				for(int i = 0; i < length(city.lista_quadra)-1; i++){

					StQuadra *sq = (StQuadra *) get(city.lista_quadra, i);

					printf("%s", sq->fill);
					rect = createRect(sq->strk, sq->fill, sq->larg, sq->alt, sq->x, sq->y);

					if(isRectInsideCircle(c, rect)){
						fprintf(fTxt, "Dq %s\n", ((StQuadra * )get(city.lista_quadra, i))->cep);
						printf(".Sobrepoe.\n");
						city.lista_quadra = del(city.lista_quadra, get(city.lista_quadra, i));
						printf("New list size %d \n", length(city.lista_quadra));
					}

				}

			}
			else if(strncmp(line, "dle", 3)==0){
				sscanf(line, "dle t %lf %lf %lf %lf ",&x, &y, &w, &h);

				rect = createRect("white", "white", w, h, x, y);
				printf("bicho ta dodio");
				if(line[4] == 't' || line[5] == 't' || line[6] == 't'){
					//remove t
					//is torre a circle?
					//

					for(int i =0; i < length(city.lista_torre)-1; i++){

						StTorre *st = (StTorre *) get(city.lista_torre, i);
						c = createCircle(st->strk, st->fill, 15, st->x, st->y);
						if(isCircleInsideRect(c, rect)){
							printf("..Sobrepoe..\n");
							fprintf(fTxt, "dle t %d\n", st->id);
							city.lista_torre = del(city.lista_torre, get(city.lista_torre, i));
							printf("New list size %d \n", length(city.lista_torre));
						}

					
					}
				}
				if(line[4] == 'h' || line[5] == 'h' || line[6] == 'h'){
					//remove h
					for(int i = 0; i < length(city.lista_hidrante)-1; i++){
						StHidrante *sh = (StHidrante *) get(city.lista_hidrante, i);
						c = createCircle(sh->strk, sh->fill, 10, sh->x, sh->y);

						if(isCircleInsideRect(c, rect)){
							printf("..Sobrepoe..\n");
							fprintf(fTxt, "dle h %d\n", sh->id);
							city.lista_hidrante = del(city.lista_hidrante, get(city.lista_hidrante, i));
							printf("New list size %d \n", length(city.lista_hidrante));

						
						}
					}
					
				}
				if(line[4] == 's' || line[5] == 's' || line[6] == 's'){
					//remove r
					for(int i = 0; i < length(city.lista_semaforo)-1; i++){
						StSemaforo *ss = (StSemaforo *) get(city.lista_semaforo, i);

						if(isRectInsideRect(rect, createRect(ss->strk, ss->fill, 10, 10, ss->x, ss->y))){
							fprintf(fTxt, "dle s %d\n", ss->id);
							city.lista_semaforo = del(city.lista_semaforo, get(city.lista_semaforo, i));
						}
					}
				}
			}
			else if(strncmp(line, "Dle", 3) == 0){
				sscanf(line, "Dle t %lf %lf %lf", &x, &y, &r );
				c = createCircle("", "", r, x, y);

				if(line[4] == 'h' || line[5] == 'h' || line[6] == 'h'){
					for(int i = 0; i < length(city.lista_hidrante) -1; i++){
					
					}
				
				}
				if(line[4] == 't' || line[5] == 't' || line[6] == 't'){
				
				}
				if(line[4] == 's' || line[5] == 's' || line[6] == 's'){
				
				}
			}
			else if(strncmp(line, "cc", 2) == 0){
				sscanf(line, "cc %s %s %s", cep, tmp_strk, tmp_fill);
				if(strncmp(line, "cc cep", 6) == 0){
					StQuadra *sq;
					if((sq = (StQuadra *) search_cep(cep, city) )!= NULL){
						strcpy(sq->fill, tmp_fill);
						strcpy(sq->strk, tmp_strk);
					}
				}
			}
		}
			fSvgQry = fopen(criaString(dir, criaString(leitura, "-", qry), ".svg"), "w");
			if(!fSvgQry){
				fprintf(stderr, "bugou ao criar file");
				exit(-1);
			}
		/*
		 * create new svg file after manipulating [deleting etc] the old list
		 *
		*/
		fprintf(fSvgQry, "<svg>\n");
		for(int i = 0 ; i < length(city.lista_quadra)-1; i++){
			printf("%d", i);

			StQuadra *sq = (StQuadra *) get(city.lista_quadra, i);
			drawRect(fSvgQry, createRect(sq->strk, sq->fill, sq->larg, sq->alt, sq->x, sq->y));
		}
	for(int i =0; i < length(city.lista_hidrante)-1; i++){
		printf("%d", i);
		StHidrante *sh = (StHidrante *) get(city.lista_hidrante, i);
		drawCircle(fSvgQry, createCircle(sh->strk, sh->fill, 10, sh->x, sh->y));
	
	}
	for(int i =0; i < length(city.lista_semaforo)-1; i++){
		StSemaforo *ss = (StSemaforo *) get(city.lista_semaforo, i);

		drawRect(fSvgQry, createRect(ss->strk, ss->fill, 10, 10, ss->x, ss->y));
	}
	for(int i = 0; i <= length(city.lista_torre)-1; i++){
		printf("aeaeaeaeae");
		StTorre *st = (StTorre *) get(city.lista_torre, i);

		drawCircle(fSvgQry, createCircle(st->strk, st->fill, 15, st->x, st->y));

	}

		fprintf(fSvgQry, "\n</svg>\n");
		fclose(fSvgQry);
	}
	if(length(listC) >0 )
		displayCircleToSvg(fDraw, listC);

	if(length(listR) > 0)
		displayRectToSvg(fDraw, listR);

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
	destroy(city.lista_torre);
	destroy(listC);
	destroy(listR);
	return 0;
}
