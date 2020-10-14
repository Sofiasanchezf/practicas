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
#include "transforma.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;
	AFND * afd;

	p_afnd = AFNDNuevo("prueba1", 3, 2);

	AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");

	AFNDInsertaEstado(p_afnd, "q0",INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "f0", FINAL);

	AFNDInsertaTransicion(p_afnd, "q0", "0", "q0");
	AFNDInsertaTransicion(p_afnd, "q0", "1", "q0");
	AFNDInsertaTransicion(p_afnd, "q1", "1", "f0");

	AFNDInsertaLTransicion(p_afnd, "q0", "q1");
	AFNDCierraLTransicion(p_afnd);

	afd  = AFNDTransforma(p_afnd);
	AFNDImprime(stdout,afd);
	AFNDADot(afd);
	AFNDADot(p_afnd);

	AFNDElimina(afd);
	AFNDElimina(p_afnd);

	return 0;
}
