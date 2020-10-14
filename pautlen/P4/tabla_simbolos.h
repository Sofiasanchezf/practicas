#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "elemento.h"
#include "hash.h"

typedef struct _TablaSimbolos TablaSimbolos;

TablaSimbolos * tablasimbolos_create();

void tablasimbolos_destroy(TablaSimbolos * t);

int tablasimbolos_get_ambito_actual(TablaSimbolos * t);

int tablasimbolos_abir_ambito_local(TablaSimbolos * t, char * nombre_funcion,
                                    int valor, int tipo, int numero_parametros,
                                    int numero_variables_locales);

int tablasimbolos_cerrar_ambito_local(TablaSimbolos * t);

int insertar_elemento_ambito_actual(TablaSimbolos * t, char * nombre_elemento,
                                    int valor, int categoria_elemento, int tipo, int categoria,
                                    int tamanio, int posicion_parametro,
                                    int posicion_variable_local);

int buscar_elemento(TablaSimbolos * t, char * nombre_elemento, Elemento **elemento);




#endif
