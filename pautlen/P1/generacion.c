#include <stdio.h>
#include "generacion.h"

/* OBSERVACIÓN GENERAL A TODAS LAS FUNCIONES:
Todas ellas escriben el código NASM a un FILE* proporcionado como primer
argumento.
*/

/*
Código para el principio de la sección .bss.
Con seguridad sabes que deberás reservar una variable entera para guardar el
puntero de pila extendido (esp). Se te sugiere el nombre __esp para esta variable.
*/
void escribir_cabecera_bss(FILE* fpasm) {

	fprintf(fpasm, "\nsegment .bss\n");
	fprintf(fpasm, "\t__esp resd 1\n" );
}

/*
Declaración (con directiva db) de las variables que contienen el texto de los
mensajes para la identificación de errores en tiempo de ejecución.
En este punto, al menos, debes ser capaz de detectar la división por 0.
*/
void escribir_subseccion_data(FILE* fpasm) {

	fprintf(fpasm, "segment .data\n" );
  fprintf(fpasm, "\t_errordiv0 db  \"*Error de ejecucion: Division por cero.*\",0\n" );
  fprintf(fpasm, "\t_erroroutrange db  \"*Error de ejecucion: Indice fuera de limite.*\", 0\n");
}

/*
Para ser invocada en la sección .bss cada vez que se quiera declarar una
variable:
- El argumento nombre es el de la variable.
- tipo puede ser ENTERO o BOOLEANO (observa la declaración de las constantes
del principio del fichero).
- Esta misma función se invocará cuando en el compilador se declaren
vectores, por eso se adjunta un argumento final (tamano) que para esta
primera práctica siempre recibirá el valor 1.
*/
void declarar_variable(FILE* fpasm, char * nombre, int tipo, int tamano) {

	fprintf(fpasm, "\t_%s resd %d \n", nombre, tamano);
}

/*
Para escribir el comienzo del segmento .text, básicamente se indica que se
exporta la etiqueta main y que se usarán las funciones declaradas en la librería
olib.o
*/
void escribir_segmento_codigo (FILE* fpasm) {

	fprintf(fpasm, "\nsegment .text \n");
	fprintf(fpasm, "\tglobal main \n");
	fprintf(fpasm, "\textern scan_int, scan_boolean, print_int, print_boolean\n");
	fprintf(fpasm, "\textern print_blank, print_endofline, print_string\n");
}

/*
En este punto se debe escribir, al menos, la etiqueta main y la sentencia que
guarda el puntero de pila en su variable (se recomienda usar __esp).
*/
void escribir_inicio_main(FILE* fpasm){

	fprintf(fpasm, "\nmain:\n");
	fprintf(fpasm, "\tmov dword [__esp], esp\n");
}

/*
Al final del programa se escribe:
- El código NASM para salir de manera controlada cuando se detecta un error
en tiempo de ejecución (cada error saltará a una etiqueta situada en esta
zona en la que se imprimirá el correspondiente mensaje y se saltará a la
zona de finalización del programa).
- En el final del programa se debe:
·Restaurar el valor del puntero de pila (a partir de su variable __esp)
·Salir del programa (ret).
*/
void escribir_fin(FILE* fpasm) {
/*	Funcionamiento: Acaba el programa, entonces:
	 	- Salta a quit para finalizarlo.
	Si durante el programa ha dado error habra saltado a la etiqueta pertinente de error
	y saldrá de manera controlada del programa:
	   - errordiv:
		 - erroroutrange*/

/* Si el programa ha finalizado correctamente */
  fprintf(fpasm, "\tjmp near quit\n");
/* Rutina de error division por cero. */
	fprintf(fpasm, "\nerrordiv0:\n");
	fprintf(fpasm, "\tpush dword _errordiv0\n");
	fprintf(fpasm, "\tcall print_string\n");
	fprintf(fpasm, "\tadd esp, 4\n");
	fprintf(fpasm, "\tcall print_endofline\n");
	fprintf(fpasm, "\tjmp near quit\n");
/* Rutina de error out of index */
	fprintf(fpasm, "\nerroroutrange:\n");
	fprintf(fpasm, "\tpush dword _erroroutrange\n");
	fprintf(fpasm, "\tcall print_string\n");
	fprintf(fpasm, "\tadd esp, 4\n");
	fprintf(fpasm, "\tcall print_endofline\n");
	fprintf(fpasm, "\tjmp near quit\n");
/* Rutina de finalización del programa */
	fprintf(fpasm, "\nquit:\n");
	fprintf(fpasm, "\tmov dword esp, [__esp]\n");
	fprintf(fpasm, "\tret\n");
}

