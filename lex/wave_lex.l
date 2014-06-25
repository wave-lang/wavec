%top{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wave/common/wave_types.h"
#include "wave/ast/wave_phrase.h"
#include "wave/generation/wave_code_generation.h"
#include "wave_yacc.h"
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
wave_int W_int;
wave_float W_float;
int lex_current_line = 1;
void incline(void);
size_t lex_nbchars = 0;
long total_chars = 0;
wave_phrase p;
void yacc_error_print();
int yyparse();

#define YY_USER_ACTION incline();
%}

Integer     [-][0-9]+|[0-9]+
Float       [0-9]+"."[0-9]+|[0-9]*"."[0-9]+
Character   "'"."'"
String      \".*\"
Boolean     True|False

%%
{Integer}                               yylval.Wave_int = wave_int_from_string(yytext); return Integer_litteral;
{Float}                                 yylval.Wave_float = wave_float_from_string(yytext); return Float_litteral;
{Character}                             yylval.Wave_char = * (yytext + 1); return Char_litteral;
{String}                                size_t length_string = strlen(yytext); yylval.Wave_string = calloc ( length_string - 1, sizeof(char) ); strncpy(yylval.Wave_string, yytext+1, length_string - 2); return String_litteral;
"True"                                  yylval.Wave_bool = true; return Boolean_litteral;
"False"                                 yylval.Wave_bool = false; return Boolean_litteral;
"."                                     return Dot;
"{||"                                   return Obrace_parallel;
"{;"                                    return Obrace_sequential;
"}"                                     return Cbrace;
"@"                                     return At;
"#"                                     return Number_sign;
"("                                     return Oparentheses;
")"                                     return Cparentheses;
"||"                                    return Parallel;
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
"["                                     return Osquare_brackets;
"]"                                     return Csquare_brackets;
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
"*"                                     return Star;
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
atom                                    return Atom;
"\n"                                    ++lex_current_line; lex_nbchars = 0;
.                                       printf("Unknown character \" %c \"\n", yytext[0]); return 0;

%%
int main(int argc, char ** argv)
{
    ++argv; --argc;
    if( argc < 1 || argc > 2 ){
        fprintf(stderr, "No input file \n");
        return EXIT_FAILURE;
    }
    yyin = fopen(argv[0], "r");
    if( yyin == NULL ){
        perror("fopen");
        return EXIT_FAILURE;
    }
    if( argc == 2 ){
        yyout = fopen(argv[1], "w");
        if( yyout == NULL ){
            fclose(yyin);
            perror("fopen");
            return EXIT_FAILURE;
        }
    }
    wave_phrase_init (&p);
    if(yyparse() == 1){
        wave_phrase_free(p._next_phrase);
        return EXIT_FAILURE;
    }
    wave_phrase_print(&p);
    wave_code_generation_generate(yyout, p._next_phrase);
    wave_phrase_free(p._next_phrase);
    fclose(yyin);
    if(argc == 2)
        fclose(yyout);
    yylex_destroy();
    return EXIT_SUCCESS;
}

void incline(void){
    lex_nbchars+=yyleng;
    total_chars+=yyleng;
}

#define NB_CHAR_ERROR_PRINT 40

void yacc_error_print(){
    char string_buf[40];
    memset(string_buf, 0, 40);
    size_t i;
    size_t error_location;
    long where_to_go = total_chars >= 20 ? (total_chars - 20) : 0;
    fprintf(stderr,"Error encountered line %d at character %d\n", lex_current_line, lex_nbchars);
    fseek(yyin, where_to_go, SEEK_SET);
    fscanf(yyin, "%40c", string_buf);
    for(i=0; i < 40 && string_buf[i] != '\0'; i++){
        if( string_buf[i] == '\n' ){
            if( i == 39 || i != 39 && (string_buf[i+1] == '\0' || string_buf[i+1] == '\n'))
                continue;
            if(i+1 > lex_nbchars){
                break;
            }
        }
        fprintf(stderr, "%c", string_buf[i]);
    }
    fprintf(stderr, "\n");
    error_location = lex_nbchars >= 20 ? 20 : lex_nbchars;
    for(i=1; i <= lex_nbchars; i++){
        if(i == error_location){
            fprintf(stderr, "^");
            break;
        }
        fprintf(stderr, " ");
    }
    fprintf(stderr, "\n");
}
