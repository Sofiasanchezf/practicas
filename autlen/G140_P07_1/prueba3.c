/**
 * Autores: Sofia Sanchez y Jesus Daniel Franco
 * Fichero: prueba3.c
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

	/*p_afnd = AFNDNuevo("prueba3", 6, 13);*/
  p_afnd = AFNDNuevo("prueba3", 6, 4);

	/*
	Para la representación de este autómata hemos optado por juntar los símobolos
	de transición numérica para facilitar la comprensión visual del afd
	*/

	/*AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");
	AFNDInsertaSimbolo(p_afnd,"2");
	AFNDInsertaSimbolo(p_afnd,"3");
	AFNDInsertaSimbolo(p_afnd,"4");
	AFNDInsertaSimbolo(p_afnd,"5");
	AFNDInsertaSimbolo(p_afnd,"6");
	AFNDInsertaSimbolo(p_afnd,"7");
	AFNDInsertaSimbolo(p_afnd,"8");
	AFNDInsertaSimbolo(p_afnd,"9");*/

	  AFNDInsertaSimbolo(p_afnd,"0,...,9");
	AFNDInsertaSimbolo(p_afnd,"+");
	AFNDInsertaSimbolo(p_afnd,"-");
	AFNDInsertaSimbolo(p_afnd,".");

	AFNDInsertaEstado(p_afnd, "q0",INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "f3", NORMAL);
	AFNDInsertaEstado(p_afnd, "q4", NORMAL);
	AFNDInsertaEstado(p_afnd, "q5", FINAL);

	AFNDInsertaTransicion(p_afnd, "q0", "+", "q1");
  AFNDInsertaTransicion(p_afnd, "q0", "-", "q1");


  AFNDInsertaTransicion(p_afnd, "q1", "0,...,9", "q1");
	/*AFNDInsertaTransicion(p_afnd, "q1", "0", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "1", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "2", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "3", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "4", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "5", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "6", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "7", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "8", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "9", "q1");*/


  AFNDInsertaTransicion(p_afnd, "q1", "0,...,9", "q4");
  /*AFNDInsertaTransicion(p_afnd, "q1", "0", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", "1", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", "2", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", "3", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", "4", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", "5", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", "6", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", "7", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", "8", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", "9", "q4");*/

	AFNDInsertaTransicion(p_afnd, "q1", ".", "q2");


  AFNDInsertaTransicion(p_afnd, "q2", "0,...,9", "f3");
	/*AFNDInsertaTransicion(p_afnd, "q2", "0", "f3");
	AFNDInsertaTransicion(p_afnd, "q2", "1", "f3");
	AFNDInsertaTransicion(p_afnd, "q2", "2", "f3");
	AFNDInsertaTransicion(p_afnd, "q2", "3", "f3");
	AFNDInsertaTransicion(p_afnd, "q2", "4", "f3");
	AFNDInsertaTransicion(p_afnd, "q2", "5", "f3");
	AFNDInsertaTransicion(p_afnd, "q2", "6", "f3");
	AFNDInsertaTransicion(p_afnd, "q2", "7", "f3");
	AFNDInsertaTransicion(p_afnd, "q2", "8", "f3");
	AFNDInsertaTransicion(p_afnd, "q2", "9", "f3");*/

  AFNDInsertaTransicion(p_afnd, "f3", "0,...,9", "f3");
  /*AFNDInsertaTransicion(p_afnd, "f3", "0", "f3");
	AFNDInsertaTransicion(p_afnd, "f3", "1", "f3");
	AFNDInsertaTransicion(p_afnd, "f3", "2", "f3");
	AFNDInsertaTransicion(p_afnd, "f3", "3", "f3");
	AFNDInsertaTransicion(p_afnd, "f3", "4", "f3");
	AFNDInsertaTransicion(p_afnd, "f3", "5", "f3");
	AFNDInsertaTransicion(p_afnd, "f3", "6", "f3");
	AFNDInsertaTransicion(p_afnd, "f3", "7", "f3");
	AFNDInsertaTransicion(p_afnd, "f3", "8", "f3");
	AFNDInsertaTransicion(p_afnd, "f3", "9", "f3");*/

  AFNDInsertaTransicion(p_afnd, "q4", ".", "f3");

	AFNDInsertaLTransicion(p_afnd, "q0", "q1");
  AFNDInsertaLTransicion(p_afnd, "f3", "q5");
	AFNDCierraLTransicion(p_afnd);

	afd  = AFNDTransforma(p_afnd);
	AFNDImprime(stdout,afd);
	AFNDADot(afd);
	AFNDADot(p_afnd);

	AFNDElimina(afd);
	AFNDElimina(p_afnd);

	return 0;
}