/*
Función que debe ser invocada cuando se sabe un operando de una operación
aritmético-lógica y se necesita introducirlo en la pila.
- nombre es la cadena de caracteres del operando tal y como debería aparecer
en el fuente NASM
- es_variable indica si este operando es una variable (como por ejemplo b1)
con un 1 u otra cosa (como por ejemplo 34) con un 0. Recuerda que en el
primer caso internamente se representará como _b1 y, sin embargo, en el
segundo se representará tal y como esté en el argumento (34).
*/
void escribir_operando(FILE* fpasm, char* nombre, int es_variable) {

	if(es_variable == REFERENCIA) {
      	fprintf(fpasm, "\tpush dword _%s\n", nombre);
  } else if (es_variable == EXPLICITO) {
      	fprintf(fpasm, "\tpush dword %s\n", nombre);
  }
}


/* Función auxiliar POP argumento de la pila */

void popVariable(FILE* fpasm, int es_variable, char * registro) {

	fprintf(fpasm, "\tpop %s\n", registro);
	if (es_variable == REFERENCIA) {
		fprintf(fpasm, "\tmov %s, [%s]\n", registro, registro);
	}
}

/*
- Genera el código para asignar valor a la variable de nombre nombre.
- Se toma el valor de la cima de la pila.
- El último argumento es el que indica si lo que hay en la cima de la pila es
una referencia (1) o ya un valor explícito (0).
*/
void asignar(FILE* fpasm, char* nombre, int es_variable) {
	fprintf(fpasm, "; asignar\n");
	popVariable(fpasm, es_variable, "eax");
	fprintf(fpasm, "\tmov [_%s], eax \n", nombre);
}


/* FUNCIONES ARITMÉTICO-LÓGICAS BINARIAS */
/*
En todas ellas se realiza la operación como se ha resumido anteriormente:
- Se extrae de la pila los operandos
- Se realiza la operación
- Se guarda el resultado en la pila
Los dos últimos argumentos indican respectivamente si lo que hay en la pila es
una referencia a un valor o un valor explícito.
Deben tenerse en cuenta las peculiaridades de cada operación. En este sentido
sí hay que mencionar explícitamente que, en el caso de la división, se debe
controlar si el divisor es “0” y en ese caso se debe saltar a la rutina de error
controlado (restaurando el puntero de pila en ese caso y comprobando en el retorno
que no se produce “Segmentation Fault”)
*/
void sumar(FILE* fpasm, int es_variable_1, int es_variable_2) {

	popVariable(fpasm, es_variable_2, "edx");
	popVariable(fpasm, es_variable_1, "eax");

	fprintf(fpasm, "\tadd eax, edx\n");
	fprintf(fpasm, "\tpush eax\n");


}

void restar(FILE* fpasm, int es_variable_1, int es_variable_2) {

	popVariable(fpasm, es_variable_2, "edx");
	popVariable(fpasm, es_variable_1, "eax");

	fprintf(fpasm, "\tsub eax, edx\n");
	fprintf(fpasm, "\tpush eax\n");
}

void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2) {

	popVariable(fpasm, es_variable_2, "ecx");
	popVariable(fpasm, es_variable_1, "eax");

	fprintf(fpasm, "\timul ecx\n");
	fprintf(fpasm,"\tcdq\n");
	fprintf(fpasm, "\tpush eax\n");
}

void dividir(FILE* fpasm, int es_variable_1, int es_variable_2) {

	popVariable(fpasm, es_variable_2, "ecx");
	popVariable(fpasm, es_variable_1, "eax");

	fprintf(fpasm, "\tcmp ecx, 0\n");
	fprintf(fpasm, "\tje errordiv0\n");
	fprintf(fpasm, "\tcdq\n");
	fprintf(fpasm, "\tidiv ecx\n");
	fprintf(fpasm, "\tpush eax\n");
}

void o(FILE* fpasm, int es_variable_1, int es_variable_2) {

	popVariable(fpasm, es_variable_2, "edx");
	popVariable(fpasm, es_variable_1, "eax");

	fprintf(fpasm, "\tor eax, edx\n");
	fprintf(fpasm, "\tpush eax\n");

}

