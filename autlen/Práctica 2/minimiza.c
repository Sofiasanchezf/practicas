#include "minimiza.h"



/**
 * notInCreados
 *
 * Nos dice si esta en la lista de creados o no.
 * En caso de estarlo devolveremos un 1, en caso de no estarlo un 0.
 *
 * Argumentos de entrada:
 * - creados: lista de enteros
 * - pos: posicion
 * - num_estados: numero de estados del automata
 *
 * Salida:
 *  0 si no esta en creados, 1 si lo esta
 */
int notInCreados(int *creados, int pos, int num_estados){
  int i;

  for(i=0; i<num_estados; i++){
    if(pos == creados[i]){
      return 1;
    }
  }

  return 0;
}

/**
 * isInAccesibles
 *
 * Nos dice si una posicion es accesible o no.
 *
 * Argumentos de entrada:
 * - accesibles: lista de enteros accesibles
 * - pos: posicion a comprobar
 *
 * Salida:
 *  0 si no es accesible, 1 si lo es
 */
int isInAccesibles(int *accesibles, int pos){
  if(accesibles[pos] == 0){
    return 0;
  }
  return 1;
}

/**
 * estadosAccesibles
 *
 * Nos permite obtener una lista de estados accesibles de un automata
 *
 * Argumentos de entrada:
 * - afnd: automata del que queremos saber los estados accesibles
 *
 * Salida:
 *  lista de enteros accesibles
 */
