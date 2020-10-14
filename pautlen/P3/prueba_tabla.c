#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabla_simbolos.h"

#define MAX_LINE 500
#define RETORNO "No encontrado porque no ha sido implementada la funcion"
#define NUMERO_PROPIEDADES 10

int main(int argc, char **argv)
{

	FILE * in = NULL;
	FILE * out = NULL;
	char tok[50];
	char tok_null[6] = "-1000"; /* -1000 == INICIALIZACIÓN POR DEFECTO */
	char * tok_line = NULL;
	char * clave = NULL;
	char * toks[NUMERO_PROPIEDADES] = {0};
	int error = -1;
	int i, j;
	char line[MAX_LINE] = "";
	TablaSimbolos * t = NULL;
	Elemento * elemento = NULL;

	if (argc != 3)
	{
		printf("Faltan argumentos de entrada.\n");
		return -1;
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if (!in || !out)
	{
		printf("Fallo al abrir los ficheros.\n");
		return -1;
	}

	/* INICIALIZACION DE LA TABLA SIMBOLOS */
	t = tablasimbolos_create();

	while (fgets(line, MAX_LINE, in))
	{
		elemento = NULL;
		tok_line = strtok(line, "\n");
		strcpy(tok, tok_line);
		clave = strtok(tok, "\t");

		for (i = 0; i < NUMERO_PROPIEDADES; i++) {
			toks[i] = strtok(NULL, " ");
			if(!toks[i])
				break;
		}
		for (j = i; j < NUMERO_PROPIEDADES; j++)
			toks[j] = tok_null;


		if (strcmp(clave, "cierre") == 0) {
				if (atoi(toks[0]) == -999) {
					error = tablasimbolos_cerrar_ambito_local(t);
					if (error < 0) {
						fprintf(out, "%s\n", clave);
					} else {
						fprintf(out, "%s\n", clave);
					}
				}
		}
		else if (i == 0) {
			error = buscar_elemento(t, clave, &elemento);
			if (error < 0) {
				fprintf(out, "%s -1\n", clave);
			} else if(error == TABLA_LOCAL) {
				fprintf(out, "%s %d\n", clave, elemento_getValor(elemento));
			} else if(error == TABLA_GLOBAL) {
				fprintf(out, "%s %d\n", clave, elemento_getValor(elemento));
			}
		}
		else if (atoi(toks[0]) < 0) {
			error = tablasimbolos_abir_ambito_local(t, clave, atoi(toks[0]), atoi(toks[1]),
																			atoi(toks[2]), atoi(toks[3]));
			if (error < 0) {
				fprintf(out, "-1 %s\n", clave);
			} else {
				fprintf(out, "%s\n", clave);
			}
		} else {

			error = insertar_elemento_ambito_actual(t, clave, atoi(toks[0]), atoi(toks[1]),
																			atoi(toks[2]), atoi(toks[3]), atoi(toks[4]),
																			atoi(toks[5]), atoi(toks[6]));
			if (error < 0) {
				fprintf(out, "-1 %s\n", clave);
			} else {
				fprintf(out, "%s\n", clave);
			}
		}
	}

	tablasimbolos_destroy(t);

	fclose(in);
	fclose(out);
	return 0;
}