void y(FILE* fpasm, int es_variable_1, int es_variable_2) {

	popVariable(fpasm, es_variable_2, "edx");
	popVariable(fpasm, es_variable_1, "eax");

	fprintf(fpasm, "\tand eax, edx\n");
	fprintf(fpasm, "\tpush eax\n");
}

/*
Función aritmética de cambio de signo.
Es análoga a las binarias, excepto que sólo requiere de un acceso a la pila ya
que sólo usa un operando.
*/
void cambiar_signo(FILE* fpasm, int es_variable) {

	popVariable(fpasm, es_variable, "eax");

	fprintf(fpasm, "\tmov ecx, -1\n");
	fprintf(fpasm, "\timul ecx\n");
	fprintf(fpasm,"\tcdq\n");
	fprintf(fpasm, "\tpush eax\n");
}

/*
Función monádica lógica de negación. No hay un código de operación de la ALU
que realice esta operación por lo que se debe codificar un algoritmo que, si
encuentra en la cima de la pila un 0 deja en la cima un 1 y al contrario.
El último argumento es el valor de etiqueta que corresponde (sin lugar a dudas,
la implementación del algoritmo requerirá etiquetas). Véase en los ejemplos de
programa principal como puede gestionarse el número de etiquetas cuantos_no.
*/
void no(FILE* fpasm, int es_variable, int cuantos_no) {

	popVariable(fpasm, es_variable, "eax");
	fprintf(fpasm, "\tcmp eax, 0\n");
	fprintf(fpasm, "\tje _escribeuno%d\n", cuantos_no);
	fprintf(fpasm, "\tmov eax, 0\n");
	fprintf(fpasm, "\tjmp continuar%d\n", cuantos_no);
	fprintf(fpasm, "_escribeuno%d:\n", cuantos_no );
	fprintf(fpasm, "\tmov eax, 1");
	fprintf(fpasm, "\ncontinuar%d:\n", cuantos_no);
	fprintf(fpasm, "\tpush eax\n");
}


/* FUNCIONES COMPARATIVAS */
/*
Todas estas funciones reciben como argumento si los elementos a comparar son o
no variables. El resultado de las operaciones, que siempre será un booleano (“1”
si se cumple la comparación y “0” si no se cumple), se deja en la pila como en el
resto de operaciones. Se deben usar etiquetas para poder gestionar los saltos
necesarios para implementar las comparaciones.
*/
void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){

	popVariable(fpasm, es_variable2, "ecx");
	popVariable(fpasm, es_variable1, "eax");

	fprintf(fpasm, "\tcmp eax, ecx\n");
	fprintf(fpasm, "\tje near igual%d\n", etiqueta);
	fprintf(fpasm, "\tpush dword 0\n");
	fprintf(fpasm, "\tjmp near continuar%d\n", etiqueta);
	fprintf(fpasm, "igual%d:\n", etiqueta);
	fprintf(fpasm, "\tpush dword 1\n");
	fprintf(fpasm, "\ncontinuar%d:\n", etiqueta);
}

void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){

	popVariable(fpasm, es_variable2, "ecx");
	popVariable(fpasm, es_variable1, "eax");

	fprintf(fpasm, "\tcmp eax, ecx\n");
	fprintf(fpasm, "\tjne near distinto%d\n", etiqueta);
	fprintf(fpasm, "\tpush dword 0\n");
	fprintf(fpasm, "\tjmp near continuar%d\n", etiqueta);
	fprintf(fpasm, "distinto%d:\n", etiqueta);
	fprintf(fpasm, "\tpush dword 1\n");
	fprintf(fpasm, "\ncontinuar%d:\n", etiqueta);
}

void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){

	popVariable(fpasm, es_variable2, "ecx");
	popVariable(fpasm, es_variable1, "eax");

	fprintf(fpasm, "\tcmp eax, ecx\n");
	fprintf(fpasm, "\tjle near menor_igual%d\n", etiqueta);
	fprintf(fpasm, "\tpush dword 0\n");
	fprintf(fpasm, "\tjmp near continuar%d\n", etiqueta);
	fprintf(fpasm, "menor_igual%d:\n", etiqueta);
	fprintf(fpasm, "\tpush dword 1\n");
	fprintf(fpasm, "\ncontinuar%d:\n", etiqueta);
}

