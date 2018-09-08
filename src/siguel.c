#include "modules/String/mystr.h"
#include "modules/Circle/circle.h"
#include "modules/Rect/rect.h"
#include "modules/Svg/svg.h"
#include "modules/Geometry/geometry.h"
#include "modules/Cidade/cidade.h"
#include "modules/Sort/sort.h"
#include "modules/Tree/kdtree.h"
#include "modules/Hash/hash_table.h"
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
	Cidade city = createCity();

	Circle c;
	Rect rect;



	char *path, *dir, *leitura, *nomeTxt, *nomeSvg, *nomePath, *qry, *ec, *pm;

	double r, x, y, w, h;
	FILE *fWrite, *fRead, *fTxt, *fDraw, *fQry, *fSvgQry, *fEc, *fPm;

	leitura = path = dir = qry = ec = pm = NULL;
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
		i++;
	}
	if(path==NULL){
		path = aloca_tamanho(3);
		strcpy(path, "./");
	}
	if(leitura == NULL || dir == NULL){
		fprintf(stderr, "siguel usage: siguel [-e path -q file.qry -ec file.ec -pm file.pm] -f arq.geo -o dir");
		exit(-1);
	}

	
	// -f 
	leitura[strlen(leitura) -4] = 0;

	nomeTxt = criaString(dir, leitura, ".txt");
	nomeSvg = criaString(dir, leitura, ".svg");

	nomePath = criaString(path, leitura, ".geo");

	fRead = fopen(nomePath, "r");

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

	startSvg(fDraw);

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
					insert(listC, createCircle(border, inside, r, x, y), id);
				}

				break;

			case 'r':
				sscanf(line, "r %d %s %s %lf %lf %lf %lf", &id, border, inside, &w, &h, &x, &y);
				insert(listR, createRect(border, inside, w, h, x, y), id);
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
				leitura = criaString(leitura, "-", suffix);
				leitura = criaString(dir, leitura, ".svg");
				printf("end: %s", path);
				fWrite = fopen(criaString(dir, criaString(leitura, "-", suffix), ".svg"), "w");

				if(fWrite == NULL)
					fprintf(stderr, "cant open file");
				startSvg(fWrite);

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
	if(ec != NULL){
		int num;
		ec[strlen(ec) -3] = 0;

		fEc =  fopen(criaString(path, ec, ".ec"), "r");
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
	if(pm != NULL){
		pm[strlen(pm) - 3] = 0;

		fPm = fopen(criaString(path, pm, ".pm"), "r");
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
		fSvgQry = fopen(qry_name, "w");

		if(!fSvgQry){
			fprintf(stderr, "bugou ao criar file");
			exit(-1);
		}
		startSvg(fSvgQry);
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
			else if(strncmp(line, "m?", 2) == 0){
				//moradores da quadra cujo cep é cep
				//
				sscanf(line, "m? %s", cep);
				if(search_cep(cep, city.arvore_quadra) == NULL){
					printf("CEP da quadra nao encontrado!\n %s", cep);
				}
				else{
					fprintf(fTxt, "\n----Moradores no Cep %s ----\n", cep);
					Lista mor_quadra = hash_filter_to_list(city.moradores, _compareCepMorador, cep);
					Node *n;
					for(n = getFirst(mor_quadra); n != NULL; n = n->next){
						HashData *hd =(HashData *) n->data;
						StPessoa *sp = (StPessoa *) search(city.pessoas, hd->key);
						fprintf(fTxt, "Nome => %s %s\n", sp->nome, sp->sobrenome);
						StMorador *sm = (StMorador *) hd->data;
						fprintf(fTxt, "Endereco => %s/%c/%d\n" , morador_get_cep(sm), morador_get_face(sm),
								morador_get_num(sm));
					}
					//need to handle freeing memory
					destroy(mor_quadra);
				}
			}
			else if(strncmp(line, "mr?", 3) == 0){
				//moradores em uma região r
				sscanf(line, "mr? %lf %lf %lf %lf", &x, &y, &w, &h);
				Rect r = createRect("", "", w,h,x,y);
				_hashSearchQuadraInRect(city, r, fTxt);
				free(r);
			}
			else if(strncmp(line, "dm?", 3) == 0){
				//imprime dados do morador indicado pelo cpf
				char cpf[50];
				sscanf(line, "dm? %s", cpf);
				StMorador  *sm = (StMorador *) search(city.moradores, cpf);
				StPessoa *sp = (StPessoa *) search(city.pessoas, cpf);
				if(sm != NULL && sp != NULL){
				fprintf(fTxt, "\nDados de => %s %s\n", sp->nome, sp->sobrenome);
					fprintf(fTxt, "Endereco => %s/%c/%d\n", morador_get_cep(sm),
						morador_get_face(sm), 
						morador_get_num(sm));

					insert(city.mor, sm, 0);
				}
				else{
					printf("Pessoa nao encontrada. Pode estar morta!\n");
				
				}
			}
			else if(strncmp(line, "de?", 3) == 0){
				//imprime todos os dados do estabelecimento comercial identificado por cnpj
				char cnpj[50];
				sscanf(line, "de? %s", cnpj);
				StComercio *sc = searchComercio(city.comercio, cnpj);
				StComercioTipo *sct = searchComercioTipo(city.tipo_comercio, estabelecimento_get_codt(sc));
				fprintf(fTxt, "\nEstabelecimento comercial identificado por -> %s\n", sc->cnpj);
				fprintf(fTxt, "Nome => %s\nDescricao: %s\nEndereco %s/%c/%d\n", sc->nome, sct->descricao,
						estabelecimento_get_cep(sc),
						estabelecimento_get_face(sc),
						estabelecimento_get_num(sc));
				insert(city.est, sc, 0);

			}
			else if(strncmp(line, "rip", 3) == 0){
				//pessoa morreu
				char cpf[50];
				sscanf(line, "rip %s", cpf);
				StPessoa *sp = searchPessoa(city.pessoas, cpf);
				StMorador *sm = searchMorador(city.moradores, cpf);
				if(sp != NULL && sm != NULL){
					if(sp->sexo == 'm' || sp->sexo == 'M'){
						fprintf(fTxt, "RIP %s %s, portador %s, do sexo Masculino, nascido a %s, residia no endereco %s/%d/%c", sp->nome, sp->sobrenome, sp->cpf, sp->nasc, morador_get_cep(sm), morador_get_num(sm), morador_get_face(sm));
					}
					else{
						fprintf(fTxt, "RIP %s %s, portador %s, do sexo Feminino, nascida a %s, residia no endereco %s/%d/%c", sp->nome, sp->sobrenome, sp->cpf, sp->nasc, morador_get_cep(sm), morador_get_num(sm), morador_get_face(sm));
					}
					remove_hash(city.pessoas, cpf);
				}
			}
			else if(strncmp(line, "ecq?", 4) == 0){
				//estabelecimento comercial numa dada regiao
				sscanf(line, "ecq? %s", cep);
					Lista estbl_quadra = hash_filter_to_list(city.comercio, _compareCepEstblcmto, cep);
					Node *n;
					fprintf(fTxt, "\n---- Estebelecimentos comerciais no cep %s ----\n", cep);
					for(n = getFirst(estbl_quadra); n != NULL; n = n->next){
						HashData *hd = (HashData *) n->data;
						StComercio * sc = (StComercio *) hd->data;
						fprintf(fTxt, "Cnpj => %s\nNome =>%s\nTipo =>%s\n",sc->cnpj, sc->nome, sc->codt);
					}
					destroy(estbl_quadra);

			}
			else if(strncmp(line, "ecr?", 4) == 0){
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
					for(n = getFirst(estblc); n != NULL; n = n->next){
						HashData *hd = (HashData *) n->data;
						StComercio *sc = (StComercio *) hd->data;
						fprintf(fTxt, "Nome => %s\nEndereco =>%s/%c/%d\n", sc->nome,
								estabelecimento_get_cep(sc),
								estabelecimento_get_face(sc), 
								estabelecimento_get_num(sc));
					}
					destroy(estblc);
				}
			}
			else if(strncmp(line, "tecq?", 5) == 0){
				sscanf(line, "tecq? %s", cep);
				/* Lista os tipos de estabelecimentos comerciais de uma quadra */
				Lista estbl_quadra = hash_filter_to_list(city.comercio, _compareCepEstblcmto, cep);
				Node *n;
				fprintf(fTxt, "\n----Tipos de comercio da quadra com o CEP %s----\n", cep);
				for(n = getFirst(estbl_quadra); n != NULL; n = n->next){
					HashData *hd = n->data;
					StComercio *sc = (StComercio *)hd->data;
					fprintf(fTxt, "Tipo => %s\n", sc->codt);
				}
				destroy(estbl_quadra);
			}
			else if(strncmp(line, "tecr?", 5) == 0){
				/* Tipos de estabelecimentos numa dada regiao */
				sscanf(line, "tecr? %lf %lf %lf %lf", &x, &y, &w, &h);
				Rect r =  createRect("", "", w, h, x, y);
				_hashSearchEstblcInRect(city, r, fTxt);
				free(r);
			}
			else if(strncmp(line, "hmpe?", 5) == 0){
				printf("Todo\n\n");
			}
			else if(strncmp(line, "fec", 3) == 0){
				char cnpj[50];
				sscanf(line, "fec %s", cnpj);
				StComercio *sc = remove_hash(city.comercio, cnpj);
				fprintf(fTxt, "\n----Estabelecimento comercial fechado ----\n");
				fprintf(fTxt, "Nome %s", sc->nome);
				free(sc);
			}
			else if(strncmp(line, "mud", 3) == 0){
				char cpf[50], cep[50], face, comp[50];
				int num;
				sscanf(line, "mud %s %s %c %d %s", cpf, cep, &face, &num, comp);
				StMorador *sm = searchMorador(city.moradores, cpf);
				StPessoa *sp = searchPessoa(city.pessoas, cpf);
				fprintf(fTxt, "\n----%s %s mudou ----\n", sp->nome, sp->sobrenome);
				fprintf(fTxt, "Antigo endereco => %s/%c/%d\n", morador_get_cep(sm), morador_get_face(sm), morador_get_num(sm));
				Ponto old = city_get_ponto(city, sm->addr);
				sm->addr = changeAddress(sm->addr, cep, face, num, comp);
				Ponto new = city_get_ponto(city, sm->addr);
				fprintf(fTxt, "Novo endereco => %s/%c/%d\n", morador_get_cep(sm), morador_get_face(sm), morador_get_num(sm));

				drawLineMudanca(fSvgQry,old, new);
			}


		}

		/*
		 * create new svg file after manipulating [deleting etc] the old list
		 */

		//it's time to print


		
		traverseTreeQuadra(city.arvore_quadra, drawQuadra, fSvgQry);
		traverseTreeSemaforo(city.arvore_semaforo, drawSemaforo, fSvgQry);
		traverseTreeHidrante(city.arvore_hidrante, drawHidrante, fSvgQry);
		traverseTreeTorre(city.arvore_torre, drawTorre, fSvgQry);
		Node *n;
		for(n = getFirst(city.mor); n != NULL; n = n->next){
			drawMorador(fSvgQry, city, n->data);
		}
		for(n = getFirst(city.est); n != NULL; n = n->next){
			drawEstabelecimento(fSvgQry, city, n->data);
		}

		
		//had to do this because the circle on svg would be printed before other elements and then be hidden
		if(crb){
				pointt(city.arvore_torre, closest_kd(city.arvore_torre), fSvgQry, fTxt );
		}

		free(qry);
		free(qry_name);
		free(qry_nameString);
		fprintf(fSvgQry, "\n</svg>\n");
		fclose(fSvgQry);
	}

	
	Node *nod;
	for(nod = getFirst(listC); nod != NULL; nod = nod->next){
		StCircle *sc = (StCircle *) nod->data;
		drawCircle(fDraw, sc);
	}
	for(nod = getFirst(listR); nod != NULL; nod = nod->next){
		StRect *sr = (StRect *) nod->data;
		drawRect(fDraw, sr);
	}
	
	fprintf(fDraw, "</svg>");

	//is there more allocated variables? 
	free(path);
	free(dir);
	free(leitura);
	free(nomeSvg);
	free(nomeTxt);
	free(nomePath);
	free(ec);
	free(pm);


	fclose(fRead);
	fclose(fTxt);
	fclose(fDraw);

	//destroying lists
	free_cidade(city);
	destroy(listC);
	destroy(listR);
	destroy(linha2);
	destroy(linha);
	return 0;
}

