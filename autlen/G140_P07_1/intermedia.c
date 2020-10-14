/**
 * Autores: Sofia Sanchez y Jesus Daniel Franco
 * Fichero: intermedia.c
 *
 * Contiene las funciones
 *
 */

#include "intermedia.h"

/*****************************************************/
/************* DEFINICION DE ESTRUCTURAS *************/
/*****************************************************/

/**
 * Estructura Transicion
 *  En esta estructura guardaremos el nombre del simbolo con el que podemos ir al estado destino, el nombre del estado destino
 *  y la codificacion del estado destino
 *
 */
struct _Transicion{
  char simbolo[MAX_NOMBRE]; /* simbolo con el que puedo ir al estado destino */
  char estado_final[MAX_NOMBRE]; /* nombre del estado destino */
  int *t_codificacion; /* codificacion del estado destino */
};


/**
 * Estructura Intermedia
 *  En esta estructura guardaremos todo lo necesario para definir los estados del automata finito determinista.
 *  Tendremos el nombre del estado en el que estamos, la codificiacion del estado, el tipo de estado que es y las transiciones que tiene este
 *  estado para pasar a otros estados destinos
 *
 */
struct _Intermedia{
  char nombre_estado[MAX_NOMBRE]; /* nombre del estado del automata determinista */
  int *i_codificacion; /* codificacion del estado del automata determinista */
  int tipo; /*tipo que va a ser: final, inicial, etc*/
  Transicion *transiciones[MAX_TRANSICIONES]; /* transiciones con las que podemos ir a otros estados destinos */
};



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
Transicion *crear_transicion(int num_estados, char* simbolo, char* final, int *estado_final) {
  Transicion *transicion = NULL;
  int i;

  /* Reservamos memoria para la transicion */
  transicion = (Transicion *)malloc(sizeof(Transicion));
  if (transicion == NULL){
    printf("Error al reservar memoria para la nueva transicion\n");
    return NULL;
  }

  /* copiamos el simbolo y estado destino */
  strcpy(transicion->simbolo, simbolo);
  strcpy(transicion->estado_final,final);

  /* Reservamos memoria para la codificación del estado al que se transita*/
  transicion->t_codificacion = (int*)malloc(sizeof(int)*num_estados);
  if (transicion->t_codificacion == NULL){
    printf("Error al reservar memoria para codificacion del estado destino\n");
    return NULL;
  }

  /* Inicializamos la codificacion de la transicion*/
  for (i = 0; i < num_estados; i++) {
    transicion->t_codificacion[i] = estado_final[i];
  }

  return transicion;
}


/**
 * Eliminar_transicion
 *
 * Libera toda la memoria de la transicion pasada como argumento
 *
 * Argumentos de entrada:
 *  - transicion: tranasicion de la que queremos liberar memoria
 *
 */
