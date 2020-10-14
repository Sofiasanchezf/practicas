#ifndef _ALFA_H
#define _ALFA_H

#include "types.h"

#define MAX_LONG_ID 1000

typedef struct
{
  char lexema[MAX_LONG_ID+1];
  int tipo;
  int valor_entero;
  int es_direccion;
  int etiquetas;
} tipo_atributos;

#endif
