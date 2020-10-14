#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define elementos_INI 100

/*! @brief Estructura Hash
 *
 *  Implementacion de una estructura hash mediante tablas.
 */
struct _Hash
{
  char **claves; /*!< Array de nombres de claves */
  Elemento **elementos;  /*!< Array de elementos */
  int numElementos;  /*!< Numero maximo de elementos */
  int tamanio;   /*!< Numero actual de elementos */
};

/*! @brief Creacion de hash
 *
 *  Crea una nueva tabla hash a partir de el numero maximo de elementos a almacenar
 *  @return El puntero al hash creado
 */

Hash *hash_create()
{
  Hash *h = (Hash *)malloc(sizeof(h[0]));
  if (!h)
    return NULL;

  h->claves = (char **)malloc(sizeof(h->claves[0]) * elementos_INI); /*calloc?*/
  if (!h->claves)
  {
    free(h);
    return NULL;
  }
  h->elementos = (Elemento **)malloc(sizeof(h->elementos[0]) * elementos_INI);
  if (!h->elementos)
  {
    free(h->claves);
    free(h);
    return NULL;
  }

  h->numElementos = 0;
  h->tamanio = elementos_INI;
  return h;
}

/*! @brief liberacion de hash
 *
 *  Libera una tabla hash dada por argumento
 *  @param h El hash a liberar
*/
void hash_destroy(Hash *h)
{
  int i;
  if(!h)
    return;

  for (i = 0; i < h->numElementos; i++)
  {
    elemento_destroy(h->elementos[i]);
    free(h->claves[i]);
  }

  free(h->elementos);
  free(h->claves);
  free(h);
}

/*! @brief Comprueba si un hash esta vacio
 *
 *  Comprueba si un hash dado por argumento esta vacio.
 *  @param h El hash a evaluar
 *  @return true si esta vacio, false en otro caso.
 */
bool hash_isVacio(Hash *h)
{
  if (h->numElementos == 0)
    return true;
  return false;
}

/*! @brief Añade un elemento al hash.
 *
 *  Añade un elemento al hash con su clave correspondiente en la última posición.
 *  @param h El hash
 *  @param n El elemento a insertar
 *  @param c La clave del elemento
 *  @return OK si es correcto, -1 en caso contrario.
 */
int hash_addElemento(Hash *h, Elemento *n, char *c)
{

  char *clave = NULL;

  if (hash_findElemento(h, c) != -1)
    return -1;

  if (h->tamanio <= h->numElementos)
  {
    h->elementos = realloc(h->elementos, h->tamanio * 2 * sizeof(h->elementos[0]));
    h->claves = realloc(h->claves, h->tamanio * 2 * sizeof(h->elementos[0]));
    if (!h->claves || !h->elementos)
      return -1;

    h->tamanio *= 2;
  }

  clave = (char *)malloc((strlen(c) + 1) * sizeof(clave[0]));
  if (!clave)
    return -1;
  strcpy(clave, c);

  h->elementos[h->numElementos] = n;
  h->claves[h->numElementos] = clave;
  h->numElementos++;

  return OK;
}

/*! @brief Borra un elemento del hash.
  *
  *  Borra un elemento del hash y su clave correspondiente. Mueve el último elemento a
  *  la posición del elemento borrado.
  *  @param h El hash
  *  @param c La clave del elemento
  *  @return OK si es correcto, -1 en caso contrario.
  */
Elemento *hash_extractElemento(Hash *h, char *c)
{

  Elemento *refElemento = NULL;
  int position = hash_findElemento(h, c);
  if (position == -1)
  {
    return NULL;
  }
  refElemento = h->elementos[position];
  free(h->claves[position]);

  h->claves[position] = NULL;

  h->numElementos--;

  h->elementos[position] = h->elementos[h->numElementos];
  h->elementos[h->numElementos] = NULL;

  h->claves[position] = h->claves[h->numElementos];
  h->claves[h->numElementos] = NULL;

  return refElemento;
}

/*! @brief Busca un elemento en el hash.

 *
 *  Busca un elemento en el hash mediante su clave y devuelve la posicion
 *  @param h El hash
 *  @param c La clave del elemento
 *  @return la posicion del elemento, -1 si no lo encuentra.
*/
int hash_findElemento(Hash *h, char *c)
{

  int i;

  for (i = 0; i < h->numElementos; i++)
    if (strcmp(h->claves[i], c) == 0)
      return i;
  return -1;
}

/*! @brief Devuelve el tamaño maximo.
 *
 *  Devuelve el tamaño de un hash dado por argumento.
 *  @param h El hash
 *  @return el tamaño actual del hash.
*/
int hash_getTamanio(Hash *h)
{
  return h->tamanio;
}

/*! @brief Devuelve el numero de nodos actual de un hash.
 *
 *  Devuelve el numero de nodos de un hash dado por argumento.
 *  @param h El hash
 *  @return el numero de nodos actual del hash.
*/
int hash_getNumelementos(Hash *h)
{
  return h->numElementos;
}

/*! @brief Obtiene un elemento del hash.
  *
  *  Devuelve un puntero al elemento(original, no copia) correspondiente a la clave dada.
  *  @param h El hash
  *  @param c La clave del elemento
  *  @return el puntero al Elemento correspondiente. NULL en caso de error.
  */
Elemento *hash_getElemento(Hash *h, char *c)
{
  int p = hash_findElemento(h, c);
  if (p == -1)
    return NULL;
  return h->elementos[p];
}

/*! @brief Copia un hash.
*
*  Devuelve un puntero del hash(original, copia)
*  @param h El hash
*  @return el puntero al Elemento correspondiente. NULL en caso de error.
*/
Hash *hash_cpy(Hash *h)
{

  int i;

  Hash *nh = hash_create();

  for (i = 0; i < h->numElementos; i++)
  {
    hash_addElemento(nh, elemento_cpy(h->elementos[i]), h->claves[i]);
  }
  return nh;
}

/*! @brief Obtiene un elemento del hash por indice.
  *
  *  Devuelve un puntero al elemento(original, no copia) correspondiente al indice dado.
  *  @param h El hash
  *  @param i El indice del elemento
  *  @return el puntero al Elemento correspondiente. NULL en caso de error.
  */
Elemento *hash_getElementoByIndex(Hash *h, int i)
{
  if (i >= hash_getNumelementos(h))
    return NULL;
  return h->elementos[i];
}

/*! @brief Imprime un esquema del hash.
  *
  *  Imprime el esquema del hash.
  *  @param h El hash.
  *  @return void.
  */
void hash_print(Hash *h)
{

  int i = 0;
  printf("Tamaño maximo (ampliable por realloc): %d\nTamaño actual: %d\n", h->tamanio, h->numElementos);
  printf("---------------------------------------------------------------\n");
  for (i = 0; i < h->numElementos; i++)
  {
    printf("%s - ", h->claves[i]); /*
    elemento_print(h->elementos[i]); */
    printf("\n");
  }
}
