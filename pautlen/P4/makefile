CC = gcc -c
CFLAGS = -g -Wall -pedantic
OBJ = pruebaSintactico.o tabla_simbolos.o hash.o elemento.o

all: pruebaSintactico

tabla_simbolos.o: tabla_simbolos.c tabla_simbolos.h elemento.h hash.h
	$(CC) $(CFLAGS) tabla_simbolos.c

elemento.o: elemento.c elemento.h
	$(CC) $(CFLAGS) elemento.c

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) hash.c

lex.yy.c: alfa.l
	flex alfa.l

y.tab.c: alfa.y
	bison -d -y -v alfa.y

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) y.tab.c

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) lex.yy.c

pruebaSintactico.o: pruebaSintactico.c
	$(CC) $(CFLAGS)  -o pruebaSintactico.o pruebaSintactico.c

pruebaSintactico: pruebaSintactico.o lex.yy.o y.tab.o
	$(CC) $(CFLAGS) -o pruebaSintactico pruebaSintactico.o lex.yy.o y.tab.o

generacion.o: generacion.c generacion.h
	$(CC) generacion.c

clean:
	rm -f prueba_tabla
	rm -f *.o y.output lex.yy.c y.tab.c pruebaSintactico
