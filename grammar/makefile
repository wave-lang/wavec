CC = gcc
IFLAGS =

all : wave_yacc.o

wave_yacc.o : wave_yacc.c
	$(CC) $(IFLAGS) -c $<

wave_yacc.c : wave2.y
	yacc $< -d -o $@

wave_yacc_debug.c : wave2.y
	yacc $< -v -o $@

clean:
	rm wave_yacc.c wave_yacc.o wave_yacc_debug.c wave_yacc.h wave_yacc_debug.output
