TARGET = siguel
DEPS = siguel.o mystr.o circle.o rect.o static_list.o svg.o 
CC = gcc
FLAGS = -g -lm -Wall -pedantic-errors -ansi -O2


SOURCEDIR = ../modules
siguel : $(DEPS)
	$(CC) $(FLAGS) $(DEPS) -o siguel

siguel.o : siguel.c
	$(CC) -c siguel.c

mystr.o : $(SOURCEDIR)/String/mystr.c
	$(CC) -c $(SOURCEDIR)/String/mystr.c

circle.o : $(SOURCEDIR)/Circle/circle.c
	$(CC) -c $(SOURCEDIR)/Circle/circle.c

rect.o : $(SOURCEDIR)/Rect/rect.c
	$(CC) -c $(SOURCEDIR)/Rect/rect.c

static_list.o : $(SOURCEDIR)/Lista/static_list.c
	$(CC) -c $(SOURCEDIR)/Lista/static_list.c

svg.o : $(SOURCEDIR)/Svg/svg.c
	$(CC) -c $(SOURCEDIR)/Svg/svg.c

clean: 
	rm *.o
