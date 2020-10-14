/**
 * Autores: Sofia Sanchez y Jesus Daniel Franco
 * Fichero: prueba4.c
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

	p_afnd = AFNDNuevo("prueba4", 7, 2);

	AFNDInsertaSimbolo(p_afnd,"a");
	AFNDInsertaSimbolo(p_afnd,"b");

	AFNDInsertaEstado(p_afnd, "q0",INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", NORMAL);
	AFNDInsertaEstado(p_afnd, "q4", NORMAL);
	AFNDInsertaEstado(p_afnd, "q5", FINAL);
	AFNDInsertaEstado(p_afnd, "q6", FINAL);

	AFNDInsertaTransicion(p_afnd, "q3", "a", "q4");
	AFNDInsertaTransicion(p_afnd, "q4", "b", "q5");

	AFNDInsertaLTransicion(p_afnd, "q0", "q1");
	AFNDInsertaLTransicion(p_afnd, "q0", "q3");
	AFNDInsertaLTransicion(p_afnd, "q1", "q2");
	AFNDInsertaLTransicion(p_afnd, "q2", "q5");
	AFNDInsertaLTransicion(p_afnd, "q4", "q6");
	AFNDCierraLTransicion(p_afnd);

	afd  = AFNDTransforma(p_afnd);
	AFNDImprime(stdout,afd);
	AFNDADot(afd);
	AFNDADot(p_afnd);

	AFNDElimina(afd);
	AFNDElimina(p_afnd);

	return 0;
}
