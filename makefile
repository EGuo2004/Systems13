all: stuff.o
	gcc -o thirteen stuff.o
	
stuff.o: stuff.c
	gcc -c stuff.c

run:
	./thirteen