int* estadosAccesibles(AFND *afnd){
   int pos_inicial;
   int *creados, *accesibles;
   int i_num_creados = 0;
   int num_estados, num_simbolos;
   int i_simbolo, i_estado, i;
   int num_creados;

   if(!afnd)
    return NULL;

   pos_inicial = AFNDIndiceEstadoInicial(afnd);
   num_estados = AFNDNumEstados(afnd);
   num_simbolos = AFNDNumSimbolos(afnd);

   creados = (int *)malloc(sizeof(int) + 4);
   creados[0] = pos_inicial;
   i_num_creados  = 0;
   num_creados = 1;

   accesibles = (int *)malloc(sizeof(int) * num_estados);
   for(i=0; i<num_estados; i++){
     accesibles[i] = 0;
   }

   while(creados[i_num_creados] != -1 || i_num_creados == 0){
     for(i_simbolo = 0; i_simbolo < num_simbolos; i_simbolo ++){
       for(i_estado = 0; i_estado < num_estados; i_estado ++){
         if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, creados[i_num_creados], i_simbolo, i_estado) == 1){
           if(notInCreados(creados, i_estado, i_num_creados) == 0){
             accesibles[i_estado] = 1;
             creados = (int *)realloc(creados, sizeof(creados)+sizeof(int) + 4*num_creados);
             creados[num_creados] = i_estado;
             num_creados ++;
             creados[num_creados] = -1;
           }
         }
         if(AFNDTipoEstadoEn(afnd, i_estado) == INICIAL || AFNDTipoEstadoEn(afnd, i_estado) == INICIAL_Y_FINAL)
          accesibles[i_estado] = 1;
       }
     }
     i_num_creados ++;
   }

   free(creados);

   return accesibles;

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
AFND *crear_automata(AFND *afnd, Intermedia **creados, int contador, int num_simbolos) {
  AFND *determinista = NULL;
  int i, k;
  determinista = AFNDNuevo("afd", contador, num_simbolos);

  /* Insertamos los símbolos en el nuevo autómata */
  for (i = 0; i < num_simbolos; i++){
    AFNDInsertaSimbolo(determinista, AFNDSimboloEn(afnd, i));
  }

  /* Insetamos los estados */
  for (i = 0; i < contador; i++){
    printf("error en a posicion %d de nuevos_estados\n", i);
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
 * estadosDistinguibles
 *
 * Nos permite saber los estados distinguibles de un automata
 *
 * Argumentos de entrada:
 * - afnd: automata del que queremos obtener los distinguivles
 *
 * Salida:
 *  matriz de los estados distingubles
 */
int** estadosDistinguibles(AFND *afnd){
  int num_estados, num_simbolos;
  int **matriz_distinguibles;
  /* i_simbolo lo utilizamos para cada simbolo
     i_cada_estado lo utilizamos para ver el siguiente estado y ver si hay transicion
   */
  int i, j, flag = 0, i_simbolo, i_cada_estado;
  /* new_pos1 y new_pos2 los utilizamos para obtener las siguientes transiciones a (i,j)*/
  int new_pos1 = 0, new_pos2 = 0;

  if(!afnd)
    return NULL;

  num_estados = AFNDNumEstados(afnd);
  num_simbolos = AFNDNumSimbolos(afnd);

  /* reservamos memoria para la matriz */
  matriz_distinguibles = (int **)malloc(sizeof(int *)*num_estados);
  for (i=0; i < num_estados; i++){
    matriz_distinguibles[i] = (int *)malloc(sizeof(int)*num_estados);
  }

  /* inicializamos la matriz todo a 0*/
  for (i=0;i<num_estados;i++){
    for(j=0;j<num_estados;j++) {
      matriz_distinguibles[i][j] = 0;
    }
  }

  /* Hayamos los primeros distinguibles, los que sean finales */
  for (i=0; i < num_estados; i++){
    if(AFNDTipoEstadoEn(afnd, i) == FINAL || AFNDTipoEstadoEn(afnd, i) == INICIAL_Y_FINAL){
      for (j=0; j < num_estados; j++){
        if(AFNDTipoEstadoEn(afnd, j) != FINAL && AFNDTipoEstadoEn(afnd, j) != INICIAL_Y_FINAL){
          matriz_distinguibles[i][j] = 1;
          matriz_distinguibles[j][i] = 1;
        }
      }
    }
  }

  /* La primera vez se tachan bien */
  /* luego hay que mirar por pares, si tenemos (q0,q1) y me da con el 0 (q3,q4) entonces si los tengo marcados como distintos, es que
  (q0,q1) tambien son distitnos asi que marcamos (q0,q1) como distintos. Utiliza un flag para si cambiamos algo de la tabla
  volver a hacerlo hasta que el flag se quede a 0 */


  /* mientras que hayamos hayamos cambiado el flag, haremos este proceso*/
  flag = 1; /*para que entre por primera vez en el bucle*/
  while(flag){
    flag = 0;
    for (i=0; i < num_estados; i++){
      for(j=0; j < num_estados; j++){
        if(i != j){
          /* miramos que no este marcado en la matriz para poder mirar sus transiciones */
          if (matriz_distinguibles[i][j] == 0) {
            /* si no esta marcado, lo estudiamos */
            /* vamos a mirar a donde podemos ir con las transiciones */
            for (i_simbolo = 0; i_simbolo < num_simbolos; i_simbolo++){
              /* para cada estado */
              for(i_cada_estado=0; i_cada_estado < num_estados; i_cada_estado++){

                if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, i_simbolo, i_cada_estado) == 1){
                  new_pos1 = i_cada_estado;
                }
                if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, j, i_simbolo, i_cada_estado) == 1){
                  new_pos2 = i_cada_estado;
                }
              }
              /* lo miramos en el caso de que sean diferentes */
              if (new_pos2 != new_pos1) {
                /* tenemos que mirar si esta transicion esta marcada*/
                if(matriz_distinguibles[new_pos1][new_pos2] == 1){
                  matriz_distinguibles[i][j] = 1;
                  matriz_distinguibles[j][i] = 1;
                  flag = 1;
                  break;
                }
              }
            }
          }
        }
      }
    }
  }

  return matriz_distinguibles;

}

/**
 * AFNDMinimiza
 *
 * Nos permite obtener un AFND minimizado
 *
 * Argumentos de entrada:
 * - afnd: automata que queremos minimizar
 *
 * Salida:
 *  AFND ya minimizado
 */
