#include <stdio.h>
#include "generacion.h"

int main (int argc, char ** argv)
{
  FILE * fd_asm;
  if (argc != 2) {
    fprintf (stdout, "ERROR POCOS ARGUMENTOS\n");
    return -1;
  }

  fd_asm = fopen(argv[1],"w");
  escribir_subseccion_data(fd_asm);
  escribir_cabecera_bss(fd_asm);
  //int x;
  declarar_variable(fd_asm, "x", ENTERO, 1);
  declarar_variable(fd_asm, "t", ENTERO, 1);
  declarar_variable(fd_asm, "m", ENTERO, 1);
  escribir_segmento_codigo(fd_asm);

  declararFuncion(fd_asm, "triple", 1);
  escribirParametro(fd_asm, 0, 1);
  escribirVariableLocal(fd_asm, 1);
  escribir_operando(fd_asm, "3", 0);
  escribirParametro(fd_asm, 0, 1);
  multiplicar(fd_asm, 0, 1);
  retornarFuncion(fd_asm, 0);

  declararFuncion(fd_asm, "mitad", 1);
  escribirParametro(fd_asm, 0, 1);
  escribirVariableLocal(fd_asm, 1);
  escribirParametro(fd_asm, 0, 1);
  escribir_operando(fd_asm, "2", 0);
  dividir(fd_asm, 1, 0);
  retornarFuncion(fd_asm, 0);

  escribir_inicio_main(fd_asm);
  leer(fd_asm, "x", ENTERO);


  escribir_operando(fd_asm, "x", 1);
  operandoEnPilaAArgumento(fd_asm, 1);
  llamarFuncion(fd_asm, "triple", 1);
  asignar(fd_asm, "t", 0);

  escribir_operando(fd_asm, "t", 1);
  operandoEnPilaAArgumento(fd_asm, 1);
  llamarFuncion(fd_asm, "mitad", 1);
  asignar(fd_asm, "m", 0);

  escribir_operando(fd_asm,"t",1);
  escribir(fd_asm, 1, ENTERO);

  escribir_operando(fd_asm,"m",1);
  escribir(fd_asm, 1, ENTERO);

  escribir_operando(fd_asm, "t", 1);
  escribir_operando(fd_asm, "m", 1);
  multiplicar(fd_asm, 1, 1);

  escribir(fd_asm, 0, ENTERO);
  escribir_fin(fd_asm);
  fclose(fd_asm);
}
