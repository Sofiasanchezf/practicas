#ifndef ELEMENTO_H
#define ELEMENTO_H

typedef struct _Elemento Elemento;

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
                          int posicion_variable_local);



/*! @brief Libera un elemento
*
*  Libera un elemento dado
*  @param e El elemento a copiar
*/
void elemento_destroy(Elemento *e);


/*! @brief Imprime la informacion de un elemento
*
*  Imprime la informacion de un elemento dado
*  @param fp el puntero a fichero donde escribe
*/
void elemento_print(FILE *fp, Elemento *e);


/*! @brief Crea una copia de un elemento
*
*  Crea una copia de un elemento dado
*  @param e El Elemento en cuestion
*  @return la copia creada
*/
Elemento *elemento_cpy(Elemento *e);

/*!
 *  @brief Obtiene la clave
 *
 *  Obtiene la clave  de un Elemento dado
 *  @param e El Elemento en cuestion
 *  @return la clave
 */
char *elemento_getClave(Elemento *e);


/*! @brief Establece la clave
*
*  Establece la clave  de un Elemento dado
*  @param e El Elemento en cuestion
*  @param clave  la clave
*/
void elemento_setClave(Elemento *e, char *clave);

/*!
 *  @brief Obtiene la clave
 *
 *  Obtiene la clave  de un Elemento dado
 *  @param e El Elemento en cuestion
 *  @return la clave
 */
int elemento_getValor(Elemento *e);


/*! @brief Establece la clave
*
*  Establece la clave  de un Elemento dado
*  @param e El Elemento en cuestion
*  @param clave  la clave
*/
void elemento_setValor(Elemento *e, int valor);

/*! @brief Obtiene el categoria
*
*  Obtiene el categoria de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el categoria
*/
int elemento_getCategoria_Elemento(Elemento *e);


/*! @brief Establece el categoria
*
*  Establece el categoria de un Elemento dado
*  @param e El Elemento en cuestion
*  @param categoria el categoria
*/
void elemento_setCategoria_Elemento(Elemento *e, int categoria_elemento);


/*! @brief Obtiene el tipo
*
*  Obtiene el tipo de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el tipo
*/
int elemento_getTipo(Elemento *e);


/*! @brief Establece el tipo
*
*  Establece el tipo de un Elemento dado
*  @param e El Elemento en cuestion
*  @param tipo el tipo
*/
void elemento_setTipo(Elemento *e, int tipo);


/*! @brief Obtiene el clase
*
*  Obtiene el clase de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el clase
*/
int elemento_getCategoria(Elemento *e);


/*! @brief Establece el clase
*
*  Establece el categoria de un Elemento dado
*  @param e El Elemento en cuestion
*  @param categoria el categoria
*/
void elemento_setCategoria(Elemento *e, int categoria);


/*! @brief Obtiene el numero_parametros
*
*  Obtiene el numero_parametros de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el numero_parametros
*/
int elemento_getNumero_parametros(Elemento *e);


/*! @brief Establece el numero_parametros
*
*  Establece el numero_parametros de un Elemento dado
*  @param e El Elemento en cuestion
*  @param numero_parametros el numero_parametros
*/
void elemento_setNumero_parametros(Elemento *e, int numero_parametros);


/*! @brief Obtiene el posicion_parametro
*
*  Obtiene el posicion_parametro de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el posicion_parametro
*/
int elemento_getPosicion_parametro(Elemento *e);


/*! @brief Establece el posicion_parametro
*
*  Establece el posicion_parametro de un Elemento dado
*  @param e El Elemento en cuestion
*  @param posicion_parametro el posicion_parametro
*/
void elemento_setPosicion_parametro(Elemento *e, int posicion_parametro);


/*! @brief Obtiene el numero_variables_locales
*
*  Obtiene el numero_variables_locales de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el numero_variables_locales
*/
int elemento_getNumero_variables_locales(Elemento *e);


/*! @brief Establece el numero_variables_locales
*
*  Establece el numero_variables_locales de un Elemento dado
*  @param e El Elemento en cuestion
*  @param numero_variables_locales el numero_variables_locales
*/
void elemento_setNumero_variables_locales(Elemento *e, int numero_variables_locales);


/*! @brief Obtiene el posicion_variable_local
*
*  Obtiene el posicion_variable_local de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el posicion_variable_local
*/
int elemento_getPosicion_variable_local(Elemento *e);


/*! @brief Establece el posicion_variable_local
*
*  Establece el posicion_variable_local de un Elemento dado
*  @param e El Elemento en cuestion
*  @param posicion_variable_local el posicion_variable_local
*/
void elemento_setPosicion_variable_local(Elemento *e, int posicion_variable_local);


/*! @brief Obtiene el tamanio
*
*  Obtiene el tamanio de un Elemento dado
*  @param e El Elemento en cuestion
*  @return el tamanio
*/
int elemento_getTamanio(Elemento *e);


/*! @brief Establece el tamanio
*
*  Establece el tamanio de un Elemento dado
*  @param e El Elemento en cuestion
*  @param tamanio el tamanio
*/
void elemento_setTamanio(Elemento *e, int tamanio);

#endif
