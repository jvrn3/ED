TARGET = siguel
DEPS = siguel.o mystr.o circle.o rect.o static_list.o svg.o geometry.o palmeiras.o
CC = gcc
FLAGS = -g -Wall -pedantic-errors -ansi -lm -O2


SOURCEDIR = ../modules
siguel : $(DEPS)
	$(CC)  $(FLAGS) $(DEPS) -o siguel 

siguel.o : siguel.c
	$(CC) $(FLAGS) -c siguel.c

mystr.o : $(SOURCEDIR)/String/mystr.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/String/mystr.c

circle.o : $(SOURCEDIR)/Circle/circle.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Circle/circle.c

rect.o : $(SOURCEDIR)/Rect/rect.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Rect/rect.c

static_list.o : $(SOURCEDIR)/Lista/static_list.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Lista/static_list.c

svg.o : $(SOURCEDIR)/Svg/svg.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Svg/svg.c

geometry.o : $(SOURCEDIR)/Geometry/geometry.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Geometry/geometry.c
palmeiras.o : palmeiras.c
	$(CC) $(FLAGS) -c palmeiras.c
clean: 
	rm *.o
