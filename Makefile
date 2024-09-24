all: compile
	gcc -o exe item.o forca_bruta.o main.o -std=c99 -Wall

compile:
	gcc -c forca_bruta.c main.c item.c
clean:
	rm *.o exe
run:
	./exe