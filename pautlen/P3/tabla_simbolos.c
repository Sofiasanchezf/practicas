#include "tabla_simbolos.h"

struct _TablaSimbolos
{

  Hash * tablaGlobal;
  Hash * tablaLocal;
};


/*! @brief Crea una tabla de simbolos
*
*  @param ??? ???
*
*  @return La tabla de simbolos creada
*/
TablaSimbolos * tablasimbolos_create() {

  TablaSimbolos * t = (TablaSimbolos *) malloc(sizeof(t[0]));
  if (!t)
    return NULL;

  t->tablaGlobal = hash_create();
  t->tablaLocal = NULL;
  return t;
}


void tablasimbolos_destroy(TablaSimbolos * t) {
  hash_destroy(t->tablaGlobal);
  hash_destroy(t->tablaLocal);
  free(t);
}

int tablasimbolos_abir_ambito_local(TablaSimbolos * t, char * nombre_funcion,
                                    int valor, int tipo, int numero_parametros,
                                    int numero_variables_locales) {

  Elemento * e1 = NULL;
  Elemento * e2 = NULL;
  if (t->tablaLocal)
    return -1;

  e1 = elemento_create(nombre_funcion, valor, 3, tipo, -1, -1, numero_parametros, -1,
                      numero_variables_locales, -1);
  hash_addElemento(t->tablaGlobal, e1, nombre_funcion);

  t->tablaLocal = hash_create();
  e2 = elemento_create(nombre_funcion, valor, 3, tipo, -1, -1, numero_parametros, -1,
                      numero_variables_locales, -1);
  hash_addElemento(t->tablaLocal, e2, nombre_funcion);
  return 0;
}


int tablasimbolos_cerrar_ambito_local(TablaSimbolos * t) {
  if (t->tablaLocal == NULL)
    return -1;
  hash_destroy(t->tablaLocal);
  t->tablaLocal = NULL;
  return 0;
}

int insertar_elemento_ambito_actual(TablaSimbolos * t, char * nombre_elemento,
                                    int valor, int categoria_elemento, int tipo, int categoria,
                                    int tamanio, int posicion_parametro, int posicion_variable_local) {

  Elemento * e = NULL;
  Elemento * e_aux = NULL;

  if (t->tablaLocal != NULL) {
    e_aux = hash_getElemento(t->tablaLocal, nombre_elemento);
    if (e_aux) {
      return -1;
    }
  } else {
    e_aux = hash_getElemento(t->tablaGlobal, nombre_elemento);
    if (e_aux) {
      return -1;
    }
  }

  e = elemento_create(nombre_elemento, valor, categoria_elemento, tipo, categoria,
                       tamanio, -1, posicion_parametro, -1, posicion_variable_local);
  if (t->tablaLocal != NULL) {
    hash_addElemento(t->tablaLocal, e, nombre_elemento);
  } else {
    hash_addElemento(t->tablaGlobal, e, nombre_elemento);
  }
  return 0;
}

int buscar_elemento(TablaSimbolos * t, char * nombre_elemento, Elemento **elemento) {

  if (t->tablaLocal != NULL) {
    *elemento = hash_getElemento(t->tablaLocal, nombre_elemento);
    if (*elemento) {
      return TABLA_LOCAL;
    }
  }

  *elemento = hash_getElemento(t->tablaGlobal, nombre_elemento);
  if (*elemento) {
    return TABLA_GLOBAL;
  }

  return -1;
}
