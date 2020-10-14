all: pruebaMorfo

pruebaMorfo: pruebaMorfo.o lex.yy.o
	gcc -Wall -g -o pruebaMorfo pruebaMorfo.o lex.yy.o

lex.yy.c: alfa.l
	flex alfa.l

lex.yy.o: lex.yy.c
	gcc -Wall -g -c lex.yy.c

clean:
	rm lex.yy.o lex.yy.c pruebaMorfo
