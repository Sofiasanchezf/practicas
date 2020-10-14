#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elemento.h"

struct _Elemento
{

  /* IDENTIFICADOR DEL ELEMENTO */
  char *clave;
  /* VALOR POR DEFECTO DE LA VARIABLE*/
  char valor;
  /* CATEGORÍA DEL ELEMENTO: variable, parametro o funcion */
  int categoria_elemento;
  /*TIPO BÁSICO DEL IDENTIFICADOR: boolean o int*/
  int tipo;
  /* CATEGORÍA DE LA INFORMACIÓN DEL ELEMENTO: escalar o vector*/
  int categoria;
  /* TAMAÑO: 1-64 */
  int tamanio;
  /* NUMERO DE PARAMETROS DE UNA FUNCION */
  int numero_parametros;
  /* POSICION PARAMETRO DE UNA FUNCION */
  int posicion_parametro;
  /* NUMERO VARIABLES DE FUNCION */
  int numero_variables_locales;
  /* POSICION VARIABLE EN FUNCION */
  int posicion_variable_local;
};

/*! @brief Crea un elemento
*
*  Crea un elemento a partir de los parametros dados
*  @param clave La clave
*  @param categoria_elemento La categoria
*  @param tipo El tipo
*  @param categoria La clase
*  @param tamanio El tamanio
*  @param numero_parametros El numero_parametros
*  @param posicion_parametro La posicion_parametro
*  @param numero_variables_locales El numero_variables_locales
*  @param posicion_variable_local La posicion_variable_local
*
*  @return El elemento creado
*/
Elemento *elemento_create(char *clave, int valor, int categoria_elemento,
                          int tipo, int categoria, int tamanio, int numero_parametros,
                          int posicion_parametro, int numero_variables_locales,
                          int posicion_variable_local) {

  Elemento *e = NULL;
  e = (Elemento *)malloc(sizeof(e[0]));
  if (!e)
    return NULL;

  e->clave = (char *)malloc((strlen(clave) + 1) * sizeof(e->clave[0]));
  if (!e->clave)
  {
    free(e);
    return NULL;
  }

  strcpy(e->clave, clave);
  e->valor = valor;
  e->categoria_elemento = categoria;
  e->tipo = tipo;
  e->categoria = categoria;
  e->tamanio = tamanio;
  e->numero_parametros = numero_parametros;
  e->posicion_parametro = posicion_parametro;
  e->numero_variables_locales = numero_variables_locales;
  e->posicion_variable_local = posicion_variable_local;
  return e;
}

/*! @brief Libera un elemento
*
*  Libera un elemento dado
*  @param e El elemento a copiar
*/
void elemento_destroy(Elemento *e)
{
  if (e->clave != NULL)
    free(e->clave);

  free(e);
}

/*! @brief Imprime la informacion de un elemento
*
*  Imprime la informacion de un elemento dado
*  @param fp el puntero a fichero donde escribe
*/
void elemento_print(FILE *fp, Elemento *e)
{
  fprintf(fp, "clave: %s\ncategoria_elemento: %d\ntipo: %d\ncategoria: %d\nnumero_parametros: %d\nposicion_parametro: %d\nnumero_variables_locales: %d\nposicion_variable_local: %d",
          e->clave, e->categoria_elemento, e->tipo, e->categoria, e->numero_parametros, e->posicion_parametro, e->numero_variables_locales, e->posicion_variable_local);
  fprintf(fp, "\n");
}

/*! @brief Crea una copia de un elemento
*
*  Crea una copia de un elemento dado
*  @param e El Elemento en cuestion
*  @return la copia creada
*/
Elemento *elemento_cpy(Elemento *e)
{

  Elemento *newE = elemento_create(
      e->clave,
      e->valor,
      e->categoria_elemento,
      e->tipo,
      e->categoria,
      e->tamanio,
      e->numero_parametros,
      e->posicion_parametro,
      e->numero_variables_locales,
      e->posicion_variable_local);

  return newE;
}

/*!
 *  @brief Obtiene la clave
 *
 *  Obtiene la clave  de un Elemento dado
 *  @param e El Elemento en cuestion
 *  @return la clave
 */
char *elemento_getClave(Elemento *e)
{
  return e->clave;
}
/*! @brief Establece la clave
*
*  Establece la clave  de un Elemento dado
*  @param e El Elemento en cuestion
*  @param clave  la clave
*/
void elemento_setClave(Elemento *e, char *clave)
{
  free(e->clave);
  e->clave = (char *)malloc((strlen(clave) + 1) * sizeof(e->clave[0]));
  if (!e->clave)
  {
    free(e);
  }

  strcpy(e->clave, clave);
}

