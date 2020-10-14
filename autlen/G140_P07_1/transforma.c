/**
 * Autores: Sofia Sanchez y Jesus Daniel Franco
 * Fichero: transforma.c
 *
 * Contiene las funciones
 *
 */

#include "transforma.h"

/**
 * Get_tipo_estado
 *
 * Nos dice qué tipo de estado es el que creamos nuevo para el afd
 * Si tenemos el estado q0q2q4 y ya sabíamos de qué tipo era q0q2,
 * a partir del tipo de q4 devuelve el valor correcto
 *
 * Argumentos de entrada:
 *  - afnd: autómata finito no determinista que vamos a transforma
 *  - posicion: posición en el afnd del estado que vamos a añadir
 *              al afd
 *  - tipo_antes: tipo del estado al que añadimos el siguiente "subestado"
 *
 * Salida:
 *    int Tipo del estado del afd, definidos como macros en afnd.h
 *
 */
int get_tipo_estado(AFND *afnd, int posicion, int tipo_antes){
  if(tipo_antes==INICIAL) {
    /* Teníamos un estado INICIAL y le añadimos uno INICIAL */
    if(AFNDTipoEstadoEn(afnd, posicion) == INICIAL){
      return INICIAL;
    }
    /* Teníamos un estado INICIAL y le añadimos uno FINAL */
    if(AFNDTipoEstadoEn(afnd, posicion) == FINAL){
      return INICIAL_Y_FINAL;
    }
    /* Teníamos un estado INICIAL y le añadimos uno INICIAL_Y_FINAL */
    if(AFNDTipoEstadoEn(afnd, posicion) == INICIAL_Y_FINAL){
      return INICIAL_Y_FINAL;
    }
    /* Teníamos un estado INICIAL y le añadimos uno NORMAL */
    if(AFNDTipoEstadoEn(afnd, posicion) == NORMAL){
      return INICIAL;
    }
  }
  if(tipo_antes==FINAL) {
    /* Teníamos un estado FINAL y le añadimos uno INICIAL */
    if(AFNDTipoEstadoEn(afnd, posicion) == INICIAL){
      return INICIAL_Y_FINAL;
    }
    /* Teníamos un estado FINAL y le añadimos uno FINAL */
    if(AFNDTipoEstadoEn(afnd, posicion) == FINAL){
      return FINAL;
    }
    /* Teníamos un estado FINAL y le añadimos uno INICIAL_Y_FINAL */
    if(AFNDTipoEstadoEn(afnd, posicion) == INICIAL_Y_FINAL){
      return INICIAL_Y_FINAL;
    }
    /* Teníamos un estado FINAL y le añadimos uno NORMAL */
    if(AFNDTipoEstadoEn(afnd, posicion) == NORMAL){
      return FINAL;
    }
  }
  /*
  * Si el estado ya era de tipo INICIAL_Y_FINAL seguirá siéndolo le añadamos
  * el subestado que le añadamos
  */
  if(tipo_antes==INICIAL_Y_FINAL) {
    return INICIAL_Y_FINAL;
  }
  /*Si la posicion anterior era normal, se queda con la que viene*/
  return AFNDTipoEstadoEn(afnd, posicion);
}

/**
 * Inicializar_codificacion
 *
 * Nos permite inicializar una codificacion toda a 0 (es decir, el array esta todo inicializado a 0's)
 *
 * Argumentos de entrada:
 *  - cod: array de enteros que queremos incializar
 *  - num_estados: numero de estados del AFND
 */
void inicializar_codificacion(int *cod, int num_estados) {
  int i;
  for (i = 0; i <num_estados; i++){
    cod[i] = 0;
  }
}

/**
 * Inicializar_codificacion_inicial
 *
 * Nos permite inicializar la codificacion del estado incial del AFD
 *
 * Argumentos de entrada:
 *  - cod: array de enteros que queremos inicializar
 *  - num_estados: numero de estados del AFND
 *  - pos_inicial: posicion del estado inicial
 *
 */
void inicializar_codificacion_inicial(int *cod, int num_estados, int pos_inicial){
  int i;

  for (i = 0; i < num_estados; i++){
    if(i == pos_inicial){
      cod[i] = 1;
    }
    else{
      cod[i] = 0;
    }
  }
}

