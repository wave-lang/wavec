%{/*
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
%}

%token Dot /* "." */
%token Osquare_brackets Csquare_brackets Obrace_sequential Obrace_parallel Cbrace /* [ ] { {; {|| } */
%token Oparentheses Cparentheses /* ( ) */
%token Semicolon Parallel /* ; || */
%token At /* @ */
%token Number_sign /* # */
%token Integer_litteral Float_litteral Boolean_litteral String_litteral Char_litteral
%token Infinity
%token Prec Succ Up Down Rewind
%token Unary_plus Unary_minus Increment Decrement Square_root Sin Cos Not Log Exp Ceil Floor
%token Plus Minus Min Max Times Divid Mod Equal Not_equal Upper_equal Lesser_equal Lesser Upper And Or Get
%token Atom Question_mark Exclamation_mark Read Print
%start Program

%%

Program : Phrase
        | Phrase Phrase
        |
        ;

Phrase : Collection_expression Dot
       ;

Collection_expression : Collection_simple
                      | Collection_sequential
                      | Collection_sequential Obrace_sequential Collection_sequential Cbrace
                      | Collection_parallel
                      | Collection_parallel Obrace_parallel Collection_parallel Cbrace
                      ;

Collection_sequential : Collection_simple Semicolon Collection_simple
                      | Collection_simple Obrace_sequential Collection_sequential Cbrace Repetition_number
                      ;

Collection_parallel : Collection_simple Parallel Collection_simple
                    | Collection_simple Obrace_parallel Collection_sequential Cbrace Repetition_number
                    ;

Collection_simple : Oparentheses Collection_expression Cparentheses
                  | Value
                  | Operator
                  | At Location
                  ;

Repetition_number : Integer_litteral
                  | Number_sign Location
                  ;

Value : Integer_litteral
      | Float_litteral
      | Boolean_litteral
      | Char_litteral
      | String_litteral
      ;

Location : Move Number
         | Move
         | Move Number Location
         | Move Location
         ;

Number : Infinity
      | Integer_litteral
      ;

Move : Prec
     | Succ
     | Up
     | Down
     | Rewind
     | Oparentheses Location Cparentheses
     | Osquare_brackets Location Csquare_brackets
     ;

Operator : Binary_operator
         | Unary_operator
         | Specific_operator
         ;

Unary_operator : Unary_plus
               | Unary_minus
               | Increment
               | Decrement
               | Square_root
               | Sin
               | Cos
               | Not
               | Log
               | Exp
               | Ceil
               | Floor
               ;

Binary_operator : Plus
                | Minus
                | Times
                | Divid
                | Min
                | Max
                | Mod
                | Equal
                | Not_equal
                | Upper_equal
                | Lesser_equal
                | Upper
                | Lesser
                | And
                | Or
                | Get
                ;

Specific_operator : Atom
                  | Question_mark
                  | Exclamation_mark
                  | Read
                  | Print
                  ;
