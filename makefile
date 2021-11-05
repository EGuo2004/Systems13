all: main.o
	gcc -o thirteen main.o
	
main.o: main.c
	gcc -c main.c

run:
	./thirteen