/**
 * crear_automata_determinista
 *
 * Nos permite formar el automata derminista llamando a las funciones de la API
 * que insertan los simbolos, estados y transiciones
 *
 * Argumentos de entrada:
 *  - afnd: AFND anterior donde tenemos los simbolos
 *  - creados: lista con todos los nuevos estados del AFD
 *  - contador: contiene el numero de estados del nuevo AFD
 *  - num_simbolos: contiene el numero de simbolos del AFD
 *
 * Salida:
 *  Automata determinista ya creado
 *
 */
AFND *crear_automata_determinista(AFND *afnd, Intermedia **creados, int contador, int num_simbolos) {
  AFND *determinista = NULL;
  int i, k;
  determinista = AFNDNuevo("afd", contador, num_simbolos);

  /* Insertamos los símbolos en el nuevo autómata */
  for (i = 0; i < num_simbolos; i++){
    AFNDInsertaSimbolo(determinista, AFNDSimboloEn(afnd, i));
  }

  /* Insetamos los estados */
  for (i = 0; i < contador; i++){
    AFNDInsertaEstado(determinista, get_intermedia_nombre(creados[i]), get_intermedia_tipo(creados[i]));
  }

  /* Insertamos las transiciones*/
  for (i = 0; i < contador; i++){
    k = 0;
    while(get_intermedia_transicion(creados[i], k) != NULL){
      AFNDInsertaTransicion(determinista,
                            get_intermedia_nombre(creados[i]),
                            get_transicion_simbolo(get_intermedia_transicion(creados[i],k)),
                            get_transicion_estadofinal(get_intermedia_transicion(creados[i],k)));

      k++;
    }
  }

  return determinista;
}

/**
 * Liberar memoria
 *
 * Nos permite liberar la memoria reservada para la lista creados de estructuras
 * intermedias eliminando la memoria reservada para las trasiciones y
 * para las estructuras intermedias
 *
 * Argumentos de entrada:
 *  - creados: lista de estructuras intermedias
 *  - creado: estructura intermedia que tenemos que eliminar
 *  - contador: contador para saber cuantos tenemos que liberar
 */