/*! @brief Obtiene el categoria
*
*  Obtiene el categoria de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el categoria
*/
int elemento_getValor(Elemento *e)
{
  return e->valor;
}
/*! @brief Establece el categoria
*
*  Establece el categoria de un Elemento dado
*  @param e El Elemento en cuestion
*  @param categoria el categoria
*/
void elemento_setValor(Elemento *e, int valor)
{
  e->valor = valor;
}
/*! @brief Obtiene el categoria
*
*  Obtiene el categoria de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el categoria
*/
int elemento_getCategoria_Elemento(Elemento *e)
{
  return e->categoria_elemento;
}
/*! @brief Establece el categoria
*
*  Establece el categoria de un Elemento dado
*  @param e El Elemento en cuestion
*  @param categoria el categoria
*/
void elemento_setCategoria_Elemento(Elemento *e, int categoria_elemento)
{
  e->categoria_elemento = categoria_elemento;
}
/*! @brief Obtiene el tipo
*
*  Obtiene el tipo de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el tipo
*/
int elemento_getTipo(Elemento *e)
{
  return e->tipo;
}
/*! @brief Establece el tipo
*
*  Establece el tipo de un Elemento dado
*  @param e El Elemento en cuestion
*  @param tipo el tipo
*/
void elemento_setTipo(Elemento *e, int tipo)
{
  e->tipo = tipo;
}
/*! @brief Obtiene el clase
*
*  Obtiene el clase de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el clase
*/
int elemento_getCategoria(Elemento *e)
{
  return e->categoria;
}
/*! @brief Establece el clase
*
*  Establece el categoria de un Elemento dado
*  @param e El Elemento en cuestion
*  @param categoria el categoria
*/
void elemento_setCategoria(Elemento *e, int categoria)
{
  e->categoria = categoria;
}

/*! @brief Obtiene el numero_parametros
*
*  Obtiene el numero_parametros de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el numero_parametros
*/
int elemento_getNumero_parametros(Elemento *e)
{
  return e->numero_parametros;
}
/*! @brief Establece el numero_parametros
*
*  Establece el numero_parametros de un Elemento dado
*  @param e El Elemento en cuestion
*  @param numero_parametros el numero_parametros
*/
void elemento_setNumero_parametros(Elemento *e, int numero_parametros)
{
  e->numero_parametros = numero_parametros;
}

/*! @brief Obtiene el posicion_parametro
*
*  Obtiene el posicion_parametro de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el posicion_parametro
*/
int elemento_getPosicion_parametro(Elemento *e)
{
  return e->posicion_parametro;
}
/*! @brief Establece el posicion_parametro
*
*  Establece el posicion_parametro de un Elemento dado
*  @param e El Elemento en cuestion
*  @param posicion_parametro el posicion_parametro
*/
void elemento_setPosicion_parametro(Elemento *e, int posicion_parametro)
{
  e->posicion_parametro = posicion_parametro;
}
/*! @brief Obtiene el numero_variables_locales
*
*  Obtiene el numero_variables_locales de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el numero_variables_locales
*/
int elemento_getNumero_variables_locales(Elemento *e)
{
  return e->numero_variables_locales;
}
/*! @brief Establece el numero_variables_locales
*
*  Establece el numero_variables_locales de un Elemento dado
*  @param e El Elemento en cuestion
*  @param numero_variables_locales el numero_variables_locales
*/
void elemento_setNumero_variables_locales(Elemento *e, int numero_variables_locales)
{
  e->numero_variables_locales = numero_variables_locales;
}
/*! @brief Obtiene el posicion_variable_local
*
*  Obtiene el posicion_variable_local de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el posicion_variable_local
*/
int elemento_getPosicion_variable_local(Elemento *e)
{
  return e->posicion_variable_local;
}
/*! @brief Establece el posicion_variable_local
*
*  Establece el posicion_variable_local de un Elemento dado
*  @param e El Elemento en cuestion
*  @param posicion_variable_local el posicion_variable_local
*/
void elemento_setPosicion_variable_local(Elemento *e, int posicion_variable_local)
{
  e->posicion_variable_local = posicion_variable_local;
}


/*! @brief Obtiene el tamanio
*
*  Obtiene el tamanio de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el tamanio
*/
int elemento_getTamanio(Elemento *e)
{
  return e->tamanio;
}
/*! @brief Establece el tamanio
*
*  Establece el tamanio de un Elemento dado
*  @param e El Elemento en cuestion
*  @param tamanio el tamanio
*/
void elemento_setTamanio(Elemento *e, int tamanio)
{
  e->tamanio = tamanio;
}
