CC = gcc
CFLAGS = -Wall -g
OBJ = main.o mochila.o item.o

run:
	./main

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

main.o: main.c mochila.h item.h
	$(CC) $(CFLAGS) -c main.c

mochila.o: mochila.c mochila.h item.h
	$(CC) $(CFLAGS) -c mochila.c

item.o: item.c item.h
	$(CC) $(CFLAGS) -c item.c

clean:
	rm -f *.o main
