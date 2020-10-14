/**
 * Autores: Sofia Sanchez y Jesus Daniel Franco
 * Fichero: intermedia.h
 * 
 * Contiene las funciones 
 * 
 */

#ifndef INTERMEDIA_H
#define INTERMEDIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"

#define MAX_NOMBRE 500
#define MAX_TRANSICIONES 500

/*****************************************************/
/************* DEFINICION DE ESTRUCTURAS *************/
/*****************************************************/

/**
 * Estructura Transicion
 *  En esta estructura guardaremos el nombre del simbolo con el que podemos ir al estado destino, el nombre del estado destino 
 *  y la codificacion del estado destino
 * 
 */
typedef struct _Transicion Transicion;

/**
 * Estructura Intermedia
 *  En esta estructura guardaremos todo lo necesario para definir los estados del automata finito determinista. 
 *  Tendremos el nombre del estado en el que estamos, la codificiacion del estado, el tipo de estado que es y las transiciones que tiene este
 *  estado para pasar a otros estados destinos
 * 
 */
typedef struct _Intermedia Intermedia;

/**
 * Crear_transicion
 *
 * Desde un estado inicial define una transicion a otro estado por medio
 * de un símbolo determinado
 *
 * Argumentos de entrada:
 *  - num_estados: numero de estados del automata finito no determinista
 *  - simbolo: cadena de caracteres para el simbolo
 *  - final: codificacion para el estado destino
 *  - estado_final: nombre del estado destino
 *
 * Salida:
 *   transicion creada si se crea de manera satisfactoria
 *   NULL en caso de error
 */
Transicion *crear_transicion(int num_estados, char* simbolo, char* final, int *estado_final);

/**
 * Eliminar_transicion
 *
 * Libera toda la memoria de la transicion pasada como argumento
 *
 * Argumentos de entrada:
 *  - transicion: tranasicion de la que queremos liberar memoria
 *
 */
void eliminar_transicion(Transicion *transicion);

/**
 * Crear_intermedia
 *
 * Creación de un estado del autómata finito determinista. Le reservamos memoria e inicializamos sus atributos.
 *
 * Argumentos de entrada:
 *  - nombre: nombre del estado
 *  - num_estados: numero de estados del automata finito no determinista
 *  - tipo: tipo que va a ser el estado
 *  - estado: codificacion del estado
 *
 * Salida:
 *   estado del AFD creado si se crea de manera satisfactoria
 *   NULL en caso de error
 */
Intermedia *crear_intermedia(char* nombre, int num_estados, int tipo, int *estado);

/**
 * Eliminar_intermedia
 *
 * Libera toda la memoria del estado del AFD pasado como argumento
 *
 * Argumentos de entrada:
 *  - intermedia: puntero a una estructura intermedia que es un estado del automata finito determinista
 *
 * Salida:
 *   void
 */
void eliminar_intermedia(Intermedia *intermedia);


/**
 * Comparar_codificacion
 *
 * Compara que si dos codificaciones representan al mismo estado o no
 *
 * Argumentos de entrada:
 *  - codificacion1: una de las codificaciones que vamos a comparar
 *  - codificacion2: una de las codificaciones que vamos a comparar
 *  - num_estados: numero de estados del automata finito no determinista
 *
 * Salida:
 *   1 si los estados son iguales
 *   0 si los estados son diferentes
 *   -1 en caso de error
 */
int comparar_codificacion(int *codificacion1, int *codificacion2, int num_estados);


/**
 * is_estado_in
 *
 * Determina si un estado ya está en la lista creados que recibe como argumento de entrada. Para ello compararemos la codificacion que recibimos como
 * argumento de entrada con las que se encuentran en la lista de creados
 *
 * Argumentos de entrada:
 *  - codificacion:  codificacion que vamos a comparar si esta en la lista creados o no
 *  - creados: lista formado por estados del automata donde miraremos si ya hay una codificacion
 *  - num_estados: numero de estados del automata finito no determinista
 *  - num_creados: 
 *
 * Salida:
 *   1 si ya está en creado
 *   0 si no lo está
 *   -1 en caso de error
 */
int is_estado_in(int *codificacion, Intermedia **creados, int num_estados, int num_creados);

/**
 * Imprimir_intermedia
 *
 * Nos permite mostrar por pantalla los datos de la estructura intermedia
 *
 * Argumentos de entrada:
 *  - intermedia: puntero a una estructura intermedia que es un estado del automata finito determinista
 *  - num_estados: numero de estados del automata finito no determinista
 *
 */
