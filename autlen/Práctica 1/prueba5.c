/**
 * Autores: Sofia Sanchez y Jesus Daniel Franco
 * Fichero: prueba5.c
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

	p_afnd = AFNDNuevo("prueba5", 4, 2);

	AFNDInsertaSimbolo(p_afnd,"a");
	AFNDInsertaSimbolo(p_afnd,"b");

	AFNDInsertaEstado(p_afnd, "q0",INICIAL_Y_FINAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", FINAL);
	AFNDInsertaEstado(p_afnd, "q3", NORMAL);

	AFNDInsertaTransicion(p_afnd, "q0", "a", "q1");

	AFNDInsertaTransicion(p_afnd, "q1", "a", "q0");
	AFNDInsertaTransicion(p_afnd, "q1", "b", "q0");
	AFNDInsertaTransicion(p_afnd, "q1", "a", "q3");
	AFNDInsertaTransicion(p_afnd, "q1", "b", "q3");
	AFNDInsertaTransicion(p_afnd, "q1", "a", "q2");

	AFNDInsertaTransicion(p_afnd, "q3", "b", "q0");
	AFNDInsertaTransicion(p_afnd, "q3", "b", "q2");

	AFNDInsertaLTransicion(p_afnd, "q1", "q2");
	AFNDInsertaLTransicion(p_afnd, "q2", "q3");
	AFNDInsertaLTransicion(p_afnd, "q3", "q2");
	AFNDInsertaLTransicion(p_afnd, "q3", "q3");

	AFNDCierraLTransicion(p_afnd);

	afd  = AFNDTransforma(p_afnd);
	AFNDImprime(stdout,afd);
	AFNDADot(afd);
	AFNDADot(p_afnd);

	AFNDElimina(afd);
	AFNDElimina(p_afnd);

	return 0;
}
