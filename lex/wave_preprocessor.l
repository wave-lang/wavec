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
%top{
#include "wave/lex/preproc_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sysexits.h>
}
Integer     [0-9]+
Float       [0-9]+"."[0-9]*|[0-9]*"."[0-9]+
Character   "'"[^\']"'"
String      "\""[^\"]*"\""
Boolean     True|False
%x Definition Naming Be MacroDefinition Comment PREPROCESSOR

%%
<Definition,Naming,Be,MacroDefinition>"\n"                        ++nb_rows;
<PREPROCESSOR>"\n"                                      {
    ++nb_rows;
    fprintf(yyout, "\n");
}
<PREPROCESSOR,Definition,Naming,Be,MacroDefinition>[ \t]
<PREPROCESSOR>"Let "+                                   {
    let_row = nb_rows;
    BEGIN(Naming);
}
<PREPROCESSOR>[a-zA-Z][a-zA-Z0-9_]*                     { /* If an identifier is encontered outside of a declaration */
    retval = preproc_check_identifier(yytext, &value);
    if(retval == 1){
        fprintf(stderr, "Error : The identifier %s line %d is not defined yet.\n", yytext, nb_rows);
        return 1;
    }
    fprintf(yyout, "%s", value);
}
<PREPROCESSOR>{String}                                         { /* Strings */
    fprintf (yyout, yytext);
}
<PREPROCESSOR>{Character}                                      { /* Character */
    fprintf (yyout, yytext);
}
<Naming><<EOF>>                                         {
    fprintf(stderr, "Error : Encontered end of file while waiting for a declaration. \"Let\" encontered line %d\n", let_row);
}
<Naming>[a-zA-Z][a-zA-Z0-9\_]*                          {
    retval = preproc_check_identifier(yytext, &value);
    if(retval == 0){
        fprintf(stderr, "Error :The identifier %s line %d is already defined.\n", yytext, nb_rows);
        return 1;
    }
    preproc_new_identifier(yytext);
    BEGIN(Be);
}
<Be>[^ \n]*" "be                                          {
    fprintf(stderr, "Error : Found %s but expected \"be\" line %d\n", yytext, nb_rows);
    return 1;
}
<Be>" "+be[ ]+                                          {
    BEGIN(MacroDefinition);
}
<Be>" "+be[\n]                                          {
    ++nb_rows;
    BEGIN(MacroDefinition);
}
<Be><<EOF>>                                             {
    fprintf(stderr, "Error : Encontered end of file while waiting for a declaration. \"Let\" encontered line %d\n", let_row);
}
<MacroDefinition>[a-zA-Z][a-zA-Z0-9_]*                            { /* Encontered macro into the macro */
    retval = preproc_add_id_definition_to_current_expression(yytext);
    if( retval == 1 ){
        fprintf(stderr, "Error : The identifier %s line %d does not exist\n", yytext, let_row);
        return 1;
    }
}
<MacroDefinition>{String}                                         { /* Strings */
    preproc_add_to_current_expression(yytext);
}
<MacroDefinition>{Character}                                      { /* Character */
    preproc_add_to_current_expression(yytext);
}
<MacroDefinition>[^.\n% a-zA-Z"']*                                { /* Not identifier */
    preproc_add_to_current_expression(yytext);
}
<MacroDefinition>"."                                              {
    retval = preproc_add_current_id_with_current_expression();
    if(retval == 1){
        fprintf(stderr, "Error : No definition between the \"be\" and \".\" for the identifier %s.\n", preproc_get_actual_identifier());
        return 1;
    }
    if( retval == 2 ){
        fprintf(stderr, "Error : The identifier %s line %d does not exist\n", preproc_get_actual_identifier(), let_row);
        return 1;
    }
    BEGIN(PREPROCESSOR);
}
<PREPROCESSOR,Definition,Naming,Be,MacroDefinition>"%"[^\n]*      /* eat up one line comments */

%%

int main(int argc, char** argv){
    --argc; ++argv;
    preproc_init(256);
    if( argc > 2 || argc < 1 ){
        fprintf (stderr, "Error: wrong number of arguments.\n");
        exit (EX_USAGE);
    }
    yyin = fopen(argv[0], "r");
    if( yyin == NULL )
        perror_and_quit("fopen", EX_OSERR);
    if( argc == 2 )
        yyout = fopen(argv[1], "w");
    else
        yyout = fopen("wavepp_out.wpp", "w");
    if( yyout == NULL )
        perror_and_quit("fopen", EX_OSERR);
    BEGIN(PREPROCESSOR);
    yylex();
    fclose( yyin );
    fclose( yyout );
    preproc_clean();
    yylex_destroy();
    return 0;
}
