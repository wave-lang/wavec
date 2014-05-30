%token Identifier
%token Operator
%token Int Bool String Char Float
%token Let Be
%token True False
%token Predecessor Up Succesor Down Rewind
%token Not And Or Min Max Print Read Sqrt Cos Code Mod Chr
%token Get Sin Log Exp Ceil Floor
%token At Dot
%token Sequential Parallel Iter
%token Oparent Cparent Obracket Cbracket Obrace_parallel Obrace_sequential Cbrace
%token Opt
%token Times_int
%token End

%start Phrase_eos

%%

Preproc_eos : Preproc_item End
            ;

Preproc_item : Preproc_phrase Dot
             ;

Preproc_token : Float
              | Int
              | Char
              | String
              | Bool
              | Rewind
              | Succesor
              | Predecessor
              | Up
              | Down
              | Operator
              | Identifier
              | At
              | Oparent
              | Cparent
              | Sequential
              | Parallel
              | Iter
              | Obracket
              | Cbracket
              | Obrace_parallel
              | Obrace_sequential
              | Cbrace
              ;

Preproc_phrase : Let Identifier Be Preproc_token
               | Preproc_token
               ;

Collection_eos : Collection End
               ;

Phrase_eos : Phrase End
           ;

Phrase : Collection Dot
       ;

Collection : Atomic_collection Collection_reste
           ;

Collection_reste : Sequential Collection_rep_sequential
           | Parallel Atomic_collection Collection_rep_parallel
           | Atomic_collection Collection_rep_sequential Times Collection_rep_sequential
           | Obrace_parallel Atomic_collection Collection_rep_parallel Cbrace Opt Collection_rep_parallel
           |
           ;

Collection_rep_sequential : Obrace_sequential Atomic_collection Collection_rep_sequential Cbrace Opt
                          | Sequential Atomic_collection
                          |
                          ;

Collection_rep_parallel : Obrace_parallel Atomic_collection Collection_rep_parallel Cbrace Opt
                        | Parallel Atomic_collection
                        |
                        ;

Atomic_collection : Oparent Collection Cparent
                  | Atom
                  | Reference
                  ;

Atom : Float
     | Int
     | Bool
     | String
     | Char
     | Operator
     ;

Reference : At Elem_path
          ;

Elem_path : Direction Opt Nb_times
     ;

Times : Times_int
      | Iter Elem_path
      ;

Nb_times :
         | Operator
         ;

Direction : Obracket Elem_path Cbracket
          | Oparent Elem_path Cparent
          | Rewind
          | Predecessor
          | Succesor
          | Up
          | Down
          ;
