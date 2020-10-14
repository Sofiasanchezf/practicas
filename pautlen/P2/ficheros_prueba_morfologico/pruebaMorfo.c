 /* Autores:
      - Sofía Sanchez Fuentes
      - Sergio Frontera Díaz
 */

#include <stdio.h>
#include "tokens.h"

int yylex();


int main(int argc, char** argv) {
  extern FILE* yyin;
  extern FILE* yyout;
  extern char* yytext;
  extern int nlin, ncol;
  int tok, error = 0;

  // comprobamos los parametros de entrada

  if (argc != 3) {
    printf("Numero de argumentos de entrada invalidos\n");
    return -1;
  }

  /*tenemos que abrir los ficheros de entrada y saida con yyin para la entrada y con yyout para la salida */

  yyin = fopen(argv[1], "r");
  if(!yyin) {
    printf("Fichero de entrada invalido\n");
    return -1;
  }

  yyout = fopen(argv[2], "w");
  if (!yyout) {
    printf("Fichero de salida invalido\n");
    fclose(yyin);
    return -1;
  }

  /* mientras se siga leyendo el fichero */
  while ((tok = yylex()) != 0) {

    if (error == 0) /* si es 0 es porque no hemos llegado a un mensaje de error */
    {
      switch ( tok ) {
      /* Palabras reservadas */
      case  TOK_MAIN:
        fprintf(yyout, "TOK_MAIN\t%d\t%s\n", TOK_MAIN, yytext);
        break;
      case  TOK_INT:
        fprintf(yyout, "TOK_INT\t%d\t%s\n", TOK_INT, yytext);
        break;
      case  TOK_BOOLEAN:
        fprintf(yyout, "TOK_BOOLEAN\t%d\t%s\n", TOK_BOOLEAN, yytext);
        break;
      case  TOK_ARRAY:
        fprintf(yyout, "TOK_ARRAY\t%d\t%s\n", TOK_ARRAY, yytext);
        break;
      case  TOK_FUNCTION:
        fprintf(yyout, "TOK_ARRAY\t%d\t%s\n", TOK_ARRAY, yytext);
        break;
      case  TOK_IF:
        fprintf(yyout, "TOK_IF\t%d\t%s\n", TOK_IF, yytext);
        break;
      case  TOK_ELSE:
        fprintf(yyout, "TOK_ELSE\t%d\t%s\n", TOK_ELSE, yytext);
        break;
      case  TOK_WHILE:
        fprintf(yyout, "TOK_WHILE\t%d\t%s\n", TOK_WHILE, yytext);
        break;
      case  TOK_SCANF:
        fprintf(yyout, "TOK_SCANF\t%d\t%s\n", TOK_SCANF, yytext);
        break;
      case  TOK_PRINTF:
        fprintf(yyout, "TOK_PRINTF\t%d\t%s\n", TOK_PRINTF, yytext);
        break;
      case  TOK_RETURN:
        fprintf(yyout, "TOK_RETURN\t%d\t%s\n", TOK_RETURN, yytext);
        break;
      case  TOK_PUNTOYCOMA:
        fprintf(yyout, "TOK_PUNTOYCOMA\t%d\t%s\n", TOK_PUNTOYCOMA, yytext);
        break;
      case  TOK_COMA:
        fprintf(yyout, "TOK_COMA\t%d\t%s\n", TOK_COMA, yytext);
        break;
      case  TOK_PARENTESISIZQUIERDO:
        fprintf(yyout, "TOK_PARENTESISIZQUIERDO\t%d\t%s\n", TOK_PARENTESISIZQUIERDO, yytext);
        break;
      case  TOK_PARENTESISDERECHO:
        fprintf(yyout, "TOK_PARENTESISDERECHO\t%d\t%s\n", TOK_PARENTESISDERECHO, yytext);
        break;
      case  TOK_CORCHETEIZQUIERDO:
        fprintf(yyout, "TOK_CORCHETEIZQUIERDO\t%d\t%s\n", TOK_CORCHETEIZQUIERDO, yytext);
        break;
      case  TOK_CORCHETEDERECHO:
        fprintf(yyout, "TOK_CORCHETEDERECHO\t%d\t%s\n", TOK_CORCHETEDERECHO, yytext);
        break;
      case  TOK_LLAVEIZQUIERDA:
        fprintf(yyout, "TOK_LLAVEIZQUIERDA\t%d\t%s\n", TOK_LLAVEIZQUIERDA, yytext);
        break;
      case  TOK_LLAVEDERECHA:
        fprintf(yyout, "TOK_LLAVEDERECHA\t%d\t%s\n", TOK_LLAVEDERECHA, yytext);
        break;
      case  TOK_ASIGNACION:
        fprintf(yyout, "TOK_ASIGNACION\t%d\t%s\n", TOK_ASIGNACION, yytext);
        break;
      case  TOK_MAS:
        fprintf(yyout, "TOK_MAS\t%d\t%s\n", TOK_MAS, yytext);
        break;
      case  TOK_MENOS:
        printf("TOK_MENOS\t%d\t%s\n", TOK_MENOS, yytext);
        break;
      case  TOK_DIVISION:
        fprintf(yyout, "TOK_DIVISION\t%d\t%s\n", TOK_DIVISION, yytext);
        break;
      case  TOK_ASTERISCO:
        fprintf(yyout, "TOK_ASTERISCO\t%d\t%s\n", TOK_ASTERISCO, yytext);
        break;
      case  TOK_AND:
        fprintf(yyout, "TOK_AND\t%d\t%s\n", TOK_AND, yytext);
        break;
      case  TOK_OR:
        fprintf(yyout, "TOK_OR\t%d\t%s\n", TOK_OR, yytext);
        break;
      case  TOK_NOT:
        fprintf(yyout, "TOK_NOT\t%d\t%s\n", TOK_NOT, yytext);
        break;
      case  TOK_IGUAL:
        fprintf(yyout, "TOK_IGUAL\t%d\t%s\n", TOK_IGUAL, yytext);
        break;
      case  TOK_DISTINTO:
        fprintf(yyout, "TOK_DISTINTO\t%d\t%s\n", TOK_DISTINTO, yytext);
        break;
      case  TOK_MENORIGUAL:
        fprintf(yyout, "TOK_MENORIGUAL\t%d\t%s\n", TOK_MENORIGUAL, yytext);
        break;
      case  TOK_MAYORIGUAL:
        fprintf(yyout, "TOK_MAYORIGUAL\t%d\t%s\n", TOK_MAYORIGUAL, yytext);
        break;
      case  TOK_MENOR:
        fprintf(yyout, "TOK_MENOR\t%d\t%s\n", TOK_MENOR, yytext);
        break;
      case  TOK_MAYOR:
        fprintf(yyout, "TOK_MAYOR\t%d\t%s\n", TOK_MAYOR, yytext);
        break;
      case  TOK_IDENTIFICADOR:
        fprintf(yyout, "TOK_IDENTIFICADOR\t%d\t%s\n", TOK_IDENTIFICADOR, yytext);
        break;
      case  TOK_CONSTANTE_ENTERA:
        fprintf(yyout, "TOK_CONSTANTE_ENTERA\t%d\t%s\n", TOK_CONSTANTE_ENTERA, yytext);
        break;
      case  TOK_TRUE:
        fprintf(yyout, "TOK_TRUE\t%d\t%s\n", TOK_TRUE, yytext);
        break;
      case  TOK_FALSE:
        fprintf(yyout, "TOK_FALSE\t%d\t%s\n", TOK_FALSE, yytext);
        break;
      case  TOK_ERROR:
        error = 1;
        fprintf(stderr, "****Error en [lin %d, col %d]: identificador demasiado largo (%s)\n", nlin, ncol, yytext);
        break;
      default:
        error = 1;
        fprintf(stderr, "****Error en [lin %d, col %d]: simbolo no permitido (%s)\n", nlin, ncol, yytext);
        break;
      }
    }
  }
  fclose(yyin);
  fclose(yyout);
  return 0;
}
