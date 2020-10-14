#ifndef HASH_H
#define HASH_H

#include "types.h"
#include "elemento.h"

/*! @brief Estructura Hash
 *
 *  Implementacion de una estructura hash mediante tablas.
 */
typedef struct _Hash Hash;

/*! @brief Creacion de hash
 *
 *  Crea una nueva tabla hash
 *  @param maxElementos El numero maximo de elementos en el hash
 *  @return El puntero al hash creado
 */
Hash *hash_create();

/*! @brief liberacion de hash
 *
 *  Libera una tabla hash dada por argumento
 *  @param h El hash a liberar
 */
void hash_destroy(Hash *h);

/*! @brief Comprueba si un hash esta vacio
*
*  Comprueba si un hash dado por argumento esta vacio.
*  @param h El hash a evaluar
*  @return true si esta vacio, false en otro caso.
*/
bool hash_isVacio(Hash *h);

/*! @brief Añade un elemento al hash.
*
*  Añade un elemento al hash con su clave correspondiente en la última posición.
*  @param h El hash
*  @param n El elemento a insertar
*  @param c La clave del elemento
*  @return OK si es correcto, ERROR en caso contrario.
*/
int hash_addElemento(Hash *h, Elemento *n, char *c);

/*! @brief Borra un elemento del hash.
*
*  Borra un elemento del hash y su clave correspondiente. Mueve el último elemento a
*  la posición del elemento borrado.
*  @param h El hash
*  @param c La clave del elemento
*  @return OK si es correcto, ERROR en caso contrario.
*/
Elemento *hash_extractElemento(Hash *h, char *c);

/*! @brief Busca un elemento en el hash.
*
*  Busca un elemento en el hash mediante su clave y devuelve la posicion
*  @param h El hash
*  @param c La clave del elemento
*  @return "position" del elemento, -1 si no lo encuentra.
*/
int hash_findElemento(Hash *h, char *c);

/*! @brief Devuelve el tamaño.
*
*  Devuelve el tamaño de un hash dado por argumento.
*  @param h El hash
*  @return el tamaño actual del hash.
*/
int hash_getTamanio(Hash *h);

/*! @brief Devuelve el numero de nodos actual de un hash.
 *
 *  Devuelve el numero de nodos de un hash dado por argumento.
 *  @param h El hash
 *  @return el numero de nodos actual del hash.
*/
int hash_getNumElementos(Hash *h);
/*! @brief Obtiene un elemento del hash.
*
*  Devuelve un puntero al elemento(original, no copia) correspondiente a la clave dada.
*  @param h El hash
*  @param c La clave del elemento
*  @return el puntero al Elemento correspondiente. NULL en caso de error.
*/
Elemento *hash_getElemento(Hash *h, char *c);
/*! @brief Imprime un esquema del hash.
*
*  Imprime el esquema del hash.
*  @param h El hash.
*  @return void.
*/
void hash_print(Hash *h);

/*! @brief Copia un hash.
*
*  Devuelve un puntero del hash(original, copia)
*  @param h El hash
*  @return el puntero al Elemento correspondiente. NULL en caso de error.
*/
Hash *hash_cpy(Hash *h);

/*! @brief Obtiene un elemento del hash por indice.
  *
  *  Devuelve un puntero al elemento(original, no copia) correspondiente al indice dado.
  *  @param h El hash
  *  @param i El indice del elemento
  *  @return el puntero al Elemento correspondiente. NULL en caso de error.
  */
Elemento *hash_getElementoByIndex(Hash *h, int i);
#endif