AFND *AFNDMinimiza(AFND *afnd){

  int *accesibles = NULL;
  int **matriz_distinguibles = NULL, i_cada_estado_AFND;
  int i, j, num_estados, num_estados_creados = 0, i_simbolo, num_simbolos, cont_transiciones;
  int *codificacion_clase_equivalencia;
  Intermedia **estados_nuevos = NULL;
  char nombre_nuevo_estado[MAX_NOMBRE];
  int contador = 0;
  AFND *minimizado;
  char buffer[MAX_NOMBRE];
  int check;

  num_estados = AFNDNumEstados(afnd);
  num_simbolos = AFNDNumSimbolos(afnd);


  accesibles = estadosAccesibles(afnd);

  matriz_distinguibles = estadosDistinguibles(afnd);

  /* Obtenemos las clases de equivalencia de la matriz, y para cada una de ellas
  creamos una estructura intermedia, un nuevo estado equivalente */

  estados_nuevos = (Intermedia **)malloc(sizeof(Intermedia *)+8);
  codificacion_clase_equivalencia = (int *)malloc(sizeof(int)*num_estados);

  for (i=0; i < num_estados; i++){
    if(accesibles[i] != 0){
      cont_transiciones = 0;
      strcpy(nombre_nuevo_estado, "");
      /* Creamos la el nodo equivalencia de i (si no lo tenemos creado aún) */
      for(j=0; j<num_estados; j++){
        codificacion_clase_equivalencia[j] = 0;
      }

      for(j=0; j < num_estados; j++){
        if(isInAccesibles(accesibles, j) == 1){
          codificacion_clase_equivalencia[j] = matriz_distinguibles[i][j];
          if(codificacion_clase_equivalencia[j] == 0){
            if(strcmp(nombre_nuevo_estado, "") == 0){
              strcat(nombre_nuevo_estado, AFNDNombreEstadoEn(afnd, j));
            } else {
              sprintf(buffer, "_%s", AFNDNombreEstadoEn(afnd, j));
              strcat(nombre_nuevo_estado, buffer);
            }
          }
        } else {
          codificacion_clase_equivalencia[j] = 1; /* La clase la forman los que estén a 0 */
        }
      }

      /* Guardamos la codificación inversa */
      check = is_estado_in(codificacion_clase_equivalencia, estados_nuevos, num_estados, num_estados_creados-1);
      if(check == 0){
        contador++;
        estados_nuevos = (Intermedia **)realloc(estados_nuevos, sizeof(estados_nuevos)+sizeof(Intermedia *)+(8*num_estados_creados));
        estados_nuevos[num_estados_creados] = crear_intermedia(nombre_nuevo_estado, num_estados, AFNDTipoEstadoEn(afnd, i), codificacion_clase_equivalencia);
        num_estados_creados++;
        estados_nuevos[num_estados_creados] = NULL;

        for(i_simbolo = 0; i_simbolo<num_simbolos; i_simbolo++){
          for(j=0; j<num_estados; j++){
            codificacion_clase_equivalencia[j] = 0;
          }
          strcpy(nombre_nuevo_estado, "");
          for(i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND++){
            if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, i_simbolo, i_cada_estado_AFND) == 1){
              for(j=0; j < num_estados; j++){
                if(isInAccesibles(accesibles, j) == 1){
                  codificacion_clase_equivalencia[j] = matriz_distinguibles[i_cada_estado_AFND][j];
                  if(codificacion_clase_equivalencia[j] == 0){
                    if(strcmp(nombre_nuevo_estado, "") == 0){
                      strcat(nombre_nuevo_estado, AFNDNombreEstadoEn(afnd, j));
                    } else {
                      sprintf(buffer, "_%s", AFNDNombreEstadoEn(afnd, j));
                      strcat(nombre_nuevo_estado, buffer);
                    }
                  }
                } else {
                  codificacion_clase_equivalencia[j] = 1; /* La clase la forman los que estén a 0 */
                }
              }

              /* Reservamos memoria para la transicion y se la asignamos al nuevo estado */
              set_intermedia_transicion(estados_nuevos[num_estados_creados-1], cont_transiciones, crear_transicion(num_estados, AFNDSimboloEn(afnd, i_simbolo), nombre_nuevo_estado, codificacion_clase_equivalencia));
              cont_transiciones++;

              /* ponemos la siguente transicion  a null para poder romper los bucles while*/
              set_intermedia_transicion(estados_nuevos[num_estados_creados-1], cont_transiciones, NULL);

            }
          }
        }
      }
    }
  }

  estados_nuevos[contador] = NULL;
  minimizado = crear_automata(afnd, estados_nuevos, contador, num_simbolos);

  /* liberamos toda la memoria que hemos necesitado */
  if(accesibles)
    free(accesibles);

  if(matriz_distinguibles){
    for (i=0; i < num_estados; i++){
      if(matriz_distinguibles[i]){
        free(matriz_distinguibles[i]);
      }
    }
    free(matriz_distinguibles);
  }

  free(estados_nuevos[contador]);
  liberar_memoria(estados_nuevos, contador);
  free(codificacion_clase_equivalencia);
  return minimizado;

}