void eliminar_transicion(Transicion *transicion) {

  /* Liberamos la memoria reservada para la codificacion de la transicion */
  free(transicion->t_codificacion);

  /* Liberamos la memoria reservada para la transicion */
  free(transicion);
}


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
Intermedia *crear_intermedia(char* nombre, int num_estados, int tipo, int *estado) {
  Intermedia *intermedia = NULL;
  int i;

  /* Reservamos memoria para la estructura intermedia */
  intermedia = (Intermedia *)malloc(sizeof(Intermedia));
  if (!intermedia) {
    printf("Error al reservar memoria para el estado el AFD\n");
    return NULL;
  }

  /* Inicializamos el tipo y el nombre del estado */
  intermedia->tipo = tipo;
  strcpy(intermedia->nombre_estado, nombre);

  /* Reservamos memoria para la codificacion */
  intermedia->i_codificacion = (int*)malloc(sizeof(int)*num_estados);

  /* Inicializamos la codificacion de la estructura intermedia */
  for (i = 0; i< num_estados; i++) {
    intermedia->i_codificacion[i] = estado[i];
  }

  return intermedia;
}


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
void eliminar_intermedia(Intermedia *intermedia) {

  /* Liberamos la memoria reservada para la codificacion de la estructura intermedia */
  free(intermedia->i_codificacion);

  /* Liberamos la memoria reservada para la estructura intermedia */
  free(intermedia);
}


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
int comparar_codificacion(int *codificacion1, int *codificacion2, int num_estados){
  int i;

  /* Comprobamos los argumentos de entrada */
  if(!codificacion1 || !codificacion2){
    return -1;
  }

  /* Pasamos a comparar las codificaciones. En cuanto una posicion ya no sea igual indicaremos que son diferentes */
  for (i=0; i<num_estados; i++){
    if(codificacion1[i] != codificacion2[i]){
      return 0;
    }
  }

  /* si recorremos toda la lista y no hay diferencias, son iguales */
  return 1;
}


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
int is_estado_in(int *codificacion, Intermedia **creados, int num_estados, int num_creados) {
  int i;

  /* Comprobamos los argumentos de entrada */
  if(!codificacion  || !creados){
    return -1;
  }

  num_creados = num_creados + 1;

  /* Para cada estructura intermedia guardada en creados, compararemos su codificacion con la codificacion que recibimos como argumento de entrada */
  for (i = 0; i < num_creados; i++) {

    /* Vemos si la codificacion dada coincide con alguna de las que ya tenemos
     en creados. Si coincide, devolvemos un 1 */
    if (comparar_codificacion(codificacion, creados[i]->i_codificacion, num_estados) == 1){
      return 1;
    }
  }

  /* si la codificacion no coincide con ningun estados de lso ya creados,
   devolvemos un 0 */
  return 0;
}

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
void imprimir_intermedia(Intermedia *intermedia, int num_estados) {
  int i;

  printf("**********IMPRIMIENDO ESTRUCTURA INTERMEDIA********\n" );
  printf("nombre_estado: %s\n", intermedia->nombre_estado);

  for (i = 0; i < num_estados; i++) {
    printf("%d-", intermedia->i_codificacion[i]);
  }

  printf("\n" );

  printf("tipo: %d\n", intermedia->tipo);
  printf("***************************************************\n");
}


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
void imprimir_transicion(Transicion *transicion, int num_estados) {
  int i;

  if (!transicion) {
    printf ("Error en argumentos de entrada de imprimir_transicion\n");
  }

  printf("***************IMPRIMIENDO TRANSICION**************\n" );
  printf ("simbolo: %s\n", transicion->simbolo);
  printf("estado destino: %s\n", transicion->estado_final);

  for (i = 0; i < num_estados; i++) {
    printf("%d-", transicion->t_codificacion[i]);
  }

  printf("\n" );
  printf("***************************************************\n");

}


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
void imprimir_codificiacion(int *cod, int num_estados) {
  int i;

  if (!cod) {
    printf ("Error en argumentos de entrada de imprimir_codificacion\n");
  }

  printf("************* imprimiendo codificacion ************\n");

  for(i = 0; i < num_estados; i++) {
    printf ("%d-", cod[i]);
  }

  printf("\n");

  printf("***************************************************\n");
}

/************************************/
/***** GETTERS Y SETTERS ************/
/************************************/


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
int *get_intermedia_codificacion(Intermedia *intermedia) {
    if (!intermedia) {
      printf ("Error en los argumentos de entrada de get_intermedia_codificacion\n");
      return NULL;
    }
    return intermedia->i_codificacion;
}

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
void set_intermedia_transicion(Intermedia *intermedia, int posicion, Transicion *transicion) {
  if (!intermedia) {
      printf ("Error en los argumentos de entrada de set_intermedia_transicion\n");
  }
  intermedia->transiciones[posicion] = transicion;
}

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
Transicion *get_intermedia_transicion(Intermedia *intermedia, int posicion) {
  if (!intermedia || posicion < 0) {
    printf ("Error en los argumentos de entrada de get_intermedia_transicion\n");
    return NULL;
  }
  return intermedia->transiciones[posicion];
}

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
char *get_intermedia_nombre(Intermedia *intermedia) {
  if (!intermedia) {
    printf ("Error en los argumentos de entrada de get_intermedia_nombre\n");
    return NULL;
  }

  return intermedia->nombre_estado;
}

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
void set_intermedia_nombre(Intermedia *intermedia, char *nombre) {
  if (!intermedia || !nombre) {
    printf ("Error en los argumentos de entrada de set_intermedia_nombre\n");
  }
  strcpy(intermedia->nombre_estado, nombre);
}

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
int get_intermedia_tipo(Intermedia *intermedia) {
  if (!intermedia) {
    printf ("Error en los argumentos de entrada de get_intermedia_tipo\n");
    return -1;
  }
  return intermedia->tipo;
}

/**
 * Set_intermedia_tipo
 *
 * Argumentos de entrada:
 *  - intermedia: puntero a una estructura intermedia que es un estado del automata finito determinista
 *  - tipo:
 *
 */
void set_intermedia_tipo(Intermedia *intermedia, int tipo) {
  if (!intermedia || tipo < 0 || tipo > 3) {
    printf ("Error en los argumentos de entrada de set_intermedia_tipo\n");
  }
  intermedia->tipo = tipo;
}

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
char *get_transicion_simbolo(Transicion *transicion) {
  if (!transicion) {
    printf ("Error en los argumentos de entrada de get_transicion_simbolo\n");
    return NULL;
  }
  return transicion->simbolo;
}

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
char *get_transicion_estadofinal(Transicion *transicion) {
  if (!transicion) {
    printf ("Error en los argumentos de entrada de get_transicion_estadofinal\n");
    return NULL;
  }
  return transicion->estado_final;
}
