CC = gcc -c
CFLAGS = -g -Wall -pedantic
OBJ = prueba_tabla.o tabla_simbolos.o hash.o elemento.o
all: prueba_tabla

prueba_tabla: $(OBJ)
	gcc $(OBJ) -o prueba_tabla

tabla_simbolos.o: tabla_simbolos.c tabla_simbolos.h elemento.h hash.h
	$(CC) $(CFLAGS) tabla_simbolos.c

elemento.o: elemento.c elemento.h
	$(CC) $(CFLAGS) elemento.c

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) hash.c

clean:
	rm -f prueba_tabla
	rm -f *.o
