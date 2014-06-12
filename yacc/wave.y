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
#include "wave_phrase.h"
#include "wave_types.h"
wave_phrase p;

%}

%union{
    wave_int Wave_int;
    wave_float Wave_float;
    wave_bool Wave_bool;
    wave_char Wave_char;
    wave_char* Wave_string;
    void* Wave_pointer;
}

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
%token Plus Minus Min Max Star Divid Mod Equal Not_equal Upper_equal Lesser_equal Lesser Upper And Or Get
%token Atom Question_mark Exclamation_mark Read Print

%type <Wave_int> Integer_litteral
%type <Wave_float> Float_litteral
%type <Wave_bool> Boolean_litteral
%type <Wave_char> Char_litteral
%type <Wave_string> String_litteral
%type <Wave_pointer> Program Phrase Collection Atomic_collection Atomic_atom Reference Value Operator Move Binary_operator Unary_operator Specific_operator Path

%start Program

%%

Program : Phrase { wave_phrase_add_phrase (&p, $1); wave_phrase_print (&p); }
        | Phrase Program { wave_phrase_add_phrase (&p, $1); }
        ;

Phrase : Collection Dot { $$ = wave_phrase_alloc (); wave_phrase_set_collection ($$, $1); }
       ;

Collection : Atomic_collection
           | Atomic_collection Collection_reste
           ;

Collection_reste : Semicolon Atomic_collection Collection_rep_seq
                 | Parallel Atomic_collection Collection_rep_par
                 | Obrace_sequential Atomic_collection Collection_rep_seq Cbrace Integer_litteral Collection_rep_seq
                 | Obrace_sequential Atomic_collection Collection_rep_seq Cbrace Number_sign Path Collection_rep_seq
                 | Obrace_sequential Atomic_collection Collection_rep_seq Cbrace /* Cyclic */
                 | Obrace_parallel Atomic_collection Collection_rep_par Cbrace Integer_litteral Collection_rep_par
                 | Obrace_parallel Atomic_collection Collection_rep_par Cbrace Number_sign Path Collection_rep_par
                 | Obrace_parallel Atomic_collection Collection_rep_par Cbrace /* Cyclic */
                 ;

Collection_rep_seq : Obrace_sequential Atomic_collection Collection_rep_seq Cbrace Integer_litteral Collection_rep_seq
                   | Obrace_sequential Atomic_collection Collection_rep_seq Cbrace Number_sign Path Collection_rep_seq
                   | Obrace_sequential Atomic_collection Collection_rep_seq Cbrace Collection_rep_seq /* Cyclic */
                   | Semicolon Atomic_collection Collection_rep_seq
                   |
                   ;

Collection_rep_par : Obrace_parallel Atomic_collection Collection_rep_par Cbrace Integer_litteral Collection_rep_par
                   | Obrace_parallel Atomic_collection Collection_rep_par Cbrace Number_sign Path Collection_rep_par
                   | Obrace_parallel Atomic_collection Collection_rep_par Cbrace Collection_rep_par /* Cyclic */
                   | Parallel Atomic_collection Collection_rep_par
                   |
                   ;

Atomic_collection : Oparentheses Collection Cparentheses { $$ = $2; }
                  | Atomic_atom { $$ = $1; }
                  | Reference { $$ = $1; }
                  ;

Reference : At Path { $$ = $2; }
          ;

Atomic_atom : Value { $$ = $1; }
             | Operator { $$ = $1; }
             ;

Value : Integer_litteral { $$ = wave_atom_alloc (); wave_atom_set_int ($$, $1); }
      | Float_litteral { $$ = wave_atom_alloc (); wave_atom_set_float ($$, $1); }
      | Boolean_litteral { $$ = wave_atom_alloc (); wave_atom_set_bool ($$, $1); }
      | Char_litteral { $$ = wave_atom_alloc (); wave_atom_set_char ($$, $1); }
      | String_litteral { $$ = wave_atom_alloc (); wave_atom_set_string ($$, $1); }
      ;