void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){

	popVariable(fpasm, es_variable2, "ecx");
	popVariable(fpasm, es_variable1, "eax");

	fprintf(fpasm, "\tcmp eax, ecx\n");
	fprintf(fpasm, "\tjge near mayor_igual%d\n", etiqueta);
	fprintf(fpasm, "\tpush dword 0\n");
	fprintf(fpasm, "\tjmp near continuar%d\n", etiqueta);
	fprintf(fpasm, "mayor_igual%d:\n", etiqueta);
	fprintf(fpasm, "\tpush dword 1\n");
	fprintf(fpasm, "\ncontinuar%d:\n", etiqueta);
}

void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta) {

	popVariable(fpasm, es_variable2, "ecx");
	popVariable(fpasm, es_variable1, "eax");

	fprintf(fpasm, "\tcmp eax, ecx\n");
	fprintf(fpasm, "\tjl near menor%d\n", etiqueta);
	fprintf(fpasm, "\tpush dword 0\n");
	fprintf(fpasm, "\tjmp near continuar%d\n", etiqueta);
	fprintf(fpasm, "menor%d:\n", etiqueta);
	fprintf(fpasm, "\tpush dword 1\n");
	fprintf(fpasm, "\ncontinuar%d:\n", etiqueta);
}

void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){

	popVariable(fpasm, es_variable2, "ecx");
	popVariable(fpasm, es_variable1, "eax");

	fprintf(fpasm, "\tcmp eax, ecx\n");
	fprintf(fpasm, "\tjg near mayor%d\n", etiqueta);
	fprintf(fpasm, "\tpush dword 0\n");
	fprintf(fpasm, "\tjmp near continuar%d\n", etiqueta);
	fprintf(fpasm, "mayor%d:\n", etiqueta);
	fprintf(fpasm, "\tpush dword 1\n");
	fprintf(fpasm, "\ncontinuar%d:\n", etiqueta);
}


/* FUNCIONES DE ESCRITURA Y LECTURA */
/*
Se necesita saber el tipo de datos que se va a procesar (ENTERO o BOOLEANO) ya
que hay diferentes funciones de librería para la lectura (idem. escritura) de cada
tipo.
Se deben insertar en la pila los argumentos necesarios, realizar la llamada
(call) a la función de librería correspondiente y limpiar la pila.
*/
void leer(FILE* fpasm, char* nombre, int tipo) {

	fprintf(fpasm,"\tpush dword _%s\n", nombre);

	if(tipo==BOOLEANO) {
		fprintf(fpasm,"\tcall scan_boolean\n");
	} else if(tipo==ENTERO) {
		fprintf(fpasm,"\tcall scan_int\n");
	}

	fprintf(fpasm, "\tadd esp, 4\n");
}

void escribir(FILE* fpasm, int es_variable, int tipo) {

	if(es_variable == REFERENCIA){
	  fprintf(fpasm, "\tpop eax\n" );
		fprintf(fpasm, "\tmov eax, [eax]\n" );
		fprintf(fpasm, "\tpush eax\n" );
	}

	if(tipo == BOOLEANO){
		fprintf(fpasm, "\tcall print_boolean\n");
	}else if(tipo == ENTERO){
		fprintf(fpasm, "\tcall print_int\n");
	}

	fprintf(fpasm,"\tadd esp, 4\n");
	fprintf(fpasm, "\tcall print_endofline\n");
}

/*
Generación de código para el inicio de una estructura if-then-else
Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva
etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
exp_es_variable
  - Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
elemento de vector)
  - Es 0 en caso contrario (constante u otro tipo de expresión)
*/
void ifthenelse_inicio(FILE * fpasm, int exp_es_variable, int etiqueta) {

	popVariable(fpasm, exp_es_variable, "eax");

	fprintf(fpasm, "\tcmp eax, 0\n");
	fprintf(fpasm, "\tje near fin_then_%d\n", etiqueta);
}

/*
Generación de código para el inicio de una estructura if-then
Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva
etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
exp_es_variable
  - Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
elemento de vector)
  - Es 0 en caso contrario (constante u otro tipo de expresión)
*/
void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta) {

	popVariable(fpasm, exp_es_variable, "eax");

	fprintf(fpasm, "\tcmp eax, 0\n");
	fprintf(fpasm, "\tje near fin_then_%d\n", etiqueta);
}

/*
Generación de código para el fin de una estructura if-then
Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta
del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca
según se ha explicado
Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas
puesto que se ha liberado la última de ellas.
*/
void ifthen_fin(FILE * fpasm, int etiqueta) {

	fprintf(fpasm, "fin_then_%d:\n", etiqueta);
}

