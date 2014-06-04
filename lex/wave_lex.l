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

#include "wave_yacc.h"
#include "preproc_utils.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "base_hash_table.h"
static unsigned int nb_rows = 1;
static unsigned int let_row = 1;
static HT_hash_table *_hash_table = NULL;
static char* identifier = NULL;
static char* value = NULL;
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
<PREPROCESSOR>"\n"                                      ++nb_rows; fprintf(yyout, "\n");
<PREPROCESSOR>"Let "+                                   printf("Let it be ligne %u\n", nb_rows); let_row = nb_rows; BEGIN(Naming);
<Naming>[a-zA-Z][a-zA-Z0-9\_]*                          identifier = strdup(yytext); printf("Name found : %s\n", identifier); BEGIN(Be);
<Be>" "+be[" "\n]+                                      printf("Be found"); BEGIN(Macro);
<Be>"Let"                                               fprintf(stderr, "Error !\nFound a \"Let\", line %u, after a \"Let\", line %u, without a \"be\" between them.", nb_rows, let_row); exit(EXIT_FAILURE);
<Be><<EOF>>                                             printf("Error, found an \"Let\" line %u but no \"be\" detected before the end of file\n", let_row); exit(EXIT_FAILURE);
<Macro>[^"."]*                                          HT_add_element_string(_hash_table, identifier, yytext);if(HT_get_element_string(_hash_table, identifier, &value) == 0)  printf("Expression :\n%s\n",value); /* add in the expression found buffer */
<Macro>"."                                              BEGIN(PREPROCESSOR); /* add in the hash table with the appropriate name */
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
static inline void perror_and_quit(const char* message){
    perror(message);
    exit(errno);
}

int main(int argc, char** argv){
    --argc; ++argv;
    _hash_table = HT_new_hash(100);
    if( argc > 2 || argc < 1 ){
        return EXIT_FAILURE;
    }
    yyin = fopen(argv[0], "r");
    if( yyin == NULL )
        perror_and_quit("fopen");
    if( argc == 2 )
        yyout = fopen(argv[1], "w");
    else
        yyout = fopen("pars_out.wave", "w");
    if( yyout == NULL )
        perror_and_quit("fopen");
    BEGIN(PREPROCESSOR);
    yylex();
    fclose( yyin );
    fclose( yyout );
    HT_delete(_hash_table);
    return EXIT_SUCCESS;
}
