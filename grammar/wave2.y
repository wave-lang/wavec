%token Let Be Dot /* Let y Be x . */
%token Identifier /* (a-z|A-Z){(a-z|A-Z|_|0-9)} */
%token Osquare_brackets Csquare_brackets Obrace_sequential Obrace_parallel Cbrace /* [ ] {; {|| } */
%token Oparentheses Cparentheses /* ( ) */
%token Semicolon Parallel /* ; || */
%token At /* @ */
%token Integer_litteral Float_litteral Boolean_litteral String_litteral Char_litteral
%token Infinity
%token Prec Succ Up Down Rewind
%token Unary_plus Unary_minus Increment Decrement Square_root Sin Cos Not Log Exp Ceil Floor
%token Plus Minus Min Max Times Divid Mod Equal Not_equal Upper_equal Lesser_equal Lesser Upper And Or Get
%token Atom Question_mark Exclamation_mark Read Print

%%

Program : Phrase
        | Phrase Phrase
        |
        ;

Phrase : Let Identifier Be Any_expression Dot
       | Collection_expression
       ;

Any_expression : Collection_expression
               | Collection_sequential
               | Collection_parallel
               | Collection_simple
               ;

Collection_expression : Collection_sequential
                      | Collection_sequential Obrace_sequential Collection_sequential Cbrace
                      | Collection_parallel
                      | Collection_parallel Obrace_parallel Collection_parallel Cbrace
                      ;

Collection_sequential : Collection_simple
                      | Collection_simple Semicolon Collection_simple
                      | Collection_simple Obrace_sequential Collection_simple Cbrace Repetition_number
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
                  | '#' Location
                  ;

Value : Integer_litteral
      | Float_litteral
      | Boolean_litteral
      | Char_litteral
      | String_litteral
      ;

Location : Move
         | Move Number
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