/*
Generación de código para el fin de la rama then de una estructura if-then-else
Sólo necesita usar la etiqueta adecuada, aunque es el final de una rama, luego debe venir
otra (la rama else) antes de que se termine la estructura y se tenga que ajustar las etiquetas
por lo que sólo se necesita que se utilice la etiqueta que corresponde al momento actual.
*/
void ifthenelse_fin_then( FILE * fpasm, int etiqueta) {

	fprintf(fpasm, "\tjmp near fin_ifelse_%d\n", etiqueta);
	fprintf(fpasm, "fin_then_%d:\n", etiqueta);
}

/*
Generación de código para el fin de una estructura if-then-else
Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta
del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca
según se ha explicado
Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas
puesto que se ha liberado la última de ellas.
*/
void ifthenelse_fin( FILE * fpasm, int etiqueta) {

	fprintf(fpasm, "fin_ifelse_%d:\n", etiqueta);
}

/*
Generación de código para el inicio de una estructura while
Como es el inicio de uno bloque de control de flujo de programa que requiere de una nueva
etiqueta deben ejecutarse antes las tareas correspondientes a esta situación
exp_es_variable:
  - Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
elemento de vector)
  - Es 0 en caso contrario (constante u otro tipo de expresión)
*/
void while_inicio(FILE * fpasm, int etiqueta) {

	fprintf(fpasm, "inicio_while_%d:\n", etiqueta);
}

/*
Generación de código para el momento en el que se ha generado el código de la expresión
de control del bucle
Sólo necesita usar la etiqueta adecuada, por lo que sólo se necesita que se recupere el valor
de la etiqueta que corresponde al momento actual.
exp_es_variable:
  - Es 1 si la expresión de la condición es algo asimilable a una variable (identificador,
o elemento de vector)
  - Es 0 en caso contrario (constante u otro tipo de expresión)
*/
void while_exp_pila (FILE * fpasm, int exp_es_variable, int etiqueta) {

	popVariable(fpasm, exp_es_variable, "eax");

	fprintf(fpasm, "\tcmp eax, 0\n");
	fprintf(fpasm, "\tje near fin_while_%d\n", etiqueta);
}


/*
Generación de código para el final de una estructura while
Como es el fin de uno bloque de control de flujo de programa que hace uso de la etiqueta
del mismo se requiere que antes de su invocación tome el valor de la etiqueta que le toca
según se ha explicado
Y tras ser invocada debe realizar el proceso para ajustar la información de las etiquetas
puesto que se ha liberado la última de ellas.
*/
void while_fin( FILE * fpasm, int etiqueta) {

	fprintf(fpasm, "\tjmp near inicio_while_%d\n", etiqueta);
	fprintf(fpasm, "fin_while_%d:\n", etiqueta);
}

/*
Generación de código para iniciar la declaración de una función.
Es necesario proporcionar:
  - Su nombre
  - Su número de variables locales
*/
void declararFuncion(FILE * fpasm, char * nombre_funcion, int num_var_loc) {

	fprintf(fpasm, "\n_%s:\n", nombre_funcion);
	fprintf(fpasm, "\tpush ebp\n");
	fprintf(fpasm, "\tmov ebp, esp\n");
	fprintf(fpasm, "\tsub esp, %d*4\n", num_var_loc);
}

/*
Generación de código para el retorno de una función:
  - La expresión que se retorna está en la cima de la pila.
  - Puede ser una variable (o algo equivalente) en cuyo caso exp_es_direccion vale 1
  - Puede ser un valor concreto (en ese caso exp_es_direccion vale 0)
*/
void retornarFuncion(FILE * fpasm, int es_variable) {

	popVariable(fpasm, es_variable, "eax");

	fprintf(fpasm, "\tmov esp, ebp\n");
	fprintf(fpasm, "\tpop ebp\n");
	fprintf(fpasm, "\tret\n");
}

/*
Función para dejar en la cima de la pila la dirección efectiva del parámetro que ocupa la
posición pos_parametro (recuerda que los parámetros se ordenan con origen 0) de un total
de num_total_parametros
*/
void escribirParametro(FILE* fpasm, int pos_parametro, int num_total_parametros) {

	int d_ebp = 4 * (1 + (num_total_parametros-pos_parametro));
	fprintf(fpasm, "; escribirParametro\n");
	fprintf(fpasm, "\tlea eax, [ebp + %d]\n", d_ebp);
	fprintf(fpasm, "\tpush dword eax\n");
}

