all: graph

graph: libout.a main.c
	gcc -Wall main.c libout.a -o graph

libout.a: funcs.o graph.o
	ar rc libout.a funcs.o graph.o

graph.o: graph.c
	gcc -Wall -c graph.c

funcs.o: funcs.c
	gcc -Wall -c funcs.c

clean:
	rm -f *.o *.a graph