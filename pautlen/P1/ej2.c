#include <stdio.h>
#include "generacion.h"
int main (int argc, char** argv)
{
  FILE * salida;
  int etiqueta = 0;
  int getiqueta = 0;
  int etiquetas[MAX_ETIQUETAS];
  int cima_etiquetas=-1;

  if (argc != 2) {
    fprintf (stdout, "ERROR POCOS ARGUMENTOS\n");
    return -1;
  }
  salida = fopen(argv[1],"w");
  escribir_subseccion_data(salida);
  escribir_cabecera_bss(salida);
  declarar_variable(salida, "b1", BOOLEANO, 1);
  declarar_variable(salida, "x", ENTERO, 1);
  escribir_segmento_codigo(salida);
  escribir_inicio_main(salida);
  /* b1 = true; */
  escribir_operando(salida, "1", 0);
  asignar(salida, "b1", 0);
  /* Incluye aqui el codigo necesario para */

  //While. Gestion inicial de las etiquetas, guardado de etiqueta.
  getiqueta++;
  cima_etiquetas++;
  etiquetas[cima_etiquetas]=getiqueta;

  // Inicio while. Impresion de la etiqueta
  etiqueta = etiquetas[cima_etiquetas];
  while_inicio(salida, etiqueta);
  // Condicion del bucle while
  escribir_operando(salida, "b1", 1);
  // Recuperamos la etiqueta para la recuperacion del while
  etiqueta = etiquetas[cima_etiquetas];
  while_exp_pila(salida, 1, etiqueta);
  // scanf(&x)
  leer(salida,"x",ENTERO);

  //If. Gestion inicial de las etiquetas, guardado de etiqueta.
  getiqueta++;
  cima_etiquetas++;
  etiquetas[cima_etiquetas]=getiqueta;

  // Inicio while. Impresion de la etiqueta
  etiqueta = etiquetas[cima_etiquetas];
  // Asignacion condicional a variable b1
  escribir_operando(salida, "x", 1);
  escribir_operando(salida, "4", 0);
  mayor(salida, 1, 0, etiqueta);
  asignar(salida, "b1", 0);
  // Condicion del if
  escribir_operando(salida, "b1", 1);
  ifthenelse_inicio(salida, 1, etiqueta);
  escribir_operando(salida, "x", 1);
  escribir(salida, 1, ENTERO);
  // Salto a fin sino al terminar el if, impresion de la etiqueta fin_si.
  // recogemos la etiqueta.
  etiqueta = etiquetas[cima_etiquetas];
  ifthenelse_fin_then(salida, etiqueta);
  escribir_operando(salida, "0", 0);
  // printf false
  escribir(salida, 0, BOOLEANO);
  // fin del condicional if. Imprimimos la etiqueta de ambito del fin del
  // condicional y restamos el contador
  etiqueta = etiquetas[cima_etiquetas];
  ifthenelse_fin(salida, etiqueta);
  cima_etiquetas--;
  // Recuperamos la etiqueta para imprimir el fin de etiqueta del while
  etiqueta = etiquetas[cima_etiquetas];
  while_fin(salida, etiqueta);
  // Decrementamos contador para cerrar el ambito.
  cima_etiquetas--;
  escribir_fin(salida),
  fclose(salida);
  return 0;
}
