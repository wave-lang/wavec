%top{
#include "wave_yacc.h"
#include "preproc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
}
%{
/*
The MIT License (MIT)

Copyright (c) 2014 Éric VIOLARD, Maxime SCHMITT, Harenome RAZANAJATO RANAIVOARIVONY

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

static unsigned int nb_rows = 1;
static unsigned int let_row = 1;
char* value = NULL;
static int retval = 0;
static char* _temp_expression = NULL;
extern int yylval;
%}
Integer     [0-9]+
Float       [0-9]+"."[0-9]*|[0-9]*"."[0-9]+
Character   "'"."'"
String      "\"".*"\""
Boolean     True|False
%x Definition Naming Be Macro Comment PREPROCESSOR

%%
<Definition,Naming,Be,Macro>"\n"                        ++nb_rows;
<PREPROCESSOR>"\n"                                      {
    ++nb_rows;
    fprintf(yyout, "\n");
}
<PREPROCESSOR>"Let "+                                   {
    printf("Let ligne %u\n", nb_rows);
    let_row = nb_rows;
    BEGIN(Naming);
}
<PREPROCESSOR>[a-zA-Z][a-zA-Z0-9_]*                     {
    retval = preproc_check_identifier(yytext, &value);
    if(retval == 1){
        fprintf(stderr, "The identifier %s line %d is not defined yet.\n", yytext, nb_rows);
        return 1;
    }
    fprintf(yyout, "%s", value);
}
<Naming><<EOF>>                                         return preproc_err_eof(let_row);
<Naming>[a-zA-Z][a-zA-Z0-9\_]*                          {
    preproc_new_identifier(yytext);
    printf("Name found : %s\n", yytext);
    BEGIN(Be);
}
<Be>[^ ]*" "be                                          return preproc_err_double_id();
<Be>" "+be[ ]+                                          {
    printf("Found the be %s\n", yytext);
    BEGIN(Macro);
}
<Be>" "+be[\n]                                          {
    printf("Found the be\n");
    ++nb_rows;
    BEGIN(Macro);
}
<Be><<EOF>>                                             return preproc_err_eof(let_row);
<Macro>[a-zA-Z][a-zA-Z0-9_]*                            {
    if( preproc_test_or_add_identifier(yytext) != 0)
        return 1;
}
<Macro>\".*\"                                           preproc_add_to_current_expression(yytext);
<Macro>'.*'                                             preproc_add_to_current_expression(yytext);
<Macro>[^.\n% a-zA-Z"']*                                 {
    preproc_add_to_current_expression(yytext);
}
<Macro>"."                                              {
    preproc_add_current_id_with_current_expression();
    BEGIN(PREPROCESSOR);
}
<PREPROCESSOR,Definition,Naming,Be,Macro>"%"[^\n]*      /* eat up one line comments */


"."                                     return Dot;
"{||"                                   return Obrace_parallel;
"{;"                                    return Obrace_sequential;
"}"                                     return Cbrace;
"@"                                     return At;
"#"                                     return Number_sign;
"("                                     return Oparentheses;
")"                                     return Cparentheses;
"|""|"                                  return Parallel;
";"                                     return Semicolon;
"p"                                     return Prec;
"s"                                     return Succ;
"u"                                     return Up;
"d"                                     return Down;
"r"                                     return Rewind;
"~+"                                    return Unary_plus;
"~-"                                    return Unary_minus;
"++"                                    return Increment;
"--"                                    return Decrement;
sqrt                                    return Square_root;
sin                                     return Sin;
cos                                     return Cos;
not                                     return Not;
log                                     return Log;
exp                                     return Exp;
ceil                                    return Ceil;
floor                                   return Floor;
"+"                                     return Plus;
"-"                                     return Minus;
min                                     return Min;
max                                     return Max;
"*"                                     return Times;
"/"                                     return Divid;
mod                                     return Mod;
"="                                     return Equal;
"<>"                                    return Not_equal;
"<="                                    return Lesser_equal;
">="                                    return Upper_equal;
"<"                                     return Lesser;
">"                                     return Upper;
and                                     return And;
or                                      return Or;
get                                     return Get;
"?"                                     return Question_mark;
"!"                                     return Exclamation_mark;
read                                    return Read;
print                                   return Print;
{Integer}                               return Integer_litteral;
{Float}                                 return Float_litteral;
{Character}                             return Char_litteral;
{String}                                return String_litteral;
{Boolean}                               // test de bool

%%

