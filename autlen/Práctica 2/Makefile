CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
CCFLAGS = -g -ansi
OBJ = *.o

all: prueba1 prueba2 prueba3

prueba1: prueba1.o afnd.o intermedia.o minimiza.o
	$(CC) $(CFLAGS) -o prueba1 prueba1.o afnd.o intermedia.o minimiza.o

prueba2: prueba2.o afnd.o intermedia.o minimiza.o
	$(CC) $(CFLAGS) -o prueba2 prueba2.o afnd.o intermedia.o minimiza.o

prueba3: prueba3.o afnd.o intermedia.o minimiza.o
	$(CC) $(CFLAGS) -o prueba3 prueba3.o afnd.o intermedia.o minimiza.o

minimiza.o: minimiza.c minimiza.h
	$(CC) $(CFLAGS) -c minimiza.c

intermedia.o: intermedia.c intermedia.h
	$(CC) $(CFLAGS) -c intermedia.c

afnd.o: afnd.c afnd.h
	$(CC) $(CCFLAGS) -c afnd.c

clean:
	rm -rf pr_afnd prueba1 prueba2 prueba3 $(OBJ) *.dot
