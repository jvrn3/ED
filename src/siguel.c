#include "modules/String/mystr.h"
#include "modules/Cidade/cidade.h"
#include "modules/Sort/sort.h"
/*
 *@authors: João Vitor Roma Neto
		    Rafael Yukio Umemoto
 *
 *
 * */
int
main(int argc, char *argv[]){
	
	int i;
	
	char *leitura, *path, *dir, *qry, *ec, *pm, *sistema_viario;
	
	leitura = path = dir = qry = ec = pm = sistema_viario = NULL;

	/*parsing arguments*/
	i = 1;
	while(i < argc){
		if(strcmp("-e", argv[i]) == 0){
			i++;
			path = aloca_tamanho(strlen(argv[i]));
			strcpy(path,argv[i]);
			path = arruma_path(path);
		}
		if(strcmp("-f", argv[i]) == 0){
			i++;
			leitura = aloca_tamanho(strlen(argv[i]));
			strcpy(leitura, argv[i]);
		}
		if(strcmp("-o", argv[i]) == 0){
			i++;
			dir = aloca_tamanho(strlen(argv[i]));
			strcpy(dir, argv[i]);
			dir = arruma_path(dir);
		}
		if(strcmp("-q", argv[i]) == 0){
			i++;
			qry = aloca_tamanho(strlen(argv[i]));
			strcpy(qry, argv[i]);

		}
		if(strcmp ("-ec", argv[i]) == 0){
			i++;
			ec = aloca_tamanho(strlen(argv[i]));
			strcpy(ec, argv[i]);
		}
		if(strcmp("-pm", argv[i]) == 0){
			i++;
			pm = aloca_tamanho(strlen(argv[i]));
			strcpy(pm, argv[i]);
		}
		if(strcmp("-v", argv[i]) == 0){
			i++;
			sistema_viario = aloca_tamanho(strlen(argv[i]));
			strcpy(sistema_viario, argv[i]);
		}
		if(strcmp("--help", argv[i]) == 0){
			printf("usage: ./siguel -f arq.geo -o dir [-e path] [-q file.qry]\n\t\t\t\t  [-ec file.ec] [-pm file.pm] [-v arq.via]");
			exit(0);
		
		}
		i++;
	}

	Circle c;
	Rect rect;
	char *nomeTxt, *nomeSvg, *nomePath;

	int id, id2;
	double r, x, y, w, h;
	FILE *fWrite, *fRead, *fTxt, *fDraw, *fQry, *fSvgQry, *fEc, *fPm;

	float point[2];
	char border[MAXSIZE];
	char inside[MAXSIZE];
	char suffix[MAXSIZE];
	char line[1000];
	char cep[MAXSIZE];
	void *linha, *linha2;
	Ponto R[10];
	/*
	 * variables used to "cc" comand
	 *
	 * */
	char fill_q[MAXSIZE], strk_q[MAXSIZE];
	char fill_h[MAXSIZE], strk_h[MAXSIZE];
	char fill_t[MAXSIZE], strk_t[MAXSIZE];
	char fill_s[MAXSIZE], strk_s[MAXSIZE];
	char tmp_strk[MAXSIZE], tmp_fill[MAXSIZE];
	/*
	 *
	 * */
	char id_equipamentos[50];
	int crb = 0;
	Lista listC = createList();
	Lista listR = createList();
	Lista hmpList = createList();
	Lista hmpeList = createList();
	Cidade city = createCity();

	//se path não existir, então é ./
	if(path==NULL){
		path = aloca_tamanho(3);
		strcpy(path, "./");
	}
	//Comandos obrigatoros
	if(leitura == NULL || dir == NULL){
		fprintf(stderr, "siguel usage: siguel [-e path -q file.qry -ec file.ec -pm file.pm -v arq.via] -f arq.geo -o dir");
		exit(-1);
	}

	// -f
	leitura[strlen(leitura) -4] = 0;
	nomeTxt = criaString(dir, leitura, ".txt");
	nomeSvg = criaString(dir, leitura, ".svg");
	nomePath = criaString(path, leitura, ".geo");

	fRead = fopen(nomePath, "r");
	fDraw = fopen(nomeSvg, "w");
	if(fDraw == NULL){
		fprintf(stderr, "cant create file");
		exit(-1);
	}
	startSvg(fDraw);
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
					sscanf(line, "cq %s %s", strk_q, fill_q);
				else if(line[1] == 'h')
					sscanf(line, "ch %s %s", strk_h, fill_h);
				else if(line[1] == 't')
					sscanf(line, "ct %s %s", strk_t, fill_t);
				else if(line[1] == 's')
					sscanf(line, "cs %s %s", strk_s, fill_s);
				else{
					sscanf(line, "c %d %s %s %lf %lf %lf", &id, border, inside, &r, &x, &y);
					insert(listC, createCircle(border, inside, r, x, y), id);
				}
				break;

			case 'r':
				sscanf(line, "r %d %s %s %lf %lf %lf %lf", &id, border, inside, &w, &h, &x, &y);
				insert(listR, createRect(border, inside, w, h, x, y), id);
				break;

			case 'd':
				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "d %d %d", &id, &id2);
				fputs(line, fTxt);
				if ((linha = search_id(listC, id, 1)) != NULL){
					if((linha2 = search_id(listC, id2, 1)) != NULL)
						fprintf(fTxt, "%.2f\n",distanceCC(linha, linha2));
					else
						fprintf(fTxt, "%.2f\n",distanceCR(search_id(listC, id, 1), search_id(listR, id2,1)));
				}
				if ((linha = search_id(listR, id,1 )) != NULL){
					if((linha2 = search_id(listC, id2, 1)) != NULL)
						fprintf(fTxt, "%.2f\n",distanceCR(linha2, linha));
					else
						fprintf(fTxt, "%.2f\n",distanceRR(linha, search_id(listR, id2, 1)));
				}
				fclose(fTxt);
				break;

			case 'o':
				fTxt = fopen(nomeTxt, "a");
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
				fclose(fTxt);
				break;
			case 'i':
				fTxt = fopen(nomeTxt, "a");
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
				fclose(fTxt);
				break;

			case 'h':
				sscanf(line, "h %s %lf %lf",id_equipamentos, &x, &y);
				Hidrante hid= createHidrante(fill_h, strk_h, id_equipamentos, x, y);
				point[0] = x;
				point[1] = y;
				city.arvore_hidrante = insert_hidrante(city, createHidrante(fill_h, strk_h, id_equipamentos, x, y), point);
				drawHidrante(fDraw, hid);
				free(hid);
				break;

				//ler quadra
			case 'q':
				sscanf(line, "q %s %lf %lf %lf %lf", cep,&x, &y, &w,&h);
				Quadra q = createQuadra(fill_q, strk_q, cep, x, y, w, h);
				//hash insertion
				put(city.cep_quadra, cep, createQuadra(fill_q, strk_q, cep, x, y, w, h));
				point[0] = x;
				point[1] = y;
				 city.arvore_quadra= insert_quadra(city, createQuadra(fill_q, strk_q, cep, x, y, w, h), point);
				drawQuadra(fDraw, q);
				free(q);
				break;

			case 's':
				sscanf(line, "s %s %lf %lf", id_equipamentos, &x, &y);
				Semaforo sem = createSemaforo(fill_s, strk_s, id_equipamentos, x, y);
				point[0] = x;
				point[1] = y;
				city.arvore_semaforo = insert_semaforo(city, createSemaforo(fill_s, strk_s, id_equipamentos, x, y), point);
				drawSemaforo(fDraw, sem);
				free(sem);
				break;
			case 't':
				sscanf(line, "t %s %lf %lf", id_equipamentos, &x, &y);
				Torre t = createTorre(fill_t, strk_t, id_equipamentos, x, y);
				point[0] = x;
				point[1] = y;
				city.arvore_torre = insert_torre(city,createTorre(fill_t, strk_t, id_equipamentos, x, y), point);
				drawTorre(fDraw, t);
				free(t);
				break;

			case 'a':
				sscanf(line, "a %d %s", &id, suffix);
				Lista appnd = createList();
				leitura = criaString(leitura, "-", suffix);
				leitura = criaString(dir, leitura, ".svg");
				printf("end: %s", path);
				fWrite = fopen(criaString(dir, criaString(leitura, "-", suffix), ".svg"), "w");

				if(fWrite == NULL)
					fprintf(stderr, "cant open file");
				startSvg(fWrite);

				display(listC, fWrite, drawCircle);

				display(listR, fWrite, drawRect);

				if((appnd = search_id(listC, id, 0)) != NULL){

					manipulate(appnd, listC, fWrite, drawLineCToC);
					manipulate(appnd, listR, fWrite, drawLineCToR);
				}
				else if((appnd = search_id(listR, id, 0)) != NULL){
					manipulate(appnd, listC, fWrite, drawLineRToC);
					manipulate(appnd, listR, fWrite, drawLineRToR);

				}
				fprintf(fWrite, "</svg>");

				fclose(fWrite);
				destroy(appnd);
				break;
			default:
				break;
		}
	}
	fclose(fDraw);
	fclose(fRead);

	//estabelecimento comercial
	if(ec != NULL){
		int num;
		ec[strlen(ec) -3] = 0;
		char *newString = criaString(path, ec, ".ec");
		fEc =  fopen(newString, "r");
		free(newString);
		if(!fEc){
			printf("Error opening ec file\n Try again\n");
			exit(-1);
		}
		while(fgets(line,1000,fEc) != NULL){

			if(strncmp(line, "e", 1) == 0){
				char cnpj[50], codt[50], cep[50], face, nome[100];
				sscanf(line, "e %s %s %s %c %d %s", cnpj, codt, cep, &face, &num, nome);
				put(city.comercio,cnpj, createComercio(cnpj, codt, cep, face, num, nome));
			}
			else if(strncmp(line, "t", 1) == 0){
				char codt[50], descr[50];
				sscanf(line, "t %s %s", codt, descr);
				put(city.tipo_comercio, codt, createTipoComercio(codt, descr));
			}
		}
		fclose(fEc);
	}

	//pessoa/morador
	if(pm != NULL){
		pm[strlen(pm) - 3] = 0;
		char *newString = criaString(path, pm, ".pm");
		fPm = fopen(newString, "r");
		free(newString);
		if(!fPm){
			printf("Error opening pm file\n Try again\n");
			exit(-1);
		}
		while(fgets(line, 1000, fPm) != NULL){
			if(strncmp(line, "p", 1) == 0){
				char cpf[50], nome[50], sobrenome[50], sexo, nasc[50];
				sscanf(line, "p %s %s %s %c %s", cpf, nome, sobrenome, &sexo, nasc);
				put(city.pessoas,cpf, createPessoa(cpf, nome, sobrenome, sexo, nasc));
			}
			else if(strncmp(line, "m", 1) == 0){
				char cpf[50], cep[50], face, comp[50];
				int num;
				sscanf(line, "m %s %s %c %d %s", cpf, cep, &face, &num, comp);
				put(city.moradores,cpf, createMorador(cpf, cep, face, num, comp));
			}

		}
		fclose(fPm);

	}
	if(sistema_viario != NULL){
		sistema_viario[strlen(sistema_viario) -4 ] = 0;
		char *newString = criaString(path, sistema_viario, ".via");
		FILE *sis_viario_file = fopen(newString, "r");
		free(newString);

		if(!sis_viario_file){
			printf("Error opening sistema viario file\nTry again!\n");
			exit(-1);
		}
		while(fgets(line, 1000, sis_viario_file) != NULL){
			if(strncmp(line, "v", 1) == 0){
				char id[100];
				sscanf(line, "v %s %lf %lf", id, &x, &y);

				via_insertEsquina(city.via, id, x, y);
			}
			else if(strncmp(line, "e", 1) == 0){
				char v1[50], v2[50], ldir[50], lesq[50], nome[50];
				double cmp, vm;
				sscanf(line, "e %s %s %s %s %lf %lf %s", v1, v2, ldir, lesq, &cmp, &vm, nome);
				via_insertRua(city.via, v1, v2, ldir, lesq, cmp, vm, nome);
			}
		}
		fclose(sis_viario_file);
	}

	//parsing and handling .qry files
	if(qry != NULL){
		qry[strlen(qry) -4] = 0;
		char *fQryString = criaString(path, qry, ".qry");
		fQry = fopen(fQryString, "r");
		free(fQryString);
		char *qry_name = qry;
		if(!fQry){
			fprintf(stdout, "Cant open file");
			exit(-1);
		}
		if(has_slash(qry))
			qry_name = get_last_slash(qry);

		char *qry_nameString = criaString(leitura, "-", qry_name);
		qry_name = criaString(dir, qry_nameString, ".svg");
		fTxt = fopen(nomeTxt, "w");
		fprintf(fTxt, "\n ----- Queries do arquivo %s.qry -----\n", qry);
		fclose(fTxt);
		while(fgets(line,1000,fQry) != NULL){
			if(strncmp(line, "dq", 2) == 0){
				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "dq %lf %lf %lf %lf", &x, &y, &w, &h);

				rect = createRect("", "", w, h, x, y);
				deleteQuadraInRect(rect, city.arvore_quadra, fTxt);
				free(rect);
				fclose(fTxt);
			}
			else if(strncmp(line, "q?", 2) == 0){

				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "q? %lf %lf %lf %lf", &x, &y, &w, &h);
				rect = createRect("", "", w, h, x, y);

				searchQuadraInRect(rect, city.arvore_quadra, fTxt);
				searchSemaforoInRect(rect, city.arvore_semaforo, fTxt);
				searchHidranteInRect(rect, city.arvore_hidrante, fTxt);
				searchTorreInRect(rect, city.arvore_torre, fTxt);
				/* drawRectPontilhado(fSvgQry, rect); */
				free(rect);
				fclose(fTxt);
			}
			else if(strncmp(line, "Q?", 2) == 0){

				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "Q? %lf  %lf %lf", &r, &x, &y);
				c = createCircle("", "", r, x, y);

				searchQuadraInCircle(c, city.arvore_quadra, fTxt);
				searchSemaforoInCircle(c, city.arvore_semaforo, fTxt);
				searchHidranteInCircle(c, city.arvore_hidrante, fTxt);
				searchTorreInCircle(c, city.arvore_torre, fTxt);


				/* drawCirclePontilhado(fSvgQry, c); */
				free(c);
				fclose(fTxt);
			}
			else if(strncmp(line, "Dq", 2) == 0){

				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "Dq %lf %lf %lf", &r, &x, &y);
				c = createCircle("", "", r, x, y);
				deleteQuadraInCircle(c, city.arvore_quadra, fTxt);
				/* drawCirclePontilhado(fSvgQry, c); */
				free(c);
				fclose(fTxt);
			}
			else if(strncmp(line, "dle", 3)==0){

				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "dle %*[srh] %lf %lf %lf %lf ",&x, &y, &w, &h);

				rect = createRect("", "", w, h, x, y);
				if(line[4] == 'r' || line[5] == 'r' || line[6] == 'r'){
					deleteTorreInRect(rect, city.arvore_torre, fTxt);
				}

				if(line[4] == 'h' || line[5] == 'h' || line[6] == 'h'){
					//remove h
					deleteHidranteInRect(rect, city.arvore_hidrante, fTxt);
				}
				if(line[4] == 's' || line[5] == 's' || line[6] == 's'){
					//remove r
					deleteSemaforoInRect(rect, city.arvore_semaforo, fTxt);
				}
				/* drawRectPontilhado(fSvgQry, rect); */
				free(rect);
				fclose(fTxt);
			}
			else if(strncmp(line, "Dle", 3) == 0){
				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "Dle %*[rsh] %lf %lf %lf", &x, &y, &r );
				c = createCircle("", "", r, x, y);

				if(line[4] == 'h' || line[5] == 'h' || line[6] == 'h'){
					deleteHidranteInCircle(c, city.arvore_hidrante, fTxt);
				}
				if(line[4] == 'r' || line[5] == 'r' || line[6] == 'r'){
					deleteTorreInCircle(c, city.arvore_torre, fTxt);
				}
				if(line[4] == 's' || line[5] == 's' || line[6] == 's'){
					deleteSemaforoInCircle(c, city.arvore_semaforo, fTxt);
				}
				/* drawCirclePontilhado(fSvgQry, c); */
				free(c);
				fclose(fTxt);
			}
			else if(strncmp(line, "cc", 2) == 0){
				sscanf(line, "cc %s %s %s", cep, tmp_strk, tmp_fill);
				Quadra sq;
				Torre st;
				Hidrante sh;
				Semaforo ss;

				sq = search_cep(cep, city.arvore_quadra);
				if(sq != NULL){
					quadra_set_fill(sq, tmp_fill);
					quadra_set_strk(sq, tmp_strk);
				}

				else if((ss =  search_id_sem(cep, city.arvore_semaforo)) != NULL){
					semaforo_set_fill(ss, tmp_fill);
					semaforo_set_strk(ss, tmp_strk);
				}
				else if((st = search_id_to(cep, city.arvore_torre) )!= NULL){
					torre_set_fill(st, tmp_fill);
					torre_set_strk(st, tmp_strk);

				}
				else if((sh =search_id_hi(cep, city.arvore_hidrante)) != NULL){
					hidrante_set_fill(sh, tmp_fill);
					hidrante_set_strk(sh, tmp_strk);
				}
			}
			else if(strncmp(line, "crd?", 4) == 0){

				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "crd? %s", cep);
				Quadra sq;
				Torre st;
				Hidrante sh;
				Semaforo ss;
				sq = search_cep(cep, city.arvore_quadra);
				if(sq != NULL)
					fprintf(fTxt, "%lf %lf %lf %lf QUADRA\n", quadra_get_x(sq), quadra_get_y(sq), quadra_get_w(sq), quadra_get_h(sq));
				else if((ss = search_id_sem(cep, city.arvore_semaforo)) != NULL)
					fprintf(fTxt, "%lf %lf SEMAFORO\n", semaforo_get_x(ss), semaforo_get_y(ss));
				else if((st = search_id_to(cep, city.arvore_torre) )!= NULL)
					fprintf(fTxt, "%lf %lf TORRE\n", torre_get_x(st), torre_get_y(st));
				else if((sh = search_id_hi(cep, city.arvore_hidrante)) != NULL)
					fprintf(fTxt, "%lf %lf HIDRANTE\n", hidrante_get_x(sh), hidrante_get_y(sh));

				fclose(fTxt);
			}
			/* closest pair */
			else if(strncmp(line, "crb?", 4) == 0){
				crb = 1;
			}
			else if(strncmp(line, "m?", 2) == 0){
				//moradores da quadra cujo cep é cep
				//
				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "m? %s", cep);
				if(search_cep(cep, city.arvore_quadra) == NULL){
					printf("\nCEP da quadra nao encontrado!\n Verifique se existe morador com cep %s\n", cep);
				}
				else{
					fprintf(fTxt, "\n---- Moradores no Cep %s ----\n", cep);
					Lista mor_quadra = hash_filter_to_list(city.moradores, _compareCepMorador, cep);
					Node *n ;
					for(n = getFirst(mor_quadra); n != NULL; n = getNext(n)){
						printf("a");
						Hash hd = list_get_data(n);
						Pessoa sp = search(city.pessoas, hash_get_key(hd));

						fprintf(fTxt, "Nome => %s %s\n", pessoa_get_nome(sp), pessoa_get_sobrenome(sp));
						Morador sm =  hash_get_data(hd);
						fprintf(fTxt, "Endereco => %s/%c/%d\n" , morador_get_cep(sm), morador_get_face(sm),
								morador_get_num(sm));
					}
					destroyList(mor_quadra);
				}

				fclose(fTxt);
			}
			else if(strncmp(line, "mr?", 3) == 0){
				//moradores em uma região r
				//
				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "mr? %lf %lf %lf %lf", &x, &y, &w, &h);
				Rect r = createRect("", "", w,h,x,y);
				_hashSearchQuadraInRect(city, r, fTxt);
				free(r);

				fclose(fTxt);
			}
			else if(strncmp(line, "dm?", 3) == 0){

				fTxt = fopen(nomeTxt, "a");
				//imprime dados do morador indicado pelo cpf
				char cpf[50];
				sscanf(line, "dm? %s", cpf);
				Morador  sm = searchMorador(city.moradores, cpf);
				Pessoa sp = searchPessoa(city.pessoas, cpf);
				if(sm == NULL || sp == NULL){
					printf("Pessoa ou morador nao encontrados com o cpf %s\nVerifiqe se existe no arquivo\n", cpf);
				}
				else{
					fprintf(fTxt, "\nDados de => %s %s\n", pessoa_get_nome(sp), pessoa_get_sobrenome(sp));
					fprintf(fTxt, "Endereco => %s/%c/%d\n",
							morador_get_cep(sm),
							morador_get_face(sm),
							morador_get_num(sm));

					Morador smm = createMorador(
							morador_get_cpf(sm),
							morador_get_cep(sm),
							morador_get_face(sm),
							morador_get_num(sm),
							morador_get_comp(sm));
					insert(city.mor, smm, 0);
				}
				fclose(fTxt);
			}
			else if(strncmp(line, "de?", 3) == 0){
				//imprime todos os dados do estabelecimento comercial identificado por cnpj
				//
				fTxt = fopen(nomeTxt, "a");
				char cnpj[50];
				Comercio sct= NULL;
				sscanf(line, "de? %s", cnpj);
				Comercio sc = searchComercio(city.comercio, cnpj);
				if(sc != NULL){
					sct = searchComercioTipo(city.tipo_comercio, estabelecimento_get_codt(sc));
				}
				if(sc != NULL && sct != NULL){
					fprintf(fTxt, "\nEstabelecimento comercial identificado por -> %s\n", estabelecimento_get_nome(sc));
					fprintf(fTxt, "Nome => %s\nDescricao: %s\nEndereco %s/%c/%d\n",
							estabelecimento_get_nome(sc),
							estabelecimento_get_descricao(sct),
							estabelecimento_get_cep(sc),
							estabelecimento_get_face(sc),
							estabelecimento_get_num(sc));


					//usado para printar os estabelecimentos
					Comercio scc = createComercio(
							estabelecimento_get_cnpj(sc),
							estabelecimento_get_cnpj(sc),
							estabelecimento_get_cep(sc),
							estabelecimento_get_face(sc),
							estabelecimento_get_num(sc),
							estabelecimento_get_nome(sc)
							);
					insert(city.est, scc, 0);
				}
				else{
					printf("Problema no comando de!\n Verifique se o cnpj %s existe\n", cnpj);
				}

				fclose(fTxt);

			}
			else if(strncmp(line, "rip", 3) == 0){
				//pessoa morreu
				//
				fTxt = fopen(nomeTxt, "a");
				char cpf[50];
				sscanf(line, "rip %s", cpf);
				kill_pessoa(city, cpf, fTxt);

				fclose(fTxt);
			}
			else if(strncmp(line, "ecq?", 4) == 0){

				fTxt = fopen(nomeTxt, "a");
				//estabelecimento comercial numa dada regiao
				sscanf(line, "ecq? %s", cep);
				Lista estbl_quadra = hash_filter_to_list(city.comercio, _compareCepEstblcmto, cep);
				Node *n;
				fprintf(fTxt, "\n---- Estebelecimentos comerciais no cep %s ----\n", cep);
				for(n = getFirst(estbl_quadra); n != NULL; n = getNext(n)){
					Hash hd = list_get_data(n);
					Comercio sc = hash_get_data(hd);
					fprintf(fTxt, "Cnpj => %s\nNome =>%s\nTipo =>%s\n",estabelecimento_get_cnpj(sc),
							estabelecimento_get_nome(sc),
							estabelecimento_get_codt(sc));
				}
				destroyList(estbl_quadra);

				fclose(fTxt);
			}
			else if(strncmp(line, "ecr?", 4) == 0){
				//estabelecimento comercial de um dado tipo numa dada região
				fTxt = fopen(nomeTxt, "a");
				char tp[50];
				if(sscanf(line, "ecr? %s %lf %lf %lf %lf", tp, &x, &y, &w, &h) == 5){
					Rect r = createRect("", "", w, h, x, y);
					_hashSearchTipoInRect(city, r, tp, fTxt);
					free(r);
				}
				else{
					sscanf(line, "ecr? %s", tp);
					Lista estblc = hash_filter_to_list(city.comercio, _compareCodtEstblc, tp);
					Node *n;
					fprintf(fTxt, "\n---- Estabelecimentos comerciais do tipo %s ----\n", tp);
					for(n = getFirst(estblc); n != NULL; n = getNext(n)){
						Hash hd = list_get_data(n);
						Comercio sc = hash_get_data(hd);
						fprintf(fTxt, "Nome => %s\nEndereco =>%s/%c/%d\n", estabelecimento_get_nome(sc),
								estabelecimento_get_cep(sc),
								estabelecimento_get_face(sc),
								estabelecimento_get_num(sc));
					}
					destroyList(estblc);
				}
				fclose(fTxt);
			}
			else if(strncmp(line, "tecq?", 5) == 0){
				/* Lista os tipos de estabelecimentos comerciais de uma quadra */

				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "tecq? %s", cep);
				Lista estbl_quadra = hash_filter_to_list(city.comercio, _compareCepEstblcmto, cep);
				Node *n;
				fprintf(fTxt, "\n----Tipos de comercio da quadra com o CEP %s----\n", cep);
				for(n = getFirst(estbl_quadra); n != NULL; n = getNext(n)){
					Hash hd = list_get_data(n);
					Comercio sc = hash_get_data(hd);
					fprintf(fTxt, "Tipo => %s\n", estabelecimento_get_codt(sc));
				}

				fclose(fTxt);
				destroyList(estbl_quadra);
			}
			else if(strncmp(line, "tecr?", 5) == 0){
				/* Tipos de estabelecimentos numa dada regiao */
				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "tecr? %lf %lf %lf %lf", &x, &y, &w, &h);
				Rect r =  createRect("", "", w, h, x, y);
				_hashSearchEstblcInRect(city, r, fTxt);
				free(r);
				fclose(fTxt);
			}
			else if(strncmp(line, "hmpe?", 5) == 0){
				//Hidrante mais proximo do endereço
				char cep[50], face;
				int num;
				sscanf(line, "hmpe? %s %c %d", cep, &face, &num);
				Address a = createAddress(cep, face, num, "");
				insert(hmpeList, a, 0);


			}
			else if(strncmp(line, "hmp?", 4) == 0){
				//Hidrante mais porixmo da radio identificada por id
				char c[50];
				sscanf(line, "hmp? %s", c);
				kd_search(city.arvore_torre, hmpList, compareTorreId, c);

			}
			else if(strncmp(line, "fec", 3) == 0){
				//fehca estabelecimeno comercial
				fTxt = fopen(nomeTxt, "a");
				char cnpj[50];
				sscanf(line, "fec %s", cnpj);
				Comercio sc = remove_hash(city.comercio, cnpj);
				if(sc != NULL){
					fprintf(fTxt, "\n----Estabelecimento comercial fechado ----\n");
					fprintf(fTxt, "Nome => %s | CPNJ => %s | TIPO => %s\n", estabelecimento_get_nome(sc),
							estabelecimento_get_cnpj(sc),
							estabelecimento_get_codt(sc));
					free(sc);
				}
				else{
					printf("Erro comando fec\nNao achou comercio");

				}

				fclose(fTxt);
			}
			else if(strncmp(line, "mudec", 5) == 0){
				//estabelecimento mudou
				fTxt = fopen(nomeTxt, "a");
				char cnpj[50], cep[50], face;
				int num;
				sscanf(line, "mudec %s %s %c %d", cnpj, cep, &face, &num);
				Address novo = createAddress(cep, face, num, "");
				mudar_estbl(city, cnpj, novo, fTxt);
				fclose(fTxt);
			}
			else if(strncmp(line, "mud", 3) == 0){
				//pessoa mudou
				fTxt = fopen(nomeTxt, "a");
				char cpf[50], cep[50], face, comp[50];
				int num;
				sscanf(line, "mud %s %s %c %d %s", cpf, cep, &face, &num, comp);

				Address novo = createAddress(cep, face, num, comp);
				mudar_pessoa(city, cpf, novo, fTxt);
				fclose(fTxt);
			}

			else if(strncmp(line, "dpr", 3) == 0){
				//desapropriar regiao
				//
				fTxt = fopen(nomeTxt, "a");
				sscanf(line, "dpr  %lf %lf %lf %lf", &x, &y, &w, &h);
				Rect r = createRect("", "", w, h, x, y);
				desapropriar(city, r, fTxt);
				fclose(fTxt);
			}
			else if(strncmp(line, "@m?", 3) == 0){
				//salva o endereco do morador identificado por cpf no registrador R
				char cpf[50], str_R[5];
				int index;
				sscanf(line, "@m? %s %s ", str_R, cpf);
				index = str_R[1] - '0';
				Morador m = searchMorador(city.moradores, cpf);
				if(m != NULL){
					R[index] = city_get_ponto(city, morador_get_addr(m));
				}
				else{
					printf("Erro no comando @m\nMorador nao encontrado com cpf %s\n", cpf);
				}

			}
			else if(strncmp(line, "@e?", 3) == 0){
				//Armazena no R dado uma posicao

				char cep[50], face, str_R[5];
				int num, index;
				sscanf(line, "@e? %s %s %c %d", str_R, cep, &face, &num);
				index = str_R[1] - '0';
				Address endereco = createAddress(cep, face, num, "");
				R[index] = city_get_ponto(city, endereco);
				free(endereco);
			}
			else if(strncmp(line, "@g?", 3) == 0){
				//armazena no R a posicao de um equipamento dado o seu id

				char id[50], str_R[5];
				int index;
				sscanf(line, "@g? %s %s", str_R, id);
				index = str_R[1] - '0';
				void *elemento;
				if((elemento = search_id_hi(id, city.arvore_hidrante)) != NULL){
					R[index].x = hidrante_get_x(elemento);
					R[index].y = hidrante_get_y(elemento);
				}
				else if((elemento = search_id_to(id, city.arvore_torre)) != NULL){
					R[index].x = torre_get_x(elemento);
					R[index].y = torre_get_y(elemento);
				}
				else if((elemento = search_id_sem(id, city.arvore_semaforo)) != NULL){
					R[index].x = semaforo_get_x(elemento);
					R[index].y = semaforo_get_y(elemento);
				}
			}
			else if(strncmp(line, "@xy", 3) == 0){
				//armazena no R dado X e Y
				char str_R[5];
				int index;
				sscanf(line, "@xy %s %lf %lf", str_R, &x, &y);
				index = str_R[1] - '0';
				R[index].x = x;
				R[index].y = y;
			}
			else if(strncmp(line, "@tp?", 4) == 0){
				//armazena no R o estabelecimento comercial mais proximo de um dado registrador

				char str_R1[5], str_R2[5], tp[50];
				Ponto best_ponto;
				int index_r2, index_r1;
				sscanf(line, "@tp? %s %s %s", str_R1, tp, str_R2);
				index_r2 = str_R2[1] - '0';
				index_r1 = str_R1[1] - '0';
				Lista l = hash_filter_to_list(city.comercio, _compareCodtEstblc, tp);
				Node *n;
				float best_dist = FLT_MAX;
				//O(n)?
				for(n = getFirst(l); n != NULL; n = getNext(n)){
					Comercio c = hash_get_data(list_get_data(n));
					Ponto p = city_get_ponto(city, estabelecimento_get_address(c));
					if(best_dist > distancePoints(R[index_r2], p)){
						best_dist = distancePoints(R[index_r2], p);
						best_ponto = p;
						printf("%lf\n", best_ponto.x);
					}
				}
				R[index_r1] = best_ponto;
				destroyList(l);
			}
			else if(strncmp(line, "p?", 2) == 0){
				//formato é :
				//p? T D R5 R9
				//01234567891011
				if(line[3] == 't' || line[3] == 'T'){

					fTxt = fopen(nomeTxt, "a");
					int R1, R2;
					R1 = line[8] - '0';
					R2 = line[11] - '0';
					if(line[5] == 'D' || line[5] == 'd'){
						Lista l = createList();
						shortest_path(city.via, R[R1], R[R2], weightDistancia, l);
						viaTxtShortestPaths(city.via, l, fTxt);
						printf("%d\n", length(l));

						destroyList(l);


					}
					else{
						Lista l = createList();
						shortest_path(city.via, R[R1], R[R2], weightTempo, l);
						viaTxtShortestPaths(city.via, l, fTxt);
						printf("%d\n", length(l));
						destroyList(l);
					}

					fclose(fTxt);
				}
				else{
					char suffix[50], dt, cor[50];
					int r1, r2;
					sscanf(line, "p? p %s %c R%d R%d %s", suffix, &dt, &r1, &r2, cor);
					Circle c = createCircle("white", "green", 5, R[r1].x, R[r1].y);
					Circle c2 = createCircle("white", "black", 5, R[r2].x, R[r2].y);
					char *nome = criaString(leitura, "-", suffix);
					char *newString = criaString(dir, nome, ".svg");
					FILE *f_dijkstra = fopen(newString, "w");
					free(newString);
					free(nome);
					if(!f_dijkstra){
						printf("Erro ao criar arquivo comando p");
						exit(-1);
					}

					startSvg(f_dijkstra);
					traverseTreeQuadra(city.arvore_quadra, drawQuadra, f_dijkstra);
					traverseTreeSemaforo(city.arvore_semaforo, drawSemaforo, f_dijkstra);
					traverseTreeHidrante(city.arvore_hidrante, drawHidrante, f_dijkstra);
					traverseTreeTorre(city.arvore_torre, drawTorre, f_dijkstra);

					
					/* drawVias(city.via, f_dijkstra); */
					Vertice all = get_all_vertices(city.via);
					nearest_via(all, R[r1], f_dijkstra);
					nearest_via(all, R[r2], f_dijkstra);
					destroyList(all);

					if(dt == 'D' || dt == 'd'){

					Lista l = createList();
					shortest_path(city.via, R[r1], R[r2], weightDistancia, l);
					viaShortestPaths(city.via, l, f_dijkstra, cor);
					printf("%d\n", length(l));

					destroyList(l);
					}
					else{
						Lista l = createList();
						shortest_path(city.via, R[r1], R[r2], weightTempo, l);
						viaShortestPaths(city.via, l, f_dijkstra, cor);
						printf("%d\n", length(l));

						destroyList(l);
					}

					drawCircle(f_dijkstra, c);
					drawCircle(f_dijkstra, c2);
					/* drawVias(city.via, f_dijkstra); */
					free(c);
					free(c2);
					fprintf(f_dijkstra,"</svg>");
					fclose(f_dijkstra);

				}
			}
			else if(strncmp(line, "sp?", 3) == 0){
				//sp? t D n r1 r2 ... rn
				//012345678
				
				if(line[4] == 't' || line[4] == 'T'){

					fTxt = fopen(nomeTxt, "a");
					if(line[6] == 'D' || line[5] == 'd'){
						//Distância

					}
					else{
						//Tempo
					}

					fclose(fTxt);
				}
				else{
					char suffix[50], dt, first_color[50], second_color[50];
					int n;
					sscanf(line, "sp? p %s %c %d", suffix, &dt, &n);
					char *nome = criaString(leitura, "-", suffix);
					char *newString = criaString(dir, nome, ".svg");
					FILE *f_dijkstra = fopen(newString, "w");
					free(nome);
					free(newString);

					startSvg(f_dijkstra);
					traverseTreeQuadra(city.arvore_quadra, drawQuadra, f_dijkstra);
					traverseTreeSemaforo(city.arvore_semaforo, drawSemaforo, f_dijkstra);
					traverseTreeHidrante(city.arvore_hidrante, drawHidrante, f_dijkstra);
					traverseTreeTorre(city.arvore_torre, drawTorre, f_dijkstra);

					int indices[n];
					int i = 0, j = 0;
					char *tok = strtok(line, " ");


					while(tok != NULL){
						if(i > 4 && i < n + 5){
							indices[j] = tok[1] - '0';
							j++;
						}
						if(i == n + 5){
							strcpy(first_color, tok);

						}
						if(i == n + 6){
							strcpy(second_color, tok);
						}

						tok  = strtok(NULL, " ");
						i++;
					}
					if(dt == 'T' || dt == 't'){
						n_shortest_paths(
								city.via, R, indices, n, first_color, second_color, weightTempo, f_dijkstra);

					}
					else{
						//D
						n_shortest_paths(
								city.via, R, indices, n, first_color, second_color, weightDistancia, f_dijkstra);
					}
					fprintf(f_dijkstra, "</svg>");
					fclose(f_dijkstra);
				}

			}
			else if(strncmp(line, "au", 2) == 0){

				//insere carro
				char placa[50];
				sscanf(line, "au %s %lf %lf %lf %lf", placa, &x, &y, &w, &h);
				Carro carro = newCarro(placa, x, y, w, h);
				insert(city.lista_carros, carro, 0);
			}
			else if(strncmp(line, "rau", 3) == 0){

				fTxt = fopen(nomeTxt, "a");
				//remove carro
				char placa[50];
				sscanf(line, "rau %s", placa);
				void *data = search_del(city.lista_carros, cmp_placa, placa);
				double x = rect_get_x(carro_get_posic(data));
				double y = rect_get_y(carro_get_posic(data));
				fprintf(fTxt, "Carro com placa %s removido. Estava na posicao %lf %lf\n", carro_get_placa(data), x, y);
				free(carro_get_posic(data));
				free(data);

				fclose(fTxt);

			}
			else if(strncmp(line, "dc", 2) == 0){
				char sufixo[50];
				sscanf(line, "dc %s", sufixo);
				char *nome = criaString(leitura, "-", sufixo);
				char *newString = criaString(dir, nome, ".svg");
				FILE *f_colisao = fopen(newString, "w");
				free(newString);
				free(nome);

				startSvg(f_colisao);
				traverseTreeQuadra(city.arvore_quadra, drawQuadra, f_colisao);
				traverseTreeSemaforo(city.arvore_semaforo, drawSemaforo, f_colisao);
				traverseTreeHidrante(city.arvore_hidrante, drawHidrante, f_colisao);
				traverseTreeTorre(city.arvore_torre, drawTorre, f_colisao);
				for(Node *n = getFirst(city.lista_carros);  n != NULL; n = getNext(n)){
					drawCarro(f_colisao, list_get_data(n));
				}

				fTxt = fopen(nomeTxt, "a");
				car_overlap(city.via, city.lista_carros, car_cmp, f_colisao, fTxt);
				fprintf(f_colisao, "</svg>");
				fclose( f_colisao );
				fclose(fTxt);

			}
		}
		/*
		 * create new svg file after manipulating [deleting etc] the old list
		 */

		//it's time to print

		fSvgQry = fopen(qry_name, "w");
		if(!fSvgQry){
			fprintf(stderr, "bugou ao criar file");
			exit(-1);
		}

		startSvg(fSvgQry);
		drawCidade(city, fSvgQry);

		if(crb){

			fTxt = fopen(nomeTxt, "a");
			Ponto p;
			printa_closest(city.arvore_torre, closest_kd(city.arvore_torre,&p), fSvgQry, fTxt, tmp, printa_closest_torre);
			fclose(fTxt);
		}
		Node *nod;

		fTxt = fopen(nomeTxt, "a");
		for(nod = getFirst(hmpList); nod != NULL; nod = getNext(nod)){
			Torre st = list_get_data(nod);
			Ponto p = createPonto(torre_get_x(st), torre_get_y(st));
			Ponto best;
			float clos = nn(city.arvore_hidrante, p, &best);
			printa_closest_given_radio(city.arvore_hidrante, p,best, clos, fSvgQry, fTxt);
			fprintf(fTxt, "Id Radio => %s | COR => %s \n", torre_get_id(st), torre_get_fill(st));
		}
		for(nod = getFirst(hmpeList); nod != NULL; nod = getNext(nod)){
			Ponto best;
			float hid = nn(city.arvore_hidrante, city_get_ponto(city, nod->data), &best);
			printa_closest_given_p(city.arvore_hidrante, city_get_ponto(city, nod->data), best, hid, fSvgQry, fTxt);
		}
		fclose(fTxt);
		free(qry);
		free(qry_name);
		free(qry_nameString);
		fprintf(fSvgQry, "\n</svg>\n");
		fclose(fSvgQry);
		fclose(fQry);
	}
	fDraw = fopen(nomeSvg, "a");
	Node *nod;
	for(nod = getFirst(listC); nod != NULL; nod = getNext(nod)){
		StCircle *sc = (StCircle *) list_get_data(nod);
		drawCircle(fDraw, sc);
	}
	for(nod = getFirst(listR); nod != NULL; nod = getNext(nod)){
		StRect *sr = (StRect *) list_get_data(nod);
		drawRect(fDraw, sr);
	}
	fprintf(fDraw, "</svg>");
	//free them all
	fclose(fDraw);
	free(path);
	free(dir);
	free(leitura);
	free(nomeSvg);
	free(hmpList);
	free(hmpeList);
	free(nomeTxt);
	free(nomePath);
	free(ec);
	free(pm);
	free(sistema_viario);
	//destroying lists
	free_cidade(city);
	destroy(listC);
	destroy(listR);
	printf("\nPrograma executado\n");

	return 0;
}

