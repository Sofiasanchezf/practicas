CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
CCFLAGS = -g -ansi 
OBJ = *.o

all: prueba1 prueba2 prueba3 prueba4 prueba5

prueba1: prueba1.o transforma.o afnd.o intermedia.o
	$(CC) $(CFLAGS) -o prueba1 prueba1.o transforma.o afnd.o intermedia.o

prueba2: prueba2.o transforma.o afnd.o intermedia.o
	$(CC) $(CFLAGS) -o prueba2 prueba2.o transforma.o afnd.o intermedia.o

prueba3: prueba3.o transforma.o afnd.o intermedia.o
	$(CC) $(CFLAGS) -o prueba3 prueba3.o transforma.o afnd.o intermedia.o

prueba4: prueba4.o transforma.o afnd.o intermedia.o
	$(CC) $(CFLAGS) -o prueba4 prueba4.o transforma.o afnd.o intermedia.o

prueba5: prueba5.o transforma.o afnd.o intermedia.o
	$(CC) $(CFLAGS) -o prueba5 prueba5.o transforma.o afnd.o intermedia.o

transforma.o: transforma.c transforma.h
	$(CC) $(CFLAGS) -c transforma.c

intermedia.o: intermedia.c intermedia.h
	$(CC) $(CFLAGS) -c intermedia.c

afnd.o: afnd.c afnd.h
	$(CC) $(CCFLAGS) -c afnd.c

clean:
	rm -rf pr_afnd prueba1 prueba2 prueba3 prueba4 prueba5 $(OBJ) *.dot
