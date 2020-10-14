%{
/* Se incluye la librería tokens y se inicializan las variables requeridas */
#include "tokens.h"

int nlin = 1;
int ncol = 1;

%}

/* Para procesar solo un fichero */
%option noyywrap

%%

"//".*"\n"                  {nlin += 1; ncol = 1;}
main                        {ncol += yyleng; return TOK_MAIN;}
int                         {ncol += yyleng; return TOK_INT;}
boolean                     {ncol += yyleng; return TOK_BOOLEAN;}
array                       {ncol += yyleng; return TOK_ARRAY;}
function                    {ncol += yyleng; return TOK_FUNCTION;}
";"                         {ncol += yyleng; return TOK_PUNTOYCOMA;}
"["                         {ncol += yyleng; return TOK_CORCHETEIZQUIERDO;}
"]"                         {ncol += yyleng; return TOK_CORCHETEDERECHO;}
"{"                         {ncol += yyleng; return TOK_LLAVEIZQUIERDA;}
"}"                         {ncol += yyleng; return TOK_LLAVEDERECHA;}
"=="                        {ncol += yyleng; return TOK_IGUAL;}
"="                         {ncol += yyleng; return TOK_ASIGNACION;}
if                          {ncol += yyleng; return TOK_IF;}
else                        {ncol += yyleng; return TOK_ELSE;}
while                       {ncol += yyleng; return TOK_WHILE;}
scanf                       {ncol += yyleng; return TOK_SCANF;}
printf                      {ncol += yyleng; return TOK_PRINTF;}
return                      {ncol += yyleng; return TOK_RETURN;}
"&&"                        {ncol += yyleng; return TOK_AND;}
"||"                        {ncol += yyleng; return TOK_OR;}
"!"                         {ncol += yyleng; return TOK_NOT;}
"("                         {ncol += yyleng; return TOK_PARENTESISIZQUIERDO;}
")"                         {ncol += yyleng; return TOK_PARENTESISDERECHO;}
","                         {ncol += yyleng; return TOK_COMA;}
"!="                        {ncol += yyleng; return TOK_DISTINTO;}
"<="                        {ncol += yyleng; return TOK_MENORIGUAL;}
">="                        {ncol += yyleng; return TOK_MAYORIGUAL;}
">"                         {ncol += yyleng; return TOK_MAYOR;}
"<"                         {ncol += yyleng; return TOK_MENOR;}
"+"                         {ncol += yyleng; return TOK_MAS;}
"-"                         {ncol += yyleng; return TOK_MENOS;}
"/"                         {ncol += yyleng; return TOK_DIVISION;}
"\*"                        {ncol += yyleng; return TOK_ASTERISCO;}
true                        {ncol += yyleng; return TOK_TRUE;}
false                       {ncol += yyleng; return TOK_FALSE;}
[0-9][0-9]*                 {ncol += yyleng; return TOK_CONSTANTE_ENTERA;}
([a-zA-Z][0-9a-zA-Z]{0,99}) {ncol += yyleng; return TOK_IDENTIFICADOR;}
([a-zA-Z][0-9a-zA-Z]{100,}) {return TOK_ERROR;}
[0-9][0-9]*[a-zA-Z]+        {return 1000;} /* 1000 (constante aleatoria) no definida en tokens.h */

"\n"                        {nlin += 1; ncol = 1;}
"\t"                        {ncol += yyleng; }
" "                         {ncol += yyleng; }

.                           {return 1000;}
%%
