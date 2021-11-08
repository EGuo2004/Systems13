all: stuff.o
	gcc -o thirteen stuff.o

stuff.o: stuff.c
	gcc -c stuff.c

read_csv:
	./thirteen -read_csv

read_data:
	./thirteen -read_data

add_data:
	./thirteen -add_data

update_data:
	./thirteen -update_data
