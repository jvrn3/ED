TARGET = siguel
CC = gcc
FLAGS = -g -Wall -pedantic-errors -std=c99 -lm  -O2 -fstack-protector-all

DEPS = siguel.o \
	   mystr.o \
	   circle.o \
	   rect.o \
	   linked_list.o \
	   svg.o \
	   geometry.o \
	   cidade.o \
	   quadra.o \
	   semaforo.o \
	   hidrante.o \
	   torre.o \
	   sort.o \
	   kdtree.o \
	   hash_table.o \
	   comercio.o \
	   pessoa.o \
	   address.o \
	   morador.o \
	   rua.o \
	   graph.o \
	   carro.o \
	   via.o \
	   priority_queue.o 
SOURCEDIR = src/modules
TEST = src/unit_test

siguel : $(DEPS)
	$(info ********* TRABALHO 5 de Estrutura de Dados *********** )
	$(CC)  $(FLAGS) $(DEPS) -o siguel 

siguel.o : src/siguel.c
	$(CC) $(FLAGS) -c src/siguel.c
hash_table.o : $(SOURCEDIR)/Hash/hash_table.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Hash/hash_table.c

comercio.o : $(SOURCEDIR)/Comercio/comercio.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Comercio/comercio.c
pessoa.o : $(SOURCEDIR)/Pessoa/pessoa.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Pessoa/pessoa.c

morador.o : $(SOURCEDIR)/Morador/morador.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Morador/morador.c

address.o : $(SOURCEDIR)/Address/address.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Address/address.c

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

kdtree.o : $(SOURCEDIR)/Tree/kdtree.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Tree/kdtree.c

rua.o : $(SOURCEDIR)/Rua/rua.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Rua/rua.c

graph.o : $(SOURCEDIR)/Graph/graph.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Graph/graph.c

carro.o : $(SOURCEDIR)/Carro/carro.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Carro/carro.c

via.o : $(SOURCEDIR)/Via/via.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Via/via.c

priority_queue.o : $(SOURCEDIR)/Fila/priority_queue.c
	$(CC) $(FLAGS) -c $(SOURCEDIR)/Fila/priority_queue.c


test_graph.o : $(TEST)/test_graph.c
	$(CC) $(FLAGS) -c $(TEST)/test_graph.c

test_graph : test_graph.o graph.o rua.o hash_table.o linked_list.o priority_queue.o
	$(CC) test_graph.o graph.o rua.o hash_table.o linked_list.o priority_queue.o -o test_graph

test_tree.o : $(TEST)/test_tree.c
	$(CC) $(FlAGS) -c $(TEST)/test_tree.c

test_tree : test_tree.o kdtree.o rect.o geometry.o linked_list.o sort.o quadra.o semaforo.o hidrante.o torre.o 
	$(CC) $(FLAGS) test_tree.o kdtree.o geometry.o linked_list.o rect.o sort.o quadra.o semaforo.o hidrante.o torre.o -o test_tree

test_hash.o : $(TEST)/test_hash.c
	$(CC) $(FLAGS) -c $(TEST)/test_hash.c
test_hash : test_hash.o hash_table.o linked_list.o morador.o address.o
	$(CC) $(FLAGS) test_hash.o hash_table.o linked_list.o morador.o address.o -o test_hash

test_sort.o : $(TEST)/test_sort.c
	$(CC) $(FLAGS) -c $(TEST)/test_sort.c

test_sort : test_sort.o sort.o linked_list.o carro.o rect.o 
	$(CC) $(FLAGS) test_sort.o sort.o linked_list.o carro.o rect.o -o test_sort

test_pq.o : $(TEST)/test_pq.c
	$(CC) $(FLAGS) -c $(TEST)/test_pq.c
test_pq : test_pq.o priority_queue.o 
	$(CC) $(FLAGS) test_pq.o priority_queue.o  -o test_pq

test_lista.o : $(TEST)/test_lista.c
	$(CC) $(FLAGS) -c $(TEST)/test_lista.c

test_lista : rect.o linked_list.o test_lista.o
	$(CC) $(FLAGS) rect.o linked_list.o test_lista.o -o test_lista

clean: 
	$(info Apagando .o)
	rm -rf *.o vgcore* 
