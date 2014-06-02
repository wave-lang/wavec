%{
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
static unsigned int nb_rows = 1;
static unsigned int let_row = 1;
static const char* help = "This program takes an input wave source file and process it to\n\
remove macro definitions and comments and place it in the file\n\
pars_out.wave or in the name pointed by the second argument if given.\n";

%}
%x Definition Naming Be Macro Comment
%%

<Definition,Naming,Be,Macro,INITIAL>"\n"    ++nb_rows;
"Let"                                       printf("Let it be ligne %u\n", nb_rows); let_row = nb_rows; BEGIN(Naming);
<Naming>[a-zA-Z][a-zA-Z0-9\_]*              printf("Name found : %s\n", yytext); BEGIN(Be);
<Be>" "*be" "*                              printf("Be found"); BEGIN(Macro);
<Be>"Let"                                   fprintf(stderr, "Error !\nFound a \"Let\", line %u, after a \"Let\", line %u, without a \"be\" between them.", nb_rows, let_row); exit(EXIT_FAILURE);
<Be><<EOF>>                                 printf("Error, found an \"Let\" line %u but no \"be\" detected before the end of file\n", let_row); exit(EXIT_FAILURE);
<Macro>[^"."]*                              printf("Expression :\n%s\n",yytext);
<Macro>"."                                  BEGIN(INITIAL);

%%
static inline void perror_and_quit(const char* message){
    perror(message);
    exit(errno);
}

int main(int argc, char** argv){
    --argc; ++argv;
    if( argc > 2 || argc < 1 ){
        fprintf(stderr, "%s", help);
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
    yylex();
    fclose( yyin );
    fclose( yyout );
    return EXIT_SUCCESS;
}
