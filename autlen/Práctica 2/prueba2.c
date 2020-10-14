/**
 * Autores: Sofia Sanchez y Jesus Daniel Franco
 * Fichero: prueba1.c
 *
 * Contiene las funciones
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "minimiza.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;
	AFND * afd;

	p_afnd = AFNDNuevo("prueba2", 8, 2);

	AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");


	AFNDInsertaEstado(p_afnd, "A", INICIAL);
	AFNDInsertaEstado(p_afnd, "B", NORMAL);
	AFNDInsertaEstado(p_afnd, "C", FINAL);
	AFNDInsertaEstado(p_afnd, "D", NORMAL);
	AFNDInsertaEstado(p_afnd, "E", NORMAL);
	AFNDInsertaEstado(p_afnd, "F", NORMAL);
	AFNDInsertaEstado(p_afnd, "G", NORMAL);
	AFNDInsertaEstado(p_afnd, "H", NORMAL);


	AFNDInsertaTransicion(p_afnd, "A", "0", "B");
	AFNDInsertaTransicion(p_afnd, "A", "1", "F");
	AFNDInsertaTransicion(p_afnd, "B", "0", "G");
	AFNDInsertaTransicion(p_afnd, "B", "1", "C");
	AFNDInsertaTransicion(p_afnd, "C", "0", "A");
	AFNDInsertaTransicion(p_afnd, "C", "1", "C");
	AFNDInsertaTransicion(p_afnd, "D", "0", "C");
	AFNDInsertaTransicion(p_afnd, "D", "1", "G");
	AFNDInsertaTransicion(p_afnd, "E", "0", "H");
	AFNDInsertaTransicion(p_afnd, "E", "1", "F");
	AFNDInsertaTransicion(p_afnd, "F", "0", "C");
	AFNDInsertaTransicion(p_afnd, "F", "1", "G");
	AFNDInsertaTransicion(p_afnd, "G", "0", "G");
	AFNDInsertaTransicion(p_afnd, "G", "1", "E");
	AFNDInsertaTransicion(p_afnd, "H", "0", "G");
	AFNDInsertaTransicion(p_afnd, "H", "1", "C");

	AFNDCierraLTransicion(p_afnd);

	afd = AFNDMinimiza(p_afnd);
	AFNDImprime(stdout,afd);
	AFNDADot(afd);

	AFNDElimina(p_afnd);
	AFNDElimina(afd);

	return 0;
}
