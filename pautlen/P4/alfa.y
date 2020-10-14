%{
#include <stdio.h>
#include "alfa.h"

extern FILE* yyin;
extern FILE* yyout;
extern int nlin;
extern int ncol;
extern int yyleng;
extern int yylex();
extern int is_morpho;
extern TablaSimbolos * t;

Elemento * e = NULL;
int error;
int res_aux;


/* Para propagacion de caracteristicas de la declaracion a las variables de a lista: */
int tipo_actual;
int clase_actual; /* se refiere a la categoria */
int tamanio_vector_actual;
int pos_variable_local_actual;
int num_variables_locales_actual;
int num_parametros_actual;
int pos_parametro_actual;
int en_explist;
int num_parametros_llamada_actual;

void yyerror(char const * s);
%}
%union
{
	tipo_atributos atributos;
}
/* Palabras reservadas */
%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_FUNCTION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_RETURN

%token TOK_PUNTOYCOMA
%token TOK_COMA
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_ASIGNACION
%token TOK_MAS
%token TOK_MENOS
%token TOK_DIVISION
%token TOK_ASTERISCO
%token TOK_AND
%token TOK_OR
%token TOK_NOT
%token TOK_IGUAL
%token TOK_DISTINTO
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL
%token TOK_MENOR
%token TOK_MAYOR


/* Valor semantico */
%token <atributos> TOK_IDENTIFICADOR
%token <atributos> TOK_CONSTANTE_ENTERA

/* Constantes */
%token TOK_TRUE
%token TOK_FALSE

/* Errores */
%token TOK_ERROR

%left TOK_MAS TOK_MENOS TOK_OR TOK_MENOR TOK_MAYOR TOK_IGUAL TOK_DISTINTO TOK_MENORIGUAL TOK_MAYORIGUAL
%left TOK_ASTERISCO TOK_DIVISION TOK_AND
%right TOK_NOT

%type <atributos> exp
%type <atributos> comparacion

%%

