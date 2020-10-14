/**
 * Autores: Sofia Sanchez y Jesus Daniel Franco
 * Fichero: transforma.h
 *
 * Contiene las funciones
 *
 */

#ifndef TRANSFORMA_H
#define TRANSFORMA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "intermedia.h"


/**
 * AFNDTransforma
 *
 * Transforma un AFND en un AFD equivalente
 *
 * Argumentos de entrada:
 *  - afnd: Automata no determinista que vamos a transformar
 *
 * Salida:
 *   Automata determinista creado
 *   NULL en caso de error
 */

AFND* AFNDTransforma(AFND* afnd);

#endif