void liberar_memoria(Intermedia **creados, int contador){
  int i, k;

  for (i = 0; i < contador; i++) {
    k = 0;
    while(get_intermedia_transicion(creados[i], k)  != NULL){
      eliminar_transicion(get_intermedia_transicion(creados[i],k));
      k++;
    }

    eliminar_intermedia(creados[i]);
  }

  free(creados);
}
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
AFND* AFNDTransforma(AFND* afnd){

  /*
  Declaramos el array de estrucutras Intermedias (nuevos estados del afd),
  el autómata en el que guardaremos la transformación y la variable para
  saber el sizeof de la lista de creados
  */
  Intermedia **creados = NULL;
  AFND *determinista;
  size_t tam_creados;


  /*
    - num_estados = numero de estados del afnd
    - num_simbolos = numero de simbolos del afnd
    - check = flag que nos indicará si el estado del afd al que queremos transitar
              está o no en la lista de creados
    - tipo_estado_nuevo = tipo de los nuevos estados del afd. Se actualiza
              cada vez que creamos un estado
    - pos_inicial = indica la posicion del estado inicial
    - flag_estado_final = buffer temporal para tipo_estado_nuevo
    - flag_hay_transiciones = flag que indica si hemos encontrado transiciones
              para un símobolo dado desde un estado del afd determinado
  */
  int num_estados, num_simbolos, check, tipo_estado_nuevo = NORMAL;
  int pos_inicial;
  int flag_estado_final = 0, flag_hay_transiciones = 0;

  /*
  Explicacion de las cadenas de caracteres utilizadas

  nombre_inicial sirve para guardar el nombre del estado inicial
  simbolo sirve para guardar la cadena de caracteres para el simbolo de una transicion
  nombre_nuevo_estado lo utlilizamos para guardar el nombre del nuevo estado que se ha generado con las transiciones
  */
  char nombre_inicial[MAX_NOMBRE], simbolo[MAX_NOMBRE], nombre_nuevo_estado[MAX_NOMBRE];

  /*
  Explicacion de los contadores

  i_simbolo: me sirve para saber porque simbolo voy
  i: me sirve para contar por el estado que voy en la lista creados
  i_subestado: me sirve para saber el indice del subestado por el que voy. Si tengo q0q2 primero tendre i_subestado = 0 y luego i_subestado = 2
  i_cada_estado_AFND: me sirve para comprobar los estados destino en las transiciones
  i_trans: me dice por donde me he quedado en las transiciones de un nuevo estado
  contador: es para saber donde tengo que añadir luego a la lista de creados
  cont_transiciones: nos permite llevar la cuenta de las transiciones que metemos en un estado nuevo
  */
  int i,i_simbolo,i_subestado, contador = 0, i_cada_estado_AFND, cont_transiciones;
  int num_estados_creados = 1;
  int *nuevo_estado;
  int *codificacion_inicial, k;

  /* obtenemos datos del automata original: numero de estados y numero de simbolos */
  num_estados = AFNDNumEstados(afnd);
  num_simbolos = AFNDNumSimbolos(afnd);

  nuevo_estado = (int*)malloc(sizeof(int)*num_estados);
  codificacion_inicial = (int*)malloc(sizeof(int)*num_estados);


  /* obtenemos la posicion del estado inicial */
  pos_inicial = AFNDIndiceEstadoInicial(afnd);

  /* tenemos que crear la estructura intermedia para el estado incial */

  /*obtenemos el nombre del estado incial y lo copiamos */
  strcpy(nombre_inicial, AFNDNombreEstadoEn(afnd, pos_inicial));
  /* inicializamos la codificacion del estado inicial */
  inicializar_codificacion_inicial(codificacion_inicial, num_estados, pos_inicial);

  /* inicializamos la codificacion del estado nuevo */
  inicializar_codificacion(nuevo_estado, num_estados);

  /* comprobamos las lambdas del estado inicial */
  for (i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND++) {
    if (AFNDCierreLTransicionIJ(afnd, pos_inicial, i_cada_estado_AFND) == 1 && pos_inicial != i_cada_estado_AFND) {

      /* cambiamos el nombre del estado inicial y la codificacion añadiendole la transicion lambda */

      strcat(nombre_inicial, AFNDNombreEstadoEn(afnd, i_cada_estado_AFND));
      codificacion_inicial[i_cada_estado_AFND] = 1;

      flag_estado_final = get_tipo_estado(afnd, i_cada_estado_AFND, tipo_estado_nuevo);
      tipo_estado_nuevo = flag_estado_final;
    }

    /* si no hay transiciones lambda indicamos que es inicial */
    else {
      if(pos_inicial == i_cada_estado_AFND){
        tipo_estado_nuevo = INICIAL;
      }
    }
  }

  /* seservamos memoria para la lista de estructuras intermedias */
  creados = (Intermedia **)malloc(sizeof(Intermedia *)+8);

  /* guardamos el estado inicial */
  creados[0] = crear_intermedia(nombre_inicial, num_estados, tipo_estado_nuevo, codificacion_inicial);
  tipo_estado_nuevo = NORMAL;

  /* ponemos el siguiente a null */
  creados[1] = NULL;
  i = contador;
  contador ++;


  /* mientras que tengamos estados en la lista de creados */
  while(creados[i] != NULL || i == 0){

    /* inicializamos el contador para las transiciones */
    cont_transiciones = 0;

    /* para cada simbolo del AFND */
    for (i_simbolo = 0; i_simbolo < num_simbolos; i_simbolo++){

      /* guardamos el simbolo que estamos mirando */
      strcpy(simbolo, AFNDSimboloEn(afnd, i_simbolo));

      /* inicializamos la flag para mirar si hay transiciones */
      flag_hay_transiciones = 0;

      /* inicializamos a 0 la codificacion del nuevo estado */
      inicializar_codificacion(nuevo_estado, num_estados);

      /* para cada subestado */
      for(i_subestado = 0; i_subestado < num_estados; i_subestado++) {
        if (get_intermedia_codificacion(creados[i])[i_subestado] == 1) {

          /* si estamos en un subestado tenemos que mirar a donde podemos ir*/
          if (flag_hay_transiciones != 1) {
            strcpy(nombre_nuevo_estado, "");
          }

          /* miramos las transiciones desde cada sub estado */
          for (i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND ++) {
            if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i_subestado, i_simbolo, i_cada_estado_AFND) == 1) {
              flag_hay_transiciones = 1;

              if(nuevo_estado[i_cada_estado_AFND] == 0){
                nuevo_estado[i_cada_estado_AFND] = 1;
              }

              flag_estado_final = get_tipo_estado(afnd, i_cada_estado_AFND, tipo_estado_nuevo);
              tipo_estado_nuevo = flag_estado_final;
              if(tipo_estado_nuevo == INICIAL_Y_FINAL){
                tipo_estado_nuevo = FINAL;
              }
              else {
                if(tipo_estado_nuevo == INICIAL){
                  tipo_estado_nuevo = NORMAL;
                }
              }
            }
          }
        }
      }

      /* Comprobación de transiciones lambda desde los estados del afd ya creados */
      /* para cada sub estado */
      for (i_subestado = 0; i_subestado < num_estados; i_subestado++) {
        if(nuevo_estado[i_subestado] == 1) {

          /* para cada sub estado destino miramos si tenemos transicones lambda */
          for (i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND++) {
            if (AFNDCierreLTransicionIJ(afnd, i_subestado, i_cada_estado_AFND) == 1 && i_subestado != i_cada_estado_AFND) {
              if (nuevo_estado[i_cada_estado_AFND] == 0) {
                nuevo_estado[i_cada_estado_AFND] = 1;
              }
              /* Actualizamos el tipo del estado */
              flag_estado_final = get_tipo_estado(afnd, i_cada_estado_AFND, tipo_estado_nuevo);
              tipo_estado_nuevo = flag_estado_final;
              /*
              Si el estado ha salido que puede ser inicial, restringimos
              esa condición, ya que en un afd tenemos un ÚNICO estado inicial
              */
              if(tipo_estado_nuevo == INICIAL_Y_FINAL){
                tipo_estado_nuevo = FINAL;
              }

              else {
                if(tipo_estado_nuevo == INICIAL){
                  tipo_estado_nuevo = NORMAL;
                }
              }
            }
          }
        }
      }

      /* comprobamos si hay transiciones. En caso de que haya tenemos que reservarles memoria */
      if(flag_hay_transiciones == 1){
        strcpy(nombre_nuevo_estado, "");
        for(k = 0; k < num_estados; k++){
          if(nuevo_estado[k] == 1){
            /*
            si el nuevo estado tiene como subestado al que está en la posicion
            k, le añadimos ese nombre
            */
            strcat(nombre_nuevo_estado, AFNDNombreEstadoEn(afnd, k));
          }
        }
        /* Reservamos memoria para la transicion y se la asignamos al nuevo estado */
        set_intermedia_transicion(creados[i], cont_transiciones, crear_transicion(num_estados, simbolo, nombre_nuevo_estado, nuevo_estado));
        cont_transiciones++;

        /* ponemos la siguente transicion  a null para poder romper los bucles while*/
        set_intermedia_transicion(creados[i], cont_transiciones, NULL);


        /* antes de meterlo en la lista de creados, tenemso que ver si ya está dentro de esta.
        En caso de que no este, reservaremos memoria para la estructura intermedia,  es decir, para el nuevo estado del AFD .
        Si esta, no haremos nada y pasaremos al siguente */
        check = is_estado_in(nuevo_estado, creados, num_estados, num_estados_creados-1);
        if (check == 0) { /* igual todo lo que hacemos aqui podemos juntarlo en una funcion para que sea mas corta */
          /* No esta en la lista de creados, entonces tenemos que añadirlo */
          tam_creados = sizeof(creados);

          creados = (Intermedia **)realloc(creados, tam_creados+sizeof(Intermedia *)+(8*num_estados_creados));
          creados[num_estados_creados] = crear_intermedia(nombre_nuevo_estado, num_estados, tipo_estado_nuevo, nuevo_estado);
          tipo_estado_nuevo = NORMAL;
          num_estados_creados++;
          creados[num_estados_creados] = NULL;

        }
      }
      /* Si no se han encontrado transiciones, se indica como transición NULL */
      else {
        set_intermedia_transicion(creados[i], cont_transiciones, NULL);
      }
    }
    /* incrementamos para coger el siguiente estado en creados */
    i++;
  }

  /* liberamos la memoria reservada para las codificaciones y apuntamos
  el último elemento de creados a NULL, ya que es un elemento que "sobra" */
  creados[i]=NULL;
  free(nuevo_estado);
  free(codificacion_inicial);
  contador = i;

  /* creamos el automata determinista */
  determinista = crear_automata_determinista(afnd, creados, contador, num_simbolos);

  /*liberamos la memoria para la lista de estados del AFND */
  free(creados[i]);
  liberar_memoria(creados, contador);

  return determinista;

}