programa: inicioTabla TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones funciones sentencias TOK_LLAVEDERECHA
{fprintf(yyout, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");}
;
inicioTabla: {
								t = tablasimbolos_create();
						 }
;
declaraciones: declaracion {fprintf(yyout, ";R2:\t<declaraciones> ::= <declaracion>\n");}
			| declaracion declaraciones { fprintf(yyout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n"); }
;

declaracion: clase identificadores TOK_PUNTOYCOMA {fprintf(yyout, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");}
;

clase: clase_escalar {clase_actual = ESCALAR; fprintf(yyout, ";R5:\t<clase> ::= <clase_escalar>\n");}
	 | clase_vector {clase_actual = VECTOR; fprintf(yyout, ";R7:\t<clase> ::= <clase_vector>\n");}
;

clase_escalar: tipo {fprintf(yyout, ";R9:\t<clase_escalar> ::= <tipo>\n");}
;

tipo: 	TOK_INT {tipo_actual = INT; fprintf(yyout, ";R10:\t<tipo> ::= int\n");}
			| TOK_BOOLEAN {tipo_actual = BOOLEAN; fprintf(yyout, ";R11:\t<tipo> ::= boolean\n");}
;

clase_vector : TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO constante_entera TOK_CORCHETEDERECHO
								{
									tamanio_vector_actual = $4.valor_entero;
									if ((tamanio_vector_actual < 1) ||
											(tamanio_vector_actual > MAX_TAMANIO_VECTOR))
											{
												error = 8
											}
									fprintf(yyout,";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ]\n");
								}
;


identificadores: TOK_IDENTIFICADOR {fprintf(yyout, ";R18:\t<identificadores> ::= <identificador>\n");}
				| TOK_IDENTIFICADOR TOK_COMA identificadores {fprintf(yyout, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");}
;

funciones: funcion funciones { fprintf(yyout, ";R20:\t<funciones> ::= <funcion> <funciones>\n");}
		 | /* vacio */ {fprintf(yyout, ";R21:\t<funciones> ::=\n");}
;
fn_name: TOK_FUNCTION tipo TOK_IDENTIFICADOR
					{
						res_aux = buscar_elemento(t, $1.lexema, NULL);
						if (res_aux != -1) {
							error = 1;
							yyerror(NULL);
						}
						tablasimbolos_abir_ambito_local(t, $1.lexema, SIN_USO, tipo_actual, num_parametros_actual,
						 																num_variables_locales_actual);

						num_variables_locales_actual = 0;
						pos_variable_local_actual = 1;
						num_parametros_actual = 0;
						pos_param_actual = 0;
					}
;

fn_declaration: fn_name TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion
	{
		buscar_elemento(t, $1.lexema, &e);
		elemento_setNumero_parametros(e, num_parametros_actual);

	}
	;

funcion: fn_declaration sentencias TOK_LLAVEDERECHA
	{

		tablasimbolos_cerrar_ambito_local(t);
		buscar_elemento(t, $1.lexema, &e);
		elemento_setNumero_parametros(e, num_parametros_actual);

		fprintf(yyout, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }\n");

	}
;

parametros_funcion: parametro_funcion resto_parametros_funcion {fprintf(yyout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");}
				| /* vacio */ {fprintf(yyout, ";R24:\t<parametros_funcion> ::=\n");}
;

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion {fprintf(yyout, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>\n");}
						| /* vacio */ {fprintf(yyout, ";R26:\t<resto_parametros_funcion> ::=\n");}
;

parametro_funcion: tipo idpf TOK_IDENTIFICADOR {fprintf(yyout, ";R27:\t<parametro_funcion> ::= <tipo> <identificador>\n");}
;

declaraciones_funcion: declaraciones {fprintf(yyout, ";R28:\t<declaraciones_funcion> ::= <declaraciones>\n");}
					 | /* vacio */ {fprintf(yyout, ";R29:\t<declaraciones_funcion> ::=\n");}
;

sentencias: sentencia {fprintf(yyout, ";R30:\t<sentencias> ::= <sentencia>\n");}
		  | sentencia sentencias {fprintf(yyout, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");}
;

sentencia: sentencia_simple TOK_PUNTOYCOMA {fprintf(yyout, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");}
		  | bloque {fprintf(yyout, ";R33:\t<sentencia> ::= <bloque>\n");}
;

sentencia_simple: asignacion {fprintf(yyout, ";R34:\t<sentencia_simple> ::= <asignacion>\n");}
				| lectura {fprintf(yyout, ";R35:\t<sentencia_simple> ::= <lectura>\n");}
				| escritura {fprintf(yyout, ";R36:\t<sentencia_simple> ::= <escritura>\n");}
				| retorno_funcion {fprintf(yyout, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");}
;

bloque: condicional {fprintf(yyout, ";R40:\t<bloque> ::= <condicional>\n");}
		| bucle {fprintf(yyout, ";R41:\t<bloque> ::= <bucle>\n");}
;

asignacion: TOK_IDENTIFICADOR TOK_ASIGNACION exp
							{

								res_aux = buscar_elemento(t, $1.lexema, &e);
								if (res_aux == -1) {
									error = 2;
									yyerror(NULL);
								}
								if(elemento_getCategoria_Elemento(e) == FUNCION) {
									error = 16;
									yyerror(NULL);
								}
								if ($$.tipo != $1.tipo) {
									error = 16;
									yyerror(NULL);
								}
								fprintf(yyout, ";R43:\t<asignacion> ::= <identificador> = <exp>\n");
							}
			| elemento_vector TOK_ASIGNACION exp
							{
								if ($$.tipo != $1.tipo) {
									error = 9;
									yyerror(NULL);
								}
								fprintf(yyout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");
							}
;

elemento_vector: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO
										{
											buscar_elemento(t, $1.lexema, &e);
											if(elemento_getTamanio(e) > MAX_TAMANIO_VECTOR || elemento_getTamanio(e)  < 1) {
												error = 8;
												yyerror(NULL);
											}
											fprintf(yyout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");
										}
;

condicional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(yyout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n");}
			| TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(yyout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");}
;

bucle: TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(yyout, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");}
;

lectura: TOK_SCANF TOK_IDENTIFICADOR

	{

		res_aux = buscar_elemento(t, $2.lexema, &e);
		if(res_aux == -1) {
			error = 2;
			yyerror(NULL);
		}

		if (elemento_getCategoria(e) == FUNCION) {
			error = 16;
			yyerror(NULL);
		}

		if (elemento_getCategoria(e) == VECTOR) {
			error = 16;
			yyerror(NULL);
		}

		if (res_aux == TABLA_GLOBAL) {

			if (clase_actual == ESCALAR) {
				tamanio_vector_actual = SIN_USO;
			}

			declarar_variable(yyout, $1.lexema, tipo_actual, tamanio_vector_actual);

		} else {

			if (categoria == PARAMETRO) {
			 		escribirParametro(yyout, pos_parametro_actual, num_parametros_actual);
			} else if(categoria == VARIABLE) {
				 	escribirVariableLocal(yyout, pos_parametro_actual);
			}
		}

		leer(yyout, $1.lexema, tipo_actual);

	}

;

escritura: TOK_PRINTF exp {fprintf(yyout, ";R56:\t<escritura> ::= printf <exp>\n");}
;

retorno_funcion: TOK_RETURN exp {fprintf(yyout, ";R61:\t<retorno_funcion> ::= return <exp>\n");}
;

exp: exp TOK_MAS exp
					{
						if ($1.tipo != INT || $3.tipo != INT) {
							error = 3;
							yyerror(NULL);
						}
						$$.tipo = INT;
						$$.es_direccion = 0;

						fprintf(yyout, ";R72:\t<exp> ::= <exp> + <exp>\n");
					}
	| exp TOK_MENOS exp
					{
						if ($1.tipo != INT || $3.tipo != INT) {
							error = 3;
							yyerror(NULL);
						}
						$$.tipo = INT;
						$$.es_direccion = 0;

						fprintf(yyout, ";R73:\t<exp> ::= <exp> - <exp>\n");
					}
	| exp TOK_DIVISION exp
					{
						if ($1.tipo != INT || $3.tipo != INT) {
							error = 3;
							yyerror(NULL);
						}
						$$.tipo = INT;
						$$.es_direccion = 0;
						fprintf(yyout, ";R74:\t<exp> ::= <exp> / <exp>\n");
					}
	| exp TOK_ASTERISCO exp
					{
						if ($1.tipo != INT || $3.tipo != INT) {
							error = 3;
							yyerror(NULL);
						}
						$$.tipo = INT;
						$$.es_direccion = 0;
						fprintf(yyout, ";R75:\t<exp> ::= <exp> * <exp>\n");
					}
	| TOK_MENOS exp %prec TOK_NOT
					{
						if ($2.tipo != INT) {
							error = 3;
							yyerror(NULL);
						}
						$$.tipo = INT;
						$$.es_direccion = 0;

						fprintf(yyout, ";R76:\t<exp> ::= - <exp>\n");
					}
	| exp TOK_AND exp
					{
						if ($1.tipo != BOOLEAN || $3.tipo != BOOLEAN) {
							error = 4;
							yyerror(NULL);
						}
						$$.tipo = BOOLEAN;
						$$.es_direccion = 0;
						fprintf(yyout, ";R77:\t<exp> ::= <exp> && <exp>\n");
					}
	| exp TOK_OR exp
					{
						if ($1.tipo != BOOLEAN || $3.tipo != BOOLEAN) {
							error = 4;
							yyerror(NULL);
						}
						$$.tipo = BOOLEAN;
						$$.es_direccion = 0;
						fprintf(yyout, ";R78:\t<exp> ::= <exp> || <exp>\n");
					}
	| TOK_NOT exp
			{
				if ($2.tipo != BOOLEANN) {
					error = 4;
					yyerror(NULL);
				}
				$$.tipo = BOOLEAN;
				$$.es_direccion = 0;
				fprintf(yyout, ";R79:\t<exp> ::= ! <exp>\n");
			}
	| TOK_IDENTIFICADOR
				{
					res_aux = buscar_elemento(t, $1.lexema, &e);
					if(res_aux == -1) {
						error = 2;
						yyerror(NULL);
					}
					if (elemento_getCategoria_Elemento(e) == FUNCION || elemento_getCategoria(e) == VECTOR) {
						error = 16;
						yyerror(NULL);
					}
					$$.tipo = elemento_getTipo(e);
					$$.es_direccion = 1;

					fprintf(yyout, ";R80:\t<exp> ::= <identificador>\n");
				}
	| constante {$$.tipo = $1.tipo; $$.es_direccion = $1.es_direccion;fprintf(yyout, ";R81:\t<exp> ::= <constante>\n");}
	| TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {$$.tipo = $2.tipo; $$.es_direccion = $2.es_direccion; fprintf(yyout, ";R82:\t<exp> ::= ( <exp> )\n");}
	| TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {$$.tipo = $2.tipo;$$.es_direccion = $2.es_direccion; fprintf(yyout, ";R83:\t<exp> ::= ( <comparacion> )\n");}
	| elemento_vector {$$.tipo = $1.tipo; $$.es_direccion = $1.es_direccion; fprintf(yyout, ";R85:\t<exp> ::= <elemento_vector> \n");}
	| idf_llamada_funcion TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO
													{
														res_aux = buscar_elemento(t, $1.lexema, &e);
														if(elemento_getNumero_parametros(e) != num_parametros_llamada_actual) {
															error = 7;
															yyerror(NULL);
														}
														en_explist = 0;
														$$.tipo = elemento_getTipo(e);
														$$.es_direccion = 0;
														fprintf(yyout, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> )\n");
													}
;

idf_llamada_funcion : TOK_IDENTIFICADOR
													{
														res_aux = buscar_elemento(t, $1.lexema, &e);
														if (res_aux == -1) {
															error = 2;
															yyerror(NULL);
														}
														if (elemento_getCategoria_Elemento(e) != FUNCION) {
															error = -1;
															yyerror(NULL);
														}
														if (en_explist == 1) {
															error = 13;
															yyerror(NULL);
														}
														num_parametros_llamada_actual == 0;
														en_explist = 1;
														strcpy($$.lexema,$1.lexema);

;

lista_expresiones: exp resto_lista_expresiones {num_parametros_llamada_actual++; fprintf(yyout, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");}
				 | /* vacio */ {fprintf(yyout, ";R90:\t<lista_expresiones> ::=\n");}
;

resto_lista_expresiones: TOK_COMA exp resto_lista_expresiones {num_parametros_llamada_actual++;fprintf(yyout, ";R91:\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>\n");}
						| /* vacio */ {fprintf(yyout, ";R92:\t<resto_lista_expresiones> ::=\n");}
;

comparacion: exp TOK_IGUAL exp
									{
										if ($1.tipo != INT || $3.tipo != INT) {
											error = 3;
											yyerror(NULL);
										}
										$$.tipo = BOOLEAN;
										$$.es_direccion = 0;
										fprintf(yyout, ";R93:\t<exp> ::= <exp> == <exp>\n");
									}
			| exp TOK_DISTINTO exp
							{
								if ($1.tipo != INT || $3.tipo != INT) {
									error = 3;
									yyerror(NULL);
								}
								$$.tipo = BOOLEAN;
								$$.es_direccion = 0;
								fprintf(yyout, ";R94:\t<exp> ::= <exp> != <exp>\n");
							}
			| exp TOK_MENORIGUAL exp
								{
									if ($1.tipo != INT || $3.tipo != INT) {
										error = 3;
										yyerror(NULL);
									}
									$$.tipo = BOOLEAN;
									$$.es_direccion = 0;
									fprintf(yyout, ";R95:\t<exp> ::= <exp> <= <exp>\n");
								}
			| exp TOK_MAYORIGUAL exp
									{
										if ($1.tipo != INT || $3.tipo != INT) {
											error = 3;
											yyerror(NULL);
										}
										$$.tipo = BOOLEAN;
										$$.es_direccion = 0;
										fprintf(yyout, ";R96:\t<exp> ::= <exp> >= <exp>\n");
									}
			| exp TOK_MENOR exp
							{
								if ($1.tipo != INT || $3.tipo != INT) {
									error = 3;
									yyerror(NULL);
								}
								$$.tipo = BOOLEAN;
								$$.es_direccion = 0;
								fprintf(yyout, ";R97:\t<exp> ::= <exp> < <exp>\n");
							}
			| exp TOK_MAYOR exp
							{
								if ($1.tipo != INT || $3.tipo != INT) {
									error = 3;
									yyerror(NULL);
								}
								$$.tipo = BOOLEAN;
								$$.es_direccion = 0;
								fprintf(yyout, ";R98:\t<exp> ::= <exp> > <exp>\n");
							}
;

constante: constante_logica {$$.tipo = $1.tipo; $$.es_direccion = $1.es_direccion; fprintf(yyout, ";R99:\t<constante> ::= <constante_logica>\n");}
		 | constante_entera {$$.tipo = $1.tipo; $$.es_direccion = $1.es_direccion;fprintf(yyout, ";R100:\t<constante> ::= <constante_entera>\n");}
;

constante_logica: TOK_TRUE {$$.tipo = BOOLEAN; $$.es_direccion = 0;fprintf(yyout, ";R102:\t<constante_logica> ::= true\n");}
				| TOK_FALSE {$$.tipo = BOOLEAN; $$.es_direccion = 0;fprintf(yyout, ";R103:\t<constante_logica> ::= false \n");}
;

constante_entera: TOK_CONSTANTE_ENTERA {$$.tipo = INT; $$.es_direccion = 0;fprintf(yyout, ";R104:\t<constante_entera> ::= TOK_CONSTANTE_ENTERA\n");}
;

idpf: TOK_IDENTIFICADOR
				{

					if (clase_actual == ESCALAR) {
						tamanio_vector_actual = SIN_USO;
					}
					res_aux = insertar_elemento_ambito_actual(t, $1.lexema, SIN_USO, PARAMETRO, tipo_actual, clase_actual,
																					SIN_USO, pos_param_actual, SIN_USO);

					if (res_aux == -1) {
						error = 1;
						yyerror(NULL);
					}

					pos_parametro_actual++;
					num_parametros_actual++;
				}

identificador: TOK_IDENTIFICADOR

 										{

												if (tablasimbolos_get_ambito_actual(t) == TABLA_LOCAL) {

													if (clase_actual == VECTOR) {
														error = 14;
														yyerror(NULL);
													}
													res_aux = insertar_elemento_ambito_actual(t, $1.lexema, SIN_USO, VARIABLE, tipo_actual, clase_actual,
																			                    SIN_USO, SIN_USO, pos_variable_local_actual);
													if (res_aux == -1) {
														error = 1;
														yyerror(NULL);
													}

												} else {

													if (clase_actual == ESCALAR) {
														tamanio_vector_actual = SIN_USO;
													}
													res_aux = insertar_elemento_ambito_actual(t, $1.lexema, SIN_USO, VARIABLE, tipo_actual, clase_actual,
																												tamanio_vector_actual, SIN_USO, SIN_USO);

													if (res_aux == -1) {
														error = 1;
														yyerror(NULL);
													}
													pos_variable_local_actual++;
													num_variables_locales_actual++;

												}

											 fprintf(yyout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");
							}

%%

void yyerror(const char * s) {

    if(!is_morpho) {
        fprintf(stderr, "****Error sintactico en [lin %d, col %d]\n", nlin, ncol-yyleng);
    }

	 switch ( error ) {

		 case  1:
			 fprintf(stderr, "****Error semantico en lin %d: Declaracion duplicada.\n", nlin);
			 break;
		 case  2:
		 	 fprintf(stderr, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n",nlin, $1.lexema);
			 break;
		 case  3:
			 fprintf(stderr, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", nlin);
			 break;
		 case  4:
			 fprintf(stderr, "****Error semantico en lin %d: Operacion logica con operandos int.\n", nlin);
			 break;
		 case  5:
			 fprintf(stderr, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", nlin);
			 break;
		 case  6:
			 fprintf(stderr, "****Error semantico en lin %d: Bucle con condicion de tipo int.\n", nlin);
			 break;
		 case  7:
			 fprintf(stderr, "****Error semantico en lin %d: Numero incorrecto de parametros en llamada a funcion.\n", nlin);
			 break;
		 case  8:
			 fprintf(stderr, "****Error semantico en lin %d: El tamanyo del vector <nombre_vector> excede los limites permitidos (1,64).\n",nlin, $1.lexema );
			 break;
		 case  9:
			 fprintf(stderr, "****Error semantico en lin %d: Intento de indexacion de una variable que no es de tipo vector.\n", nlin );
			 break;
		 case  10:
			 fprintf(stderr, "****Error semantico en lin %d: El indice en una operacion de indexacion tiene que ser de tipo entero.\n", nlin);
			 break;
		 case  11:
			 fprintf(stderr, "****Error semantico en lin %d: Funcion <nombre_funcion> sin sentencia de retorno.\n", nlin, $1.lexema );
			 break;
		 case  12:
			 fprintf(stderr, "****Error semantico en lin %d: Sentencia de retorno fuera del cuerpo de una funcion.\n", TOK_MAIN, yytext);
			 break;
		 case  13:
			 fprintf(stderr, "****Error semantico en lin %d: No esta permitido el uso de llamadas a funciones como parametros de otras funciones.\n", nlin);
			 break;
		 case  14:
			 fprintf(stderr, "****Error semantico en lin %d: Variable local de tipo no escalar.\n", nlin);
			 break;
		 case  15:
			 fprintf(stderr, "****Error semantico en lin %d: Condicional con condicion de tipo int.\n", nlin);
			 break;
		 case  16:
			 fprintf(stderr, "****Error semantico en lin %d: Asignacion incompatible.\n", nlin);
			 break;
		 default:
       fprintf(stderr, "****Error en [lin %d, col %d]: error no identificado.\n", nlin, ncol);
       break;

		}
}
