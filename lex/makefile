YACCPATH = ../grammar/
YACCNAME = wave_yacc.o
CC = gcc
IFLAGS = -I$(YACCHEAD)
CFLAGS = -lfl -ly

all : wave_lex

wave_lex.c : wave_lex.l
	lex -o $@ $<

wave_lex.o : wave_lex.c
	(cd $(YACCPATH); make)
	$(CC) $(IFLAGS) -c $<

wave_lex : wave_lex.o
	$(CC) $(CFLAGS) wave_lex.o $(YACCPATH)$(YACCNAME) -o $@

clean :
	rm wave_lex.o wave_lex.c wave_lex
