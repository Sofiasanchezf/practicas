#include <stdio.h>
#include "y.tab.h"
int yylex();


int main (int argc, char **argv) {

    extern FILE * yyin;
    extern FILE * yyout;


    if (argc != 3){
        printf("Parametros de entrada incorrectos.\n");
        return -1;
    }


    /* abrimos los ficheros de entrada y salida */
    yyin = fopen(argv[1], "r");
    if (!yyin){
        printf("Error abriendo el fichero de entrada.\n");
        return -1;
    }

    yyout = fopen(argv[2], "w");
    if (!yyout){
        printf("Error abriendo el fichero de salida.\n");
        return -1;
    }

    yyparse();

    fclose(yyin);
    fclose(yyout);

    return 0;

}