Path : Move { $$ = $1; }
     | Move Integer_litteral {
            $$ = wave_path_alloc ();
            wave_path_set_repeat_path ($$, $1);
            wave_path_set_repeat_number ($$, $2);
        }
     | Move Star{
            $$ = wave_path_alloc ();
            wave_path_set_repeat_path ($$, $1);
            wave_path_set_repeat_type ($$, WAVE_PATH_REPEAT_INFINITE);
        }
     | Move Integer_litteral Path {
            $$ = wave_path_alloc ();
            wave_path_set_repeat_path ($$, $1);
            wave_path_set_repeat_number ($$, $2);
            wave_path_add_path ($$, $3);
        }
     | Move Star Path {
            $$ = wave_path_alloc ();
            wave_path_set_repeat_path ($$, $1);
            wave_path_set_repeat_type ($$, WAVE_PATH_REPEAT_INFINITE);
            wave_path_add_path ($$, $3);
        }
     | Move Path { $$ = $1; wave_path_add_path ($$, $2); }
     | error { fprintf(stderr, "Error on Path\n"); return 1;}
     ;

Move : Prec { $$ = wave_path_alloc (); wave_path_set_move ($$, WAVE_MOVE_PRE); }
     | Succ { $$ = wave_path_alloc (); wave_path_set_move ($$, WAVE_MOVE_SUC); }
     | Up { $$ = wave_path_alloc (); wave_path_set_move ($$, WAVE_MOVE_UP); }
     | Down { $$ = wave_path_alloc (); wave_path_set_move ($$, WAVE_MOVE_DOWN); }
     | Rewind { $$ = wave_path_alloc (); wave_path_set_move ($$, WAVE_MOVE_REWIND); }
     | Osquare_brackets Path Csquare_brackets { $$ = wave_path_alloc (); wave_path_set_part ($$, $2); }
     | Oparentheses Path Cparentheses { $$ = $2; }
     ;

Operator : Binary_operator { $$ = $1; }
         | Unary_operator { $$ = $1; }
         | Specific_operator { $$ = $1; }
         ;

Unary_operator : Unary_plus { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_PLUS); }
               | Unary_minus { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_MINUS); }
               | Increment { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_INCREMENT); }
               | Decrement { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_DECREMENT); }
               | Square_root { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_SQRT); }
               | Sin { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_SIN); }
               | Cos { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_COS); }
               | Not { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_NOT); }
               | Log { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_LOG); }
               | Exp { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_EXP); }
               | Ceil { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_CEIL); }
               | Floor { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_UNARY_FLOOR); }
               ;

Binary_operator : Plus { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_PLUS); }
                | Minus { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_MINUS); }
                | Star { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_TIMES); }
                | Divid { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_DIVIDE); }
                | Min { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_MIN); }
                | Max { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_MAX); }
                | Mod { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_MOD); }
                | Equal { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_EQUALS); }
                | Not_equal { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_DIFFERS); }
                | Upper_equal { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_GREATER_OR_EQUALS); }
                | Lesser_equal { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_LESSER_OR_EQUALS); }
                | Upper { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_GREATER); }
                | Lesser { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_LESSER); }
                | And { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_AND); }
                | Or { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_OR); }
                | Get { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_BINARY_GET); }
                ;

Specific_operator : Atom { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_SPECIFIC_ATOM); }
                  | Question_mark { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_SPECIFIC_STOP); }
                  | Exclamation_mark { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_SPECIFIC_CUT); }
                  | Read { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_SPECIFIC_READ); }
                  | Print { $$ = wave_atom_alloc (); wave_atom_set_operator ($$, WAVE_OP_SPECIFIC_PRINT); }
                  ;

%%
int main(int argc, char ** argv)
{
    wave_phrase_init (&p);
    yyparse();
}
