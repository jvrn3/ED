TARGET = siguel
DEPS = siguel.o mystr.o circle.o rect.o linked_list.o svg.o geometry.o  cidade.o quadra.o semaforo.o hidrante.o torre.o sort.o kdtree.o
CC = gcc
FLAGS = -g -Wall -pedantic-errors -std=c99 -lm  -O2 -fstack-protector-all


SOURCEDIR = src/modules
siguel : $(DEPS)
	$(CC)  $(FLAGS) $(DEPS) -o siguel 

siguel.o : src/siguel.c
	$(CC) $(FLAGS) -c src/siguel.c

mystr.o : $(SOURCEDIR)/String/mystr.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/String/mystr.c

circle.o : $(SOURCEDIR)/Circle/circle.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Circle/circle.c

rect.o : $(SOURCEDIR)/Rect/rect.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Rect/rect.c

linked_list.o : $(SOURCEDIR)/Lista/linked_list.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Lista/linked_list.c

svg.o : $(SOURCEDIR)/Svg/svg.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Svg/svg.c

cidade.o : $(SOURCEDIR)/Cidade/cidade.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Cidade/cidade.c
sort.o : $(SOURCEDIR)/Sort/sort.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Sort/sort.c
geometry.o : $(SOURCEDIR)/Geometry/geometry.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Geometry/geometry.c
quadra.o : $(SOURCEDIR)/Quadra/quadra.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Quadra/quadra.c
semaforo.o : $(SOURCEDIR)/Semaforo/semaforo.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Semaforo/semaforo.c
hidrante.o : $(SOURCEDIR)/Hidrante/hidrante.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Hidrante/hidrante.c
torre.o : $(SOURCEDIR)/Torre/torre.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Torre/torre.c
# palmeiras.o : src/palmeiras.c
	# $(CC) $(FLAGS) -c src/palmeiras.c
kdtree.o : $(SOURCEDIR)/Tree/kdtree.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Tree/kdtree.c
clean: 
	rm *.o
