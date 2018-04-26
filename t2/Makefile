TARGET = t2
DEPS = t2.o mystr.o circle.o rect.o static_list.o svg.o 
CC = gcc
FLAGS = -g -lm -Wall 

SOURCEDIR = ../modules
t2 : $(DEPS)
	$(CC) $(FLAGS) $(DEPS) -o $(TARGET)

t2.o : t2.c
	$(CC) -c t2.c

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
