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

	p_afnd = AFNDNuevo("prueba1", 3, 2);

	AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");

	AFNDInsertaEstado(p_afnd, "C",INICIAL_Y_FINAL);
	AFNDInsertaEstado(p_afnd, "D", FINAL);
	AFNDInsertaEstado(p_afnd, "E", NORMAL);

	AFNDInsertaTransicion(p_afnd, "C", "0", "D");
	AFNDInsertaTransicion(p_afnd, "C", "1", "E");
	AFNDInsertaTransicion(p_afnd, "D", "0", "D");
	AFNDInsertaTransicion(p_afnd, "D", "1", "E");
	AFNDInsertaTransicion(p_afnd, "E", "0", "C");
	AFNDInsertaTransicion(p_afnd, "E", "1", "E");

	AFNDCierraLTransicion(p_afnd);

	afd = AFNDMinimiza(p_afnd);
	AFNDImprime(stdout,afd);
	AFNDADot(afd);

	AFNDElimina(p_afnd);
	AFNDElimina(afd);

	return 0;
}
