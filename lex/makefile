YACCPATH = ../grammar/
YACCNAME = wave_yacc.o
CC = gcc
IFLAGS = -I$(YACCPATH)
CFLAGS = -lfl -ly

all : wave_lex

wave_lex.c : wave_lex.l
	lex -o $@ $<

wave_lex.o : wave_lex.c
	(cd $(YACCPATH); make)
	$(CC) $(IFLAGS) -c $<

wave_lex : wave_lex.o
	$(CC) -o $@ $(YACCPATH)$(YACCNAME) $< $(CFLAGS)

clean :
	@(cd $(YACCPATH); make clean 1>/dev/null 2>&1; echo $(YACCPATH) Cleaned.)
	@rm wave_lex.o wave_lex.c wave_lex 2>/dev/null; echo Directory cleaned.