/*
Función para dejar en la cima de la pila la dirección efectiva de la variable local que ocupa
la posición posicion_variable_local (recuerda que ordenadas con origen 1)
*/
void escribirVariableLocal(FILE* fpasm, int posicion_variable_local) {

	int d_ebp = 4 * posicion_variable_local;
	fprintf(fpasm, "; escribirVariableLocal\n");
	fprintf(fpasm, "\tlea eax, [ebp - %d]\n", d_ebp);
	fprintf(fpasm, "\tpush dword eax\n");
}

/*
Función para poder asignar a un destino que no es una variable “global” (tipo _x ) por
ejemplo parámetros o variables globales (ya que en ese caso su nombre real de alto nivel, no
se tiene en cuenta pues es realmente un desplazamiento a partir de ebp : ebp+4 o ebp-8 por
ejemplo.
Se debe asumir que en la pila estará
  - Primero (en la cima) lo que hay que asignar
  - Debajo (se ha introducido en la pila antes) la dirección donde hay que asignar
es_variable
  - Es 1 si la expresión que se va a asignar es algo asimilable a una variable
(identificador, o elemento de vector)
  - Es 0 en caso contrario (constante u otro tipo de expresión)
*/
void asignarDestinoEnPila(FILE* fpasm, int es_variable) {

	fprintf(fpasm, "\tpop ebx\n");
	popVariable(fpasm, es_variable, "eax");
	fprintf(fpasm, "\tmov [ebx], eax \n");


}

/*
Como habrás visto en el material, nuestro convenio de llamadas a las funciones asume que
los argumentos se pasan por valor, esto significa que siempre se dejan en la pila “valores” y
no “variables”
Esta función realiza la tarea de dado un operando escrito en la pila y sabiendo si es variable
o no (es_variable) se deja en la pila el valor correspondiente
*/
void operandoEnPilaAArgumento(FILE * fpasm, int es_variable) {
	fprintf(fpasm, "; operandoEnPilaAArgumento\n");

	if (es_variable == REFERENCIA) {
		fprintf(fpasm, "\tpop eax\n");
		fprintf(fpasm, "\tmov eax, [eax]\n");
		fprintf(fpasm, "\tpush eax\n");
	}
}

/*
Esta función genera código para llamar a la función nombre_funcion asumiendo que los
argumentos están en la pila en el orden fijado en el material de la asignatura.
Debe dejar en la cima de la pila el retorno de la función tras haberla limpiado de sus
argumentos
Para limpiar la pila puede utilizar la función de nombre limpiarPila
*/
void llamarFuncion(FILE * fpasm, char * nombre_funcion, int num_argumentos) {

	fprintf(fpasm, "; llamarFuncion\n");
	fprintf(fpasm, "\tcall _%s\n", nombre_funcion);
	limpiarPila(fpasm, num_argumentos);
	fprintf(fpasm, "\tpush dword eax\n");
}

/*
Genera código para limpiar la pila tras invocar una función
Esta función es necesaria para completar la llamada a métodos, su gestión dificulta el
conocimiento por parte de la función de llamada del número de argumentos que hay en la
pila
*/
void limpiarPila(FILE * fpasm, int num_argumentos) {

	fprintf(fpasm, "\tadd esp, %d*4\n", num_argumentos);
}

/*
Generación de código para indexar un vector
Cuyo nombre es nombre_vector
Declarado con un tamaño tam_max
La expresión que lo indexa está en la cima de la pila
Puede ser una variable (o algo equivalente) en cuyo caso exp_es_direccion vale 1
*/
void escribir_elemento_vector(FILE * fpasm,char * nombre_vector, int tam_max, int exp_es_direccion) {

	popVariable(fpasm, exp_es_direccion, "eax");

	fprintf(fpasm, "cmp eax, 0\n");
	fprintf(fpasm, "jl near erroroutrange\n");
	fprintf(fpasm, "cmp eax, %d\n", tam_max-1 );
	fprintf(fpasm, "jg near erroroutrange\n");
	fprintf(fpasm, "mov dword edx, _%s\n", nombre_vector);
	fprintf(fpasm, "lea eax, [edx + eax*4]\n");
	fprintf(fpasm, "push dword eax\n");
}