void imprimir_intermedia(Intermedia *intermedia, int num_estados) ;

/**
 * Imprimir_transiscion
 *
 * Nos permite mostrar por pantalla los datos de la estructura para las transiciones
 *
 * Argumentos de entrada:
 *  - transicion: puntero a una estructura transicion
 *  - num_estados: numero de estados del automata finito no determinista
 *
 */
void imprimir_transicion(Transicion *transicion, int num_estados);

/**
 * 
 * Imprimir_codificacion
 *
 * Nos permite imprimir un array de teneros donde tenemos guardada una codificacion
 *
 * Argumentos de entrada:
 *  - cod: array de enteros con la codificacion
 *  - num_estados: numero de estados del automata finito no determinista
 * 
 */
void imprimir_codificiacion(int *cod, int num_estados);

/**
 * Get_intermedia_codificacion
 * 
 * Nos permite obtener la codificacion de la estructura intermedia
 * 
 * Argumentos de entrada:
 *  - intermedia: puntero a una estructura intermedia que es un estado del automata finito determinista
 * 
 * Salida:
 *   Codificacion de la estructura intermedia
 * 
 */
int *get_intermedia_codificacion(Intermedia *intermedia);

/**
 * Set_intermedia_transicion
 * 
 * Nos permite introducir una transicion en las transiciones de la estructura intermedia en la posicion que recibe como argumento de entrada
 * 
 * Argumentos de entrada:
 *  - intermedia: puntero a una estructura intermedia que es un estado del automata finito determinista
 *  - posicion: numero entero con la posicion
 *  - transicicion: punteor a una estructura transicion
 * 
 */
void set_intermedia_transicion(Intermedia *intermedia, int posicion, Transicion *transicion);

/**
 * Get_intermedia_transicion
 * 
 * Nos permite obtener la transicion en la posicion pasada como argumento de entrada de las transiciones de la estructura intermedia
 * 
 * Argumentos de entrada:
 *  - intermedia: puntero a una estructura intermedia que es un estado del automata finito determinista
 *  - posicion: numero entero con la posicion
 * 
 * Salida:
 *  Transicion de la estructura en la posicion "posicion"
 * 
 */
Transicion *get_intermedia_transicion(Intermedia *intermedia, int posicion);

/**
 * Get_intermedia_nombre
 * 
 * Nos permite obtener el nombre de la estructura intermedia
 * 
 * Argumentos de entrada:
 *  - intermedia: puntero a una estructura intermedia que es un estado del automata finito determinista
 * 
 * Salida:
 *  nombre de la estructura intermedia
 * 
 */
char *get_intermedia_nombre(Intermedia *intermedia);

/**
 * set_intermedia_nombre
 * 
 * Nos permite cambiar el nombre_estado de la estructura intermedia y poner el nombre que recibe como argumento de entrada
 * 
 * Argumentos de entrada:
 *  - intermedia: puntero a una estructura intermedia que es un estado del automata finito determinista
 *  - nombre: cadena de caracteres con el nombre
 * 
 */
void set_intermedia_nombre(Intermedia *intermedia, char *nombre);

/**
 * get_intermedia_tipo
 * 
 * Argumentos de entrada:
 *  - intermedia: puntero a una estructura intermedia que es un estado del automata finito determinista
 * 
 * Salida:
 *  tipo de la estructura intermedia
 * 
 */
int get_intermedia_tipo(Intermedia *intermedia);

/**
 * Set_intermedia_tipo
 * 
 * Argumentos de entrada:
 *  - intermedia: puntero a una estructura intermedia que es un estado del automata finito determinista
 *  - tipo:
 * 
 */
void set_intermedia_tipo(Intermedia *intermedia, int tipo);

/**
 * Get_transicion_simbolo
 * 
 * Argumentos de entrada:
 *  - transicion: putnero a una estructura transicion
 * 
 * Salida:
 *  simbolo de la transicion
 * 
 */
char *get_transicion_simbolo(Transicion *transicion);

/**
 * Get_transicion_estadofinal
 * 
 * Argumentos de entrada:
 *  - transicion: puntero a una estructura transicion
 * 
 * Salida:
 *  nombre del estado final de la transicion
 * 
 */
char *get_transicion_estadofinal(Transicion *transicion);

#endif
