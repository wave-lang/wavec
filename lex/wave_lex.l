%top{
#include "wave_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
{String}                                return String_litteral;
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

