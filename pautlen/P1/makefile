all: compilar_ejercicio1 compilar_ejercicio2 compilar_ejercicio3 compilar_ejercicio4 compilar_ejercicio5	compilar_ejercicio6	compilar_ejercicio7 compilar_ej2 compilar_ej3 limpiar_

compilar_ejercicio1: generacion.o generacion.h
	gcc -c ejemplo1_generacion.c
	gcc -o ej1_c generacion.o ejemplo1_generacion.o
	./ej1_c ej1.asm
	nasm -g -o ej1.o -f elf32 ej1.asm
	gcc -m32 -o ej1_f ej1.o alfalib.o

compilar_ejercicio2: generacion.o generacion.h
	gcc -c ejemplo2_generacion.c
	gcc -o ej2_c generacion.o ejemplo2_generacion.o
	./ej2_c ej2.asm
	nasm -g -o ej2.o -f elf32 ej2.asm
	gcc -m32 -o ej2_f ej2.o alfalib.o

compilar_ejercicio3: generacion.o generacion.h
	gcc -c ejemplo3_generacion.c
	gcc -o ej3_c generacion.o ejemplo3_generacion.o
	./ej3_c ej3.asm
	nasm -g -o ej3.o -f elf32 ej3.asm
	gcc -m32 -o ej3_f ej3.o alfalib.o

compilar_ejercicio4: generacion.o generacion.h
	gcc -c ejemplo4_generacion.c
	gcc -o ej4_c generacion.o ejemplo4_generacion.o
	./ej4_c ej4.asm
	nasm -g -o ej4.o -f elf32 ej4.asm
	gcc -m32 -o ej4_f ej4.o alfalib.o

compilar_ejercicio5: generacion.o generacion.h
	gcc -c ejemplo5_generacion.c
	gcc -o ej5_c generacion.o ejemplo5_generacion.o
	./ej5_c ej5.asm
	nasm -g -o ej5.o -f elf32 ej5.asm
	gcc -m32 -o ej5_f ej5.o alfalib.o

compilar_ejercicio6: generacion.o generacion.h
	gcc -c ejemplo6_generacion.c
	gcc -o ej6_c generacion.o ejemplo6_generacion.o
	./ej6_c ej6.asm
	nasm -g -o ej6.o -f elf32 ej6.asm
	gcc -m32 -o ej6_f ej6.o alfalib.o

compilar_ejercicio7: generacion.o generacion.h
	gcc -c ejemplo7_generacion.c
	gcc -o ej7_c generacion.o ejemplo7_generacion.o
	./ej7_c ej7.asm
	nasm -g -o ej7.o -f elf32 ej7.asm
	gcc -m32 -o ej7_f ej7.o alfalib.o

compilar_ej2: generacion.o generacion.h
	gcc -c ej2.c
	gcc -o ej2_opcional_c generacion.o ej2.o
	./ej2_opcional_c ej2_opcional.asm
	nasm -g -o ej2_opcional.o -f elf32 ej2_opcional.asm
	gcc -m32 -o ej2_opcional_f ej2_opcional.o alfalib.o

compilar_ej3: generacion.o generacion.h
	gcc -c ej3.c
	gcc -o ej3_opcional_c generacion.o ej3.o
	./ej3_opcional_c ej3_opcional.asm
	nasm -g -o ej3_opcional.o -f elf32 ej3_opcional.asm
	gcc -m32 -o ej3_opcional_f ej3_opcional.o alfalib.o


limpiar_:
	rm -f *_c
	rm -f ej*.o
	mkdir asm_files
	mv ej*.asm asm_files

generacion.o: generacion.c generacion.h
	gcc -c generacion.c

clean:
	mv alfalib.o alfalib
	rm -f *.o
	mv alfalib alfalib.o
	rm -f *_f
	rm -f *_c
	rm -f *.asm
	rm -r -f asm_files
