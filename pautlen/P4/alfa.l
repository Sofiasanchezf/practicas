%{
/* Se incluye la librería tokens y se inicializan las variables requeridas */

#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>

int nlin = 1;
int ncol = 1;
int is_morpho = 0;


%}

/* Para procesar solo un fichero */
%option noyywrap

%%


"\n"                        {nlin += 1; ncol = 1;}
"\t"                        {ncol += yyleng; }
" "                         {ncol += yyleng; }
"//".*"\n"                  {nlin += 1; ncol = 1;}

main                        {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAIN;}
int                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_INT;}
boolean                     {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_BOOLEAN;}
array                       {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ARRAY;}
function                    {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_FUNCTION;}
";"                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PUNTOYCOMA;}
"["                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_CORCHETEIZQUIERDO;}
"]"                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_CORCHETEDERECHO;}
"{"                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_LLAVEIZQUIERDA;}
"}"                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_LLAVEDERECHA;}
"="                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ASIGNACION;}
if                          {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_IF;}
else                        {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ELSE;}
while                       {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_WHILE;}
scanf                       {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_SCANF;}
printf                      {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PRINTF;}
return                      {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_RETURN;}
"&&"                        {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_AND;}
"||"                        {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_OR;}
"!"                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_NOT;}
"("                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PARENTESISIZQUIERDO;}
")"                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PARENTESISDERECHO;}
","                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_COMA;}
==                        {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_IGUAL;}
"!="                        {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_DISTINTO;}
"<="                        {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MENORIGUAL;}
">="                        {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAYORIGUAL;}
">"                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAYOR;}
"<"                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MENOR;}
"+"                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAS;}
"-"                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MENOS;}
"/"                         {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_DIVISION;}
"*"                        {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ASTERISCO;}
true                        {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_TRUE;}
false                       {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_FALSE;}
[0-9][0-9]*                 {ncol += yyleng;fprintf(yyout, ";D:\t%s\n", yytext); return TOK_CONSTANTE_ENTERA;}
([a-zA-Z]([0-9a-zA-Z]){0,99}) {ncol += yyleng; fprintf(yyout,";D:\t%s\n", yytext);return TOK_IDENTIFICADOR;}
([a-zA-Z]([0-9a-zA-Z]){100,}) {is_morpho=1; return TOK_ERROR;}
[0-9][0-9]*[a-zA-Z]+        {is_morpho=1;return TOK_ERROR;} /* 1000 (constante aleatoria) no definida en tokens.h */

.                           {is_morpho=1;printf ("*****Error morpho en [lin %d, col %d]: simbolo (%s) no permitido\n", nlin, ncol, yytext); return TOK_ERROR;}
%%
